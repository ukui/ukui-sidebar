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


#include <glib/gi18n.h>
#include <gio/gio.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <pwd.h>

#define PROGRAM_NAME "sidebar"
#define PATH_MAX_LEN	1024
#define PID_STRING_LEN	64
#define APP_ID_DESKTOP_FILE  "sidebar.desktop"
#define ENV_VARIABLE_STRING_NAME "DESKTOP_AUTOSTART_SIDEBAR_ID"

#define SM_DBUS_NAME      "org.gnome.SessionManager"
#define SM_DBUS_PATH      "/org/gnome/SessionManager"
#define SM_DBUS_INTERFACE "org.gnome.SessionManager"
#define SM_CLIENT_DBUS_INTERFACE "org.gnome.SessionManager.ClientPrivate"

extern gboolean register_client_to_gnome_session (void);
extern int checkProcessRunning(const char *processName);
