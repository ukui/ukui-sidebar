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


#include "register_client_to_gnome_session.h"
#include <QDebug>
static GDBusProxy      *sm_proxy;
static GDBusProxy      *client_proxy = nullptr;
static GMainLoop       *loop;


static void stop_cb (void)
{
	g_main_loop_quit (loop);
}

static gboolean end_session_response (gboolean is_okay, const gchar *reason)
{
	GVariant *res;
	GError *error = nullptr;

	res = g_dbus_proxy_call_sync (client_proxy,
			"EndSessionResponse",
			g_variant_new ("(bs)",
				is_okay,
				reason),
			G_DBUS_CALL_FLAGS_NONE,
			-1, /* timeout */
			nullptr, /* GCancellable */
			&error);
    if (! res) {
        g_warning ("Failed to call EndSessionResponse: %s", error->message);
        g_error_free (error);
		return FALSE;
	}

	g_variant_unref (res);
	return TRUE;
}

static void query_end_session_cb (void)
{
	end_session_response (TRUE, "");
}

static void end_session_cb (void)
{
	end_session_response (TRUE, "");
	g_main_loop_quit (loop);
}

static void signal_cb (GDBusProxy *proxy, gchar *sender_name, gchar *signal_name,GVariant *parameters, gpointer user_data)
{
    Q_UNUSED(proxy);
    Q_UNUSED(sender_name);
    Q_UNUSED(parameters);
    Q_UNUSED(user_data);

	if (strcmp (signal_name, "Stop") == 0) {
		stop_cb ();
	} else if (strcmp (signal_name, "QueryEndSession") == 0) {
		query_end_session_cb ();
	} else if (strcmp (signal_name, "EndSession") == 0) {
		end_session_cb ();
	}
}

gboolean register_client_to_gnome_session (void)
{
	GError     *error = nullptr;
	GVariant   *res;
	const char *startup_id;
	const char *app_id;
	char       *client_id;

	startup_id = getenv ("DESKTOP_AUTOSTART_SIDEBAR_ID");
	app_id = APP_ID_DESKTOP_FILE;
    printf("环境变量：%s\n", startup_id);
	/* g_dbus_proxy_new_for_bus_sync
	   ( GBusType bus_type, GDBusProxyFlags flags,
	   GDBusInterfaceInfo* info, gchar* name, gchar* object_path,
	   gchar* interface_name, GCancellable* cancellable, GError*
	   error ) */
	sm_proxy = g_dbus_proxy_new_for_bus_sync (G_BUS_TYPE_SESSION,
			G_DBUS_PROXY_FLAGS_NONE,
			nullptr, /* GDBusInterfaceInfo */
			SM_DBUS_NAME,
			SM_DBUS_PATH,
			SM_DBUS_INTERFACE,
			nullptr, /* GCancellable */
			&error);
	if (sm_proxy == nullptr) {
		g_message("Failed to get session manager: %s", error->message);
		g_error_free (error);
		return FALSE;
	}

	/* GVariant        *g_dbus_proxy_call_sync               (GDBusProxy          *proxy,
	   const gchar         *method_name,
	   GVariant            *parameters,
	   GDBusCallFlags       flags,
	   gint                 timeout_msec,
	   GCancellable        *cancellable,
	   GError              **error); */
	res = g_dbus_proxy_call_sync (sm_proxy,
			"RegisterClient",
			g_variant_new ("(ss)",
				app_id,
				startup_id),
			G_DBUS_CALL_FLAGS_NONE,
			-1, /* timeout */
			nullptr, /* GCancellable */
			&error);
	if (! res) {
		g_warning ("Failed to register client: %s", error->message);
		g_error_free (error);
		return FALSE;
	}

	if (! g_variant_is_of_type (res, G_VARIANT_TYPE ("(o)"))) {
		g_warning ("RegisterClient returned unexpected type %s",
				g_variant_get_type_string (res));
		return FALSE;
	}
	g_variant_get (res, "(&o)", &client_id);

	// implement the signals to fix "policykit agent not responding"
	// error (LP: #623819)
	client_proxy = g_dbus_proxy_new_for_bus_sync (G_BUS_TYPE_SESSION,
			G_DBUS_PROXY_FLAGS_NONE,
			nullptr, /* GDBusInterfaceInfo */
			SM_DBUS_NAME,
			client_id,
			SM_CLIENT_DBUS_INTERFACE,
			nullptr, /* GCancellable */
			&error);
	g_variant_unref (res);
	if (client_proxy == nullptr) {
		g_message("Failed to get client proxy: %s", error->message);
		g_error_free (error);
		return FALSE;
	}
	g_signal_connect (client_proxy, "g-signal", G_CALLBACK (signal_cb), nullptr);

	return TRUE;
}

int checkProcessRunning(const char *processName)
{
    int uid = getuid();
	int pid = getpid();

	char pid_file[PATH_MAX_LEN] = {0};
	char pid_string[PID_STRING_LEN] = {0};


	snprintf(pid_file, PATH_MAX_LEN, "/run/user/%d/%s.pid", uid, processName);
	int pid_file_fd = open(pid_file, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (pid_file_fd < 0)
	{
		fprintf(stderr, "Can not open pid file: %s\n", pid_file);
		return -1;
	}

	int lock_ret = flock(pid_file_fd, LOCK_EX | LOCK_NB);
	if (lock_ret < 0)
	{
		struct passwd *pwd = getpwuid(uid);
		fprintf(stdout, "User %s[%d] has run %s, the current program exits.\n",
				pwd->pw_name, uid, processName);
		return 1;
	}

	snprintf(pid_string, PID_STRING_LEN, "%d\n", pid);
    write(pid_file_fd, (const void *)pid_string, strlen(pid_string));

	fsync(pid_file_fd);

    return 0;
}
