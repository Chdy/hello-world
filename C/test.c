//
// Created by Vain loser on 26/11/2016.
//

#include <stdio.h>
#include <stdlib.h>
struct student
{
    int num;
    int age;
    struct student *next;
};
struct student *c;
void insert_node(struct student **head,struct student *p);
void traverse(struct student *head);
void delete_node(struct student *head);
void convert(struct student **head);
int main(void)
{
    setbuf(stdout,NULL);
    struct student *h = NULL,*q,*p;
    int i,n;
    puts("请输入学生人数:");
    scanf("%d",&n);
    getchar();
    printf("输入%d个学生的信息:\n",n);
    for(i=0;i<n;i++){
        q = (struct student *)malloc(sizeof(struct student));
        printf("输入第%d个学生信息\n",i+1);
        scanf("%d%d",&q->num,&q->age);
        getchar();
        if(i == 0)
        {
            h = q;
            p = q;
            continue;
        }
        insert_node(&p,q);
        printf("%d",p->next->age);
        p = q;
    }
    puts("输出学生的信息");
    traverse(h);
    convert(&h);
    //traverse(h);
    while(h->next)
        delete_node(h);
    free(h);
    h=NULL;
    return 0;
}
void insert_node(struct student **head,struct student *p)
{
    p->next = NULL;
    (*head)->next = p;
}
void traverse(struct student *head)
{
    struct student *p;
    p = head;
    puts("num\t\tage");
    while(p){
        printf("%d\t\t%d\n",p->num,p->age);
        p=p->next;
    }
}
void delete_node(struct student *head)
{
    struct student *p;
    p=head->next;
    head->next=p->next;
    printf("删除学号为%d的学生\n",p->num);
    free(p);
    p=NULL;
}
void convert(struct student **head){
    if(NULL==(*head)|| NULL==(*head)->next) return;    //少于两个节点没有反转的必要。
    struct student* p;
    struct student* q;
    struct student* r;
    p = *head;
    q = (*head)->next;
    (*head)->next = NULL; //旧的头指针是新的尾指针，next需要指向NULL
    while(q){
        r = q->next; //先保留下一个step要处理的指针
        q->next = p; //然后p q交替工作进行反向
        p = q;
        q = r;
    }
    (*head)=p; // 最后q必然指向NULL，所以返回了p作为新的头指针
    traverse(*head);
}
