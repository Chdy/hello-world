//
// Created by 邓岩 on 13/06/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

struct node
{
    int x;
    int y;
    struct node * prev;
};

int x;
int y;

int main(void)
{
    initscr();
    clear();
    standout();
    keypad(stdscr,TRUE);
    char a = 67,b;
    int x_add = 0;
    int y_add = 2;
    struct winsize win;
    ioctl(0,TIOCGWINSZ,&win);
    struct node * head,* end,* tmp;
    x = LINES/2;
    y = COLS/2;
    int i = fcntl(0,F_GETFL);
    i |= O_NONBLOCK;
    fcntl(0,F_SETFL,i);
    for (int i = 2; i > -3; --i) {
        tmp = (struct node *)malloc(sizeof(struct node));
        tmp->x = x;
        tmp->y = y+2*i;
        move(x,y+2*i);
        addstr("  ");
        if(head==NULL)
        {
            head = tmp;
            end = tmp;
        }
        tmp->prev = end;
        end = tmp;
    }
    while(1) {
        refresh();
        usleep(200000);
        while (read(0, &b, 1) != EOF) {
            if (b == 27)
                continue;
            else if (b == 79)
                continue;
            if (b == 65)//上
            {
                if (a == b || a == b + 1)
                    continue;
                x_add = -1;
                y_add = 0;
                a = 65;
            } else if (b == 66)//下
            {
                if (a == b || a == b - 1)
                    continue;
                x_add = 1;
                y_add = 0;
                a = 66;
            } else if (b == 68)//左
            {
                if (a == b || a == b - 1)
                    continue;
                x_add = 0;
                y_add = -2;
                a = 68;
            } else if (b == 67)//右
            {
                if (a == b || a == b + 1)
                    continue;
                x_add = 0;
                y_add = 2;
                a = 67;
            } else;
        }
        standend();
        move(end->x,end->y);
        addstr("  ");
        tmp = end;
        end = end->prev;
        tmp->x = head->x + x_add;
        tmp->y = head->y + y_add;
        if(tmp->x == win.ws_row)
            tmp->x = 0;
        if(tmp->x == -1)
            tmp->x = win.ws_row-1;
        if(tmp->y == win.ws_col)
            tmp->y = 0;
        if(tmp->y < 0)//这里用小于0是因为y如果从0减2会等于-2，所以不能向上面x那样写
            tmp->y = win.ws_col-2;//这里-2也是因为一次横向平移的位移是两个字符单元
        head->prev = tmp;
        tmp->prev = NULL;
        head = tmp;
        move(head->x,head->y);
        standout();
        addstr("  ");
    }
    pause();
    endwin();
}