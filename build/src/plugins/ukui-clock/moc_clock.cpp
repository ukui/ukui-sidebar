/****************************************************************************
** Meta object code from reading C++ file 'clock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/plugins/ukui-clock/clock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Clock_t {
    QByteArrayData data[76];
    char stringdata0[1307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Clock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Clock_t qt_meta_stringdata_Clock = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Clock"
QT_MOC_LITERAL(1, 6, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(4, 53, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(5, 77, 17), // "button_image_init"
QT_MOC_LITERAL(6, 95, 14), // "Countdown_init"
QT_MOC_LITERAL(7, 110, 14), // "stopwatch_init"
QT_MOC_LITERAL(8, 125, 10), // "clock_init"
QT_MOC_LITERAL(9, 136, 10), // "setup_init"
QT_MOC_LITERAL(10, 147, 18), // "notice_dialog_show"
QT_MOC_LITERAL(11, 166, 15), // "model_setup_set"
QT_MOC_LITERAL(12, 182, 10), // "Count_down"
QT_MOC_LITERAL(13, 193, 27), // "on_pushButton_Start_clicked"
QT_MOC_LITERAL(14, 221, 26), // "on_pushButton_ring_clicked"
QT_MOC_LITERAL(15, 248, 32), // "on_pushButton_timeselect_clicked"
QT_MOC_LITERAL(16, 281, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(17, 305, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(18, 329, 11), // "timerUpdate"
QT_MOC_LITERAL(19, 341, 16), // "text_timerUpdate"
QT_MOC_LITERAL(20, 358, 15), // "set_Alarm_Clock"
QT_MOC_LITERAL(21, 374, 16), // "cancelAlarmClock"
QT_MOC_LITERAL(22, 391, 16), // "updateAlarmClock"
QT_MOC_LITERAL(23, 408, 12), // "On_Off_Alarm"
QT_MOC_LITERAL(24, 421, 11), // "deleteAlarm"
QT_MOC_LITERAL(25, 433, 13), // "stopPlayMusic"
QT_MOC_LITERAL(26, 447, 11), // "selectMusic"
QT_MOC_LITERAL(27, 459, 11), // "rePlayMusic"
QT_MOC_LITERAL(28, 471, 9), // "aItem_new"
QT_MOC_LITERAL(29, 481, 19), // "listdoubleClickslot"
QT_MOC_LITERAL(30, 501, 13), // "listClickslot"
QT_MOC_LITERAL(31, 515, 23), // "on_pushButton_9_clicked"
QT_MOC_LITERAL(32, 539, 25), // "stopwatch_start_Animation"
QT_MOC_LITERAL(33, 565, 24), // "stopwatch_stop_Animation"
QT_MOC_LITERAL(34, 590, 14), // "stat_countdown"
QT_MOC_LITERAL(35, 605, 18), // "setcoutdown_number"
QT_MOC_LITERAL(36, 624, 1), // "h"
QT_MOC_LITERAL(37, 626, 1), // "m"
QT_MOC_LITERAL(38, 628, 1), // "s"
QT_MOC_LITERAL(39, 630, 18), // "startbtn_countdown"
QT_MOC_LITERAL(40, 649, 19), // "on_min_5btn_clicked"
QT_MOC_LITERAL(41, 669, 20), // "on_min_10btn_clicked"
QT_MOC_LITERAL(42, 690, 20), // "on_min_20btn_clicked"
QT_MOC_LITERAL(43, 711, 20), // "on_min_30btn_clicked"
QT_MOC_LITERAL(44, 732, 20), // "on_min_60btn_clicked"
QT_MOC_LITERAL(45, 753, 23), // "get_countdown_over_time"
QT_MOC_LITERAL(46, 777, 21), // "on_count_push_clicked"
QT_MOC_LITERAL(47, 799, 12), // "stopwatch_jg"
QT_MOC_LITERAL(48, 812, 15), // "change_time_NUM"
QT_MOC_LITERAL(49, 828, 4), // "Hour"
QT_MOC_LITERAL(50, 833, 6), // "Minute"
QT_MOC_LITERAL(51, 840, 24), // "countdown_set_start_time"
QT_MOC_LITERAL(52, 865, 20), // "alarm_set_start_time"
QT_MOC_LITERAL(53, 886, 17), // "alarm_Cancel_save"
QT_MOC_LITERAL(54, 904, 14), // "set_alarm_save"
QT_MOC_LITERAL(55, 919, 24), // "verticalscroll_ring_time"
QT_MOC_LITERAL(56, 944, 12), // "alarm_repeat"
QT_MOC_LITERAL(57, 957, 20), // "repeat_listClickslot"
QT_MOC_LITERAL(58, 978, 12), // "select_Music"
QT_MOC_LITERAL(59, 991, 19), // "music_listClickslot"
QT_MOC_LITERAL(60, 1011, 10), // "time_Music"
QT_MOC_LITERAL(61, 1022, 24), // "time_music_listClickslot"
QT_MOC_LITERAL(62, 1047, 11), // "set_up_page"
QT_MOC_LITERAL(63, 1059, 25), // "alarm_clcok_Self_starting"
QT_MOC_LITERAL(64, 1085, 13), // "Mute_starting"
QT_MOC_LITERAL(65, 1099, 16), // "set_volume_Value"
QT_MOC_LITERAL(66, 1116, 5), // "value"
QT_MOC_LITERAL(67, 1122, 23), // "countdown_music_sellect"
QT_MOC_LITERAL(68, 1146, 25), // "count_music_listClickslot"
QT_MOC_LITERAL(69, 1172, 28), // "countdown_notice_dialog_show"
QT_MOC_LITERAL(70, 1201, 9), // "off_Alarm"
QT_MOC_LITERAL(71, 1211, 30), // "get_alarm_clock_will_ring_days"
QT_MOC_LITERAL(72, 1242, 3), // "num"
QT_MOC_LITERAL(73, 1246, 32), // "get_alarm_clock_will_ring_days_2"
QT_MOC_LITERAL(74, 1279, 17), // "change_NUM_to_str"
QT_MOC_LITERAL(75, 1297, 9) // "alarmHour"

    },
    "Clock\0on_pushButton_clicked\0\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked\0"
    "button_image_init\0Countdown_init\0"
    "stopwatch_init\0clock_init\0setup_init\0"
    "notice_dialog_show\0model_setup_set\0"
    "Count_down\0on_pushButton_Start_clicked\0"
    "on_pushButton_ring_clicked\0"
    "on_pushButton_timeselect_clicked\0"
    "on_pushButton_5_clicked\0on_pushButton_4_clicked\0"
    "timerUpdate\0text_timerUpdate\0"
    "set_Alarm_Clock\0cancelAlarmClock\0"
    "updateAlarmClock\0On_Off_Alarm\0deleteAlarm\0"
    "stopPlayMusic\0selectMusic\0rePlayMusic\0"
    "aItem_new\0listdoubleClickslot\0"
    "listClickslot\0on_pushButton_9_clicked\0"
    "stopwatch_start_Animation\0"
    "stopwatch_stop_Animation\0stat_countdown\0"
    "setcoutdown_number\0h\0m\0s\0startbtn_countdown\0"
    "on_min_5btn_clicked\0on_min_10btn_clicked\0"
    "on_min_20btn_clicked\0on_min_30btn_clicked\0"
    "on_min_60btn_clicked\0get_countdown_over_time\0"
    "on_count_push_clicked\0stopwatch_jg\0"
    "change_time_NUM\0Hour\0Minute\0"
    "countdown_set_start_time\0alarm_set_start_time\0"
    "alarm_Cancel_save\0set_alarm_save\0"
    "verticalscroll_ring_time\0alarm_repeat\0"
    "repeat_listClickslot\0select_Music\0"
    "music_listClickslot\0time_Music\0"
    "time_music_listClickslot\0set_up_page\0"
    "alarm_clcok_Self_starting\0Mute_starting\0"
    "set_volume_Value\0value\0countdown_music_sellect\0"
    "count_music_listClickslot\0"
    "countdown_notice_dialog_show\0off_Alarm\0"
    "get_alarm_clock_will_ring_days\0num\0"
    "get_alarm_clock_will_ring_days_2\0"
    "change_NUM_to_str\0alarmHour"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Clock[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      66,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  344,    2, 0x0a /* Public */,
       3,    0,  345,    2, 0x0a /* Public */,
       4,    0,  346,    2, 0x0a /* Public */,
       5,    0,  347,    2, 0x08 /* Private */,
       6,    0,  348,    2, 0x08 /* Private */,
       7,    0,  349,    2, 0x08 /* Private */,
       8,    0,  350,    2, 0x08 /* Private */,
       9,    0,  351,    2, 0x08 /* Private */,
      10,    2,  352,    2, 0x08 /* Private */,
      11,    0,  357,    2, 0x08 /* Private */,
      12,    0,  358,    2, 0x08 /* Private */,
      13,    0,  359,    2, 0x08 /* Private */,
      14,    0,  360,    2, 0x08 /* Private */,
      15,    0,  361,    2, 0x08 /* Private */,
      16,    0,  362,    2, 0x08 /* Private */,
      17,    0,  363,    2, 0x08 /* Private */,
      18,    0,  364,    2, 0x08 /* Private */,
      19,    0,  365,    2, 0x08 /* Private */,
      20,    0,  366,    2, 0x08 /* Private */,
      21,    0,  367,    2, 0x08 /* Private */,
      22,    0,  368,    2, 0x08 /* Private */,
      23,    0,  369,    2, 0x08 /* Private */,
      24,    0,  370,    2, 0x08 /* Private */,
      25,    0,  371,    2, 0x08 /* Private */,
      26,    0,  372,    2, 0x08 /* Private */,
      27,    0,  373,    2, 0x08 /* Private */,
      28,    0,  374,    2, 0x08 /* Private */,
      29,    0,  375,    2, 0x08 /* Private */,
      30,    0,  376,    2, 0x08 /* Private */,
      31,    0,  377,    2, 0x08 /* Private */,
      32,    0,  378,    2, 0x08 /* Private */,
      33,    0,  379,    2, 0x08 /* Private */,
      34,    0,  380,    2, 0x08 /* Private */,
      35,    3,  381,    2, 0x08 /* Private */,
      39,    0,  388,    2, 0x08 /* Private */,
      40,    0,  389,    2, 0x08 /* Private */,
      41,    0,  390,    2, 0x08 /* Private */,
      42,    0,  391,    2, 0x08 /* Private */,
      43,    0,  392,    2, 0x08 /* Private */,
      44,    0,  393,    2, 0x08 /* Private */,
      45,    0,  394,    2, 0x08 /* Private */,
      46,    0,  395,    2, 0x08 /* Private */,
      47,    0,  396,    2, 0x08 /* Private */,
      48,    2,  397,    2, 0x08 /* Private */,
      51,    0,  402,    2, 0x08 /* Private */,
      52,    0,  403,    2, 0x08 /* Private */,
      53,    0,  404,    2, 0x08 /* Private */,
      54,    0,  405,    2, 0x08 /* Private */,
      55,    0,  406,    2, 0x08 /* Private */,
      56,    0,  407,    2, 0x08 /* Private */,
      57,    0,  408,    2, 0x08 /* Private */,
      58,    0,  409,    2, 0x08 /* Private */,
      59,    0,  410,    2, 0x08 /* Private */,
      60,    0,  411,    2, 0x08 /* Private */,
      61,    0,  412,    2, 0x08 /* Private */,
      62,    0,  413,    2, 0x08 /* Private */,
      63,    0,  414,    2, 0x08 /* Private */,
      64,    0,  415,    2, 0x08 /* Private */,
      65,    1,  416,    2, 0x08 /* Private */,
      67,    0,  419,    2, 0x08 /* Private */,
      68,    0,  420,    2, 0x08 /* Private */,
      69,    0,  421,    2, 0x08 /* Private */,
      70,    1,  422,    2, 0x08 /* Private */,
      71,    1,  425,    2, 0x08 /* Private */,
      73,    1,  428,    2, 0x08 /* Private */,
      74,    1,  431,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   36,   37,   38,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   49,   50,
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
    QMetaType::Void, QMetaType::Int,   66,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Int, QMetaType::Int,   72,
    QMetaType::Int, QMetaType::Int,   72,
    QMetaType::QString, QMetaType::Int,   75,

       0        // eod
};

