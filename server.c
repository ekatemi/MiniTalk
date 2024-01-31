#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void ft_putnbr(pid_t pid)
{
    char idx[10] = "0123456789";
    if (pid > 9)
        ft_putnbr(pid / 10);
    write (1, &idx[pid % 10], 1);
}

static void print_pid(pid_t pid)
{
    write (1, "The PID is : ", 13);
    ft_putnbr(pid);
}

int main ()
{
    pid_t pid;
    pid = getpid();
    if (pid == -1)
        return (1);
    print_pid(pid);
    while (1)
    {
        sleep(1);
    }
    return(0);
}