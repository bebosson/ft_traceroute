#include "ft_traceroute.h"

extern t_pr pr;

void print_pkt(uint8_t *pkt, int len, int fd)
{
    int i = 0;
    int j = 0;

    dprintf(fd , "Paquet icmphdr + data\n");
    while (i <= len)
    {
       dprintf(fd , "%02x ", pkt[i]);
        if(j == 3)
            write(fd, " ", 1);
        else if (j == 7)
        {
            j = -1;
            write(fd, "\n", 1);
        }
       i++;
       j++;
    }
    dprintf(fd , "\n\n");
}

u_int8_t check_type(char *buf)
{
    struct icmp *icmpptr;
    struct iphdr *ip;
    int hlen;

    ip = (struct iphdr *)buf;
    hlen = ip->ihl << 2;
    icmpptr = (struct icmp *)(buf + hlen);
    return (icmpptr->icmp_type); //TTL EXCEDEED || DESTINATION UNREACHABLE 
}

u_int8_t check_code(char *buf)
{
    struct icmp *icmpptr;
    struct iphdr *ip;
    int hlen;

    ip = (struct iphdr *)buf;
    hlen = ip->ihl << 2;
    icmpptr = (struct icmp *)(buf + hlen);
    return (icmpptr->icmp_code);
}

uint16_t check_recv_udphdr(char *buf)
{
    struct udphdr *udp;
    
    udp = (struct udphdr *)(buf + 2 * sizeof(struct iphdr) + sizeof(struct icmphdr));
    return (ntohs(udp->uh_dport));
}