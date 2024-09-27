#include "../includes/ft_ls.h"

static void debug(unsigned char args)
{
    ft_putstr_fd("debug: ", 1);
    if (args & 0x01)
        ft_putstr_fd("a", 1);
    if (args & 0x02)
        ft_putstr_fd("R", 1);
    if (args & 0x04)
        ft_putstr_fd("l", 1);
    if (args & 0x08)
        ft_putstr_fd("t", 1);
    if (args & 0x10)
        ft_putstr_fd("r", 1);
    ft_putstr_fd("\n", 1);
}

int main(int ac, char **av)
{
    unsigned char flags = check_args(ac, &av[1]);
    debug(flags);
    
    t_file **collected_data = collect_data(ac, av, flags);
    return 0;
}