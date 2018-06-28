//
// Created by 邓岩 on 13/06/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main(void)
{
    initscr();
    clear();
    char a,b,bb;
    int xmoved,ymoved;
    xmoved = ymoved = 0;
    int x_dir,y_dir;
    x_dir = y_dir = 1;
    int x_pos,y_pos;
    x_pos = LINES/2;
    y_pos = 10;
    int y_speed,y_cur;
    y_speed = y_cur = 5;
    int x_speed,x_cur;
    x_speed = x_cur = 8;
    int timerval = 100000;
    int i = fcntl(0,F_GETFL);
    i |= O_NONBLOCK;
    fcntl(0,F_SETFL,i);
    move(x_pos,y_pos);
    addch('o');
    while(1)
    {
        usleep(timerval);
        refresh();
        while(read(0,&b,1)!=EOF)
        {
            if(b==27)
                continue;
            else if(b==79)
                continue;
            if(b==65)//上
            {
                y_speed--;
            }
            else if(b==66)//下
            {
                y_speed++;
            }
            else if(b==68)//左
            {
                x_speed--;
            }
            else if(b==67)//右
            {
                x_cur++;
            }
            else
                ;
        }
        if(x_speed>0&&x_cur--==1)
        {
            x_cur = x_speed;
            x_pos += x_dir;
            xmoved = 1;
        }
        if(y_speed>0&&y_cur--==1)
        {
            y_cur = y_speed;
            y_pos += y_dir;
            ymoved = 1;
        }
        if(xmoved || ymoved)
        {
            if(xmoved == 1)
                mvaddch(x_pos-x_dir,y_pos,' ');
            if(ymoved == 1)
                mvaddch(x_pos,y_pos-y_dir,' ');
            if(xmoved && ymoved)
                mvaddch(x_pos-x_dir,y_pos-y_dir,' ');
            move(x_pos,y_pos);
            addch('o');
            xmoved = ymoved = 0;
        }
        if(y_pos > COLS-1 || y_pos < 1)
        {
            x_dir = -x_dir;
        }
        if(x_pos < 0 || x_pos > LINES-10) {
            y_dir = -y_dir;
        }
    }
    endwin();
    return 0;
}
