#! [0]
TEMPLATE    =   subdirs

TRANSLATIONS += \
    src/Sidebar_zh_CN.ts \
    src/Sidebar_tr.ts \
    src/bo.ts
    
SUBDIRS	    =   ./src/ukui-sidebar-core.pro \
                ./src/plugins/notification_plugin/notification_plugin.pro \
                ./src/plugins/clipboardPlugin/clipboardPlugin.pro \
                ./src/plugins/Clock_deamon/Clock.pro \
                ./src/plugins/feedback/feedback.pro \
                ./src/plugins/ukui_notebook/ukui_notebook.pro
