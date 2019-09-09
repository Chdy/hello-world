//
// Created by 邓岩 on 2018/11/12.
//
# include </Users/dengyan/ClionProjects/Linux/linux.h>

#define WHITE 0
#define BLACK 1

typedef struct {
    int x;
    int y;
}position;

typedef struct qnode
{
    position cur;
    struct qnode * next;
}Node,*pNode;

typedef struct queue
{
    struct qnode * front;
    struct qnode * rear;
}Queue,*pQueue;

typedef struct {
    int color;
    position cur;
    position parent;
}node;

void init_queue(pQueue);
void push_queue(pQueue,position);
int pop_queue(pQueue,position *);
void traverse_queue(pQueue);
void destroy_queue(pQueue);


node rc[22][22];

char maze[22][22];

void BFS()
{
    Queue T;
    init_queue(&T);
    position start = {1, 1};
    rc[1][1].color = BLACK;
    push_queue(&T, start);
    position tmp;
    int direct[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    while (T.front != T.rear) {
        pop_queue(&T, &tmp);
        for (int i = 0; i < 4; ++i) {
            int x = tmp.x + direct[i][0];
            int y = tmp.y + direct[i][1];
            if (maze[x][y] == '0' || maze[x][y] == 0) //一个可选的办法是在迷宫周围增加一圈0
                continue;
            if (rc[x][y].color == WHITE) {
                position cur = {x, y};
                push_queue(&T, cur);
                rc[x][y].parent = tmp;
                rc[x][y].color = BLACK;
            }
        }
    }
}

void print_path(position start, position end)
{
    if (start.x == end.x && start.y == end.y) {
        printf("%d %d\n",start.x - 1, start.y - 1);
    }
    else if (rc[end.x][end.y].parent.x == 0) {
        printf("Path cant pass");
    } else {
        print_path(start, rc[end.x][end.y].parent);
        printf("%d %d\n",end.x - 1, end.y - 1);
    }
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    char buf[1000];
    int fd[2];
    int pid;
    socketpair(AF_UNIX, SOCK_DGRAM, 0, fd);
    if((pid = fork()) == 0) {
        if (dup2(fd[0],0) != 0) {
            printf("error %s",strerror(errno)); //0读
            exit(-1);
        }
        close(fd[0]);
        if (dup2(fd[1],1) != 1) {
            printf("error %s",strerror(errno)); //1写
            exit(-1);
        }
        close(fd[1]);
        execlp("/Users/dengyan/PycharmProjects/Py/Maze.py",(char *)(0));
    } else { //1写 0读
        int i;
        int n = 1;
        while (i = read(fd[0], buf, 100)) {
            if(!strncmp(buf,"Please enter any key to exit",i))
                break;
            memcpy(maze[n++] + 1, buf, i - 1);
        }
        for (int j = 0; j < 22; ++j) {
            for (int k = 0; k < 22; ++k) {
                printf("%c ", maze[j][k]);
            }
            printf("\n");
        }
        BFS();
        position start = {1, 1};
        position end = {20, 20};
        print_path(start, end);
        getchar();
        write(fd[1],"w\n",2);
    }
    return 0;
}

void destroy_queue(pQueue p)
{
    pNode r = p->rear;
    while(p->rear != p->front)
    {
        p->rear = r->next;
        free(r);
        r = p->rear;
    }
    free(r);
}

void traverse_queue(pQueue p)
{
    int i = 1;
    pNode q = p->rear;
    while(q != p->front)
    {
        printf("第%d个数为%d\n",i++,q->cur.x);
        q = q->next;
    }
}

int pop_queue(pQueue p,position * val)
{
    if( p->front == p->rear )
    {
        printf("队列为空，删除失败！\n");
        return 0;
    }
    *val = p->rear->cur;
    pNode r = p->rear;
    p->rear = p->rear->next;
    free(r);
    return 1;
}

void push_queue(pQueue p,position val)
{
    pNode pNew = (pNode)malloc(sizeof(Node));
    p->front->cur = val;
    p->front->next = pNew;
    p->front = pNew;
}

void init_queue(pQueue p)
{
    p->front = (pNode)malloc(sizeof(Node));
    if(p->front == NULL)
    {
        printf("分配失败！\n");
        exit(-1);
    }
    p->front->next = NULL;
    p->rear = p->front;
}