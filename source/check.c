/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:11:40 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/05 21:03:43 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	sign_bit(unsigned char *flags, char c)
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
	else
	{
		ft_putstr_fd("ft_ls: invalid option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd("usage: ft_ls [-artlR] [file ...]", 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
}

unsigned char	check_args(int argc, char **argv)
{
	int				i;
	int				j;
	unsigned char	flags;

	i = -1;
	flags = 0;
	(void) argc;
	while (++i < argc - 1)
	{
		if (ft_strlen(argv[i]) > 1 && argv[i][0] == '-')
		{
			j = 0;
			while (argv[i][++j])
				sign_bit(&flags, argv[i][j]);
		}
		else
			break ;
	}
	return (flags);
}

void	print_errors(char **av, int i, int error_count)
{
	char	**errors;
	DIR		*dir;
	char	*tmp;
	char	*tmp2;
	char	*str_err_msg;

	errors = (char **)malloc(sizeof(char *) * (error_count + 1));
	error_count = 0;
	while (av[i])
	{
		dir = opendir((const char *)av[i]);
		if (dir == NULL)
		{
			tmp = ft_strjoin(av[i], ": ");
			str_err_msg = ft_strdup(strerror(errno));
			tmp2 = ft_strjoin(tmp, str_err_msg);
			free(str_err_msg);
			free(tmp);
			errors[error_count++] = tmp2;
		}
		else
			closedir(dir);
		i++;
	}
	errors[error_count] = NULL;
	string_sort(errors, error_count, 0);
	i = 0;
	while (errors[i])
		print_err(errors[i++]);
	free_double_pointer(&errors);
}

size_t	get_err_count(char **av, int i)
{
	size_t		err_count;
	DIR			*dir;

	err_count = 0;
	if (!av)
		return (0);
	while (av[i])
	{
		dir = opendir((const char *)av[i]);
		if (dir == NULL)
			err_count++;
		else
			closedir(dir);
		i++;
	}
	return (err_count);
}

char	**path_parser(int ac, char **av, int *err, unsigned char flags)
{
	char		**paths;
	DIR			*dir;
	int			i;
	int			j;
	size_t		err_count;

	(void) flags;
	i = 1;
	while (av[i] && ft_strlen(av[i]) > 1 && av[i][0] == '-')
		i++;
	err_count = get_err_count(av, i);
	print_errors(av, i, err_count);
	if (err_count)
		*err = 1;
	if (ac - i == 0)
	{
		paths = (char **) malloc(sizeof(char *) * 2);
		if (!paths)
			return (NULL);
		paths[0] = (char *) malloc(sizeof(char) * PATH_MAX);
		if (!paths[0])
		{
			free(paths);
			return (NULL);
		}
		ft_strlcpy(paths[0], ".", PATH_MAX);
		paths[1] = NULL;
		return (paths);
	}
	if (ac - i - err_count == 0)
		return (NULL);
	paths = malloc(sizeof(char *) * (ac - i + 1 - err_count));
	j = -1;
	err_count = 0;
	while (++j < ac - i)
	{
		dir = opendir((const char *)av[i + j]);
		if (dir != NULL)
		{
			closedir(dir);
			paths[err_count] = (char *) malloc(sizeof(char) * PATH_MAX);
			ft_strlcpy(paths[err_count++], av[i + j], PATH_MAX);
		}
	}
	paths[err_count] = NULL;
	if (has_flag(flags, FLAG_T))
		string_sort_time(paths, ac - i - get_err_count(av, i), (uint8_t) has_flag(flags, FLAG_RR));
	else
		string_sort(paths, ac - i - get_err_count(av, i), (uint8_t) has_flag(flags, FLAG_RR));
	return (paths);
}
