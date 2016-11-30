# backup-root-to-btrfs
Small project consisting of a bash script rsyncing whole linux filesystem to a btrfs storage.

# How to install

## Link backup.sh to executable path

```ln -s PROJECT_FOLDER/backup-root-to-btrfs /usr/bin/backup-root-to-btrfs```

## (Optional) Have a notification on each time USB disk is plugged in

This is a simple approach consisting of
* A C piece of code showing a notification and launching the backup script.
* A systemd unit description to launch the notification with correct path.

### Compiling and installing notification program

```$ g++ main.c -o backup-root-to-btrfs-notify $(pkg-config --cflags --libs libnotify)```
```$ sudo ln -s PROJECT_FOLDER/backup-root-to-btrfs-notify/backup-root-to-btrfs-notify /usr/bin/backup-root-to-btrfs-notify```

### Install systemd unit
In file ```PROJECT_FOLDER/systemd/backup-root-on-usb-plugged.service```. Replace ```MOUNT-TARGET.mount``` with systemd actual mount target you want to.
You can retrieve the mount target by plugging in your USB device and type:

```systemctl list-units -t mount```

Then:
```$ sudo ln -s PROJECT_FOLDER/systemd/backup-root-on-usb-plugged.service /etc/systemd/user/```

Finally:
```$ systemd --user start backup-root-on-usb-plugged.service```
```$ systemd --user enable backup-root-on-usb-plugged.service```

#Usage

```$ sudo backup-root-to-btrfs /path/to/receive/backup```

# Dependencies:

* rsync
* xterm
* sudo
* base-devel