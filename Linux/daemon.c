//
// Created by 邓岩 on 2018/12/23.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

#define MAXFD 64

extern int daemon_proc;

int daemon_init(const char * pname, int facility)
{
    int i;
    pid_t pid;

    if ((pid = fork()) < 0)
        return -1;
    else if (pid)
        _exit(0);

    if (setsid() < 0) //设置会话id，因为当前进程不是会话的首进程，所以会新建立一个会话，会话id为该进程的pid
        return -1;

    signal(SIGHUP, SIG_IGN); //需要线忽略SIGHUP信号，因为会话头进程终止时，其会话中的所有进程都收到SIGHUP信号
    if ((pid = fork()) < 0) //第二次fork确保该进程不是会话头进程，无法获取控制终端
        return -1;
    else if (pid)
        _exit(0);

    daemon_proc = 1;
    chdir("/"); //设置工作目录

    for (int i = 0; i < MAXFD; ++i) {
        close(i);
    }

    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    openlog(pname, LOG_PID, facility); //MAC上不知道日志信息被发到哪个文件上去了
    return 0;
}