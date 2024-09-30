#include "../includes/ft_ls.h"

static void	debug(unsigned char args)
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
}

int	main(int ac, char **av)
{
	unsigned char flags = check_args(ac, &av[1]);
	char **paths = path_parser(ac, av);
	debug(flags);
	t_list *collected_data = collect_data(ac, av, paths, flags);
	ft_putstr_fd("Roots----------------------:\n", 1);
	t_list *tmp = collected_data;
	while (tmp)
	{
		ft_putstr_fd(tmp->root, 1);
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
	ft_putstr_fd("Roots END------------------:\n", 1);
	write_paths(collected_data, paths, flags);
	//system("leaks ft_ls");

	free_double_pointer(&paths);
	if (collected_data == NULL)
		return 0;
	return 0;
}