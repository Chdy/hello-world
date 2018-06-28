//
// Created by Vain loser on 03/12/2016.
//
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
int main(void)
{
    int n1 = 0,n2 = 0;
    char * buf,* p;
    char arg1[10],arg2[10],content[1000];
    if((buf = getenv("QUERY_STRING")) != NULL)
    {
        p = strchr(buf,'&');
        *p = '\0';
        strcpy(arg1,buf);
        strcpy(arg2,p+1);
        n1 = atoi(arg1);
        n2 = atoi(arg2);
    }

    sprintf(content,"Welcome to add.com: ");
    sprintf(content,"%sThe Internet addition portal.\r\n<p>",content);
    sprintf(content,"%s,The answer is: %d + %d = %d\r\n<p>",content,n1,n2,n1+n2);
    printf("Content-length: %d\r\n",(int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s",content);
    fflush(stdout);
    exit(0);
}