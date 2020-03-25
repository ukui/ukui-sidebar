#ifndef UKUI_NOTEBOOK_H
#define UKUI_NOTEBOOK_H

#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QFontDialog>
#include <QDateTime>
#include <QPainter>
#include <QPrinter>
#include <QMouseEvent>
#include <QTextEdit>
#include <QStyleOption>
#include <QDesktopWidget>
namespace Ui {
class ukui_NoteBook;
}

class ukui_NoteBook : public QWidget
{
    Q_OBJECT

public:
    explicit ukui_NoteBook(QWidget *parent = nullptr);
    ~ukui_NoteBook();

signals:
    void listItemClicked(int);
    void fileSaved(QString);

public:
    QString fileName;//文件路径
    Ui::ukui_NoteBook *ui;
private slots:
    //新建文件
    void newFileSlot();
    //退出软件
    void exitFileSlot();
    //插入时间/日期
    void insertTimeDateSlot();
    //新建窗口
    void newWindowsSlot();
    //打开文件前的判断
    void openFileSlot();
    //保存文件
    void saveFileSlot();
    //文件另存为
    void saveFileAsSlot();
    //文本保存状态
    void textStatusSlot();

    //导出pdf
    void exportPdfSlot();
    //导出jpg/png
    void exportJpgSlot();
    //字体
    void fontChooseSlot();


private:
    //Ui::ukui_NoteBook *ui;
    ukui_NoteBook *notebook;

    QString fileContent;//读到的文件内容
    QSettings *setting;
    int index;
    QPoint m_lastPoint;//记录鼠标位置
    //保存文本到文件
    void saveTextToFile();
    //初始化
    void ukuiNoteBook_init();
    //关联槽函数
    void ukuiNoteBook_connect();
    //打开文件
    void realOpenFile();
    //保存文件
    void saveFile();
    //设置快捷键
    void ukui_setShortCut();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // UKUI_NOTEBOOK_H
