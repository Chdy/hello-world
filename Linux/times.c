//
// Created by 邓岩 on 26/11/2017.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

int main()
{
    struct tms a,b;
    long c = sysconf(_SC_CLK_TCK);
    clock_t t = times(&a);
    time_t s = t/c;
    for (int i = 0; i < 100000000; ++i) {

    }
    printf("%s",ctime(&s));
    clock_t q = times(&b);
    printf("real time: %8f\n",(q-t)/(double)c);
    printf("User time: %8f\n",(b.tms_utime-a.tms_utime)/(double)c);
    printf("Sys time: %9f",(b.tms_stime-a.tms_stime)/(double)c);
}