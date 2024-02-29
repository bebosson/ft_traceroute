#include "ft_traceroute.h"
 
int		save_first_ttl(int num)
{
	if (num < 1 || num > 30 || pr.opt_fttl == 1)
	{
		if (num < 1 || num > 30)
			printf("first hop out of range");
		else if (pr.opt_fttl == 1)
			printf("option already set");
		exit(EXIT_FAILURE);
	}
	pr.fttl = num;
	return (1);
}

int		save_max_ttl(int num)
{
	if (num < 1 || num > 255 || pr.opt_mttl == 1)
	{
		if (num < 1)
			printf("ping: can't set unicast time-to-live: Argument invalide");
		else if (num > 255)
			printf("ping: ttl %d out of range", num);
		else if (pr.opt_mttl == 1)
			printf("option already set");
		exit(EXIT_FAILURE);
	}
	pr.ttlmax = num + 1;
	return (1);
}

int		save_max_time(int num)
{
	if (num < 0 || num > INT16_MAX || pr.opt_wait == 1)
	{
		if (num < 0)
			printf("bad wait specifications `%d' used", num);
		else if (num > INT16_MAX)
			printf("bad wait specifications `%d' used (max %d)", num, INT16_MAX);
		else if (pr.opt_wait == 1)
			printf("option already set");
		exit(EXIT_FAILURE);
	}
	pr.wait = num;
	return (1);
}

int		save_max_queries(int num)
{
	if (num < 0 || num > 10 || pr.opt_nque == 1)
	{
		if (num < 0)
			printf("no less than 0 hops");
		else if (num > 10)
			printf("no more than 10 probes per hop");
		else if (pr.opt_nque == 1)
			printf("option already set");
		exit(EXIT_FAILURE);
	}
	pr.nqueries = num;
	return (1);
}

void 	save_opt_num(char opt, int num)
{
	switch (opt)
	{
		case 'm':
			pr.opt_mttl = save_max_ttl(num);
			break;
		case 'f':
			pr.opt_fttl = save_first_ttl(num);
			break;
		case 'w':
			pr.opt_wait = save_max_time(num);
			break;
		case 'q':
			pr.opt_nque = save_max_queries(num);
			break;
	}
}

int		already_set(int opt)
{
	if (opt == 1)
		e_printf("option already set", 0);
	else
		return 1;
	return 0;
}

void 	save_opt(char opt)
{
	switch (opt)
	{
		case 'v':
		// no need
			pr.opt_verb = already_set(pr.opt_verb);
			break;
		case 'h':
			print_help_exit();
			break;
		case 'n':
			pr.opt_name = already_set(pr.opt_name);
	}
}