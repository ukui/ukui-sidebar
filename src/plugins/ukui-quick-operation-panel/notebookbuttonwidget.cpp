#include "notebookbuttonwidget.h"

notebookButtonWidget::notebookButtonWidget(QWidget *parent) : QWidget(parent)
{
    initMemberVariables();
    initLayout();
}

void notebookButtonWidget::initMemberVariables()
{
    m_pButtonWidget = new QWidget();
    m_pButtonWidget->setFixedSize(56, 56);

    m_pNoteButton = new QPushButton();
    connect(m_pNoteButton, &switchButton::clicked, this, &notebookButtonWidget::NoteButtonClickSlots);
    m_pNoteButton->setIcon(QIcon::fromTheme(KYLIN_BLUETOOTH_NORMAL_NAME, QIcon(KYLIN_BLUETOOTH_NORMAL_PATH)));
    m_pNoteButton->setFixedSize(56, 56);
    m_pNoteButton->setIconSize(QSize(16, 16));

    m_pDeleteButton = new QPushButton();
    m_pDeleteButton->setFixedSize(20, 20);
    m_pDeleteButton->setIcon(QIcon(KYLIN_DELETE_ICONPATH));
    m_pDeleteButton->setIconSize(QSize(12, 12));

    m_pNoteLabel  = new QLabel();
    m_pNoteLabel->setText(QObject::tr("NoteBook"));
    m_pNoteLabel->setAlignment(Qt::AlignHCenter);

    m_pVboxButtonLayout = new QVBoxLayout();
    m_pVboxButtonLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxButtonLayout->setSpacing(0);

    m_pVboxLayout       = new QVBoxLayout();
    m_pVboxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVboxLayout->setSpacing(0);

    m_pStyleNormal = new customstyle_switchNormalStatus("ukui-default");
    m_pNoteButton->setStyle(m_pStyleNormal);

    this->setFixedSize(63, 78);
    this->setContentsMargins(0, 0, 0, 0);
}

void notebookButtonWidget::initLayout()
{
    m_pVboxButtonLayout->addWidget(m_pNoteButton);
    m_pButtonWidget->setLayout(m_pVboxButtonLayout);

    m_pVboxLayout->addWidget(m_pButtonWidget, 0, Qt::AlignCenter);
    m_pVboxLayout->addItem(new QSpacerItem(5, 4));
    m_pVboxLayout->addWidget(m_pNoteLabel);
    this->setLayout(m_pVboxLayout);
    m_pDeleteButton->setParent(this);
    m_pDeleteButton->move(43, 0);
    m_pDeleteButton->setVisible(false);
    return;
}

void notebookButtonWidget::NoteButtonClickSlots()
{
    QProcess p(0);
    p.startDetached("ukui-notebook");
    p.waitForStarted();
    return;
}
