#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QStandardPaths>
#include <QFileDialog>
#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qApp->installEventFilter(this);

    setupTestChart();
    setupTrainChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QChart* MainWindow::createChart(const QString& title)
{
    auto chart = new QChart();
    chart->createDefaultAxes();
    chart->setTitle(title);
    return chart;
}

QChartView* MainWindow::createChartView(QChart* chart)
{
    auto chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    return chartView;
}

void MainWindow::setupTestChart()
{
    auto testChart = createChart("Test Responce Delay");
    testChartView = createChartView(testChart);
    neutralTestSeries = new QLineSeries();
    salientTestSeries = new QLineSeries();
    setupSeriesColors(neutralTestSeries, salientTestSeries);
    setupChartViewSeries(testChartView, neutralTestSeries, salientTestSeries);
    ui->testChartVerticalLayout->addWidget(testChartView);
}

void MainWindow::setupTrainChart()
{
    auto trainChart = createChart("Train Responce Delay");
    trainChartView = createChartView(trainChart);
    neutralTrainSeries = new QLineSeries();
    salientTrainSeries = new QLineSeries();
    setupSeriesColors(neutralTrainSeries, salientTrainSeries);
    setupChartViewSeries(trainChartView, neutralTrainSeries, salientTrainSeries);
    ui->trainChartVerticalLayout->addWidget(trainChartView);
}

void MainWindow::addDataToChart(QChartView* view,
                                QLineSeries* neutral,
                                QLineSeries* salient,
                                const QList<ProbeResult>& results)
{
    removeSeriesFromChart(view, neutral, salient);
    clearChartSeries(neutral, salient);
    addResultsToSeries(results, neutral, salient);
    addSeriesToChart(view, neutral, salient);
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    Q_UNUSED(object)
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Left) {
            prober->stop("<");
            prober->start();
            return true;
        } else if (keyEvent->key() == Qt::Key_Right) {
            prober->stop(">");
            prober->start();
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

QString MainWindow::askDir()
{
    QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    home, QFileDialog::ShowDirsOnly);
    return dir;
}

QString MainWindow::askFile(const QString& name)
{
    QString home = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    home + "/" + name,
                                                    tr("CSV (*.csv)"));
    return filename;
}

void MainWindow::on_setSalientFolderToolButton_clicked()
{
    QString dir = askDir();
    if (!dir.isNull())
        ui->salientLineEdit->setText(dir);
}

void MainWindow::on_setNeutralFolderToolButton_clicked()
{
    QString dir = askDir();
    if (!dir.isNull())
        ui->neutralLineEdit->setText(dir);
}

void MainWindow::setupProber()
{
    prober = make_unique<DotProber>();
    prober->setWidget(ui->probeWidget);
    prober->setDelay(ui->delaySpinBox->value());
    prober->setDirectoryWithNeutralStimuli(ui->neutralLineEdit->text());
    prober->setDirectoryWithSalientStimuli(ui->salientLineEdit->text());
    if (ui->verticalCheckBox->isChecked()) {
        prober->setLayoutMode(LayoutMode::Vertical);
    } else {
        prober->setLayoutMode(LayoutMode::Horizontal);
    }
}

void MainWindow::clearChartSeries(QLineSeries* neutral, QLineSeries* salient)
{
    neutral->clear();
    salient->clear();
}

void MainWindow::removeSeriesFromChart(QChartView* view, QLineSeries* neutral, QLineSeries* salient)
{
    view->chart()->removeSeries(neutral);
    view->chart()->removeSeries(salient);
}

void MainWindow::addSeriesToChart(QChartView* view, QLineSeries* neutral, QLineSeries* salient)
{
    view->chart()->addSeries(neutral);
    view->chart()->addSeries(salient);
}

void MainWindow::addResultsToSeries(const QList<ProbeResult>& results, QLineSeries* neutral, QLineSeries* salient)
{
    for(int i = 0; i < results.size(); i++) {
        auto result = results.at(i);
        if (result.getNeutral()) {
            neutral->append(i, result.getDelay());
        } else {
            salient->append(i, result.getDelay());
        }
    }
}

