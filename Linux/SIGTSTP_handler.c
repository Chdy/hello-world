//
// Created by 邓岩 on 18/06/2017.
//

// SIGTSTP与SIGSTOP都是使进程暂停（都使用SIGCONT让进程重新激活）。唯一的区别是SIGSTOP不可以捕获。
//
// 捕捉SIGTSTP后一般处理如下：
//
// 1）处理完额外的事
//
// 2）恢复默认处理
//
// 3）发送SIGTSTP信号给自己。（使进程进入suspend状态。）

void sig_handler(int sig)
{
    sigset_t mask;
    sigset_t premask;
    struct sigvec sv;
    printf("Caught SIGTSTP\n");
    signal(SIGTSTP,SIG_DFL);//将信号处理程序恢复成默认处理
    raise(SIGTSTP);//向自身发送SIGTSTP信号，此处可以发送SIGSTOP信号，下面的内容将不再需要，但是如果父进程需要获取子进程退出信息，将导致收到的退出信息不准确
    sigemptyset(&mask);
    sigaddset(&mask,SIGTSTP);
    sigprocmask(SIG_UNBLOCK,&mask,&premask);//取消对SIGTSTP的阻塞，此时进程会在此时停止
    //当接收到SIGCONT信号后，从此处开始继续执行，恢复开始的信号处理程序
    sigprocmask(SIG_SETMASK,&premask,NULL);
    sv.sv_mask = 0;
    sv.sv_handler = sig_handler;
    sigvec(SIGTSTP,&sv,NULL);
    printf("Handler is exiting\n");
}

int main(void)
{
    struct sigvec sv;
    sv.sv_handler = sig_handler;
    sv.sv_mask = 0;
    sigvec(SIGTSTP,&sv,NULL);
    for (;;)
        pause();
    return 0;
}
