//
// Created by 邓岩 on 2018/10/20.
//

#ifndef LINUX_UNIX_SOCKET_API_H
#define LINUX_UNIX_SOCKET_API_H

#define QLEN 10 //监听队列的长度
#define STALE 30 //套接字的创建时间应该在30秒内
#define CLI_PATH "/Users/dengyan/"
#define CLI_PERM S_IRWXU

int serv_listen(const char * name);//用于服务器端，生成一个unix域的监听套接字
int serv_accept(int listenfd,uid_t * uidptr);//接受一个unix域套接字的连接请求，返回新生成用于通讯的套接字
int cli_conn(const char * name);//用于客户端，与服务器端进行连接

int serv_listen(const char * name)//用于服务器端，生成一个unix域的监听套接字
{
    int fd,len,err,rval;
    struct sockaddr_un un;

    if(strlen(name) >= sizeof(un.sun_path)) {
        errno = ENAMETOOLONG;
        return -1;
    }

    if ((fd = socket(AF_UNIX,SOCK_STREAM,0)) < 0) {
        rval = -2;
        goto errout;
    }

    unlink(name);//保证在bind前此文件不存在
    memset(&un,0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path,name);
    len = __offsetof(struct sockaddr_un, sun_path) + strlen(name);

    if (bind(fd,(struct sockaddr *)&un,len) < 0) {
        rval = -3;
        goto errout;
    }

    if(listen(fd,QLEN) < 0) {
        rval = -4;
        goto errout;
    }
    return fd;//返回监听描述符

errout:
    err = errno;
    close(fd);
    errno = err;
    return rval;
}

int serv_accept(int listenfd,uid_t * uidptr)//接受一个unix域套接字的连接请求，返回新生成用于通讯的套接字
{
    int clifd, err, rval;
    socklen_t len;
    time_t staletime;
    struct sockaddr_un un;
    struct stat statbuf;
    char * name;

    if ((name = malloc(sizeof(un.sun_path) + 1)) == NULL)
        return -1;
    len = sizeof(un);
    if ((clifd = accept(listenfd,(struct sockaddr *)&un,&len)) < 0) {
        free(name);
        return -2 ;
    }

    len -= __offsetof(struct sockaddr_un,sun_path);
    memcpy(name,un.sun_path,len);//这里的sun_path很有可能不是0结尾的，所以不能用strlen(un.sun_path)代替len
    name[len] = 0;
    if (stat(name,&statbuf) < 0) {
        printf("stat error: %s",strerror(errno));
        rval = -3;
        goto errout;
    }

#ifdef S_ISSOCK //查看该文件是不是套接字，由于有些系统没哟定义该宏所以可以跳过此检测
    if (S_ISSOCK(statbuf.st_mode) == 0)
    {
        printf("S_ISSOCK error: %s",strerror(errno));
        rval = -4;
        goto errout;
    }

#endif
    staletime = time(NULL) - STALE;
    if (statbuf.st_atimespec.tv_sec < staletime || statbuf.st_ctimespec.tv_sec < staletime || statbuf.st_mtimespec.tv_sec < staletime) {
        printf("time error: %s",strerror(errno));
        rval = -5;
        goto  errout;
    }

    if (uidptr != NULL)
        *uidptr = statbuf.st_uid;

    //unlink(name);
    free(name);
    return clifd;

errout:
    err = errno;
    close(clifd);
    free(name);
    errno = err;
    return rval;
}

int cli_conn(const char * name) //用于客户端，与服务器端进行连接
{
    int fd, len, err, rval;
    struct sockaddr_un un,sun;
    int do_unlink = 0;

    if (strlen(name) >= sizeof(un.sun_path)) {
        errno = ENAMETOOLONG;
        return -1;
    }

    if ((fd = socket(AF_UNIX,SOCK_STREAM,0)) < 0) {
        return -1;
    }
    memset(&un,0, sizeof(un));
    un.sun_family = AF_UNIX;
    sprintf(un.sun_path, "%s%s", CLI_PATH, "client");
    len = __offsetof(struct sockaddr_un,sun_path) + strlen(un.sun_path);
    unlink(un.sun_path);

    if (bind(fd, (struct sockaddr *)&un, len) < 0) {
        printf("bind error: %s",strerror(errno));
        rval = -2;
        goto errout;
    }

    if (chmod(un.sun_path, CLI_PERM) < 0) {
        printf("chmod error: %s",strerror(errno));
        rval = -3;
        do_unlink = 1;
        goto errout;
    }

    memset(&sun, 0, sizeof(sun));
    sun.sun_family = AF_UNIX;
    strcpy(sun.sun_path, name);
    len = __offsetof(struct sockaddr_un,sun_path) + strlen(name);
    if (connect(fd, (struct sockaddr *)&sun, len) < 0) {
        printf("%s\n",strerror(errno));
        rval = -4;
        do_unlink = 1;
        goto errout;
    }
    return fd;

errout:
    err = errno;
    close(fd);
    if (do_unlink)
        unlink(un.sun_path);
    errno = err;
    return rval;
}

#endif //LINUX_UNIX_SOCKET_API_H
