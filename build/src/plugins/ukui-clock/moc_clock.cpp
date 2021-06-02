/****************************************************************************
** Meta object code from reading C++ file 'clock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-clock/clock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Clock_t {
    QByteArrayData data[83];
    char stringdata0[1299];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Clock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Clock_t qt_meta_stringdata_Clock = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Clock"
QT_MOC_LITERAL(1, 6, 19), // "CountdownPageSwitch"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "AlarmPageSwitch"
QT_MOC_LITERAL(4, 43, 19), // "StopwatchPageSwitch"
QT_MOC_LITERAL(5, 63, 13), // "settingsStyle"
QT_MOC_LITERAL(6, 77, 10), // "blackStyle"
QT_MOC_LITERAL(7, 88, 10), // "whiteStyle"
QT_MOC_LITERAL(8, 99, 17), // "drawNoAlarmPrompt"
QT_MOC_LITERAL(9, 117, 15), // "buttonImageInit"
QT_MOC_LITERAL(10, 133, 13), // "CountdownInit"
QT_MOC_LITERAL(11, 147, 13), // "stopwatchInit"
QT_MOC_LITERAL(12, 161, 9), // "clockInit"
QT_MOC_LITERAL(13, 171, 9), // "setupInit"
QT_MOC_LITERAL(14, 181, 16), // "noticeDialogShow"
QT_MOC_LITERAL(15, 198, 13), // "modelSetupSet"
QT_MOC_LITERAL(16, 212, 9), // "CountDown"
QT_MOC_LITERAL(17, 222, 24), // "onPushbuttonStartClicked"
QT_MOC_LITERAL(18, 247, 23), // "onPushbuttonRingClicked"
QT_MOC_LITERAL(19, 271, 29), // "onPushbuttonTimeselectClicked"
QT_MOC_LITERAL(20, 301, 20), // "windowClosingClicked"
QT_MOC_LITERAL(21, 322, 23), // "windowMinimizingClicked"
QT_MOC_LITERAL(22, 346, 11), // "timerUpdate"
QT_MOC_LITERAL(23, 358, 15), // "textTimerupdate"
QT_MOC_LITERAL(24, 374, 13), // "setAlarmClock"
QT_MOC_LITERAL(25, 388, 16), // "cancelAlarmClock"
QT_MOC_LITERAL(26, 405, 16), // "updateAlarmClock"
QT_MOC_LITERAL(27, 422, 10), // "OnOffAlarm"
QT_MOC_LITERAL(28, 433, 11), // "deleteAlarm"
QT_MOC_LITERAL(29, 445, 13), // "stopPlayMusic"
QT_MOC_LITERAL(30, 459, 16), // "ChooseAlarmMusic"
QT_MOC_LITERAL(31, 476, 11), // "rePlayMusic"
QT_MOC_LITERAL(32, 488, 8), // "aitemNew"
QT_MOC_LITERAL(33, 497, 19), // "listdoubleClickslot"
QT_MOC_LITERAL(34, 517, 13), // "listClickslot"
QT_MOC_LITERAL(35, 531, 18), // "alarmReEditClicked"
QT_MOC_LITERAL(36, 550, 23), // "stopwatchStartAnimation"
QT_MOC_LITERAL(37, 574, 22), // "stopwatchStopAnimation"
QT_MOC_LITERAL(38, 597, 13), // "statCountdown"
QT_MOC_LITERAL(39, 611, 17), // "setcoutdownNumber"
QT_MOC_LITERAL(40, 629, 1), // "h"
QT_MOC_LITERAL(41, 631, 1), // "m"
QT_MOC_LITERAL(42, 633, 1), // "s"
QT_MOC_LITERAL(43, 635, 17), // "startbtnCountdown"
QT_MOC_LITERAL(44, 653, 17), // "onMin_5btnClicked"
QT_MOC_LITERAL(45, 671, 18), // "onMin_10btnClicked"
QT_MOC_LITERAL(46, 690, 18), // "onMin_20btnClicked"
QT_MOC_LITERAL(47, 709, 18), // "onMin_30btnClicked"
QT_MOC_LITERAL(48, 728, 18), // "onMin_60btnClicked"
QT_MOC_LITERAL(49, 747, 20), // "getCountdownOverTime"
QT_MOC_LITERAL(50, 768, 18), // "onCountPushClicked"
QT_MOC_LITERAL(51, 787, 11), // "stopwatchJg"
QT_MOC_LITERAL(52, 799, 13), // "changeTimeNum"
QT_MOC_LITERAL(53, 813, 4), // "Hour"
QT_MOC_LITERAL(54, 818, 6), // "Minute"
QT_MOC_LITERAL(55, 825, 21), // "countdownSetStartTime"
QT_MOC_LITERAL(56, 847, 17), // "alarmSetStartTime"
QT_MOC_LITERAL(57, 865, 15), // "alarmCancelSave"
QT_MOC_LITERAL(58, 881, 12), // "setAlarmSave"
QT_MOC_LITERAL(59, 894, 22), // "verticalscrollRingTime"
QT_MOC_LITERAL(60, 917, 11), // "alarmRepeat"
QT_MOC_LITERAL(61, 929, 19), // "repeatListclickslot"
QT_MOC_LITERAL(62, 949, 16), // "selectAlarmMusic"
QT_MOC_LITERAL(63, 966, 18), // "musicListclickslot"
QT_MOC_LITERAL(64, 985, 9), // "timeMusic"
QT_MOC_LITERAL(65, 995, 22), // "timeMusicListclickslot"
QT_MOC_LITERAL(66, 1018, 9), // "setUpPage"
QT_MOC_LITERAL(67, 1028, 22), // "alarmClcokSelfStarting"
QT_MOC_LITERAL(68, 1051, 12), // "MuteStarting"
QT_MOC_LITERAL(69, 1064, 14), // "setVolumeValue"
QT_MOC_LITERAL(70, 1079, 5), // "value"
QT_MOC_LITERAL(71, 1085, 21), // "countdownMusicSellect"
QT_MOC_LITERAL(72, 1107, 23), // "countMusicListclickslot"
QT_MOC_LITERAL(73, 1131, 25), // "countdownNoticeDialogShow"
QT_MOC_LITERAL(74, 1157, 8), // "offAlarm"
QT_MOC_LITERAL(75, 1166, 25), // "getAlarmClockWillRingDays"
QT_MOC_LITERAL(76, 1192, 3), // "num"
QT_MOC_LITERAL(77, 1196, 27), // "getAlarmClockWillRingDays_2"
QT_MOC_LITERAL(78, 1224, 14), // "changeNumToStr"
QT_MOC_LITERAL(79, 1239, 9), // "alarmHour"
QT_MOC_LITERAL(80, 1249, 28), // "onCustomContextMenuRequested"
QT_MOC_LITERAL(81, 1278, 3), // "pos"
QT_MOC_LITERAL(82, 1282, 16) // "countStatBtnGray"

    },
    "Clock\0CountdownPageSwitch\0\0AlarmPageSwitch\0"
    "StopwatchPageSwitch\0settingsStyle\0"
    "blackStyle\0whiteStyle\0drawNoAlarmPrompt\0"
    "buttonImageInit\0CountdownInit\0"
    "stopwatchInit\0clockInit\0setupInit\0"
    "noticeDialogShow\0modelSetupSet\0CountDown\0"
    "onPushbuttonStartClicked\0"
    "onPushbuttonRingClicked\0"
    "onPushbuttonTimeselectClicked\0"
    "windowClosingClicked\0windowMinimizingClicked\0"
    "timerUpdate\0textTimerupdate\0setAlarmClock\0"
    "cancelAlarmClock\0updateAlarmClock\0"
    "OnOffAlarm\0deleteAlarm\0stopPlayMusic\0"
    "ChooseAlarmMusic\0rePlayMusic\0aitemNew\0"
    "listdoubleClickslot\0listClickslot\0"
    "alarmReEditClicked\0stopwatchStartAnimation\0"
    "stopwatchStopAnimation\0statCountdown\0"
    "setcoutdownNumber\0h\0m\0s\0startbtnCountdown\0"
    "onMin_5btnClicked\0onMin_10btnClicked\0"
    "onMin_20btnClicked\0onMin_30btnClicked\0"
    "onMin_60btnClicked\0getCountdownOverTime\0"
    "onCountPushClicked\0stopwatchJg\0"
    "changeTimeNum\0Hour\0Minute\0"
    "countdownSetStartTime\0alarmSetStartTime\0"
    "alarmCancelSave\0setAlarmSave\0"
    "verticalscrollRingTime\0alarmRepeat\0"
    "repeatListclickslot\0selectAlarmMusic\0"
    "musicListclickslot\0timeMusic\0"
    "timeMusicListclickslot\0setUpPage\0"
    "alarmClcokSelfStarting\0MuteStarting\0"
    "setVolumeValue\0value\0countdownMusicSellect\0"
    "countMusicListclickslot\0"
    "countdownNoticeDialogShow\0offAlarm\0"
    "getAlarmClockWillRingDays\0num\0"
    "getAlarmClockWillRingDays_2\0changeNumToStr\0"
    "alarmHour\0onCustomContextMenuRequested\0"
    "pos\0countStatBtnGray"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Clock[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      72,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  374,    2, 0x0a /* Public */,
       3,    0,  375,    2, 0x0a /* Public */,
       4,    0,  376,    2, 0x0a /* Public */,
       5,    0,  377,    2, 0x0a /* Public */,
       6,    0,  378,    2, 0x0a /* Public */,
       7,    0,  379,    2, 0x0a /* Public */,
       8,    0,  380,    2, 0x0a /* Public */,
       9,    0,  381,    2, 0x08 /* Private */,
      10,    0,  382,    2, 0x08 /* Private */,
      11,    0,  383,    2, 0x08 /* Private */,
      12,    0,  384,    2, 0x08 /* Private */,
      13,    0,  385,    2, 0x08 /* Private */,
      14,    2,  386,    2, 0x08 /* Private */,
      15,    0,  391,    2, 0x08 /* Private */,
      16,    0,  392,    2, 0x08 /* Private */,
      17,    0,  393,    2, 0x08 /* Private */,
      18,    0,  394,    2, 0x08 /* Private */,
      19,    0,  395,    2, 0x08 /* Private */,
      20,    0,  396,    2, 0x08 /* Private */,
      21,    0,  397,    2, 0x08 /* Private */,
      22,    0,  398,    2, 0x08 /* Private */,
      23,    0,  399,    2, 0x08 /* Private */,
      24,    0,  400,    2, 0x08 /* Private */,
      25,    0,  401,    2, 0x08 /* Private */,
      26,    0,  402,    2, 0x08 /* Private */,
      27,    0,  403,    2, 0x08 /* Private */,
      28,    0,  404,    2, 0x08 /* Private */,
      29,    0,  405,    2, 0x08 /* Private */,
      30,    0,  406,    2, 0x08 /* Private */,
      31,    0,  407,    2, 0x08 /* Private */,
      32,    0,  408,    2, 0x08 /* Private */,
      33,    0,  409,    2, 0x08 /* Private */,
      34,    0,  410,    2, 0x08 /* Private */,
      35,    0,  411,    2, 0x08 /* Private */,
      36,    0,  412,    2, 0x08 /* Private */,
      37,    0,  413,    2, 0x08 /* Private */,
      38,    0,  414,    2, 0x08 /* Private */,
      39,    3,  415,    2, 0x08 /* Private */,
      43,    0,  422,    2, 0x08 /* Private */,
      44,    0,  423,    2, 0x08 /* Private */,
      45,    0,  424,    2, 0x08 /* Private */,
      46,    0,  425,    2, 0x08 /* Private */,
      47,    0,  426,    2, 0x08 /* Private */,
      48,    0,  427,    2, 0x08 /* Private */,
      49,    0,  428,    2, 0x08 /* Private */,
      50,    0,  429,    2, 0x08 /* Private */,
      51,    0,  430,    2, 0x08 /* Private */,
      52,    2,  431,    2, 0x08 /* Private */,
      55,    0,  436,    2, 0x08 /* Private */,
      56,    0,  437,    2, 0x08 /* Private */,
      57,    0,  438,    2, 0x08 /* Private */,
      58,    0,  439,    2, 0x08 /* Private */,
      59,    0,  440,    2, 0x08 /* Private */,
      60,    0,  441,    2, 0x08 /* Private */,
      61,    0,  442,    2, 0x08 /* Private */,
      62,    0,  443,    2, 0x08 /* Private */,
      63,    0,  444,    2, 0x08 /* Private */,
      64,    0,  445,    2, 0x08 /* Private */,
      65,    0,  446,    2, 0x08 /* Private */,
      66,    0,  447,    2, 0x08 /* Private */,
      67,    0,  448,    2, 0x08 /* Private */,
      68,    0,  449,    2, 0x08 /* Private */,
      69,    1,  450,    2, 0x08 /* Private */,
      71,    0,  453,    2, 0x08 /* Private */,
      72,    0,  454,    2, 0x08 /* Private */,
      73,    0,  455,    2, 0x08 /* Private */,
      74,    1,  456,    2, 0x08 /* Private */,
      75,    1,  459,    2, 0x08 /* Private */,
      77,    1,  462,    2, 0x08 /* Private */,
      78,    1,  465,    2, 0x08 /* Private */,
      80,    1,  468,    2, 0x08 /* Private */,
      82,    0,  471,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   40,   41,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   53,   54,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   70,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Int, QMetaType::Int,   76,
    QMetaType::Int, QMetaType::Int,   76,
    QMetaType::QString, QMetaType::Int,   79,
    QMetaType::Void, QMetaType::QPoint,   81,
    QMetaType::Void,

       0        // eod
};

