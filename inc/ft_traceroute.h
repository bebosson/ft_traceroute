#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H
# define BUFSIZE 1500
# define MAXLINE 1500
#define PING_SLEEP_RATE 1000000
#define SRC_PORT    57002
#define DEST_PORT    37000
#define SERV_PORT    33434
#define NI_MAXHOST 1025


#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include "libft.h"
#include <sys/time.h>
#include <unistd.h>
#include <netinet/udp.h>
#include <errno.h>
#include <netinet/ip.h>
#include <netdb.h>



typedef struct s_pr
{
    int opt_fttl;
    int opt_mttl;
    int opt_verb;
    int opt_wait;
    int opt_nque;
    int opt_name;
    int ttlmax;
    int fttl;
    int sockfd;
    int sockrecv;
    pid_t pid;
    u_int8_t code_recv;
    struct timeval timeout;
    struct timeval timerecv;
    struct timeval timesend;
    int ttl;
    struct sockaddr_in servaddr;
    char *buf_addr;
    int port;
    int ttlsrch;
    int ttlm;
    int wait;
    int nqueries;
}               t_pr;

typedef struct s_recv
{
    double rtt;
    u_int32_t addr;
    uint16_t dport;
    struct timeval timesend;
    struct timeval timerecv;
    u_int16_t ttl;
	u_int8_t codercv;
    u_int8_t typercv;
}               t_recv;

typedef struct sockaddr SA;
extern t_pr pr;


/*      parse_option.c */
int		    try_opt_addr(int ac, char **av);
void	    print_help_exit();

/*      set_option.c   */
void 	    save_opt_num(char opt, int num);
void 	    save_opt(char opt);
int		    ft_getopt(char **av, int ac, int nbr_add);

/*      print.c         */
void        e_printf(char *msg, int e);
void        print_pkt(uint8_t *pkt, int len, int fd);
void        print_source(uint8_t *pkt, int i);
void        print_source_addr(uint32_t addr);
void        icmp_code_type(t_recv *ptr);

/*      read_pck.c      */
uint16_t    check_recv_udphdr(char *buf);
void        send_signal_set_alarm();
u_int8_t    check_type(char *buf);
u_int8_t    check_code(char *buf);

/*      recv.c           */
void        print_respond(t_recv *ptr, int i, int by_probe, int *last);
int         save_buffer(t_recv *ptr, char *buf);
void        print_buffer(char *buf);
void        ft_recvfrom(int sockfd, void *buf, t_recv *recv_buf);
void        dg_recv(int sockfd, t_recv *buf);
/*      send.c           */
void        send_probe(t_recv *recv_buf, int *pck);
/*      addr.c */
void        save_addr(struct addrinfo *ai_info, t_pr *pr);
int         reverse_addr(char *addr, t_pr *pr, int bool);
void        ft_name_addr(u_int32_t addr, char *str);

/*      traceroute.c    */
void        ft_name_addr(u_int32_t addr, char *str);
void        save_addr(struct addrinfo *ai_info, t_pr *pr);
int         reverse_addr(char *addr, t_pr *pr, int bool);
int         set_config_socket(char *argv);
void        free_and_exit(t_recv *ptr);
int         main(int argc, char **argv);


# endif       
