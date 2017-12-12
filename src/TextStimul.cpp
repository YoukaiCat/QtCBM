#include "TextStimul.h"

TextStimul::TextStimul(QString value)
    : text(value)
{
    text.setAlignment(Qt::AlignCenter);
    stack.addWidget(&text);
}

TextStimul::TextStimul(QString value, bool neutral)
    : Stimul(neutral),
      text(value)
{
    text.setAlignment(Qt::AlignCenter);
    stack.addWidget(&text);
}

QString TextStimul::getText() const
{
    return text.text();
}

void TextStimul::setText(const QString& value)
{
    text.setText(value);
}

QStackedWidget* TextStimul::getWidget()
{
    return &stack;
}

void TextStimul::replaceWith(QWidget* widget)
{
    stack.addWidget(widget);
    stack.setCurrentWidget(widget);
}

void TextStimul::hide()
{
    text.clear();
}
