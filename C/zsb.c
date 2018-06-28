//
// Created by dengyan on 2018/4/17.
//

# include <stdio.h>
# include <memory.h>
# include <math.h>
# include <stdlib.h>
//# include <sys/time.h>
//# include <fcntl.h>
//# include <unistd.h>

int P2_2(char c)
{
    return c-64+9+15;
}

void P3_4(void)
{
    char buf[10];
    memset(buf,' ',9);
    buf[9] = 0;
    for (int i = 4; i != -1; --i) {
        buf[i] = buf[8-i] = '*';
        printf("%s\n",buf);
    }
}

void P3_5(void)
{
    int x,y,z;
    printf("请输入三个整数:");
    scanf("%d %d %d",&x,&y,&z);
    printf("%f",(x+y+z)/3.);
}

void P3_6(void)
{
    double f;
    printf("请输入华氏温度:");
    scanf("%lf",&f);
    printf("%.2f",5./9*(f-32));
}

void P3_7(void)
{
    double radius;
    printf("请输入圆的半径:");
    scanf("%lf",&radius);
    printf("圆的面积为:%f\n圆的周长为:%f\n",2*3.14*radius,3.14*radius*radius);
}

void P3_8(void)
{
    //太简单又费时间不做
}

void P3_9(void)
{
    int n,sum = 0;
    printf("请输入一个整数:");
    scanf("%d",&n);
    while(n)
    {
        sum += n%10;
        n /= 10;
    }
    printf("%d\n",sum);
}

void P4_1(void)
{
    int a,b;
    printf("请输入两个整数:");
    scanf("%d %d",&a,&b);
    if(a*a+b*b>100)
        printf("%d",a+b);
    else
        printf("%d",a-b);
}

void P4_2(void)
{
    int n;
    printf("请输入一个整数:");
    scanf("%d",&n);
    if(n%(7*5)==0)
        printf("%s","yes");
    else
        printf("%s","no");
}

void P4_3(void)
{
    //太长不写
}

void P4_4(void)
{
    char c;
    printf("请输入一个字符:");
    scanf("%c",&c);
    if(c>='0'&&c<='9')
        printf("%d",c-'0'+15);
    else if(c>='a'&&c<='f')
        printf("%d",c-96+9+15);
    else if(c>='A'&&c<='F')
        printf("%d",c-64+9+15);
    else
        printf("输入错误\n");
}

void P4_5(void)
{
    char c;
    char buf[35];
    memset(buf,'*',34);
    strncpy(buf+14,"Time",4);
    buf[34] = 0;
    printf("%s\n",buf);
    sprintf(buf,"%s\n%s\n%s\n","1 morning","2 afternoon","3 night");
    printf("%s",buf);
    memset(buf,'*',34);
    printf("%s\nplease input your choise:",buf);
    scanf("%c",&c);
    switch (c)
    {
        case '1':
            printf("Good morning\n");
            break;
        case '2':
            printf("Good afternoon\n");
            break;
        case '3':
            printf("Good night\n");
            break;
        default:
            printf("error\n");
    }
}

void P5_1(void)
{
    for (int i = 30; i != 0; i-=2) {
        printf("%4d",i);
    }
}

void P5_2(void)
{
    int tmp,max = 0,min = 0,sum = 0;
    scanf("%d",&tmp);
    min = max = tmp;
    scanf("%d",&tmp);
    if(tmp >= max)
        max = tmp;
    else
        min = tmp;
    for (int i = 0; i != 8; ++i) {
        scanf("%d",&tmp);
        if(tmp <= min)
        {
            sum += min;
            min = tmp;
        }
        else if(tmp >= max)
        {
            sum += max;
            max = tmp;
        }
    }
    printf("%d",sum/8);
}

void P5_3(void)
{
    int sum = 1;
    for (int i = 1; i <= 10; sum*=i,++i);
    printf("%d",sum);
}

void P5_4(void)
{
    int n = 1,sum = 1;
    for (int i = 2; i <= 10; ++i) {
        n *= i;
        sum += n;
    }
    printf("%d",sum);
}

void P5_5(void)
{
    int a,n,sum = 0;
    scanf("%d %d",&a,&n);
    sum = a;
    for (int i = 1; i != n; ++i) {
        a = 10*a+6;
        sum += a;
    }
    printf("%d",sum);
}

void P5_6(void)
{
    double sum = 0;
    int n;
    scanf("%d",&n);
    n *= 2;
    for (int i = 1; i < n; i+=2) {
        sum += 1./i;
    }
    printf("%f",sum);
}

void P5_7(void)
{
    double sum = 0,minus = 1;
    int n;
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) {
        sum += minus/i;
        minus = -minus;
    }
    printf("%f",sum);
}

void P5_8(void)
{
    double sum = 0,i = 2,j = 1;
    for (int k = 0; k != 20; ++k) {
        sum += i/j;
        i += j;
        j = i-j;
    }
    printf("%f",sum);
}

void P5_9(void)
{
    int minus = 1;
    double sum = 0,i = 1,j = 1;
    for (int k = 0; k != 20; ++k) {
        sum += minus*i/j;
        minus = -1;
        i++;
        j += 2;
    }
    printf("%f",sum);
}