QPair<double, double> MainWindow::neutralAndSalientAverageDelay(const QList<ProbeResult>& results)
{
    int neutralCount = 0;
    int salientCount = 0;
    double avgNeutral = 0.0;
    double avgSalient = 0.0;
    for(int i = 0; i < results.size(); i++) {
        auto result = results.at(i);
        if (result.getNeutral()) {
            neutralCount += 1;
            avgNeutral += result.getDelay();
        } else {
            salientCount += 1;
            avgSalient += result.getDelay();
        }
    }
    if (neutralCount > 0)
        avgNeutral /= neutralCount;
    if (salientCount > 0)
        avgSalient /= salientCount;
    return qMakePair(avgNeutral, avgSalient);
}

void MainWindow::showAverage(const QList<ProbeResult>& results,
                             QLabel* neutralLabel,
                             QLabel* salientLabel)
{
    QPair<double, double> avgs = neutralAndSalientAverageDelay(results);
    neutralLabel->setText(QString::number(avgs.first));
    salientLabel->setText(QString::number(avgs.second));
}

void MainWindow::on_startTestPushButton_clicked()
{
    setupProber();
    connect(prober.get(), &DotProber::resultReady,
            this, &MainWindow::addTestData);
    prober->setTraining(false);
    prober->start();
}

void MainWindow::on_startTrainPushButton_clicked()
{
    setupProber();
    connect(prober.get(), &DotProber::resultReady,
            this, &MainWindow::addTrainData);
    prober->setTraining(true);
    prober->start();
}

void MainWindow::on_saveTestDataPushButton_clicked()
{
    QString filename = askFile("test_results.csv");
    saveToCSV(testResults, filename);
}

void MainWindow::on_clearTestDataPushButton_clicked()
{
    testResults.clear();
    removeSeriesFromChart(testChartView, neutralTestSeries,
                          salientTestSeries);
    clearChartSeries(neutralTestSeries, salientTestSeries);
    ui->averageNeutralDelayLabel->setText("0");
    ui->averageSalientDelayLabel->setText("0");
}

void MainWindow::on_saveTrainDataPushButton_clicked()
{
    QString filename = askFile("train_results.csv");
    saveToCSV(trainResults, filename);
}

void MainWindow::on_clearTrainDataPushButton_clicked()
{
    trainResults.clear();
    removeSeriesFromChart(trainChartView, neutralTrainSeries,
                          salientTrainSeries);
    clearChartSeries(neutralTrainSeries, salientTrainSeries);
    ui->averageNeutralTrainDelayLabel->setText("0");
    ui->averageSalientTrainDelayLabel->setText("0");
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 2) {
        addDataToChart(testChartView, neutralTestSeries,
                       salientTestSeries, testResults);
        showAverage(testResults, ui->averageNeutralDelayLabel,
                    ui->averageSalientDelayLabel);
    }
    if (index == 3) {
        addDataToChart(trainChartView, neutralTrainSeries,
                       salientTrainSeries, trainResults);
        showAverage(trainResults, ui->averageNeutralTrainDelayLabel,
                    ui->averageSalientTrainDelayLabel);
    }
}

void MainWindow::addTestData(const ProbeResult& result)
{
    testResults.append(result);
}

void MainWindow::addTrainData(const ProbeResult& result)
{
    trainResults.append(result);
}

void MainWindow::saveToCSV(const QList<ProbeResult>& results, const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for(auto& result : results) {
        out << result.getNeutral() << ", "
            << result.getDelay() << ", "
            << result.getTimestamp().toString() << "\n";
    }
}

QList<ProbeResult> MainWindow::loadFromCSV(const QString& filename)
{
    QList<ProbeResult> results;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return results;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        //TODO
    }
    return results;
}

void MainWindow::setupSeriesColors(QLineSeries* neutral, QLineSeries* salient)
{
    neutral->setColor(Qt::green);
    salient->setColor(Qt::red);
}

void MainWindow::setupChartViewSeries(QChartView* view, QLineSeries* neutral,
                                      QLineSeries* salient)
{
    view->chart()->addSeries(neutral);
    view->chart()->addSeries(salient);
}
