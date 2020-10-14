#ifndef LABELFOTMATTEXT_H
#define LABELFOTMATTEXT_H

#include <QObject>
#include <QFontMetrics>
#include <QLabel>
#include <QGSettings>

class LabelFotmatText : public QObject
{
    Q_OBJECT
public:
    LabelFotmatText();
    QString SetFormatBody(QString text, QLabel *CopyDataLabal);
    void    setWidgetFont();
    void    initLabelText();
    bool    m_bTooltips = false;
    QLabel  *m_pLabel;
    QString m_pFormatBody;
};

#endif // LABELFOTMATTEXT_H