void P5_10(void)
{
    int i = 1,j = 2,sum = 0;
    for (int k = 3; k <= 25; ++k) {
        sum = i + j;
        i = j;
        j = sum;
    }
    printf("%d",sum);
}

void P5_11(void)
{
    int f1 = 0,f2 = 1,f3 = 2,sum;
    printf("%6d%6d%6d",f1,f2,f3);
    for (int i = 4; i <= 20; ++i) {
        sum = f1 + f2 + f3;
        printf("%6d",sum);
        f1 = f2;
        f2 = f3;
        f3 = sum;
        if(i%5 == 0)
            printf("\n");
    }
}

void P5_12(void)//可输入100内任意长度，回车键结束
{
    char c;
    char buf[100];
    int ch = 0,num = 0,oth = 0,space = 0,n;
    fgets(buf,100,stdin);
    n = strlen(buf)-1;
    for (int i = 0; i != n; ++i) {
        c = buf[i];
        if(c>='a'&&c<'z'||c>='A'&&c<='Z')
            ch++;
        else if(c>='0'&&c<='9')
            num++;
        else if(c == ' ')
            space++;
        else
            oth++;
    }
    printf("英文字母%d个，数字字母%d个，空格%d个，其他%d个",ch,num,space,oth);
}

void P5_13(void)
{
    int j = 0;
    for (int i = 2000; i <= 2100; i+=4) {
        if(i%4 == 0 && i%100)
        {
            j++;
            printf("%6d",i);
        }
        if(i%400 == 0)
        {
            j++;
            printf("%6d",i);
        }
        if(j%5 == 0)
        {
            printf("\n");
        }
    }
}

void P5_14(void)
{
    int sum;
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            for (int k = 1; k <= 9; ++k) {
                sum = i*100 + j*10 + k;
                if(i*i*i + j*j*j + k*k*k == sum)
                    printf("%6d",sum);
            }
        }
    }
}

void P5_15(void)//P5_2改
{
    int tmp,max = 0,min = 0,sum = 0,i = 2;
    scanf("%d",&tmp);
    min = max = tmp;
    scanf("%d",&tmp);
    if(tmp >= max)
        max = tmp;
    else
        min = tmp;
    while (1) {
        scanf("%d",&tmp);
        if(tmp == -1)
            break;
        i++;
        if(tmp <= min)
        {
            sum += min;
            min = tmp;
        }
        else if(tmp >= max)
        {
            sum += max;
            max = tmp;
        }
    }
    if(i == 2)
        printf("输入个数不够\n");
    else
        printf("%f",sum*1.0/(i-2));
}

void P5_16(void)
{
    //P5_12
}

void P5_17(void)
{
    int i = 1;
    double minus = 1,sum = 0,tmp;
    while((tmp = 1./i++) >= 1.e-5)
    {
        sum += minus*tmp;
        minus = -minus;
    }
    printf("%f",sum);
}

void P5_18(void)
{
    int i = 1;
    double minus = 1,sum = 0,tmp;
    while((tmp = 1./i) >= 1.e-5)
    {
        sum += minus*tmp;
        minus = -minus;
        i += 2;
    }
    printf("%f",sum);
}

void P5_19(void)
{
    int i = 1;
    double minus = 1,sum = 0,tmp;
    while((tmp = 1./i) >= 1.e-5)
    {
        sum += minus*tmp;
        minus = -minus;
        i += 3;
    }
    printf("%f",sum);
}

void P5_20(void)
{
    int i,j,min,result = 2;
    scanf("%d%d",&i,&j);
    if(i > j)
        min = j;
    else
        min = i;
    while(i%result||j%result)
    {
        result++;
        if(result > min)
        {
            printf("没有最大公约数");
            return ;
        }
    }
    printf("%d",result);
}

void P5_21(void)
{
    int n,i = 0;
    scanf("%d",&n);
    while(n)
    {
        n /= 10;
        i++;
    }
    printf("%d",i);
}

void P5_22_1(void)//方法一
{
    int num;
    int i = 0,sum = 0,k = 0;//形成num的逆向数字sum，然后与num比较
    printf("请输入需要验证的回文数:\n");//num是需要验证的数
    scanf("%d",&num);
    k = num;//先将num复制给k，以免改变num
    while(k>=10)//验证k是否大于10，如果小于10，则退出，因为个位数余10还是它本身
    {
        i = k%10;//获取k的个位数值
        sum = (sum+i)*10;//将j加上个位数后乘以10
        k /= 10;//因为k的最后一位数已经被读取掉了，所以让它除10舍弃掉最后一位
    }
    sum += k;//循环结束后还需将num的最高位数加上，因为他是小于10的，无法在循环中执行
    if(sum == num)//验证逆向num和num是否相等
        printf("%d是回文数",num);
    else
        printf("不是回文数\n");
}

void P5_22_2(void)//方法二
{
    int a,b,i,j = 0;
    printf("请输入需要验证的回文数:\n");
    scanf("%d",&a);
    b = a;
    int buf[10];
    for(i = 0;b>=10;i++)
    {
        buf[i] = b%10;
        b /= 10;
    }
    buf[i] = b;
    while(j<=i)
    {
        if(buf[j++]==buf[i--])
            continue;
        printf("不是回文数\n");
        return ;
    }
    printf("%d是回文数",a);
}

