#include "previewimagewidget.h"

previewImageWidget::previewImageWidget(QPixmap *pixmap, QWidget *parent)
{
    Q_UNUSED(parent);
    m_pLabel = new QLabel();
    m_pLabel->setFixedSize(260, 130);
    int width  = m_pLabel->width();
    int height = m_pLabel->height();
    QPixmap fitpixmap = (*pixmap).scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    m_pLabel->setPixmap(fitpixmap);
    m_pVlaout = new QVBoxLayout();
    this->setContentsMargins(0, 0, 0, 0);
    m_pVlaout->setContentsMargins(0, 0, 0, 0);
    m_pVlaout->addWidget(m_pLabel);
    this->setLayout(m_pVlaout);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);
}
