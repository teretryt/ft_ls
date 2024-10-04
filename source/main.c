#include "../includes/ft_ls.h"

/* static void	debug(unsigned char args)
{
	ft_putstr_fd("DEBUG Flags: ", 1);
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
} */

static int	dir_count(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
		return (1);
	while (av[i] && av[i][0] && av[i][0] == '-')
		i++;
	return (ac - i);
}

int	main(int ac, char **av)
{
	unsigned char	flags;
	char			**paths;
	int				err;
	int				_dir_count;
	t_list			*collected_data;

	err = 0;
	flags = check_args(ac, &av[1]);
	paths = path_parser(ac, av, &err, flags);
	_dir_count = dir_count(ac, av);
	collected_data = collect_data(paths, flags);
	/* debug(flags);
	ft_putstr_fd("Roots----------------------:\n", 1);
	t_list *tmp = collected_data;
	while (tmp)
	{
		ft_putstr_fd(tmp->root, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
	ft_putstr_fd("Roots END------------------:\n", 1); */
	
	write_paths(collected_data, paths, _dir_count, flags);

	free_double_pointer(&paths);
	/* system("leaks ft_ls"); */
	if (collected_data == NULL)
		return err;
	return err;
}