void P5_23(void)
{
    int i,j;
    for (i = j = 1; j <= 20 ; j++) {
        if(i >= 10)
            break;
        if(i%2)
        {
            i += 5;
            continue;
        }
        i -= 3;
    }
    printf("%d",j);
}

void P5_24(void)
{
    int i;
    for (i = 0; i <=5 ; i++) {
        switch (i)
        {
            case 1:
                printf("i = 1\n");
                continue;
            case 2:
                i = 1;
            case 3:
                printf("i = 3\n");
                i += 2;
                continue;
            case 4:
                printf("i = %d\n",i);
                i++;
                break;
        }
    }
    printf("i = %d\n",i);
}

void P5_25(void)
{
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= 5; ++j) {
            if(i <= j)
                printf("%d * %d = %d\t",i,j,i*j);
            else
                printf("         \t");
        }
        printf("\n");
    }
}

void P5_26(void)//P3_4改
{
    char buf[14];
    memset(buf,' ',13);
    buf[13] = 0;
    for (int i = 6; i != -1; --i) {
        buf[i] = buf[12 - i] = '*';
        printf("%s\n", buf);
    }
}

void P5_27(void)
{
    printf("请输入一个奇数:\n");
    int n,i;
    scanf("%d",&n);
    char buf[n+1];
    memset(buf,' ',n);
    buf[n] = 0;
    for (i = n/2; i != -1; --i) {
        printf("%s\n",buf);
        buf[i] = buf[n-1-i] = '*';
    }
    printf("%s\n",buf);
    for (++i; i < n/2; ++i) {
        buf[i] = buf[n-1-i] = ' ';
        printf("%s\n",buf);
    }
}

void P5_28(void)
{
    int i = 0,k;
    for (int j = 2; j <= 100; ++j) {
        for (k = 2; k <= j; ++k) {
            if(j%k == 0)
                break;
        }
        if(k == j)
        {
            printf("%2d  ",j);
            if(++i%5 == 0)
                printf("\n");
        }
    }
}

void P5_29(void)//等价于三百个铜钱，公鸡一只15，母鸡一只9，小鸡一只1
{
    int j;//公鸡
    //假设买了一百只小鸡，花了一百，还剩两百，将一只小鸡换成母鸡花费8，换成公鸡花费14，等于解方程8x + 14y = 200，x，y均为整数，解4x + 7y = 100
    for (int i = 0; i <= 25; ++i) {
        if((100-4*i)%7==0)
        {
            j = (100-4*i)/7;
            printf("i(母鸡)等于%d,j(公鸡)%d,小鸡%d\n",i,j,100-i-j);
        }
    }
}

void P6_1(void)
{
    int index = 0;
    double min;
    double buf[10];
    scanf("%lf",buf);
    min = buf[0];
    for (int i = 1; i < 10; ++i) {
        scanf("%lf",buf+i);
        if(min > buf[i])
        {
            min = buf[i];
            index = i;
        }
    }
    printf("min = %f,index = %d",min,index);
}

void P6_2(void)
{
    int flag = 0;
    double num;
    double buf[10];
    for (int i = 0; i < 10; ++i) {
        scanf("%lf", buf + i);
    }
    scanf("%lf",&num);
    for (int j = 0; j < 10; ++j) {
        if(buf[j] == num)
        {
            flag = 1;
            printf("%d  ",j);
        }
    }
    if(flag == 0)
        printf("-1");
}

void P6_3(void)
{
    double tmp;
    double buf[10];
    for (int i = 0; i < 10; ++i) {
        scanf("%lf", buf + i);
    }
    for (int j = 1; j < 10; ++j) {
        for (int k = 0; k < 10 - j; ++k) {
            if(buf[k] < buf[k + 1])
            {
                tmp = buf[k+1];
                buf[k + 1] = buf[k];
                buf[k] = tmp;
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        printf("%lf ",buf[i]);
    }
}

void P6_4(void)
{
    int i,tmp,t[10];
    for (i = 0; i < 10; ++i) {
        scanf("%d", t + i);
    }
    for (i = 0;i != 5;i++)
    {
        tmp = t[i];
        t[i] = t[9-i];
        t[9-i] = tmp;
    }
    for (i = 0; i < 10; ++i) {
        printf("%d ",t[i]);
    }
}

void P6_5(void)
{
    int i,tmp,t[9];
    for (i = 0; i < 9; ++i) {
        scanf("%d", t + i);
    }
    for (i = 0;i != 4;i++)
    {
        tmp = t[i];
        t[i] = t[8-i];
        t[8-i] = tmp;
    }
    for (i = 0; i < 9; ++i) {
        printf("%d ",t[i]);
    }
}

void P6_6(void)
{
    int j,num,flag = 0;
    scanf("%d",&num);
    int a[10] = {0,10,20,30,40,50,60,70,80,90};
    for (j = 0; j < 10; ++j) {
        if(a[j] == num)
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0)
        printf("-1");
    else
    {
        for (; j < 10; ++j) {
            a[j] = a[j + 1];
        }
        for (int i = 0; i < 9; ++i) {
            printf("%d  ", a[i]);
        }
    }
}

void P6_7(void)
{
    int x,y;
    double min;
    double a[3][5];
    for (int i = 0; i < 15; ++i) {
        scanf("%lf",*a+i);
    }
    min = a[0][0];
    x = y = 0;
    for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 5; ++k) {
            if(min > a[j][k])
            {
                min = a[j][k];
                x = j;
                y = k;
            }
        }
    }
    printf("最小值是%lf 第%d行 %d列",min,x+1,y+1);
}

