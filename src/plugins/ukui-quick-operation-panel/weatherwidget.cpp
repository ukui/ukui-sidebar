#include "weatherwidget.h"

weatherWidget::weatherWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLabelData();
    initLayout();
}

void weatherWidget::initMemberVariables()
{
    m_pWeatherIconLabel = new QLabel();
    m_pWeatherIconLabel->setFixedSize(16, 16);

    m_pAreaLabel = new QLabel();
    m_pAreaLabel->setFixedHeight(18);

    QFont font = m_pAreaLabel->font();
    font.setPixelSize(12);
    m_pAreaLabel->setFont(font);

    QPalette palette = m_pAreaLabel->palette();
    QColor color(89, 89, 89, 255);
    palette.setBrush(QPalette::Text, color);
    m_pAreaLabel->setPalette(palette);

    m_pMainHLayout = new QHBoxLayout();
    m_pMainHLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainHLayout->setSpacing(0);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void weatherWidget::initLabelData()
{
    QPixmap pixmap = QIcon::fromTheme("indicator-china-weather").pixmap(QSize(m_pWeatherIconLabel->size()));
    m_pWeatherIconLabel->setPixmap(pixmap);
    QString WeatherInfo = QStringLiteral("%1·%2 %3°").arg("湖南").arg("长沙").arg("26");
    m_pAreaLabel->setText(WeatherInfo);
    QPalette palette;
    palette.setBrush(QPalette::WindowText, Qt::black);
    m_pAreaLabel->setPalette(palette);
    this->update();

    return;
}

void weatherWidget::initLayout()
{
    m_pMainHLayout->addItem(new QSpacerItem(32, 10));
    m_pMainHLayout->addWidget(m_pWeatherIconLabel);
    m_pMainHLayout->addItem(new QSpacerItem(2, 0));
    m_pMainHLayout->addWidget(m_pAreaLabel);
    m_pMainHLayout->addItem(new QSpacerItem(243, 10, QSizePolicy::Expanding));
    this->setLayout(m_pMainHLayout);
    return;
}
