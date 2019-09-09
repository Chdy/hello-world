//
// Created by 邓岩 on 28/03/2018.
//
/*--------------------------------------------
 * html中使用get方法，尚不会写能够得到post传值的程序
 *
 --------------------------------------------*/
#include <stdio.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>

void not_found(int client);
void unimplemented(int client);
int bindsocket(char * port);
int readline(int fd,char * buf);
void handle_request(int sock);
int get_line(int sock, char *buf, int size);

void hand(int sig)
{
    while((sig = waitpid(-1,NULL,WNOHANG))>0)
    {
        //printf("reap the process %d\n",sig);
        continue;
    }
}

int bindsocket(char * port)
{
    in_port_t len;
    socklen_t namelen;
    struct addrinfo hints,* result;
    struct sockaddr_in name;
    int server = socket(AF_INET,SOCK_STREAM,0);
    /*hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE|AI_ADDRCONFIG|AI_NUMERICSERV;
    hints.ai_protocol = 0;
    if(getaddrinfo(NULL,port,&hints,&result)==-1)
    {
        printf("getaddrinfo error");
        exit(-1);
    }*/
    name.sin_family = AF_INET;
    name.sin_port = htons(atoi(port));
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(server,(struct sockaddr *)&name, sizeof(struct sockaddr_in))==0)
    {
        getsockname(server, (struct sockaddr *)&name, &namelen);
        printf("httpd opened using port %d ip %s\n",htons(name.sin_port),inet_ntoa(name.sin_addr));
    }
    else
    {
        printf("bind error\n");
        exit(-1);
    }
   // freeaddrinfo(result);
    if(listen(server,5)==-1)
        exit(-1);
    return server;
}