void P6_8(void)
{
    double min;
    double a[3][5];
    for (int i = 0; i < 15; ++i) {
        scanf("%lf",*a+i);
    }
    for (int j = 0; j < 5; ++j) {
        min = a[0][j];
        for (int i = 0; i < 3; ++i) {
            if (min > a[i][j])
            {
                min = a[i][j];
            }
        }
        printf("第%d列的最小值为:%lf\n",j+1,min);
    }
}

void P6_9(void)
{
    double sum = 0;
    double a[3][3];
    for (int i = 0; i < 9; ++i) {
        scanf("%lf",*a+i);
    }
    printf("和为%lf",a[0][0]+a[1][1]+a[2][2]);
}

void P6_10(void)
{
    int a[3][4];
    int b[4][5];
    int c[3][5];
    memset(c,0, sizeof(c));
    printf("请输入一个三行四列的矩阵:\n");
    for (int i = 0; i < 12; ++i) {
        scanf("%d",*a+i);
    }
    printf("请输入一个四行五列的矩阵:\n");
    for (int j = 0; j < 20; ++j) {
        scanf("%d",*b+j);
    }
    for (int k = 0; k < 3; ++k) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 4; ++j) {
                c[k][i] += a[k][j] * b[j][i];
            }
        }
    }
    for (int l = 0; l < 3; ++l) {
        for (int i = 0; i < 5; ++i) {
            printf("%d ",c[l][i]);
        }
        printf("\n");
    }
}

