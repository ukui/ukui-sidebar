#include "clipboardwidgetentry.h"

ClipboardWidgetEntry::ClipboardWidgetEntry(QWidget *parent)
{
    Q_UNUSED(parent);
    this->setObjectName("WidgetEntry");
    QIcon EditIcon;
    EditIcon.addFile(EDIT_SVG_PATH);
    QIcon PopIcon;
    PopIcon.addFile(COPY_SVG_PATH);
    QIcon RemoveIcon;
    RemoveIcon.addFile(REMOVE_SVG_PATH);
    m_pPopButton     = new QPushButton();
    m_pPopButton->setFixedSize(34, 34);
    m_pPopButton->setIcon(PopIcon);
    m_pEditButon     = new QPushButton();
    m_pEditButon->setFixedSize(34, 34);
    m_pEditButon->setIcon(EditIcon);
    m_pRemoveButton  = new QPushButton();
    m_pRemoveButton->setFixedSize(34, 34);
    m_pRemoveButton->setIcon(RemoveIcon);
    m_pCopyDataLabal = new QLabel();
    m_pCopyDataLabal->setFixedSize(200, 34);
    m_pCopyDataLabal->setObjectName("EntryLable");
    m_pHLayout       = new QHBoxLayout();
    m_pHLayout->addWidget(m_pCopyDataLabal);
    m_pHLayout->addWidget(m_pPopButton);
    m_pHLayout->setSpacing(1);
    m_pHLayout->addWidget(m_pEditButon);
    m_pHLayout->addWidget(m_pRemoveButton);
    this->setLayout(m_pHLayout);
}
