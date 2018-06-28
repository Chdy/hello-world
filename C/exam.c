# include <stdlib.h>
# include <stdio.h>
# include <curses.h>
# include <fcntl.h>
# include <unistd.h>
# include <time.h>
// 如果此时蛇的行走方向是上，如果以特别快的速度连按左下和右下，是可以让蛇逆向走的，这是因为这个操作改变了bb字符
int * start;
int * end;

typedef struct position
{
    int l;
    int c;
    struct position * next;
}position;

int main(void)
{
    int bb = 0;
	int i = 0,j = 2;
	int ti = 0,tj = 0;
	char b;
	int fd = open("/dev/tty",O_RDWR|O_NONBLOCK);
	if(fd==EOF)
		exit(-1);
	initscr();
    cbreak();
    keypad(stdscr,TRUE);
    srand(time(NULL));
    int x = rand()%44;
    x += 20;
    int y = rand()%120;
    y += 20;
    move(x,y);
    position * p;
    position * start = (position *)malloc(sizeof(position));
    start->l = LINES/2;
    start->c = COLS/2;
    start->next = NULL;
    position * end = (position *)malloc(sizeof(position));
    end->l = LINES/2;
    end->c = COLS/2-2;
    end->next = start;
    standout();
    move(LINES/2,COLS/2);
    addstr("  ");
    move(LINES/2,COLS/2-2);
    addstr("  ");
    refresh();
	while(1)
	{
        while(read(fd,&b,1)!=EOF)
        {
            if(bb==b+1||bb==b-1)
                continue;
            if(b==27)
                continue;
            else if(b==79)
                continue;
            if(b==65)//上
            {
                bb = b;
                i = -1;
                j = 0;
            }
            else if(b==66)//下
            {
                bb = b-2;
                i = 1;
                j = 0;
            }
            else if(b==68)//左
            {
                bb = b;
                i = 0;
                j = -2;
            }
            else if(b==67)//右
            {
                bb = b+2;
                i = 0;
                j = 2;
            }
            else
                ;
        }
		ti += i;
		tj += j;
        move(end->l,end->c);
        standend();
        addstr("  ");
        move(LINES/2+ti,COLS/2+tj);
        standout();
        addstr("  ");
        p = start;
        start = end;
        end = end->next;
        p->next = start;
        start->l = LINES/2+ti;
        start->c = COLS/2+tj;
        refresh();
        usleep(300000);
        //clear();
	}
	endwin();
	return 0;
}