void P6_11(void)
{
    int i = 0;
    char s1[80],s2[80];
    gets(s1);
    while (s1[i]!=0)
    {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = 0;
    printf("%s",s2);
}

void P6_12(void)
{
    int max = 0;
    char buf[10][1024];
    for (int i = 0; i < 10; ++i) {
        scanf("%s",buf[i]);
    }
    for (int j = 1; j < 10; ++j) {
        if(strcmp(buf[max],buf[j]) < 0)
        {
            max = j;
        }
    }
    printf("%s",buf[max]);
}

void P6_13(void)
{
    char s[80];
    gets(s);
    int i;
    int len = strlen(s);
    for (i = 0; i < len/2; ++i) {
        if(s[i]!=s[len-1-i])
            break;
    }
    if(i==len/2)
        printf("%s是回文\n",s);
}

void P6_14(void)
{
    char c;
    char s[80];
    int begin,len;
    gets(s);
    scanf("%d%d",&begin,&len);
    c = s[begin+len];
    s[begin+len] = 0;
    printf("%s",s+begin);
    s[begin+len] = c;
}

void P7_1(void)
{
    int a,b,c,*pmin,*pmid,*pmax;
    scanf("%d%d%d",&a,&b,&c);
    if(a < b)
    {
        if(a < c)
        {
            pmin = &a;
            if(b < c)
            {
                pmid = &b;
                pmax = &c;
            }
            else
            {
                pmid = &c;
                pmax = &b;
            }
        }
        else
        {
            pmin = &c;
            pmid = &a;
            pmax = &b;
        }
    }
    else
    {
        if(c < b)
        {
            pmin = &c;
            pmid = &b;
            pmax = &a;
        }
        else
        {
            pmin = &b;
            if(a < c)
            {
                pmid = &a;
                pmax = &c;
            }
            else
            {
                pmid = &c;
                pmax = &a;
            }
        }
    }
    printf("%d %d %d",*pmin,*pmid,*pmax);
}

void P7_2(void)
{
    int mi = 0,ma = 0;
    double min,max;
    double buf[10];
    scanf("%lf",buf);
    min = max = buf[0];
    for (int i = 1; i < 10; ++i) {
        scanf("%lf",buf+i);
        if(min > *(buf+i))
        {
            min = *(buf+i);
            mi = i;
            continue;
        }
        if(max < *(buf+i))
        {
            max = *(buf+i);
            ma = i;
        }
    }
    buf[mi] = buf[0];
    buf[ma] = buf[9];
    buf[0] = min;
    buf[9] = max;
    for (int j = 0; j < 10; ++j) {
        printf("%.0lf  ",buf[j]);
    }
}

void P7_3(void)//P6_3改，改buf[k]为 *(buf+k)即可
{
    double tmp;
    double buf[10];
    for (int i = 0; i < 10; ++i) {
        scanf("%lf", buf + i);
    }
    for (int j = 1; j < 10; ++j) {
        for (int k = 0; k < 10 - j; ++k) {
            if(buf[k] > buf[k + 1])
            {
                tmp = buf[k+1];
                buf[k + 1] = buf[k];
                buf[k] = tmp;
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        printf("%lf ",buf[i]);
    }
}

void P7_4(void)
{
    int index = 0;
    double min;
    double a[3][4];
    scanf("%lf",*a);
    min = **a;
    for (int i = 1; i < 12; ++i) {
        scanf("%lf",*a+i);
        if(min > *(*a+i))
        {
            min = *(*a+i);
            index = i;
        }
    }
    printf("最小值为%lf,行下标为%d 列下标为%d",min,(index+1)/4,index%4);
}

void P7_5(void)
{
    int i;
    char s[10],*p = "Chinese";
    int len = strlen(p);
    for (i = 0; i < len; ++i) {
        s[i] = p[i];
    }
    s[i] = 0;
    printf("%s",s);
}

void P7_6(void)
{
    char * min;
    char * t[3] = {"google","baidu","yahoo"};
    if(strcmp(t[0],t[1]) > 0)
    {
        if(strcmp(t[1],t[2]) > 0)
            min = t[2];
        else
            min = t[1];
    }
    else
    {
        if(t[0] < t[2])
            min = t[0];
        else
            min = t[2];
    }
    printf("%s",min);
}

void P8_1(void)//P5_15改
{
    double tmp,max = 0,min = 0,sum = 0;
    int i = 2,n = 8;
    scanf("%lf",&tmp);
    min = max = tmp;
    scanf("%lf",&tmp);
    if(tmp >= max)
        max = tmp;
    else
        min = tmp;
    while (n--) {
        scanf("%lf",&tmp);
        i++;
        if(tmp <= min)
        {
            sum += min;
            min = tmp;
        }
        else if(tmp >= max)
        {
            sum += max;
            max = tmp;
        }
    }
    if(i == 2)
        printf("输入个数不够\n");
    else
        printf("%.1f",sum/(i-2));
}


void P8_2(double a,double b,double c)
{
    double x1,x2;
    double delta = sqrt(b*b - 4*a*c);
    if(delta > 0)
    {
        x1 = (-b + delta)/(2*a);
        x2 = (-b - delta)/(2*a);
    }
    else if(delta == 0)
    {
        x1 = x2 = -b/(2*a);
    }
    else
    {
        printf("无解");
        return;
    }
    printf("x1 = %lf,x2 = %lf",x1,x2);
}

double P8_3(int n)//P5_7改
{
    double sum = 0,minus = 1;
    for (int i = 1; i <= n; ++i) {
        sum += minus/i;
        minus = -minus;
    }
    return sum;
}

int P8_4(int m,int n)
{
    int i = 1,j,gcd;
    if(m < n)
        gcd = m;
    else
        gcd = n;
    while(m%gcd||n%gcd)
        gcd--;
    return gcd;
}

int P8_5(int n)
{
    for (int i = 2; i < n; ++i) {
        if(n%i == 0)
            return 0;
    }
    return 1;
}

void P8_6(void)
{
    //P8_1
}

void P8_7(void)
{
    //P8_2
}

void P8_8(void)
{
    //P8_3
}

void P8_9(void)
{
    //P8_4
}

void P8_10(void)
{
    //P8_5
}

void P8_11(int radius)//P3_7改，写为一个函数
{
    printf("圆的面积为:%f\n圆的周长为:%f\n",2*3.14*radius,3.14*radius*radius);
}

int P8_12(int n,int t[])//P5_2改
{
    int max = 0,min = 0,sum = 0;
    min = max = t[0];
    if(t[1] >= max)
        max = t[1];
    else
        min = t[0];
    for (int i = 2; i != n; ++i) {
        if(t[i] <= min)
        {
            sum += min;
            min = t[i];
        }
        else if(t[i] >= max)
        {
            sum += max;
            max = t[i];
        }
    }
    return sum/(n-2);
}

int P8_13(char s1[],char s2[])
{
    while(*s1!=0&&*s2!=0)
    {
        if(*s1 == *s2)
        {
            s1++;
            s2++;
            continue;
        }
        else if(*s1 > *s2)
        {
            return 1;
        }
        else
            return -1;
    }
    if(*s1 == 0&&*s2 == 0)
        return 0;
    else if(*s1 == 0)
        return -1;
    else
        return 1;
}

void P8_14(int row,int t[][5])
{
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%4d",t[i][j]);
        }
        printf("\n");
    }
}
int P8_15(int n,int r[][3])
{
    int min = 0,index = n*3;
    min = r[0][0];
    for (int i = 1; i < index; ++i) {
        if(min > *(*r+i))
            min = *(*r+i);
    }
    return min;
}

void P8_16(int * m,int * n)
{
    *m += 5;
    *n -= 3;
    /*
      int main(void)
    {
        int m = 5,n = 3;
        P8_16(&m,&n);
        printf("%d %d",m,n);
        return 0;
    }
     */
}

void P8_17(void)
{
    void P8_17_input(int n1,int t1[]);
    void P8_17_output(int n3,int t3[]);
    void P8_17_sort(int n2,int t2[]);
    int buf[10];
    P8_17_input(10,buf);
    P8_17_sort(10,buf);
    P8_17_output(10,buf);
}

void P8_17_input(int n1,int t1[])
{
    for (int i = 0; i < n1; ++i) {
        scanf("%d",t1+i);
    }
}

void P8_17_sort(int n2,int t2[])
{
    int tmp;
    for (int i = 0; i < n2-1; ++i) {
        for (int j = i+1; j < n2; ++j) {
            if(t2[i] > t2[j])
            {
                tmp = t2[i];
                t2[i] = t2[j];
                t2[j] = tmp;
            }
        }
    }
}

void P8_17_output(int n3,int t3[])
{
    for (int i = 0; i < n3; ++i) {
        printf("%d ",t3[i]);
    }
}

void P8_18(void)
{
    void P8_18_input(int n1,int t1[]);
    void P8_18_swapmin(int n2,int t2[]);
    void P8_18_swapmax(int n3,int t4[]);
    void P8_18_output(int n4,int t4[]);
    int buf[10];
    P8_18_input(10,buf);
    P8_18_swapmin(10,buf);
    P8_18_swapmax(10,buf);
    P8_18_output(10,buf);
}

void P8_18_input(int n1,int t1[])
{
    for (int i = 0; i < n1; ++i) {
        scanf("%d",t1+i);
    }
}

void P8_18_swapmin(int n2,int t2[])
{
    int min = t2[0],n = 0;
    for (int i = 1; i < n2; ++i) {
        if(min > t2[i])
        {
            min = t2[i];
            n = i;
        }
    }
    min = t2[n2-1];
    t2[n2-1] = t2[n];
    t2[n] = min;
}

void P8_18_swapmax(int n3,int t4[])
{
    int max = t4[0],n = 0;
    for (int i = 1; i < n3; ++i) {
        if(max < t4[i])
        {
            max = t4[i];
            n = i;
        }
    }
    max = t4[0];
    t4[0] = t4[n];
    t4[n] = max;
}

void P8_18_output(int n4,int t4[])
{
    for (int i = 0; i < n4; ++i) {
        printf("%d ",t4[i]);
    }
}

void P8_19(void)
{
    void P8_19_input(int row1,int (*t1)[3]);
    void P8_19_change(int row2,int (*t2)[3]);
    void P8_19_output(int row3,int (*t3)[3]);
    int buf[3][3];
    P8_19_input(3,buf);
    P8_19_change(3,buf);
    P8_19_output(3,buf);
}

void P8_19_input(int row1,int (*t1)[3])
{
    for (int i = 0; i < 3*row1; ++i) {
        scanf("%d",*t1+i);
    }
}

void P8_19_change(int row2,int (*t2)[3])
{
    for (int i = 0; i < 3*row2; ++i) {
        (*(*t2 + i))++;
    }
}

void P8_19_output(int row3,int (*t3)[3])
{
    for (int i = 0; i < 3*row3; ++i) {
        printf("%d ",*(*t3+i));
    }
}

void P8_20(void)
{
    //太简单跳过
}

void P8_21(void)
{
    double P8_21_call(int radius,double (*p)(int));
    double P8_21_area(int radius);
    double P8_21_circum(int radius);
    int radis;
    scanf("%d",&radis);
    printf("area   = %.2f\n",P8_21_call(radis,P8_21_area));
    printf("circum = %.2f",P8_21_call(radis,P8_21_circum));
}

double P8_21_call(int radius,double (*p)(int))
{
    return p(radius);
}

double P8_21_area(int radius)
{
    return 3.14*radius*radius;
}

double P8_21_circum(int radius)
{
    return 2*3.14*radius;
}

int fac(int n)
{
    return (n==1)?1:n*fac(n-1);
}

int P8_22(int n)
{
    return (n==1)?1:n+P8_22(n-1);
}

double P8_23(double x,int n)
{
    return (n==0)?1:x*P8_23(x,n-1);
}

int hanoi(int n,char first,char second,char third)
{
    static int i = 0;
    i++;
    if (n > 1)
    {
        hanoi(n-1,first,third,second);
        printf("Move disk %d from %c to %c\n",n,first,third);
        hanoi(n-1,second,first,third);
    }
    else
        printf("Move disk %d from %c to %c\n",n,first,third);
    return i;
}

void P8_24(void)
{
    printf("%d",hanoi(3,'A','B','C'));
}

int x,y;

void P9_1(void)
{
    x = 3,y = 5;
    void P9_1_exchange();
    P9_1_exchange();
    printf("x = %d y = %d",x,y);
}

void P9_1_exchange()
{
    int t;
    t = x;
    x = y;
    y = t;
}

# define swap(a,b) {int t;t = a;a = b;b = t;}

void P9_2()
{
    int a = 3,b = 4;
    swap(a,b);
    printf("a = %d,b = %d",a,b);
}

void P10_1()
{
    struct book
    {
        char title[20];
        char author[20];
        char press[20];
        double price;
        int amount;
    };
    struct book b1 = {"C language","lipmen","machine",26,2};
    struct book * b2 = &b1;
    printf("%s %s %s",b1.title,b2->title,(*b2).title);
}

void P10_2()//输入方式为xxxx yy zz
{
    int count = 0,day;
    struct date
    {
        int year;
        int month;
        int day;
    };
    struct date today;
    scanf("%d%d%d",&today.year,&today.month,&today.day);
    if(!(today.year%4)&&today.year%100)
        day = 1;
    else
        day = 0;
    switch (today.month)
    {
        case 12: count += 30;
        case 11: count += 31;
        case 10: count += 30;
        case 9: count += 31;
        case 8: count += 31;
        case 7: count += 30;
        case 6: count += 31;
        case 5: count += 30;
        case 4: count += 31;
        case 3: count += 28+day;
        case 2: count += 31;
        case 1: count += today.day;
    }
    printf("%d-%d-%d是%d年的第%d天\n",today.year,today.month,today.day,today.year,count);
}

void P10_3()//输入方式为 书名 作者 出版社 价格 数量
{
    struct book
    {
        char title[20];
        char author[20];
        char press[20];
        double price;
        int amount;
    };
    struct book * p;
    struct book ** bk = (struct book **)malloc(sizeof(struct book *)*5);
    for (int i = 0; i < 5; ++i) {
        bk[i] = (struct book *)malloc(sizeof(struct book));
        scanf("%s%s%s%lf%d",bk[i]->title,bk[i]->author,bk[i]->press,&bk[i]->price,&bk[i]->amount);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = i+1; j < 5; ++j) {
            if(bk[i]->price > bk[j]->price)
            {
                p = bk[i];
                bk[i] = bk[j];
                bk[j] = p;
            }
        }
    }
    for (int j = 0; j < 5; ++j) {
        printf("%s %s %s %.2lf %d\n",bk[j]->title,bk[j]->author,bk[j]->press,bk[j]->price,bk[j]->amount);
    }

}

