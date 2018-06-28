//
// Created by 邓岩 on 02/06/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>
# include <termios.h>

int get_response(char * question)
{
    char c;
    int maxtries = 50;
    printf("%s (y/n)?",question);
    fflush(stdout);
    while(1)
    {
        usleep(100000);
        while((c = getchar())!=EOF&&strchr("YyNn",c)==NULL)
            maxtries = 50;
        if(c == 'y')
            return 0;
        if(c == 'n')
            return 1;
        if(maxtries-- == 0)
            return 2;
    }
}

set_crmode()
{
    struct termios ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&ttystate);
}

tty_mode(int how)
{
    static struct termios original_mode;
    if(how==0)
        tcgetattr(0,&original_mode);
    else
        tcsetattr(0,TCSANOW,&original_mode);
}

set_noblock()
{
    int termflags;
    fcntl(0,F_GETFL);
    termflags |= O_NONBLOCK;
    fcntl(0,F_SETFL,termflags);
}

void sig_handler(int sig)
{
    tty_mode(1);
    exit(1);
}

int main(int argc,char ** argv) {
    int response;
    tty_mode(0);
    set_crmode();
    set_noblock();
    signal(SIGINT,sig_handler);
    signal(SIGQUIT,SIG_IGN);
    response = get_response("Do you want another transaction");
    tty_mode(1);
    return 0;
}