#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DotProber.h"

#include <QLabel>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
using namespace QtCharts;

#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::move;

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    bool eventFilter(QObject* object, QEvent* event);

public slots:
    void on_setSalientFolderToolButton_clicked();
    void on_setNeutralFolderToolButton_clicked();

    void on_startTestPushButton_clicked();
    void on_startTrainPushButton_clicked();

    void on_saveTestDataPushButton_clicked();
    void on_clearTestDataPushButton_clicked();

    void on_saveTrainDataPushButton_clicked();
    void on_clearTrainDataPushButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void addTestData(const ProbeResult& result);
    void addTrainData(const ProbeResult& result);

private:
    QChart* createChart(const QString& title);
    QChartView* createChartView(QChart* chart);
    void setupSeriesColors(QLineSeries* neutral, QLineSeries* salient);
    void setupChartViewSeries(QChartView* view, QLineSeries* neutral,
                              QLineSeries* salient);
    void setupTestChart();
    void setupTrainChart();
    void addDataToChart(QChartView* view, QLineSeries* neutral,
                          QLineSeries* salient, const QList<ProbeResult>& results);
    QString askDir();
    QString askFile(const QString& name);
    void setupProber();
    void clearChartSeries(QLineSeries* neutral, QLineSeries* salient);
    void removeSeriesFromChart(QChartView* view, QLineSeries* neutral,
                               QLineSeries* salient);
    void addSeriesToChart(QChartView* view, QLineSeries* neutral,
                          QLineSeries* salient);
    void addResultsToSeries(const QList<ProbeResult>& results,
                            QLineSeries* neutral, QLineSeries* salient);
    QPair<double, double> neutralAndSalientAverageDelay(const QList<ProbeResult>& results);
    void showAverage(const QList<ProbeResult>& results, QLabel* neutralLabel, QLabel* salientLabel);
    void saveToCSV(const QList<ProbeResult>& results, const QString& filename);
    QList<ProbeResult> loadFromCSV(const QString& filename);

    unique_ptr<DotProber> prober;

    QChartView* testChartView;
    QLineSeries* neutralTestSeries;
    QLineSeries* salientTestSeries;

    QChartView* trainChartView;
    QLineSeries* neutralTrainSeries;
    QLineSeries* salientTrainSeries;

    QList<ProbeResult> testResults;
    QList<ProbeResult> trainResults;

    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