void serve_file(int sock,char * path)
{
    int n,fl;
    char buf[1024];
    int fd;
    if((fd = open(path,O_RDONLY))==-1)
        not_found(sock);
    fcntl(sock,F_GETFL,&fl);
    fl |= O_NONBLOCK;
    fcntl(sock,F_SETFL,fl);
    while(read(sock,buf,1024)!=-1);
    strcpy(buf, "HTTP/1.0 200 OK\r\n");
    send(sock, buf, strlen(buf), 0);
    strcpy(buf,"Server: dyhttpd/0.1.0" );
    send(sock, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(sock, buf, strlen(buf), 0);
    strcpy(buf, "\r\n");
    send(sock, buf, strlen(buf), 0);
    printf("serve\n");
	while(n = read(fd,buf,1024))
    {
        send(sock,buf,n,0);
    }
	printf("serve_file\n");
    close(fd);
}

/*void excute_cgi(int sock,char * path,char * arg)
{
    char buf[1024];
    printf("arg = %s\n",arg);
    int i = 0,j = 0,fl;
    while(arg[i++]!='&');
    arg[i-1] = 0;
    fcntl(sock,F_GETFL,&fl);
    fl |= O_NONBLOCK;
    fcntl(sock,F_SETFL,fl);
    while(read(sock,buf,1024)!=-1);

    /*while(read(sock,buf,1024)!=-1);
    while(arg[j++] != '=');
    while(arg[i++] != '=');
    if(!strcmp(arg+j,"837123564"))
        if(!strcmp(arg+i,"123456"))
        {
            strcpy(buf, "HTTP/1.0 200 OK\r\n");
            send(sock, buf, strlen(buf), 0);
            strcpy(buf,"Server: dyhttpd/0.1.0" );
            send(sock, buf, strlen(buf), 0);
            sprintf(buf, "Content-Type: text/html\r\n");
            send(sock, buf, strlen(buf), 0);
            sprintf(buf,"login success\n");
            send(sock,buf,strlen(buf),0);
        }
    close(sock);
}*/

void execute_cgi(int client, const char *path,
                 const char *method, const char *query_string)
{
    char buf[1024];
    int cgi_output[2];
    int cgi_input[2];
    pid_t pid;
    int status;
    int i = 0;
    char c;
    int numchars = 1;
    int content_length = -1;

    buf[0] = 'A'; buf[1] = '\0';
    if (strcasecmp(method, "GET") == 0)//如果是get就抛弃掉客户端发来的所有数据
        while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
            numchars = readline(client, buf) ;
    else    //如果是post读取参数长度
    {
        numchars = readline(client, buf) ;
        while ((numchars > 0) && strcmp("\n", buf))
        {
            buf[15] = '\0';
            if (strcasecmp(buf, "Content-Length:") == 0)
                content_length = atoi(&(buf[16]));
            numchars = readline(client, buf) ;
        }
        printf("content-length%d\n",content_length);
        if (content_length == -1) {
            return;
        }
    }

    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    send(client, buf, strlen(buf), 0);

    if (pipe(cgi_output) < 0) {
        return;
    }
    if (pipe(cgi_input) < 0) {
        return;
    }

    if ( (pid = fork()) < 0 ) {
        return;
    }
    if (pid == 0)  /* child: CGI script */
    {
        char meth_env[255];
        char query_env[255];
        char length_env[255];

        dup2(cgi_output[1], 1);
        dup2(cgi_input[0], 0);
        close(cgi_output[0]);
        close(cgi_input[1]);
        sprintf(meth_env, "REQUEST_METHOD=%s", method);
        putenv(meth_env);
        if (strcasecmp(method, "GET") == 0) {
            sprintf(query_env, "QUERY_STRING=%s", query_string);
            putenv(query_env);
        }
        else {   /* POST */
            sprintf(length_env, "CONTENT_LENGTH=%d", content_length);
            putenv(length_env);
        }
        execl(path, path, NULL);
        exit(0);
    } else {    /* parent */
        close(cgi_output[1]);
        close(cgi_input[0]);
        if (strcasecmp(method, "POST") == 0)
            for (i = 0; i < content_length; i++) {
                recv(client, &c, 1, 0);
                printf("%c",c);
                write(cgi_input[1], &c, 1);
            }
        printf("\nsend:");
        //usleep(100000);
        //serve_file(client,"/Users/dengyan/test");
	//int fd = open("./date",O_WRONLY|O_TRUNC);
	//printf("fd = %d\n",fd);
        /*while ((i = read(cgi_output[0], buf, 1024)) != 0)//不知为何非要先将数据写到文件然后读取，客户端才能成功接受数据
        {
            printf("%dbyte",i);
            //send(client, buf, i, 0);
            write(fd,buf,i);
        }
	*/
	usleep(100000);
        serve_file(client,"./date");
        //printf("ok\n");
        close(cgi_output[0]);
        close(cgi_input[1]);
    }
}



void handle_request(int sock)
{
    int n,cgi = 0,fl;
    struct stat st;
    char * url;
    char buf[1024];
    char method[255];
    char path[255];
    n = readline(sock,buf);
    //printf("all url %s\n",buf); 这行代码导致程序运行出现异常，在telnet输入 GET /无反应
    int i = 0,j = 0;
    while(!isspace(buf[i]))
    {
        method[j++] = buf[i++];
    }
    method[j] = 0;
    if(strcmp(method,"GET")&&strcmp(method,"POST"))
        unimplemented(sock);
    while(isspace(buf[i++]));
    url = buf+i-1;
    while(!isspace(buf[i++]));
    buf[i-1] = 0;
    if(!strcasecmp(method,"GET"))
    {
        j = 0;
        while(url[j])
        {
            if(url[j++]=='?')
            {
                cgi = 1;
                url[j-1] = 0;//j开始为参数
                break;
            }
        int fd = open("/root/date",O_WRONLY|O_TRUNC);}
    }
    printf("url = %s\n",url);
    printf("method = %s\n",method);
    printf("pwd = %s\n",getwd(NULL));
    sprintf(path,"www%s",url);
    if(path[strlen(path)-1] == '/')//以域名直接访问时，默认会以/结尾
        strcat(path,"index.html");//在/后加上主页名
    printf("path = %s\n",path);
    if(stat(path,&st)!=0)
    {
        fcntl(sock,F_GETFL,&fl);
        fl |= O_NONBLOCK;
        fcntl(sock,F_SETFL,fl);
        while(read(sock,buf+512,512)!=-1);
        printf("not found\n");
        not_found(sock);
    } else {
        if ((st.st_mode & S_IXUSR) ||
            (st.st_mode & S_IXGRP) ||
            (st.st_mode & S_IXOTH))
            cgi = 1;
        if (cgi) {
            printf("execute cgi\n");
            execute_cgi(sock,path,method,url+j);
        }
        else {
		printf("se\n");//shaole zheyang wufa fasong shuju ,gaobudong
            serve_file(sock, path);
        }
    }
    close(sock);
}

int readline(int fd,char * buf)
{
    char c = 0;
    int n = 0;
    while(read(fd,&c,1)&&c!='\n')
    {
        if(c=='\r')
            c = '\n';
        buf[n++] = c;
    }
    if(buf[n-1] == '\n')
        buf[n] = 0;
    else
    {
        buf[n] = '\n';
        buf[++n] = 0;
    }
    return n;
}

void not_found(int client)
{
    char buf[1024];
    sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Server: dyhttpd/0.1.0");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "your request because the resource specified\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "is unavailable or nonexistent.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

void unimplemented(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Server: dyhttpd/0.1.0");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</TITLE></HEAD>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>HTTP request method not supported.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}

int main(int argc,char ** argv)
{
    char tport[6];
    char * port;
    setbuf(stdout,NULL);
    if(argc == 2)
        port = argv[1];
    else
    {
        printf("please input the port number:");
        scanf("%s",tport);
        port = tport;
    }
    struct sigvec sigv;
    pthread_t pthread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    struct sockaddr_in client;
    int sock,listensock;
    socklen_t len;
    sigv.sv_handler = hand;
    sigv.sv_flags = 0;
    sigv.sv_mask = 0;
    sigvec(SIGCHLD,&sigv,NULL);
    signal(SIGPIPE,SIG_IGN);
    listensock = bindsocket(port);
    while(1)
    {
        if((sock = accept(listensock,(struct sockaddr *)&client,&len))==-1)
        {
            printf("linkerror");
            exit(-1);
        }
        printf("link to %s\n",inet_ntoa(client.sin_addr));
        int b = pthread_create(&pthread,&attr,handle_request,sock);
    }
}
