/*
* Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
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
