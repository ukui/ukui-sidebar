# ukui-sidebar
The sidebar mainly consists of two parts: notification center and cutting board. It starts from the start-up and is placed in the tray bar in the form of a tray. After clicking, it can pop up dynamically from the right side of the screen.

  + The notification center can display the pop-up messages sent by each application to mate notification teamon in a list form. Unimportant information can be stored in the storage box for viewing. At the same time, it can call the control panel directly.


  + The main function of the clipboard is to save the latest cutting information, and display it under the sidebar in the form of a list. At the same time, it can also put the previous cutting information at the top, so that it can be pasted directly. In addition, it can record the cut text information as well as the URL.

The ukui-sidebar is a shortcut tool on the right side of the screen for UKUI.

# How to test notification-center
`notify-send -a wechat -i "/home/ccn/heart.png" Summary Body`

# How to report bugs
Bugs should be reported to the UKUI bug tracking system:

	https://github.com/ukui/ukui-sidebar/issues

You will need to create an account for yourself.

Please read the HACKING file for information on where to send changes or
bugfixes for this package.

# How to build
## Preparation
You can build pre-depends with such command:

`sudo apt install libglib2.0-dev qtbase5-dev libqt5svg5-dev qttools5-dev-tools`

Note: build-depends references the paragraph in debian/control.

## Build from source and test

> git clone https://github.com/ukui/ukui-sidebar

> cd ukui-sidebar && mkdir build && cd build

> qmake .. && make

> sudo make install

Note: If you want to run ukui-sidebar, you need to make some changes in the code after build.
  + Find `libnotification_plugin.so` in your build path like `/home/XX/ukui-sidebar/build/src/plugins/notification_plugins`. Then set this path as pluginDir in file widget.cpp fuction `bool Widget::loadNotificationPlugin()`.
  
  + Find `libclipboardPlugin.so` in your build path like `/home/XX/ukui-sidebar/build/src/plugins/sidebar_pushbutton_plugins`. Then set this path as pluginDir in file pluginmanage.cpp fuction `PluginManager::PluginManager(QObject *parent) : QObject(parent)`.