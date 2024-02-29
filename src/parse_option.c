#include "ft_traceroute.h"

void	print_help_exit()
{
	const char *help = "Usage: traceroute [--help] [-f first_ttl] [-m max_ttl] [-f first_ttl] [-q nqueries] [-w wait] host\n";
	printf("%s",help);
	printf(
	"-n"                  		
	"							Do not resolve IP addresses to their domain names\n" 
	"-m max_ttl \n"
	"							Set the max number of hops (max TTL to be\n"
    "							reached). Default is 30\n"
	"-f first_ttl \n"
	"							Start from the first_ttl hop (instead from 1)\n"
	"-q nqueries  \n"
    "							Set the number of probes per each hop. Default is 3\n" 
	"-w"
	"							Wait for a probe no more than HERE (default 3)\n"
    "							times longer than a response from the same hop\n"
	"--help"
	"							Read this help and exit\n");
	exit(EXIT_SUCCESS);
}


int		ft_getopt(char **av, int ac, int nbr_add)
{
	const char *list_opt = "--mfwqn";  
	const char *list_opt_num = "mfwq";  
	int i;
	// int j;

	i = 0;
	while (++i < ac)
	{
		// j = 0;
		if (av[i][0] == '-' && i != nbr_add) //  && ft_strlen(av[i]) < 3  
		{
			if (!ft_strchr(list_opt + 1, av[i][1]))
				e_printf("bad option", 0);
			else if (ft_strchr(list_opt_num, av[i][1]))
			{
				if (i + 1 < ac && ft_str_is_numeric(av[i + 1]) && i + 1 != nbr_add) //i + 1 != nbr_add
				{
					save_opt_num(av[i][1], ft_atoi(av[i + 1]));
					i+=1;
				}
				else
				{
					printf("Option `%s' (argc %d) requires an argument \n", av[i], i);
					exit(EXIT_FAILURE);
				}
			}
			else if (ft_strequ((av[i]), "--help"))
					print_help_exit();
			else
				save_opt(av[i][1]);
		}
		else if (i != nbr_add)
			e_printf("bad option", 0);
	}
	return (0);
}

int		try_opt_addr(int ac, char **av)
{
	int i;
	int j; 
	struct addrinfo ai_addr;
    struct addrinfo *p_adr;

    i = 0;
	j = 0;
	p_adr = NULL;
	ft_memset(&ai_addr, 0, sizeof(ai_addr));
    while (++i < ac)
	{
		if (getaddrinfo(av[i], NULL, &ai_addr, &p_adr) == 0)
		{
			freeaddrinfo(p_adr);
			if (i - 1 > 0 && av[i - 1][0] == '-' && ft_strchr("fmwq", av[i - 1][1]) && ft_str_is_numeric(av[i]))
				continue;
			else if (j == 0)
				j = i;
			else
				print_help_exit();
		}
		else if (ft_strequ("--help", av[i]))
			print_help_exit();
	}
	return (j);
}