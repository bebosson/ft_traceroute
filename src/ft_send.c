#include "ft_traceroute.h"

extern t_pr pr;

void send_probe(t_recv *recv_buf, int *pck)
{
    int i = -1;

    while (++i < pr.nqueries) //nqueries 
    {
        pr.servaddr.sin_port = htons(pr.port++);
        setsockopt(pr.sockfd, IPPROTO_IP, IP_TTL, &(pr.ttl), sizeof(u_int8_t));
        gettimeofday(&(recv_buf[*pck].timesend), NULL);
        sendto(pr.sockfd, "abc", 3, 0, (const SA *) &(pr.servaddr), sizeof(pr.servaddr));
        close(pr.sockfd);
        if ((pr.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
            e_printf("erreur_socket", 0);
        *pck += 1;
    }
}
