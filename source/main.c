/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:29:10 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/05 20:29:41 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int	dir_count(int ac, char **av)
{
	int	i;

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
	write_paths(collected_data, paths, _dir_count, flags);
	ft_clear_all(&collected_data);
	free_double_pointer(&paths);
	if (collected_data == NULL)
		return (err);
	return (err);
}
