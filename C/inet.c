//
// Created by Vain loser on 24/11/2016.
//

# include <stdio.h>
# include <stdlib.h>
# include <netinet/in.h> // htonl(struct in_addr) ntohl
# include <arpa/inet.h> //int inet_aton(const char * cp,struct in_addr * inp) 将"点分十进制ip地址(小端法)"转换成16进制的大端法(网络直接顺序)
                       //char * inet_ntoa(struct in_addr in) 将"十六进制的大端法(网络字节顺序)"转换成"点分十进制ip地址"
# include <netdb.h> //struct hostent * gethostbyname(const char * name) struct hostent * gethostbyaddr(const char *addr,int len,0)
/*
 * struct hostent {
                 * char * h_name;
                 * char ** h_aliases;
                 * int h_addrtype;
                 * int h_length;
                 * char ** h_addr_list;
* }
*/
//首先本地IP地址转成本地网络地址，然后转换成发送的大端法型.
//in_addr为整形,为本机网络地址,0x________
int main(int argc,char ** argv)
{
    char **pp;
    struct in_addr addr;
    struct hostent * hostp;
    if(inet_aton(argv[1],&addr)!=0)
        hostp = gethostbyaddr((const char *)&addr,sizeof(addr),AF_INET);
    else
        hostp = gethostbyname(argv[1]);
    printf("offical hostname: %s\n",hostp->h_name);
    for(pp = hostp->h_aliases;*pp!=NULL;pp++)
        printf("alias:%s\n",*pp);
    for(pp = hostp->h_addr_list;*pp!=NULL;pp++)
    {
        addr.s_addr = ((struct in_addr *)*pp)->s_addr;
        printf("address:%s\n",inet_ntoa(addr));
    }
    return 0;
}
//struct in_addr host;
//unsigned int i = 0x8002c2f2;
//host.s_addr = htonl(i);
//const char * b;
//b = inet_ntoa(host);
//printf("host = %s\n",b);
//result:128.2.194.242

//struct in_addr host;
//const char * a = "128.2.194.242";
//inet_aton(a,&host);//IP地址转换网络形式(本机网络地址)以方便打包
//unsigned int b = htonl(host.s_addr);//主机转网络(转换成大端法)
//printf("host = %0x\n",b);
//result:0x8002c2f2