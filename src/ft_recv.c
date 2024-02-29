#include "ft_traceroute.h"

t_pr pr;

int save_buffer(t_recv *ptr, char *buf) //pr.ttl_print && pr.prb_ttl
{
    struct iphdr *iphdr;
    iphdr = (struct iphdr *)buf;
    
    ptr->addr = iphdr->saddr;
    ptr->dport = check_recv_udphdr(buf);
    if (ptr->dport != 0)
		ptr->ttl = (ptr->dport - SERV_PORT) / pr.nqueries + 1;
	ptr->typercv = check_type(buf);
	ptr->codercv = check_code(buf);
    pr.code_recv = ptr->codercv; //erase by the other pckt
    gettimeofday(&(ptr->timerecv), NULL);
    if (ptr->timerecv.tv_sec != 0)
        ptr->rtt = (ptr->timerecv.tv_sec - ptr->timesend.tv_sec) * 1000.0 + (ptr->timerecv.tv_usec - ptr->timesend.tv_usec) / 1000.0;
    else
        ptr->rtt = 0;
    if (ptr->ttl == pr.ttlsrch) 
        return (1);
    else 
        return (0);
}



void print_respond(t_recv *ptr, int i, int by_probe, int *last)
{
    char addr[150];
    
    if (ptr[i].typercv == 3)
            *last = 1;
    if (!by_probe)
    {
        ft_name_addr(ptr[i].addr, addr);
        (pr.opt_name) ? printf(" %s", addr) : printf(" (%s)", addr); 
        if (ft_strequ(addr, pr.buf_addr) == 1)
            *last = 1;
    }
    else if (i != 0 && ptr[i].addr != ptr[i - 1].addr)
    {
        ft_name_addr(ptr[i].addr, addr);
        (pr.opt_name) ? printf(" %s", addr) : printf(" (%s)", addr); 
    }
    icmp_code_type(&ptr[i]);
    
    
    if (*last == 1 && by_probe == (pr.nqueries - 1)) // doesn't come in if timeout ..
        free_and_exit(ptr);
}

void print_all(t_recv *ptr)
{
    int i;
    int ttl;
    int by_probe;
    int last;

    i = -1;
    ttl = pr.ttlm;
    by_probe = 0;
    last = 0;
    while (++i < (pr.ttl - pr.ttlm) * pr.nqueries) // nqueries
    {
        if (ttl == ptr[i].ttl)
        {
            if (!by_probe)
                printf("%d ", ptr[i].ttl);
            if (ptr[i].dport == 0)
                printf(" * ");
            else
                print_respond(ptr, i, by_probe, &last);
            if (last == 1 && by_probe == (pr.nqueries - 1))
                free_and_exit(ptr);
            by_probe++;
        }
        if (by_probe / pr.nqueries ==  1) //nqueries 
        {
            ttl++;
            by_probe = 0;
            i = -1;
            printf("\n");
        }
    }
}



void ft_recvfrom(int sockfd, void *buf, t_recv *recv_buf)
{
    int j;
    int i;
    
    i = 0;
    j = 0;
    while (j < pr.ttl - pr.ttlm) 
    {
        ft_memset(buf, 0, MAXLINE); 
        if (pr.timeout.tv_sec && recvfrom(sockfd, buf, MAXLINE ,0, NULL, NULL) > 0)
            save_buffer(&(recv_buf[i]), buf);
        else
        {
            save_buffer(&(recv_buf[i]), buf);
            recv_buf[i].ttl = pr.ttlm + j;
        }
        i++;
        j = i / pr.nqueries; //nqueries ? 
    }
    print_all(recv_buf);
    pr.ttlm = pr.ttl;
}

void dg_recv(int sockfd, t_recv *recv_buf)
{
    char recvline[MAXLINE];
    ft_recvfrom(sockfd, recvline, recv_buf);
}
