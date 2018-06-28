//
// Created by 邓岩 on 09/03/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

# define BUF_SIZE 1025

int main(int argc,char ** argv)
{
    char c;
    struct stat info;
    int oldfile,newfile;
    char buf[BUF_SIZE];
    char newname[60];
    size_t readnum;
    if(argc==4&&!strcmp(argv[1],"-i"))
    {
        argv[1] = argv[2];
        strcpy(newname,argv[3]);
        stat(newname,&info);
        if((info.st_mode&0040000)==0040000)//如果是目录
            strcat(newname,argv[1]);
        if((newfile = open(newname,O_RDONLY|O_CREAT|O_EXCL,S_IREAD|S_IWUSR|S_IRGRP|S_IROTH))==EOF)
        {
            if(errno==EEXIST)
            {
                printf("This file is exit,do you want to cover it? [yes or no] ");
                scanf("%c",&c);
                if(c=='y')
                {
                    if((oldfile=open(argv[1],O_RDONLY))==EOF)
                    {
                        printf("Dont find the source_file");
                        exit(-1);
                    }
                    if((newfile=open(newname,O_WRONLY|O_CREAT|O_TRUNC,S_IREAD|S_IWUSR|S_IRGRP|S_IROTH))==EOF)
                    {
                        printf("Dont find the destination");
                        exit(-1);
                    }
                    while((readnum=read(oldfile,buf,BUF_SIZE))>0)
                        if(write(newfile,buf,readnum)!=readnum)
                            exit(-1);
                    close(oldfile);
                    close(newfile);
                    exit(EXIT_SUCCESS);
                }
                else
                {
                    printf("Dont find the destination");
                    exit(-1);
                }
            }
            else
            {
                if((oldfile=open(argv[1],O_RDONLY))==EOF)
                {
                    printf("Dont find the source_file");
                    exit(-1);
                }
                while((readnum=read(oldfile,buf,BUF_SIZE))>0)
                    if(write(newfile,buf,readnum)!=readnum)
                        exit(-1);
                close(oldfile);
                close(newfile);
                exit(EXIT_SUCCESS);
            }
        }
    }
    if(argc<3)
    {
        printf("Parameter number is not matching");
        exit(-1);
    }
    if((oldfile=open(argv[1],O_RDONLY))==EOF)
    {
        printf("Dont find the source_file");
        exit(-1);
    }
    strcpy(newname,argv[2]);
    stat(newname,&info);
    if((info.st_mode&0040000)==0040000)
        strcat(newname,argv[1]);
    if((newfile=open(newname,O_WRONLY|O_CREAT|O_TRUNC,S_IREAD|S_IWUSR|S_IRGRP|S_IROTH))==EOF)
    {
        printf("Dont find the destination");
        exit(-1);
    }
    while((readnum=read(oldfile,buf,BUF_SIZE))>0)
        if(write(newfile,buf,readnum)!=readnum)
            exit(-1);
    close(oldfile);
    close(newfile);
    exit(EXIT_SUCCESS);
}