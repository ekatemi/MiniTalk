#include "minitalk.h"


void ft_putnbr_fd(int n, int fd)
{
    char *idx = "0123456789";

    if (n > 9)
        ft_putnbr_fd(n / 10, fd);
    write(fd, &idx[n % 10], 1);
}

void ft_putendl_fd(char *str, int fd)
{
    if (!str)
        return ;
    while (*str)
    {
        write(1, str, 1);
        str++;
    }
    write(fd, "\n", 1);
}

void ft_putstr_fd(char *str, int fd)
{
    if (!str)
        return ;
    while (*str)
    {
        write(fd, str, 1);
        str++;
    }
}

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ');
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	res = res * sign;
	return (res);
}

void	error_sigaction(void)
{
	ft_putendl_fd("Error with the server\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	error_kill(void)
{
	ft_putendl_fd("Error sending signal", STDERR_FILENO);
	exit(EXIT_FAILURE);
}