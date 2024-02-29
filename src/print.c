#include "ft_traceroute.h"

extern t_pr pr;

void    print_option()
{
    printf("opt_fttl = %d\n", pr.opt_fttl);
    printf("opt_mttl = %d\n", pr.opt_mttl);
    printf("max_ttl = %d\n", pr.ttlmax);
    printf("first_ttl = %d\n", pr.fttl);
    printf("nqueries = %d\n", pr.nqueries);
    printf("opt nqueries = %d\n", pr.opt_nque);
}

void    e_printf(char *msg, int e)
{
    printf("%s \n", msg);
    (e > 0) ? exit(EXIT_SUCCESS) : exit(EXIT_FAILURE);
}

void    print_source(uint8_t *pkt, int i)
{
    int j;
    
    j = 0;
    while (j < 4)
    {
        printf("%d", pkt[i + j]);
        if (j < 3)
            printf(".");
        j++;
    }
    printf("\n");

}

void    print_source_addr(uint32_t addr)
{
    int i = 0;
    while (i < 4)
    {
        printf("%d", addr & 0b11111111);
        addr >>= 8;
        if (i < 3)
            printf(".");
        i++;
    }
}

void    icmp_code_type(t_recv *ptr)
{

    if (ptr->typercv != ICMP_TIMXCEED)
    {
        if (ptr->codercv == ICMP_NET_UNREACH)
            printf("!N");
        else if (ptr->codercv == ICMP_HOST_UNREACH)
            printf("!H");
        else if (ptr->codercv == ICMP_PROT_UNREACH)
            printf("!P");
        else if (ptr->codercv == ICMP_SR_FAILED)
            printf("!S");
        else if (ptr->codercv == ICMP_PKT_FILTERED)
            printf("!X");
        else if (ptr->codercv == ICMP_UNREACH_PRECEDENCE_CUTOFF)
            printf("!C");
        else if (ptr->codercv == ICMP_UNREACH_FILTER_PROHIB)
            printf("!V");
    }
    if (ptr->typercv == ICMP_TIME_EXCEEDED || (ptr->typercv == 3 && ptr->codercv == 3))
        printf("    %.3f ms ", ptr->rtt);
}