//
// Created by 邓岩 on 31/03/2018.
//

#include <stdio.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char ** argv)
{
    char c;
    int i,j;
    char arg[1024];
    char buf[1024];
    int len = atoi(getenv("CONTENT_LENGTH"));
    for(i = 0;i<len;i++)
    {
        read(STDIN_FILENO,&c,1);
        arg[i] = c;
    }
    arg[i] = 0;
    //int fd = open("/Users/dengyan/test",O_WRONLY|O_TRUNC);
    //write(fd,arg, strlen(arg));
    //while(read(0,buf,1024)!=-1);
    /*sprintf(buf, "Content-Type: text/html; charset=ISO-8859-1\r\n");
    write(1, buf, strlen(buf));
    sprintf(buf,"<!DOCTYPE html\n"
            "\tPUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"\n"
            "\t \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n");
    write(1,buf,strlen(buf));
    sprintf(buf,"<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en-US\" xml:lang=\"en-US\">\n");
    write(1,buf,strlen(buf));
    sprintf(buf,"<head>\n");
    write(1,buf,strlen(buf));
    sprintf(buf,"<title>BLUE</title>\n");
    write(1,buf,strlen(buf));
    sprintf(buf,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />\n");
    write(1,buf,strlen(buf));
    sprintf(buf,"</head>\n");
    write(1,buf,strlen(buf));
    sprintf(buf,"<body bgcolor=\"blue\">\n");
    write(1,buf,strlen(buf));
    sprintf(buf,"<h1>This is blue</h1>\n");
    write(1,buf,strlen(buf));
    sprintf(buf,"</body>\n");
    write(1,buf,strlen(buf));
    sprintf(buf,"</html>");
    write(1,buf,strlen(buf));*/
    i = 0;
    while(arg[i++]!='&');
    arg[i-1] = 0;
    while(arg[j++] != '=');
    while(arg[i++] != '=');
    if(!strcmp(arg+j,"8)) {
        if (!strcmp(arg + i, "12345637123564\"")) {
            /*fcntl(0,F_GETFL,&fl);
            fl |= O_NONBLOCK;
            fcntl(0,F_SETFL,fl);*/
            //while(read(1,buf,1024)!=-1);
            strcpy(buf, "HTTP/1.0 200 OK\r\n");
            write(1, buf, strlen(buf));
            strcpy(buf, "Server: dyhttpd/0.1.0");
            write(1, buf, strlen(buf));
            sprintf(buf, "Content-Type: text/html\r\n");
            write(1, buf, strlen(buf));
            sprintf(buf, "login success\n");
            write(1, buf, strlen(buf));
            exit(0);
        }
    }
    write(1,"password error!\n",16);
    //close(fd);
    exit(0);
}