void Clock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Clock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CountdownPageSwitch(); break;
        case 1: _t->AlarmPageSwitch(); break;
        case 2: _t->StopwatchPageSwitch(); break;
        case 3: _t->settingsStyle(); break;
        case 4: _t->blackStyle(); break;
        case 5: _t->whiteStyle(); break;
        case 6: _t->drawNoAlarmPrompt(); break;
        case 7: _t->buttonImageInit(); break;
        case 8: _t->CountdownInit(); break;
        case 9: _t->stopwatchInit(); break;
        case 10: _t->clockInit(); break;
        case 11: _t->setupInit(); break;
        case 12: _t->noticeDialogShow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->modelSetupSet(); break;
        case 14: _t->CountDown(); break;
        case 15: _t->onPushbuttonStartClicked(); break;
        case 16: _t->onPushbuttonRingClicked(); break;
        case 17: _t->onPushbuttonTimeselectClicked(); break;
        case 18: _t->windowClosingClicked(); break;
        case 19: _t->windowMinimizingClicked(); break;
        case 20: _t->timerUpdate(); break;
        case 21: _t->textTimerupdate(); break;
        case 22: _t->setAlarmClock(); break;
        case 23: _t->cancelAlarmClock(); break;
        case 24: _t->updateAlarmClock(); break;
        case 25: _t->OnOffAlarm(); break;
        case 26: _t->deleteAlarm(); break;
        case 27: _t->stopPlayMusic(); break;
        case 28: _t->ChooseAlarmMusic(); break;
        case 29: _t->rePlayMusic(); break;
        case 30: _t->aitemNew(); break;
        case 31: _t->listdoubleClickslot(); break;
        case 32: _t->listClickslot(); break;
        case 33: _t->alarmReEditClicked(); break;
        case 34: _t->stopwatchStartAnimation(); break;
        case 35: _t->stopwatchStopAnimation(); break;
        case 36: _t->statCountdown(); break;
        case 37: _t->setcoutdownNumber((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 38: _t->startbtnCountdown(); break;
        case 39: _t->onMin_5btnClicked(); break;
        case 40: _t->onMin_10btnClicked(); break;
        case 41: _t->onMin_20btnClicked(); break;
        case 42: _t->onMin_30btnClicked(); break;
        case 43: _t->onMin_60btnClicked(); break;
        case 44: _t->getCountdownOverTime(); break;
        case 45: _t->onCountPushClicked(); break;
        case 46: _t->stopwatchJg(); break;
        case 47: _t->changeTimeNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 48: _t->countdownSetStartTime(); break;
        case 49: _t->alarmSetStartTime(); break;
        case 50: _t->alarmCancelSave(); break;
        case 51: _t->setAlarmSave(); break;
        case 52: _t->verticalscrollRingTime(); break;
        case 53: _t->alarmRepeat(); break;
        case 54: _t->repeatListclickslot(); break;
        case 55: _t->selectAlarmMusic(); break;
        case 56: _t->musicListclickslot(); break;
        case 57: _t->timeMusic(); break;
        case 58: _t->timeMusicListclickslot(); break;
        case 59: _t->setUpPage(); break;
        case 60: _t->alarmClcokSelfStarting(); break;
        case 61: _t->MuteStarting(); break;
        case 62: _t->setVolumeValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: _t->countdownMusicSellect(); break;
        case 64: _t->countMusicListclickslot(); break;
        case 65: _t->countdownNoticeDialogShow(); break;
        case 66: _t->offAlarm((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 67: { int _r = _t->getAlarmClockWillRingDays((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 68: { int _r = _t->getAlarmClockWillRingDays_2((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 69: { QString _r = _t->changeNumToStr((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 70: _t->onCustomContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 71: _t->countStatBtnGray(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Clock::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Clock.data,
    qt_meta_data_Clock,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Clock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Clock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Clock.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Clock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 72)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 72;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 72)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 72;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