void P10_4()
{
    //与10_3相似，跳过
}

struct mycomplex
{
    double real;
    double image;
};


void P10_5()
{
    struct mycomplex input(void);
    struct mycomplex add(struct mycomplex c1,struct mycomplex c2);
    struct mycomplex mul(struct mycomplex c1,struct mycomplex c2);
    void output(struct mycomplex c);
    struct mycomplex c1 = input();
    struct mycomplex c2 = input();
    struct mycomplex c0 = add(c1,c2);
    struct mycomplex c = mul(c1,c2);
    output(c0);
    output(c);
}

struct mycomplex input(void)
{
    struct mycomplex c;
    printf("请输入一个复数(格式为x+yi):");
    scanf("%lf+%lfi",&c.real,&c.image);
    return c;
}

struct mycomplex add(struct mycomplex c1,struct mycomplex c2)
{
    struct mycomplex c3;
    c3.real = c1.real + c2.real;
    c3.image = c1.image + c2.image;
    return c3;
}

struct mycomplex mul(struct mycomplex c1,struct mycomplex c2)
{
    struct mycomplex c;
    c.real = c1.real*c2.real - c1.image*c2.image;
    c.image = c1.image*c2.real + c1.real*c2.image;
    return c;
}

void output(struct mycomplex c)
{
    printf("%.2lf",c.real);
    if(c.image == 0)
        return;
    else
        printf("+%.2lfi\n",c.image);
}

