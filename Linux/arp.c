//
// Created by 邓岩 on 2018/11/17.
//

# include </Users/dengyan/ClionProjects/Linux/linux.h>

#define print_errno(fmt, ...) \
printf("[%d] errno=%d (%s) #" fmt, \
    __LINE__, errno, strerror(errno), ####__VA_ARGS__)

#define ETH_DATA_LEN 1500
static unsigned char s_ip_frame_data[ETH_DATA_LEN];
static unsigned int s_ip_frame_size = 0;

int main(int argc,char** argv)
{

    struct ether_header *eth = NULL;
    struct ether_arp *arp = NULL;
    struct ifreq ifr;
      struct in_addr daddr;
      struct in_addr saddr;
      struct sockaddr_ll sll;

      int skfd;
      int n = 0;

      unsigned char dmac[ETHER_ADDR_LEN] = {0x50,0x46,0x5d,0x71,0xcd,0xc0};
      /*伪造 源MAC*/
      unsigned char smac[ETHER_ADDR_LEN] = {0x00,0x11,0x22,0x33,0x44,0x55};

      daddr.s_addr = inet_addr("192.168.1.60");
      /*伪造 源IP*/
      saddr.s_addr = inet_addr("192.168.1.71");

      memset(s_ip_frame_data, 0x00, sizeof(unsigned char)*ETH_DATA_LEN);

      /*创建原始套接字*/
      skfd = socket(PF_INET, SOCK_RAW, htons(ETHERTYPE_ARP));
      if (skfd < 0) {
            print_errno("socket() failed! \n");
            return -1;
          }

      bzero(&ifr,sizeof(ifr));
      strcpy(ifr.ifr_name, "eth1");
      if (-1 == ioctl(skfd, SIOCGIF, &ifr)) {
            print_errno("ioctl() SIOCGIFINDEX failed!\n");
            return -1;
          }
      printf("ifr_ifindex = %d\n", ifr.ifr_ifru);

      bzero(&sll, sizeof(sll));
      sll.sll_ifindex = ifr.ifr_ifindex;
      sll.sll_family  = PF_PACKET;
      sll.sll_protocol = htons(ETH_P_ALL);

      #if 0
      /*获取本机IP*/
      if(-1 == ioctl(skfd, SIOCGIFADDR, &ifr)){
            printf("ioctl() SIOCGIFADDR failed! \n");
            return -1;
          }
      printf("ifr_addr  = %s\n", \
    inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));

      /*获取本机MAC*/
      if(-1 == ioctl(skfd, SIOCGIFHWADDR, &ifr)) {
            printf("ioctl() SIOCGIFHWADDR failed! \n");
            return -1;
          }
      printf("ifr_hwaddr  = %02x-%02x-%02x-%02x-%02x-%02x\n",  \
    (unsigned char)ifr.ifr_hwaddr.sa_data[0],       \
    (unsigned char)ifr.ifr_hwaddr.sa_data[1],       \
    (unsigned char)ifr.ifr_hwaddr.sa_data[2],       \
    (unsigned char)ifr.ifr_hwaddr.sa_data[3],       \
    (unsigned char)ifr.ifr_hwaddr.sa_data[4],       \
    (unsigned char)ifr.ifr_hwaddr.sa_data[5]);


      #endif

      /*构造以太报文*/
      eth = (struct ether_header*)s_ip_frame_data;
      eth->ether_type = htons(ETHERTYPE_ARP);
      memcpy(eth->ether_dhost, dmac, ETH_ALEN);
      memcpy(eth->ether_shost, smac, ETH_ALEN);

      /*构造ARP报文*/
      arp = (struct ether_arp*)(s_ip_frame_data + sizeof(struct ether_header));
      arp->arp_hrd = htons(ARPHRD_ETHER);
      arp->arp_pro = htons(ETHERTYPE_IP);
      arp->arp_hln = ETH_ALEN;
      arp->arp_pln = 4;
      arp->arp_op = htons(ARPOP_REQUEST);

      memcpy(arp->arp_sha, smac, ETH_ALEN);
      memcpy(arp->arp_spa, &saddr.s_addr, 4);
    /*
  memcpy(arp->arp_tha, dmac, ETH_ALEN);*/
      memcpy(arp->arp_tpa, &daddr.s_addr, 4);
      s_ip_frame_size = sizeof(struct ether_header) + sizeof(struct ether_arp);
      n = sendto(skfd, s_ip_frame_data, s_ip_frame_size, 0, \
    (struct sockaddr*)&sll, sizeof(sll));
      if (n < 0) {
            print_errno("sendto() failed!\n");
          }
      else {
            printf("sendto() n = %d \n", n);
          }
      close(skfd);
      return 0;
}
