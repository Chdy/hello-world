//
// Created by 邓岩 on 13/06/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(void)
{
    int i;
    char * p[5] = {0};
    char buf[1024];
    while(1)
    {
        i = 0;
        printf("please input the instructment:");
        fflush(stdout);
        if(fork())
        {
            wait(NULL);
        } else {
            int a = read(0, buf, 1024);
            buf[a - 1] = 0;
            while ((p[i] = strrchr(buf, ' ')) != NULL) {
                *(p[i++]++) = 0;
            }
            p[i] = buf;
            printf("%s", p[i]);
            execlp(p[i], p[i], ((--i) < 0) ? 0 : p[i], ((--i) < 0) ? 0 : p[i], ((--i) < 0) ? 0 : p[i],
                   ((--i) < 0) ? 0 : p[i]);
        }
    }
}