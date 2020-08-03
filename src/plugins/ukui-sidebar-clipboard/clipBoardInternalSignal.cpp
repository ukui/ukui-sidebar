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
#include "clipBoardInternalSignal.h"
static ClipBoardInternalSignal* Global_internal_signal = nullptr;
void ClipBoardInternalSignal::initInternalSignal()
{
    ClipBoardInternalSignal::getGlobalInternalSignal();
    return;
}

ClipBoardInternalSignal* ClipBoardInternalSignal::getGlobalInternalSignal()
{
    if (Global_internal_signal == nullptr)
        Global_internal_signal = new ClipBoardInternalSignal();
    return Global_internal_signal;
}
