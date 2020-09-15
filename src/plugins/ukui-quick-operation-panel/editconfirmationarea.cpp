#include "editconfirmationarea.h"

EditConfirmationArea::EditConfirmationArea(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void EditConfirmationArea::initMemberVariables()
{
    m_pAddButton = new QPushButton();
    m_pAddButton->setIcon(QIcon::fromTheme("aaaa", QIcon(":/image/fold-normal.svg")));
    m_pAddButton->setText(QObject::tr("append"));
    m_pAddButton->setFixedSize(96, 32);

    m_pCompleteAreaButton = new QPushButton(QObject::tr("Complete"));
    m_pCompleteAreaButton->setFixedSize(96, 32);

    m_pHboxAreaLayout = new QHBoxLayout();
    m_pHboxAreaLayout->setContentsMargins(0, 0, 0, 0);
    m_pHboxAreaLayout->setSpacing(0);
    this->setContentsMargins(0, 0, 0, 0);
    return;
}

void EditConfirmationArea::initLayout()
{
    m_pHboxAreaLayout->addItem(new QSpacerItem(92, 10));
    m_pHboxAreaLayout->addWidget(m_pAddButton);
    m_pHboxAreaLayout->addItem(new QSpacerItem(16, 10));
    m_pHboxAreaLayout->addWidget(m_pCompleteAreaButton);
    m_pHboxAreaLayout->addItem(new QSpacerItem(92, 10));
    this->setLayout(m_pHboxAreaLayout);
}
