//
// Created by 邓岩 on 25/03/2018.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int lock_reg(int fd,int cmd,int type,off_t offset,int whence,off_t len)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return fcntl(fd, cmd, &lock);
}

int main(void)
{

    return 0;
}
