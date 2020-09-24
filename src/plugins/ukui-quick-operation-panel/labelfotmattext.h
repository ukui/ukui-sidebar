#ifndef LABELFOTMATTEXT_H
#define LABELFOTMATTEXT_H

#include <QObject>
#include <QFontMetrics>
#include <QLabel>

class LabelFotmatText
{
public:
    LabelFotmatText();
    QString SetFormatBody(QString text, QLabel *CopyDataLabal);
    bool m_bTooltips = false;
};

#endif // LABELFOTMATTEXT_H
