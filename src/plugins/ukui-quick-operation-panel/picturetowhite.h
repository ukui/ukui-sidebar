#ifndef PICTURETOWHITE_H
#define PICTURETOWHITE_H

#include <QObject>
#include <QGSettings>
#include <QString>
#include <QVariant>
#include <QPixmap>

#define ORG_UKUI_STYLE            "org.ukui.style"
#define STYLE_NAME                "styleName"
#define STYLE_NAME_KEY_DARK       "ukui-dark"
#define STYLE_NAME_KEY_DEFAULT    "ukui-default"
//#define STYLE_NAME_KEY_BLACK       "ukui-black"
#define STYLE_NAME_KEY_LIGHT       "ukui-light"
#define STYLE_NAME_KEY_WHITE       "ukui-white"
#define TRAY_ICON_COLOR_LOGHT      255
#define TRAY_ICON_COLOR_DRAK       0

class PictureToWhite : public QObject
{
    Q_OBJECT
public:
    explicit PictureToWhite(QObject *parent = nullptr);
    void initGsettingValue();
    QPixmap drawSymbolicColoredPixmap(const QPixmap &source);

public:
    QGSettings  *m_pgsettings;
    int         tray_icon_color;

};

#endif // PICTURETOWHITE_H
