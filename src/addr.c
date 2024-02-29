#include "ft_traceroute.h"

extern t_pr pr;

void save_addr(struct addrinfo *ai_info, t_pr *pr)
{
    char buf[150];
    struct sockaddr_in *sock_addr;

    sock_addr = (struct sockaddr_in *)ai_info->ai_addr;
    if (inet_ntop(AF_INET, &sock_addr->sin_addr.s_addr, buf, sizeof(buf)) == NULL)
        printf("error\n");
    printf(" (%s)", buf);
    printf(", %d hops max, 60 byte packets\n", pr->ttlmax - 1);
    pr->buf_addr = ft_strdup(buf);
    inet_pton(AF_INET, buf, &pr->servaddr.sin_addr);
}

int reverse_addr(char *addr, t_pr *pr, int bool)
{
    struct addrinfo ai_addr;
    struct addrinfo *ai_info;

    ft_memset(&ai_addr, 0, sizeof(ai_addr));
    ai_addr.ai_family = AF_INET;
    ai_addr.ai_flags = AI_CANONNAME;
    ai_addr.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(addr, NULL, &ai_addr, &ai_info) != 0)
    {
        printf("error getaddrinfo\n");
        return (0);
    }
    printf("traceroute to %s", ai_info->ai_canonname);
    if (bool == 1)
        save_addr(ai_info, pr);
    freeaddrinfo(ai_info);
    return (1);
}

void ft_name_addr(u_int32_t addr, char *str)
{
    struct sockaddr_in sa;    /* input */
    socklen_t len;         /* input */
    char hbuf[NI_MAXHOST];
    
    ft_memset(&sa, 0, sizeof(struct sockaddr_in));
    
    /* For IPv4*/
    inet_ntop(AF_INET, &addr, str, 150);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(str);
    len = sizeof(struct sockaddr_in);
    if (getnameinfo((struct sockaddr *) &sa, len, hbuf, sizeof(hbuf), 
        NULL, 0, NI_NAMEREQD)) 
        printf("%s", str);
    else if (pr.opt_name == 0)
        printf("%s", hbuf);
}