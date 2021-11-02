#ifndef PREVIEWIMAGEWIDGET_H
#define PREVIEWIMAGEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
class previewImageWidget : public QWidget
{
    Q_OBJECT
public:
    previewImageWidget(QPixmap *pixmap, QWidget *parent = nullptr);
    QLabel *m_pLabel;
    QVBoxLayout *m_pVlaout;
};

#endif // PREVIEWIMAGEWIDGET_H
