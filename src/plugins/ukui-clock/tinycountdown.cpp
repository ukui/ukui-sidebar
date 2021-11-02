#include "tinycountdown.h"
#include "ui_tinycountdown.h"

tinyCountdown::tinyCountdown(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tinyCountdown)
{
    ui->setupUi(this);


    // 添加窗管协议

    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);




    //时间显示
    ui->timeLabel->setAlignment(Qt::AlignHCenter);
    //右上角关闭
    closeStyle();
    //
    switchStyle();

    connect(ui->clocseBtn, SIGNAL(clicked()), this, SLOT(set_dialog_close()) );

    //左上闹钟图标
   ui->clockIcon->setPixmap(QIcon::fromTheme("kylin-alarm-clock").pixmap(24,24));
   //闹钟时间字体改为灰色
   QPalette pa;
   pa.setColor(QPalette::WindowText,Qt::gray);


   //主窗口connect
   connect(ui->switchBtn, SIGNAL(clicked()), this, SLOT(showMainWindow()) );


   //显示，但不可移动
   setWindowFlags(Qt::ToolTip);
   settingsStyle();
}

tinyCountdown::~tinyCountdown()
{
    delete ui;
}
/**
 * @brief 显示倒计时时间
 */
void tinyCountdown::updateTimeInfo(QString str)
{
    ui->timeLabel->setText(str);
}


/*
void tinyCountdown::focusOutEvent(QFocusEvent *event)
{
    qDebug()<<"dbq-"<<"focusOutEvent";
}

void tinyCountdown::focusInEvent(QFocusEvent *event)
{
    qDebug()<<"dbq-"<<"focusInEvent";
}
*/
// 在鼠标光标在小部件内部时按下鼠标按钮时调用，或者当小部件使用grabMouse ()抓住鼠标时调用。按下鼠标而不释放它实际上与调用grabMouse ()相同。
void tinyCountdown::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QWidget::mousePressEvent(event);
}
//在鼠标按钮被释放时被调用。当小部件接收到相应的鼠标按下事件时，它就会接收鼠标释放事件。这意味着如果用户在您的小部件内按下鼠标，然后在释放鼠标按钮之前将鼠标拖动到其他地方，您的小部件将收到释放事件。
void tinyCountdown::mouseReleaseEvent(QMouseEvent *event)
{

    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
    }

    QWidget::mouseReleaseEvent(event);
    this->setCursor(Qt::ArrowCursor);
}
//每当鼠标移动而按住鼠标按钮时调用。这在拖放操作期间很有用。
void tinyCountdown::mouseMoveEvent(QMouseEvent *event)
{


    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
        this->setCursor(Qt::ClosedHandCursor);
    }

    QWidget::mouseMoveEvent(event);
}

void tinyCountdown::closeEvent(QCloseEvent *event)
{
    event->ignore();//忽视
    this->hide();
}


/**
 * @brief 清空数据
 */
void tinyCountdown::clearData()
{
    ui->timeLabel->setText("00:00:00");
    this->hide();
}

void tinyCountdown::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    QPainterPath rectPath;
    rectPath.addRoundedRect(this->rect(), 0, 0); // 左上右下

    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    painter.setBrush(opt.palette.color(QPalette::Base));

    QColor mainColor;
    if(QColor(255,255,255) == opt.palette.color(QPalette::Base) || QColor(248,248,248) == opt.palette.color(QPalette::Base))
    {
        mainColor = QColor(221, 228, 235,198);
    }else{
        mainColor = QColor(26, 26, 26,198);
    }

    p.fillPath(rectPath,QBrush(mainColor));
}



void tinyCountdown::set_dialog_close()
{
    this->hide();
}

void tinyCountdown::showMainWindow()
{
    this->hide();
    emit mainWindowClick();
}



void tinyCountdown::showTop()
{

    this->hide();

    this->show();
}



void tinyCountdown::closeStyle()
{
    ui->clocseBtn->setIcon(QIcon::fromTheme("window-close-symbolic"));
    ui->clocseBtn->setProperty("isWindowButton", 0x2);
    ui->clocseBtn->setProperty("useIconHighlightEffect", 0x8);
    ui->clocseBtn->setFlat(true);
}

void tinyCountdown::settingsStyle()
{
    const QByteArray style_id(ORG_UKUI_STYLE);
    QStringList stylelist;
    QGSettings *style_settings = new QGSettings(style_id);

    stylelist<<STYLE_NAME_KEY_DARK<<STYLE_NAME_KEY_BLACK; //<<STYLE_NAME_KEY_DEFAULT;
    if(QGSettings::isSchemaInstalled(style_id)){
        style_settings = new QGSettings(style_id);
        if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
            blackStyle();
        }else{
            whiteStyle();
        }
    }

    connect(style_settings, &QGSettings::changed, this, [=] (const QString &key){
        if(key==STYLE_NAME){
            qDebug()<<"STYLE_NAME : "<<key;
            if(stylelist.contains(style_settings->get(STYLE_NAME).toString())){
                blackStyle();
            }else{
                whiteStyle();
            }
        }
        if(key==STYLE_ICON_NAME || key==STYLE_ICON){
            ui->clockIcon->setPixmap(QIcon::fromTheme("kylin-alarm-clock").pixmap(24,24));
        }
    });
}

void tinyCountdown::whiteStyle()
{
    ui->switchBtn->setIcon(QIcon(":image/switchIconB.png"));
}

void tinyCountdown::blackStyle()
{
    ui->switchBtn->setIcon(QIcon(":image/switchIconW.png"));
}

void tinyCountdown::switchStyle()
{
    ui->switchBtn->setIcon(QIcon(":image/switchIconB.png"));
    ui->switchBtn->setProperty("useIconHighlightEffect", 0x8);
    ui->switchBtn->setFlat(true);
}




