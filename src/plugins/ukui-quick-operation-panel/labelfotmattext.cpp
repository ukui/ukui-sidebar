#include "labelfotmattext.h"
#include <QDebug>
LabelFotmatText::LabelFotmatText()
{

}

/* 设置...字样 */
QString LabelFotmatText::SetFormatBody(QString text, QLabel *CopyDataLabal)
{
    QFontMetrics fontMetrics(CopyDataLabal->font());
    int LableWidth = CopyDataLabal->width();
    int fontSize = fontMetrics.width(text);
    m_pLabel = CopyDataLabal;
    m_pFormatBody = text;
    if(fontSize > (LableWidth)) {
        //说明只存在一行，在最后面加...就行
        QString format = m_pFormatBody + "aa";
        format = fontMetrics.elidedText(format, Qt::ElideRight, LableWidth - 10);
        m_bTooltips = true;
        return format;
    }
    setWidgetFont();
    return m_pFormatBody;
}

/* 监听gsetting，修改所有的字体 */
void LabelFotmatText::setWidgetFont()
{
    const QByteArray id("org.ukui.style");
        QGSettings * fontSetting = new QGSettings(id);
        connect(fontSetting, &QGSettings::changed,[=](QString key){
            if ("systemFont" == key || "systemFontSize" ==key) {
                initLabelText();
            }
        });
}

void LabelFotmatText::initLabelText()
{
    if (m_bTooltips) {
        m_pLabel->setToolTip(m_pFormatBody);
    }
    m_pLabel->setText(this->SetFormatBody(m_pFormatBody, m_pLabel));
}
