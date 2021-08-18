/*
* Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
*
*/
#include "utils.h"

void Utils::setCLIName(QCommandLineParser &parser) {
    //添加帮助信息(-h,--help)，这个方法由QCommandLineParser自动处理
    parser.addHelpOption();
    //添加（-v,--version）方法，显示应用的版本，这个方法由QCommandLineParser自动处理
    parser.addVersionOption();
}