void Clock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Clock *_t = static_cast<Clock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_2_clicked(); break;
        case 2: _t->on_pushButton_3_clicked(); break;
        case 3: _t->button_image_init(); break;
        case 4: _t->Countdown_init(); break;
        case 5: _t->stopwatch_init(); break;
        case 6: _t->clock_init(); break;
        case 7: _t->setup_init(); break;
        case 8: _t->notice_dialog_show((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->model_setup_set(); break;
        case 10: _t->Count_down(); break;
        case 11: _t->on_pushButton_Start_clicked(); break;
        case 12: _t->on_pushButton_ring_clicked(); break;
        case 13: _t->on_pushButton_timeselect_clicked(); break;
        case 14: _t->on_pushButton_5_clicked(); break;
        case 15: _t->on_pushButton_4_clicked(); break;
        case 16: _t->timerUpdate(); break;
        case 17: _t->text_timerUpdate(); break;
        case 18: _t->set_Alarm_Clock(); break;
        case 19: _t->cancelAlarmClock(); break;
        case 20: _t->updateAlarmClock(); break;
        case 21: _t->On_Off_Alarm(); break;
        case 22: _t->deleteAlarm(); break;
        case 23: _t->stopPlayMusic(); break;
        case 24: _t->selectMusic(); break;
        case 25: _t->rePlayMusic(); break;
        case 26: _t->aItem_new(); break;
        case 27: _t->listdoubleClickslot(); break;
        case 28: _t->listClickslot(); break;
        case 29: _t->on_pushButton_9_clicked(); break;
        case 30: _t->stopwatch_start_Animation(); break;
        case 31: _t->stopwatch_stop_Animation(); break;
        case 32: _t->stat_countdown(); break;
        case 33: _t->setcoutdown_number((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 34: _t->startbtn_countdown(); break;
        case 35: _t->on_min_5btn_clicked(); break;
        case 36: _t->on_min_10btn_clicked(); break;
        case 37: _t->on_min_20btn_clicked(); break;
        case 38: _t->on_min_30btn_clicked(); break;
        case 39: _t->on_min_60btn_clicked(); break;
        case 40: _t->get_countdown_over_time(); break;
        case 41: _t->on_count_push_clicked(); break;
        case 42: _t->stopwatch_jg(); break;
        case 43: _t->change_time_NUM((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 44: _t->countdown_set_start_time(); break;
        case 45: _t->alarm_set_start_time(); break;
        case 46: _t->alarm_Cancel_save(); break;
        case 47: _t->set_alarm_save(); break;
        case 48: _t->verticalscroll_ring_time(); break;
        case 49: _t->alarm_repeat(); break;
        case 50: _t->repeat_listClickslot(); break;
        case 51: _t->select_Music(); break;
        case 52: _t->music_listClickslot(); break;
        case 53: _t->time_Music(); break;
        case 54: _t->time_music_listClickslot(); break;
        case 55: _t->set_up_page(); break;
        case 56: _t->alarm_clcok_Self_starting(); break;
        case 57: _t->Mute_starting(); break;
        case 58: _t->set_volume_Value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 59: _t->countdown_music_sellect(); break;
        case 60: _t->count_music_listClickslot(); break;
        case 61: _t->countdown_notice_dialog_show(); break;
        case 62: _t->off_Alarm((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: { int _r = _t->get_alarm_clock_will_ring_days((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 64: { int _r = _t->get_alarm_clock_will_ring_days_2((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 65: { QString _r = _t->change_NUM_to_str((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject Clock::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Clock.data,
      qt_meta_data_Clock,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Clock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Clock::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Clock.stringdata0))
        return static_cast<void*>(const_cast< Clock*>(this));
    return QWidget::qt_metacast(_clname);
}

int Clock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 66)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 66;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 66)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 66;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