typedef struct node{
    int num;
    struct node * next;
}Node,* pNode;

void traverse(pNode head)
{
    while(head = head->next)
        printf("%d ",head->num);
    printf("\n");
}

void insert_node(pNode head,pNode p)
{
    p->next = head->next;
    head->next = p;
}

void convert(pNode head)
{
    pNode p = head,q;
    if((p = p->next)==NULL)
        return;
    q = p->next;
    p->next = NULL;
    while (p = q)
    {
        q = p->next;
        p->next = head->next;
        head->next = p;
    }
}

void delete_node(pNode head)
{
    pNode p = head->next;
    if (p!=NULL)
    {
        head->next = p->next;
        printf("数据%d已删除\n",p->num);
        free(p);
    }
    else
        printf("无可删除的数据\n");
}

void P10_6()
{
    int n;
    pNode head = (pNode)malloc(sizeof(Node));
    pNode tmp,p = head;
    head->next = NULL;
    printf("请输入需要输入的数据个数:");
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) {
        tmp = (pNode)malloc(sizeof(Node));
        scanf("%d",&tmp->num);
        p->next = tmp;
        p = tmp;
    }
    p->next = NULL;
    traverse(head);
    convert(head);
    traverse(head);
    while(head->next)
        delete_node(head);
    traverse(head);
}

void str_cpy(char * s1,char * s2)
{
    int i = 0;
    while(s1[i] = s2[i])
        i++;
}

void P11_1(void)
{
    char c;
    int i = 0;
    char buf[100];
    while((c = getchar())!='\n')
        buf[i++] = c;
    buf[i] = 0;
    for (int j = 0; j < i; ++j) {
       if('a' <= buf[j] && buf[j] <= 'z')
           buf[j] -= 32;
    }
    printf("%s",buf);
}

void P11_2(void)
{
    int i;
    char buf[100];
    FILE * fp = fopen("/Users/dengyan/chenhui","r");
    while (fgets(buf, sizeof(buf),fp) != NULL)
    {
        i = strlen(buf);
        for (int j = 0; j < i; ++j) {
            if('A' <= buf[j] && buf[j] <= 'Z')
                buf[j] += 32;
        }
        printf("%s",buf);
    }
}

