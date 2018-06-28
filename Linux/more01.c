//
// Created by 邓岩 on 06/03/2017.
//

# include <stdio.h>
# include <stdlib.h>

# define PAGELEN 24
# define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);
int main(int argc,char ** argv)
{
    FILE * fp;
    if(argc==1)
        do_more(stdin);
    else
        while(--argc)
        if((fp = fopen(*++argv,"r"))!=NULL)
        {
            do_more(fp);
            fclose(fp);
        }
        else
            exit(-1);
    return 0;
}

void do_more(FILE * fp)
{
    char line[LINELEN];
    int reply;
    FILE * tty;
    if((tty = fopen("/dev/tty","r"))==NULL)
        exit(-1);
    int num_of_line = 0;
    while(fgets(line,LINELEN,fp))
    {
        if(num_of_line==PAGELEN)
        {
            reply=see_more(tty);
            if(reply==0)
                break;
            num_of_line-=reply;
        }
        if(fputs(line,stdout)==EOF)
            exit(-1);
        num_of_line++;
    }
}

int see_more(FILE * tty)
{
    char c;
    printf("\033[7m more? \033[m");
    while((c=getc(tty))!=EOF)
    {
        if(c=='q')
            return 0;
        if(c==' ')
            return PAGELEN;
        if(c=='\n')
            return 1;
    }
}