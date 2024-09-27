#include "../includes/ft_ls.h"

static void sign_bit(unsigned char *flags, char c)
{
    if (c == 'a')
        *flags = *flags | 0x01;
    else if (c == 'R')
        *flags = *flags | 0x02;
    else if (c == 'l')
        *flags = *flags | 0x04;
    else if (c == 't')
        *flags = *flags | 0x08;
    else if (c == 'r')
        *flags = *flags | 0x10;
    else {
        ft_putstr_fd("ft_ls: illegal option -- '", 2);
        ft_putchar_fd(c, 2);
        ft_putstr_fd("'\n", 2);
        exit(1);
    }
}

unsigned char check_args(int argc, char **argv) 
{
    int           i;
    int           j;
    unsigned char flags;

    i = -1;
    flags = 0;
    while (argv[++i])
        if (argv[i][0] && argv[i][0] == '-')
        {
            j = 0;
            while (argv[i][++j])
                sign_bit(&flags, argv[i][j]);
        }
    return (flags);
}