void P11_3(void)
{
    struct student
    {
        char sno[8];
        char name[20];
        char sex;
        int age;
        double score;
    };
    FILE * fp = fopen("/Users/dengyan/chenhui","w");//文件名根据自己的情况填写
    struct student s[5];
    for (int i = 0; i < 5; ++i) {
        scanf("%s %s %c %d %lf",s[i].sno,s[i].name,&s[i].sex,&s[i].age,&s[i].score);//一定要在%s和%c中间加一个空格，不然%c会读取到空格，可以去掉%s和%c中的空格查看会发生什么
    }
    for (int j = 0; j < 5; ++j) {
        fprintf(fp,"%s %s %c %d %lf\n",s[j].sno,s[j].name,s[j].sex,s[j].age,s[j].score);
    }
}

void P11_4(void)
{
    struct student
    {
        char sno[8];
        char name[20];
        char sex;
        int age;
        double score;
    };
    double sum = 0;
    int tmp,i = 0;
    char buf[100];
    FILE * fp = fopen("/Users/dengyan/chenhui","r");
    while ( fgets(buf,100,fp) != NULL) {
        sscanf(strrchr(buf,' '),"%d",&tmp);
        sum += tmp;
        i++;
    }
    printf("%lf",1.0*sum/i);
}

int isPalindrome(int x) {
    if (x < 0)
        return 0;
    int back = x,sum = 0,tmp = 0;
    while (back != 0)
    {
        sum *= 10;
        sum += back%10;
        printf("%d\n",back);
        back /= 10;
    }
    printf("%d",sum);
    if (sum == x)
        return 1;
    return 0;
}


int main(void)
{
    /*FILE * fp;
    char str[10];
    fp = fopen("/Users/dengyan/exam","w");
    fputs("abc",fp);
    fclose(fp);
    fp = fopen("/Users/dengyan/exam","a+");
    fputs("28",fp);
    fseek(fp,0,SEEK_SET);
    //rewind(fp);
    fgets(str,10,fp);
    puts(str);*/
    char c,buf[100];
    char * s[3] = {"google","baudi","yahoo"};
    FILE * fd = fopen("/Users/dengyan/exam","w+");
    for (int i = 0; i < 3; ++i) {
        fputs(s[i],fd);
        fputc('\n',fd);
    }
    fflush(fd);
    fseek(fd,0,SEEK_SET);
    memset(buf,0, sizeof(buf));
    for (int j = 0; j < 3; ++j) {
        fgets(buf, sizeof(buf),fd);
        printf("%s",buf);
    }
}

void P10_7()
{

}

void is_Palindrome(void)
{
    int i,tmp,sum = 0;
    scanf("%d",&i);
    tmp = i;
    while(tmp)
    {
        sum = sum*10 + tmp%10;
        tmp /= 10;
    }
    if(sum == i)
        printf("%d 是回文数",i);
}

void primer_in_100()
{
    int i,j,flag;
    for (i = 2; i <= 100; ++i) {
        for (j = 2; j < i; ++j) {
            if (i%j == 0)
                break;
        }
        if(i == j)
            printf("%d ",i);
    }
}

void I11_3()
{
    struct student
    {
        char sno[8];
        char name[20];
        char sex;
        int age;
        double score;
    };
    FILE * fp = fopen("/Users/dengyan/chenhui","w+");
    struct student s[3] = {
            {"2014","dengyan",'m',21,99},
            {"2011","chenhui",'m',19,49},
            {"2012","yuanlin",'m',15,29},
    };
    struct student info;
    for (int i = 0; i < 3; ++i) {
        fprintf(fp,"%s %s %c %d %lf\n",s[i].sno,s[i].name,s[i].sex,s[i].age,s[i].score);
    }
    fseek(fp,0,SEEK_SET);
    for (int j = 0; j < 3; ++j) {
        fscanf(fp,"%s%s %c%d%lf",info.sno,info.name,&info.sex,&info.age,&info.score);//一定要在%s和%c中间加一个空格，不然%c会读取到空格
        printf("%s %s %c %d %lf\n",info.sno,info.name,info.sex,info.age,info.score);
    }
}

void I11_2()
{
    char c,buf[100];
    char * s[3] = {"google","baudi","yahoo"};
    FILE * fd = fopen("/Users/dengyan/chenhui","w+");
    for (int i = 0; i < 3; ++i) {
        fputs(s[i],fd);
        fputc('\n',fd);
    }
    fflush(fd);
    fseek(fd,0,SEEK_SET);
    memset(buf,0, sizeof(buf));
    for (int j = 0; j < 3; ++j) {
        fgets(buf, sizeof(buf),fd);
        printf("%s",buf);
    }
}

void I5_26(void)
{
    int n,i;
    scanf("%d",&n);
    char buf[n+1];
    memset(buf,'*',n);
    buf[n] = 0;
    for (i = 0; i < n/2; ++i) {
        printf("%s\n",buf);
        buf[i] = buf[n-1-i] = ' ';
    }
    printf("%s\n",buf);
    for (--i; i >= 0; --i) {
        buf[i] = buf[n-1-i] = '*';
        printf("%s\n",buf);
    }
}



void gcd(void)
{
    int i = 1,j,gcd;
    scanf("%d%d",&i,&j);
    if(i < j)
        gcd = i;
    else
        gcd = j;
    while(i%gcd||j%gcd)
        gcd--;
    printf("%d",gcd);
}