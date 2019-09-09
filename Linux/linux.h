//
// Created by 邓岩 on 09/03/2017.
//

#ifndef LINUX_LINUX_H
#define LINUX_LINUX_H

# include <sys/types.h>
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <mach-o/getsect.h>
# include <pwd.h>
# include <grp.h>
# include <utmp.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <setjmp.h>
# include <sys/time.h>
# include <sys/times.h>
# include <sys/utsname.h>
# include <time.h>
# include <utime.h>
# include <dirent.h>
# include <libgen.h>
# include <signal.h>
# include <pthread.h>
# include <termios.h> //用于设置tty
# include <utmpx.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <sys/msg.h>
# include <sys/sem.h>
# include <sys/shm.h>
# include <sys/types.h>
# include <sys/msg.h>
# include <sys/mman.h>
# include <sys/socket.h> //套接字API
# include <sys/un.h>
# include <arpa/inet.h> //大小端字节序转换
# include <netdb.h> //用于访问dns
# include <sys/select.h>
# include <poll.h>
# include <aio.h> //posix 异步io
# include <syslog.h>
# include <sys/event.h>
# include <sys/sysctl.h>
# include <sys/param.h>

#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/tcp.h>

#include "error.c"

#define MAXLINE 4096

char * itoa(int s)
{
    int i = 1;
    int t = s;
    while(t /= 10)
        i++;
    char * a = (char *)malloc(i+1);
    a[i] = 0;
    for (i--; i>=0; i--) {
        t = s%10;
        s /= 10;
        a[i] = t+48;
    }
    return a;
}

#endif //LINUX_LINUX_H
