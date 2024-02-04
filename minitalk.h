#ifndef MINITALK_H
# define MINITALK_H

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	error_sigaction(void);
void    ft_putnbr_fd(int n, int fd);
void    ft_putendl_fd(char *str, int fd);
void    ft_putstr_fd(char *str, int fd);
int     ft_atoi(const char *nptr);

#endif