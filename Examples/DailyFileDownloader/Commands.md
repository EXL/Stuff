Enable:

```bash
$ sudo cp dailyfiledownloader.* /etc/systemd/system/
$ sudo systemctl enable dailyfiledownloader.timer
$ sudo systemctl start dailyfiledownloader.timer
```

Disable:

```bash
$ sudo systemctl stop dailyfiledownloader.timer
$ sudo systemctl disable dailyfiledownloader.timer
$ sudo rm -Rf /etc/systemd/system/dailyfiledownloader*
```
Show timers:

```bash
$ systemctl list-timers
```
