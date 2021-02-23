/* Exit when a monitor is plugged in */

#include <libudev.h>
#include <stdio.h>

#define SUBSYSTEM "drm"


static void monitor_devices(struct udev* udev)
{
    struct udev_monitor* mon = udev_monitor_new_from_netlink(udev, "udev");

    udev_monitor_filter_add_match_subsystem_devtype(mon, SUBSYSTEM, NULL);
    udev_monitor_enable_receiving(mon);

    int fd = udev_monitor_get_fd(mon);

    while (1) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        int ret = select(fd+1, &fds, NULL, NULL, NULL);
        if (ret <= 0)
            break;

        if (FD_ISSET(fd, &fds)) {
            break;
        }
    }
}

int main(void)
{
    struct udev* udev = udev_new();
    if (!udev) {
        fprintf(stderr, "udev_new() failed\n");
        return 1;
    }

    monitor_devices(udev);

    udev_unref(udev);
    return 0;
}
