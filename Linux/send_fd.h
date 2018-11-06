//
// Created by 邓岩 on 2018/10/21.
//

#ifndef LINUX_SEND_FD_H
#define LINUX_SEND_FD_H
# include "rio.h"

#define CONTROLLEN CMSG_LEN(sizeof(int))

static struct cmsghdr * cmptr = NULL;

int send_fd(int fd, int fd_to_send);
int send_err(int fd, int status, const char * errmsg);
int recv_fd(int fd, ssize_t (*userfunc)(int, const void *, size_t));

int send_fd(int fd, int fd_to_send)
{
    struct iovec iov[1];
    struct msghdr msg;
    char buf[2];

    iov[0].iov_base = buf;
    iov[0].iov_len = 2;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;

    if (fd_to_send < 0) { //发送的描述符非法
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        buf[1] = -fd_to_send; //破坏信息协议结构
        if (buf[1] == 0)
            buf[1] = 1;
    } else {
        if (cmptr == NULL && (cmptr = malloc((CONTROLLEN))) == NULL)
            return -1;
        cmptr->cmsg_level = SOL_SOCKET; //表示套接字级
        cmptr->cmsg_type = SCM_RIGHTS; //表示转移套接字级的访问权
        cmptr->cmsg_len = CONTROLLEN; //该结构体及关联数据的大小总和
        msg.msg_control = cmptr; //指向控制信息头部
        msg.msg_controllen = CONTROLLEN; //控制信息长度
        *(int *)CMSG_DATA(cmptr) = fd_to_send; //随控制信息一起发送的关联数据
        buf[1] = 0;
    }

    buf[0] = 0;
    if (sendmsg(fd, &msg, 0) != 2)
        return -1;
    return 0;
}

int recv_fd(int fd, ssize_t (*userfunc)(int, const void *, size_t))
{
    int newfd, nr, status;
    char * ptr;
    char buf[20];
    struct iovec iov[1];
    struct msghdr msg;

    status = -1;
    for (;;) {
        iov[0].iov_base = buf;
        iov[0].iov_len = sizeof(buf);
        msg.msg_iov = iov;
        msg.msg_iovlen = 1;
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        if (cmptr == NULL && (cmptr = malloc((CONTROLLEN))) == NULL) //分配控制信息及其关联数据的空间
            return -1;
        msg.msg_control = cmptr;
        msg.msg_controllen = CONTROLLEN;
        if ((nr = recvmsg(fd, &msg, 0)) < 0) {
            printf("recvmsg error");
            return -1;
        } else if (nr == 0) {
            printf("connection closed by server");
            return -1;
        }

        for (ptr = buf; ptr < buf + nr; ++ptr) {
            if (*ptr++ == 0) {
                if (ptr != buf + nr - 1) {
                    printf("message formate error");
                } //如果刚刚读到的0不是倒数第2个字节
                status = *ptr & 0xFF; //拓展字符类型为整形并且保证为正数，即扩展时往前加0
                if (status == 0) {
                    if (msg.msg_controllen < CONTROLLEN) {
                        printf("status = 0 buf no fd");
                        return -1;
                    }
                    newfd = *(int *)CMSG_DATA(cmptr);
                } else {
                    newfd = -status;
                }
                nr -= 2;
            }
        }

        if (nr > 0 && (*userfunc)(STDERR_FILENO, buf, nr) != nr)
            return -1;

        if (status >= 0)
            return newfd;
    }
}

int send_err(int fd, int errcode, const char * msg)
{
    int n;
    if ((n = strlen(msg)) > 0)
        if (rio_writen(fd, msg, n) != n)
            return -1;

    if (errcode >= 0)
        errcode = -1;

    if (send_fd(fd, errcode) < 0)
        return -1;

    return 0;
}


#endif //LINUX_SEND_FD_H
