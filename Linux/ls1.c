//
// Created by 邓岩 on 21/05/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include <sys/ioctl.h>
char * fn;

void show_stat(char * filename,char * dirname)
{
    char buf[1024];
    strcpy(buf,dirname);
    strcat(buf,"/");
    strcat(buf,filename);
    struct stat info;
    stat(buf,&info);
    if((info.st_mode&0170000)==0040000)//如果是目录
        printf("d");
    else
        printf("-");
    for(int i = 8;i>=0;i--)
    {
        if(info.st_mode&1<<i)
            printf("%s",((i%3)?(((i%3)==1)?"w":"r"):"x"));
        else
            printf("-");
    }
    printf("%3d",info.st_nlink);
    printf("%8s",getpwuid(info.st_uid)->pw_name);
    printf("%7s",getgrgid(info.st_gid)->gr_name);
    printf("%7ld",(long)info.st_size);
    printf("%.13s",ctime(&info.st_mtimespec)+3);
    printf(" %s",filename);
    printf("\n");
}

int strsort(const char ** a,int len)
{
    const char * ptr;
    for (int i = 0; i < len; ++i) {
        for (int j = i+1; j < len; ++j) {
            if(strcmp(a[i],a[j])>0)
            {
                ptr = a[i];
                a[i] = a[j];
                a[j] = ptr;
            }
        }
    }
}

void do_ls(char * dirname,int l)
{
    char * buf[1000];
    char s[1000];
    int i = 0;
    int size = 0;
    int tsize;
    DIR * dir_ptr;
    struct dirent * dir_item;
    if((dir_ptr = opendir(dirname))==NULL)
    {
        fprintf(stderr,"cant open the directory %s\n",dirname);
        exit(1);
    }
    if(l == 0) {
        int col;
        struct winsize info;
        ioctl(STDIN_FILENO,TIOCGWINSZ,&info);//获取终端尺寸
        while (dir_item = readdir(dir_ptr)) {
            tsize = (int) strlen(dir_item->d_name);
            if (size < tsize) {
                size = tsize;
            }
            buf[i] = (char *) malloc(tsize + 1);
            strcpy(buf[i++], dir_item->d_name);
        }
        strsort(buf,i-1);
        col = info.ws_col/(size+1);
        s[0] = '%';
        s[1] = '-';
        strcat(s,itoa(size+1));
        strcat(s,"s");
        for (int j = 0; j < i ; ++j) {
            printf(s,buf[j]);
            if((j+1)%col==0)
                printf("\n");
        }
        if(1%col!=0)
            printf("\n");
    }
    else
    {
        while(dir_item = readdir(dir_ptr))
        {
            show_stat(dir_item->d_name,dirname);
        }
    }
    closedir(dir_ptr);
}

int main(int argc,char ** argv) {
    if(argc == 1)
        do_ls(".",0);
    else if(argc == 2) {
        if(strcmp(argv[1],"-l"))
            do_ls(*++argv, 0);
        else
            do_ls(".",1);
    }
    else if(argc == 3 && !strcmp(argv[1],"-l"))
        do_ls(argv[2],1);
}