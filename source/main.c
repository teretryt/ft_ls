/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:29:10 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/13 00:50:56 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static size_t get_last_file_idx(char **paths)
{
	size_t last_file_idx = 0;
	size_t i = -1;
	size_t flag = 0;
	while (paths[++i])
	{
		DIR *dir = opendir(paths[i]);
		if (!dir)
			last_file_idx = i;
		else
			flag = 1;
	}
	return (flag) ? last_file_idx + ((size_t)1 << (sizeof(size_t) * 8 - 1)) : last_file_idx;
}

static int	arg_count(int ac, char **av)
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
	int				_arg_count;
	t_list			*collected_data;

	err = 0;
	flags = check_args(ac, &av[1]);
	paths = path_parser(ac, av, &err, flags);
	_arg_count = arg_count(ac, av);
	size_t last_file_idx = get_last_file_idx(paths);
	collected_data = collect_data(paths, flags, last_file_idx);
	write_paths(collected_data, paths, _arg_count, flags);
	ft_clear_all(&collected_data);
	free_double_pointer(&paths);
	if (collected_data == NULL)
		return (err);
	return (err);
}
