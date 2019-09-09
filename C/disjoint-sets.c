//
// Created by 邓岩 on 2018/11/19.
//

//不相交集合的链表表示

# include <stdio.h>
# include <stdlib.h>

typedef struct node {
    struct node * next;
    struct set * p;
    char value;
}Node;

typedef struct set {
    struct node * head;
    struct node * tail;
}Set;

Node * make_set(char v)
{
    Set * s = (Set *)malloc(sizeof(Set));
    s->head = s->tail = (Node *)calloc(1, sizeof(Node));
    s->head->value = v;
    s->head->p = s;
    return s->head;
}

Set * union_set(Set * dst, Set * src)
{
    Node * head;

    if (src == NULL)
        return dst;
    head = src->head;
    while (head != NULL) {
        head->p = dst;
        head = head->next;
    }
    dst->tail->next = src->head;
    dst->tail = src->tail;
    free(src);
    return dst;
}

Set * find_set(Node * src)
{
    return src->p;
}

int main(void)
{
    Node * a = make_set('a');
    Node * b = make_set('b');
    Node * c = make_set('c');
    Node * d = make_set('d');
    union_set(find_set(a), find_set(b));
    union_set(find_set(a), find_set(c));
    union_set(find_set(a), find_set(d));
    printf("%c", d->value);
    return 0;
}