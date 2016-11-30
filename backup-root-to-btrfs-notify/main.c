#include "libnotify/notify.h"
#include "stdlib.h"
#include "string.h"

GMainLoop *MAINLOOP;
char* BACKUP_PATH;


GdkPixbuf *makeIcon() {

    /* GdkPixbuf *icon = gdk_pixbuf_new_from_xpm_data(ICON);*/
    GdkPixbuf* icon;
    return icon;
}

int performBackup() {

    /* */
    const char* pattern = "xterm -e /bin/bash -l -c \"sudo backup-root-to-btrfs %s\"";
    char* cmd = (char*)malloc(sizeof(char) * (strlen(pattern) + strlen(BACKUP_PATH)));
    sprintf(cmd, pattern, BACKUP_PATH);

    printf("Will launch: %s\n", cmd);
    system(cmd);

    free(cmd);

    return 0;
}

void closed(NotifyNotification *notification, gpointer user_data) {

    gint reason = notify_notification_get_closed_reason(notification);

    g_main_loop_quit(MAINLOOP);
}

int main(int argc, char** argv) {

    /* Argument parsing*/

    if(argc != 2) {
	fprintf(stderr, 
		"Usage: \n    backup-root-to-btrfs-notify PATH_WHERE_TO_STORE_BACKUP"
		);
	return 1;
    } else {
	BACKUP_PATH=argv[1];
    }

    /* */

    notify_init ("Backup your disk!");
    NotifyNotification *backupNotif = notify_notification_new("Backup",
                                                              "You backup harddisk has been pluged in, do you want to perform a backup?",
                                                              NULL);
    GdkPixbuf *icon = makeIcon();
    //notify_notification_set_icon_from_pixbuf(backupNotif, icon);
    notify_notification_set_timeout(backupNotif, 10000); //10 sec
    notify_notification_set_urgency(backupNotif, NOTIFY_URGENCY_LOW);

    notify_notification_add_action(backupNotif, "launchbackup", "Launch backup", NOTIFY_ACTION_CALLBACK(performBackup), NULL, NULL);

    notify_notification_show (backupNotif, NULL);

    g_signal_connect(backupNotif, "closed", G_CALLBACK(closed), NULL);

    /* */
    MAINLOOP = g_main_loop_new(NULL, TRUE);
    g_main_loop_run(MAINLOOP);

    /* */
    g_object_unref(G_OBJECT(backupNotif));
    notify_uninit();
    return 0;
}
