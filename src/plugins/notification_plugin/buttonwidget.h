#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include <QWidget>
#include <QLabel>


class SingleMsg;
class QSvgRenderer;

class ButtonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonWidget(QString strIcon, QString strHoverIcon, QString strPressIcon);

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QLabel*         m_ToolButton;
    QSvgRenderer*   m_pTakeinSvgRender;
    QPixmap*        m_pTakeinPixmap;                //收纳默认或悬停时的像素
    QPixmap*        m_pTakeinPressPixmap;           //收纳点击时的像素

    bool            m_bTakeInFlag;
    QString         m_strIcon;
    QString         m_strHoverIcon;
    QString         m_strPressIcon;

signals:
    void            Sig_clicked();

public slots:

};

#endif // BUTTONWIDGET_H
