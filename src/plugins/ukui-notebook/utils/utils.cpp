#include "utils.h"

void Utils::setCLIName(QCommandLineParser &parser) {
    //添加帮助信息(-h,--help)，这个方法由QCommandLineParser自动处理
    parser.addHelpOption();
    //添加（-v,--version）方法，显示应用的版本，这个方法由QCommandLineParser自动处理
    parser.addVersionOption();
}
