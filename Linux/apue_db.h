//
// Created by 邓岩 on 2018/10/26.
//

#ifndef LINUX_APUE_DB_H
#define LINUX_APUE_DB_H

typedef void * DBHANDLE;

DBHANDLE db_open(const char *, int, ...); //如果是创建时，需要同时指定O_CREAT和0_TRUNC，不然数据库不会被初始化
void db_close(DBHANDLE); ////关闭数据库，不会对文件有影响
char * db_fetch(DBHANDLE, const char *); //查找数据
int db_store(DBHANDLE, const char *, const char *, int);
int db_delete(DBHANDLE, const char *);
void db_rewind(DBHANDLE);
char * db_nextrec(DBHANDLE, char *);

/* 用于db_store的标志 */
#define DB_INSERT 1
#define DB_REPLACE 2
#define DB_STORE 3

/* 实现限制 */
#define IDXLEN_MIN 6 //最小索引长度，键，分隔符，开始位置，分隔符，长度，换行符，由于索引部分有这六类数据，所以最小是6字节
#define IDXLEN_MAX 1024 //最大索引长度
#define DATLEN_MIN 2
#define DATLEN_MAX 1024
#endif //LINUX_APUE_DB_H
