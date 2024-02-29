#include "ft_traceroute.h"

extern t_pr pr;

void    free_and_exit(t_recv *ptr)
{
    free(ptr);
    free(pr.buf_addr);
    exit(EXIT_SUCCESS);
}

int    set_config_socket(char *argv)
{
    ft_bzero(&(pr.servaddr), sizeof(pr.servaddr));
    if (!reverse_addr(argv, &pr, 1))
        return (0);
    pr.servaddr.sin_family = AF_INET;
    pr.servaddr.sin_port = htons(SERV_PORT);
    if(inet_pton(AF_INET, argv, &pr.servaddr.sin_addr) < 0)
        return (0);
    if ((pr.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        return (0);
    if ((pr.sockrecv = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
        return (0);
    return (1);
}

void    set_option_default()
{
    pr.pid = getpid(); // necessaire ? 
    pr.ttlsrch = 1;
    pr.code_recv = 0;
    if (!pr.opt_mttl)
        pr.ttlmax = 31;
    if (!pr.opt_fttl)
        pr.ttl = 1;
    else
        pr.ttl = pr.fttl;
    if (!pr.opt_nque)
        pr.nqueries = 3;
    pr.port = SERV_PORT + (pr.ttl - 1)  * pr.nqueries; //nqueries 
    pr.ttlm = pr.ttl;
    if (pr.opt_wait)
        pr.timeout.tv_sec = pr.wait;
    else
        pr.timeout.tv_sec = 1;
    pr.timeout.tv_usec = 0;
}

void    set_full_config(int argc, char **argv)
{
    int arg_addr;   

    if (getuid() != 0)
        e_printf("permission denied", 0);
    if (!(arg_addr = try_opt_addr(argc, argv)))
        e_printf("host missing or Cannot handle \"host\" cmdline", 0);
    if (argc > 2)
       ft_getopt(argv, argc, arg_addr);
    set_option_default();    
    if (pr.fttl > pr.ttlmax - 1)
        e_printf("first hop out of range", 0); 
    if (!set_config_socket(argv[arg_addr]))
        e_printf("Erreur socket", 0);
    if (setsockopt(pr.sockrecv, SOL_SOCKET, SO_RCVTIMEO, &(pr.timeout), sizeof (pr.timeout)) < 0)
        e_printf("setsockopt failed", 0);
}


 int    main(int argc, char **argv)
 {
    int i = 0;
    int j;
    t_recv *recv_buff;

    set_full_config(argc, argv);
    if (!(recv_buff = (t_recv *)ft_memalloc(sizeof(t_recv) * pr.nqueries)))
        return (0);
    ft_memset(recv_buff, 0, sizeof(t_recv));
    j = 0;
    
    while (pr.code_recv != ICMP_DEST_UNREACH && pr.ttl < pr.ttlmax)
    {
        while (i < 1)
        {
            send_probe(recv_buff, &j);
            pr.ttl++;
            i++;
        }
        i = 0;
        j = 0;
        dg_recv(pr.sockrecv, recv_buff);
    }
    free_and_exit(recv_buff);
    exit(0);
}
