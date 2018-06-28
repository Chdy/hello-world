//
// Created by 邓岩 on 30/05/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

void printPath(int inode);
void inum_to_name(int inum,char * buf,int size);
int get_inode(char * name);

int main(int argc,char ** argv)
{
    printPath(get_inode("."));
    printf("\n");
    return 0;
}

void printPath(int inode)
{
    char buf[100];
    int pnode;
    chdir("..");
    if(get_inode(".")!=inode) {
        inum_to_name(inode,buf,100);
        pnode = get_inode(".");
        printPath(pnode);
        printf("/%s",buf);
    }
}

void inum_to_name(int inum,char * buf,int size)
{
    DIR * dirptr;
    struct dirent * dir_item;
    if((dirptr = opendir("."))==EOF)
        fprintf(stderr,"cant open the dir");
    while(dir_item = readdir(dirptr))
    {
        if(dir_item->d_ino==inum)
        {
            strcpy(buf,dir_item->d_name);
            return;
        }
    }
}

int get_inode(char * name)
{
    struct stat info;
    stat(name,&info);
    return info.st_ino;
}