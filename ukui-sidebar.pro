#! [0]
DEFINES += PLATFORM_TYPE
TEMPLATE    =   subdirs
SUBDIRS	    =   ./src/ukui-sidebar-core.pro \
                ./src/plugins/ukui-notification-plugin/ukui-notification-plugin.pro \
                ./src/plugins/ukui-clipboard-plugins/ukui-clipboard-plugin.pro \
                ./src/plugins/ukui-clock/ukui-clock.pro \
                ./src/plugins/ukui-notebook/ukui-notebook.pro

greaterThan(QT_MINOR_VERSION, 7): SUBDIRS     +=  ./src/plugins/ukui-feedback/ukui-feedback.pro
