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
#include "clock.h"
#include "singleApplication.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    a.setAttribute(Qt::AA_UseHighDpiPixmaps,true);
#endif
    if (!a.isRunning()) {
        Clock w;
        a.w = &w;
        w.show();
        return a.exec();
    }
    return 0;
}
