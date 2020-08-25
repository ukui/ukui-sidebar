#! [0]
DEFINES += PLATFORM_TYPE
TEMPLATE    =   subdirs
SUBDIRS	    =   ./src/ukui-sidebar-core.pro \
                ./src/plugins/ukui-sidebar-notification/ukui-sidebar-notification.pro \
#                ./src/plugins/ukui-sidebar-clipboard/ukui-sidebar-clipboard.pro \
                ./src/plugins/ukui-clock/ukui-clock.pro \
                ./src/plugins/ukui-notebook/ukui-notebook.pro \
                ./src/plugins/ukui-quick-operation-panel/ukui-quick-operation-panel.pro

greaterThan(QT_MINOR_VERSION, 7): SUBDIRS     +=  ./src/plugins/ukui-feedback/ukui-feedback.pro
