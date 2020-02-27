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
    explicit ButtonWidget(QString strIcon, QString strHoverIcon);

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QLabel*         m_ToolButton;
    QSvgRenderer*   m_pTakeinSvgRender;
    QPixmap*        m_pTakeinPixmap;
    QPixmap*        m_pTakeinPixmap80percent;

    bool            m_bTakeInFlag;
    QString         m_strIcon;
    QString         m_strHoverIcon;

signals:
    void            Sig_clicked();

public slots:

};

#endif // BUTTONWIDGET_H
