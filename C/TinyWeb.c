//
// Created by Vain loser on 03/12/2016.
//

# include <stdio.h>
# include <stdlib.h>
# include <netinet/in.h>;
# include <unistd.h>
# include <sys/stat.h>
# include <strings.h>
# include <fcntl.h>
# include <sys/mman.h>
/*
 * void* mmap(void* start,size_t length,int prot,int flags,int fd,off_t offset);
 * int munmap(void* start,size_t length);
 */

typedef struct
{
    int rio_fd;
    int rio_cnt;//缓冲区未被读取区域大小
    char * rio_bufptr;//缓冲区有效区头地址
    char rio_buf[8192];//缓冲区域
}rio_t;

void doit(int fd);
void get_filetype(char * filename,char * filetype);
void read_requesthdrs(rio_t * rp);
int parse_uri(char * uri,char * filename,char * cgiargs);
void serve_static(int fd,char * filename,int filesize);
void get_filetype(char * filename,char * filetype);
void serve_dynamic(int fd,char * filename,char * cgiargs);
void clienterror(int fd,char * cause,char * errnum,char * shortmsg,char * longmsg);

int main(int agrc,char **argv)
{
    struct sockaddr_in clientaddr;
    int listenfd,connfd,port,clientlen;
    port = atoi(argv[1]);
    listenfd = open_listenfd(port);
    while(1)
    {
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd,(struct sockaddr *)&clientaddr,(socklen_t *)&clientlen);
        printf("OK\n");
        doit(connfd);
        close(connfd);
    }
}

void doit(int fd)
{
    int a;
    int is_static;
    struct stat sbuf;
    char buf[1000],method[100],uri[100],version[100];
    char filename[100],cgiargs[100];
    rio_t rio;
    rio_readinitb(&rio,fd);
    rio_readlineb(&rio,buf,100);
    sscanf(buf,"%s %s %s",method,uri,version);
    if(strcasecmp(method,"GET"))
    {
        clienterror(fd,method,"501","Not found","Tiny does not implement this method");
        return;
    }
    //read_requesthdrs(&rio);
    is_static = parse_uri(uri,filename,cgiargs);
    if(stat(filename,&sbuf)<0)//文件位置必须与此程序在同一个目录
    {
        clienterror(fd,filename,"404","Not found","Tiny couldn't found this file");
        return;
    }
    if(is_static)
    {
        if(!S_ISREG(sbuf.st_mode) || !(S_IRUSR & sbuf.st_mode))
        {
            clienterror(fd,filename,"403","Forbidden","Tiny couldn't read this file");
            return;
        }
        //get_filetype(filename,filetype);
        //printf("type %s",filename);
        /*sprintf(buf,"HTTP/1.0 200 OK\r\n");
        sprintf(buf,"%sServe: Tiny Web Server\r\n",buf);
        sprintf(buf,"%sContent-length: \r\n",buf);
        sprintf(buf,"%sContent-type:\r\n",buf);
        rio_writen(fd,buf,strlen(buf));*/
        serve_static(fd,filename,sbuf.st_size);
    }
    else
    {
        if(!(S_ISREG(sbuf.st_mode) && (S_IXUSR) & sbuf.st_mode))
        {
            clienterror(fd,filename,"403","Forbidden","Tiny couldn't run this CGI program");
            return;
        }
        serve_dynamic(fd,filename,sbuf.st_size);
    }
}

void serve_dynamic(int fd,char * filename,char * cgiargs)
{
    char buf[1000],*emptylist[] = {NULL};
    sprintf(buf,"HTTP/1.0 200 OK\r\n");
    rio_writen(fd,buf,strlen(buf));
    sprintf(buf,"Serve: Tiny Web Server\r\n");
    rio_writen(fd,buf,strlen(buf));
    if(fork() == 0)
    {
        setenv("QUERY_SREING",cgiargs,1);
        dup2(fd,STDOUT_FILENO);
        execve(filename,emptylist,NULL);
    }
    wait(NULL);
}

void serve_static(int fd,char * filename,int filesize)
{
    int srcfd;
    char * srcp,filetype[100],buf[1000];
    get_filetype(filename,filetype);
    sprintf(buf,"HTTP/1.0 200 OK\r\n");
    sprintf(buf,"%sServe: Tiny Web Server\r\n",buf);
    sprintf(buf,"%sContent-length: %d\r\n",buf,filesize);
    sprintf(buf,"%sContent-type: %s\r\n",buf,filetype);
    rio_writen(fd,buf,strlen(buf));
    srcfd = open("filename",O_RDONLY,0);
    //srcp = mmap(0,filesize,PROT_READ,MAP_PRIVATE,srcfd,0);
    //close(srcfd);
    while(rio_readnb(srcfd,buf,1))
        rio_writen(srcfd,buf,1);
    //munmap(srcp,filesize);
}

void get_filetype(char * filename,char * filetype)
{
    if(strstr(filename,".html"))
        strcpy(filetype,"text/html");
    else if(strstr(filename,".jpg"))
        strcpy(filetype,"image/jpg");
    else if(strcmp(filename,".gif"))
        strcpy(filetype,"image/gif");
    else
        strcpy(filename,"text/plain");
}

void clienterror(int fd,char * cause,char * errnum,char * shortmsg,char * longmsg)
{
    char buf[2000],body[2000];
    sprintf(body,"<html><>title>Tiny error</title>");
    sprintf(body,"%s<body bgcolor=""ffffff"">\r\n",body);
    sprintf(body,"%s%s: %s\r\n",body,errnum,shortmsg);
    sprintf(body,"%s<p>%s: %s\r\n",body,longmsg,cause);
    sprintf(body,"%s<hr><em>The Tiny Web server</em>\r\n",body);

    sprintf(buf,"HTTP/1.0 %s %s\r\n",errnum,shortmsg);
    rio_writen(fd,buf,strlen(buf));
    sprintf(buf,"Content-tyoe: text/html\r\n");
    rio_writen(fd,buf,strlen(buf));
    sprintf(buf,"Content-length: %d\r\n\r\n",strlen(body));
    rio_writen(fd,buf,strlen(buf));
    rio_writen(fd,body,strlen(body));
}

int parse_uri(char * uri,char * filename,char * cgiargs)
{
    char * ptr;
    if(!strstr(uri,"cgi"))
    {
        strcpy(cgiargs,"");
        strcpy(filename,".");
        strcat(filename,uri);//第一个参数必须为数组，而且大小必须大于第一个加上第二个参数的总大小
        if(uri[0] == '/' && uri[1] == '\0')
            strcat(filename,"index.html");
        return 1;
    }
    else
    {
        ptr = strchr(uri,'?');
        if(ptr)
        {
            strcpy(cgiargs,ptr+1);
            *ptr = '\0';
        }
        else
            strcpy(cgiargs,"");
        strcpy(filename,".");
        strcat(filename,uri);
        return 0;
    }
}

void read_requesthdrs(rio_t * rp)
{
    char buf[100];
    rio_readlineb(rp,buf,100);
    printf("%s",buf);
    while(strcmp(buf,"\n"))
    {
        rio_readlineb(rp,buf,100);
        rio_writen(rp->rio_fd,buf,100);
        printf("%s",buf);
    }
    fflush(stdout);
    return;
}