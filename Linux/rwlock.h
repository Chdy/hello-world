//
// Created by 邓岩 on 2018/10/27.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
#ifndef LINUX_RWLOCK_H
#define LINUX_RWLOCK_H
int lock_reg(int fd,int cmd,int type,off_t offset,int whence,off_t len)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return fcntl(fd, cmd, &lock);
}

#define read_lock(fd, offset, whence, len) \
        lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)

#define readw_lock(fd, offset, whence, len)\
        lock_reg(fd, F_SETLKW, F_RDLCK, offset, whence, len)

#define write_lock(fd, offset, whence, len)\
        lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, len)

#define writew_lock(fd, offset, whence, len)\
        lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, len)

#define un_lock(fd, offset, whence, len)\
        lock_reg(fd, F_SETLK, F_UNLCK, offset, whence, len)

#define is_readlock(fd, offset, whence, len)\
            test_lock(fd, F_RDLCK, offset, whence, len)

#define is_writelock(fd, offset, whence, len)\
            test_lock(fd, F_WRLCK, offset, whence, len)

#endif //LINUX_RWLOCK_H
