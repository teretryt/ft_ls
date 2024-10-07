/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:40:56 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/07 23:29:43 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	write_total(size_t total)
{
	ft_putstr_fd("total ", 1);
	ft_putnbr_fd((int) total, 1);
	ft_putchar_fd('\n', 1);
}

static void	write_size(off_t size, size_t max_len)
{
	int	tmp;
	int	max;

	tmp = size;
	max = 0;
	if (max_len == 0)
		max = 1;
	while (max_len)
	{
		max_len /= 10;
		max++;
	}
	if (size == 0)
		tmp = 1;
	while (tmp)
	{
		tmp /= 10;
		max--;
	}
	while (max--)
		ft_putchar_fd(' ', 1);
	ft_putnbr_fd(size, 1);
	ft_putchar_fd(' ', 1);
}

static void	write_owner(uid_t st_uid, size_t max_len)
{
	struct passwd	*pw;

	pw = getpwuid(st_uid);
	ft_putstr_fd(pw->pw_name, 1);
	max_len = max_len - ft_strlen(pw->pw_name);
	while (max_len-- > 0)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd("  ", 1);
}

static void	write_group(gid_t st_gid, size_t max_len)
{
	struct group	*gr;

	gr = getgrgid(st_gid);
	ft_putstr_fd(gr->gr_name, 1);
	max_len = max_len - ft_strlen(gr->gr_name);
	while (max_len-- > 0)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd("  ", 1);
}

static void	write_link_count(nlink_t n, size_t max)
{
	uint16_t	tmp;
	uint8_t		max_len;

	tmp = n;
	max_len = 0;
	while (max)
	{
		max /= 10;
		max_len++;
	}
	while (tmp)
	{
		tmp /= 10;
		max_len--;
	}
	while (max_len--)
		ft_putchar_fd(' ', 1);
	ft_putnbr_fd(n, 1);
	ft_putchar_fd(' ', 1);
}

static void	write_file_type(mode_t	m)
{
	if (S_ISREG(m))
		ft_putchar_fd('-', 1);
	else if (S_ISDIR(m))
		ft_putchar_fd('d', 1);
	else if (S_ISLNK(m))
		ft_putchar_fd('l', 1);
	else if (S_ISCHR(m))
		ft_putchar_fd('c', 1);
	else if (S_ISBLK(m))
		ft_putchar_fd('b', 1);
	else if (S_ISFIFO(m))
		ft_putchar_fd('p', 1);
	else if (S_ISSOCK(m))
		ft_putchar_fd('s', 1);
	else
		ft_putchar_fd('?', 1);
}

static void	output_permissions(mode_t m)
{
	ow_rd(m);
	ow_wr(m);
	ow_ex(m);
	gr_rd(m);
	gr_wr(m);
	gr_ex(m);
	oth_rd(m);
	oth_wr(m);
	oth_ex(m);
	ft_putstr_fd("  ", 1);
}

static void	print_path_title(size_t j, char **arr, char *root)
{
	ft_putstr_fd(root, 1);
	ft_putstr_fd("/", 1);
	while (j > 0)
	{
		ft_putstr_fd(arr[--j], 1);
		if (j != 0)
			ft_putstr_fd("/", 1);
	}
	ft_putstr_fd(":\n", 1);
}

static void	print_parent_path(t_file *file, char *root)
{
	char	**arr;
	t_file	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	tmp = file;
	while (tmp)
	{
		i++;
		tmp = tmp->_parent_dir;
	}
	arr = (char **) malloc(sizeof(char *) * (i + 1));
	j = 0;
	while (file)
	{
		arr[j++] = ft_strdup(file->_info->d_name);
		file = file->_parent_dir;
	}
	arr[j] = NULL;
	print_path_title(j, arr, root);
	free_double_pointer(&arr);
}

void	write_paths(t_list *path_list, char **paths, int dir_count, unsigned char flags)
{
	size_t	i;

	i = 0;
	while (path_list)
	{
		if (dir_count > 1)
		{
			ft_putstr_fd(paths[i++], 1);
			ft_putstr_fd(":\n", 1);
		}
		if (has_flag(flags, FLAG_L))
			write_files_l(get_head_file(path_list->content), path_list->root, flags);
		else
			write_files(get_head_file(path_list->content), path_list->root, flags);
		if (path_list->next && arr_len((const char **)paths) > 1)
			ft_putchar_fd('\n', 1);
		path_list = path_list->next;
	}
}

size_t	*get_max_values(t_file *files)
{
	struct group	*_group;
	struct passwd	*pw;
	size_t			*r;

	r = (size_t *)malloc(sizeof(size_t) * 5);
	if (!files || !r)
		return (NULL);
	r[0] = 0;
	r[1] = 0;
	r[2] = 0;
	r[3] = 0;
	r[4] = 0;
	while (files)
	{
		_group = getgrgid(files->_stat->st_gid);
		pw = getpwuid(files->_stat->st_uid);
		if (!pw || !_group)
		{
			ft_putstr_fd("Permission denied.\n", 2);
			return (NULL);
		}
		if (files->_stat->st_nlink > (int)r[0])
			r[0] = files->_stat->st_nlink;
		if (ft_strlen(pw->pw_name) > (int) r[1])
			r[1] = ft_strlen(pw->pw_name);
		if (ft_strlen(_group->gr_name) > (int) r[2])
			r[2] = ft_strlen(_group->gr_name);
		if (files->_stat->st_size > (int) r[3])
			r[3] = files->_stat->st_size;
		r[4] += (size_t) files->_stat->st_blocks;
		files = files->_next;
	}
	return (r);
}

void	write_files_l(t_file *files, char *root, unsigned char flags)
{
	t_file	*tmp;
	size_t	i;
	size_t	max_len;
	size_t	*max_lens;
	char	*time;

	if (!files)
		return ;
	if (has_flag(flags, FLAG_T))
		files = sort_files_time(files);
	else
		files = sort_files_alph(files);
	if (has_flag(flags, FLAG_RR))
		files = sort_files_reverse(files);
	tmp = files;
	i = 0;
	max_len = find_max_lenght(files);
	if (has_flag(flags, FLAG_R) && tmp->_parent_dir != NULL)
		print_parent_path(tmp->_parent_dir, root);
	max_lens = get_max_values(tmp);
	if (!max_lens)
		exit(1);
	write_total(max_lens[4]);
	while (tmp)
	{
		write_file_type(tmp->_stat->st_mode);
		output_permissions(tmp->_stat->st_mode);
		write_link_count(tmp->_stat->st_nlink, max_lens[0]);
		write_owner(tmp->_stat->st_uid, max_lens[1]);
		write_group(tmp->_stat->st_gid, max_lens[2]);
		write_size(tmp->_stat->st_size, max_lens[3]);
		time = ft_substr(ctime(&(tmp->_stat->st_mtime)), 4, 12);
		ft_putstr_fd(time, 1);
		free(time);
		ft_putstr_fd(" ", 1);
		if (tmp->_info->d_type != DT_LNK)
		{
			ft_putstr_fd(tmp->_info->d_name, 1);
			i = ft_strlen(tmp->_info->d_name);
			while (i++ < max_len)
				ft_putchar_fd(' ', 1);
		}
		else {
			char	path[4096];
			char	buffer[4096];
			ssize_t	linkLen;
			t_file	*tmpp;

			tmpp = tmp;
			path[0] = 0;
			buffer[0] = 0;
			while (tmpp->_parent_dir)
			{
				ft_strlcpy(buffer, path, 4096);
				ft_strlcpy(path, "/", 4096);
				ft_strlcat(path, tmpp->_info->d_name, 4096);
				ft_strlcat(path, buffer, 4096);
				tmpp = tmpp->_parent_dir;
			}
			ft_strlcpy(buffer, path, 4096);
			ft_strlcpy(path, root, 4096);
			ft_strlcat(path, "/", 4096);
			ft_strlcat(path, tmpp->_info->d_name, 4096);
			ft_strlcat(path, buffer, 4096);
			linkLen = readlink(path, buffer, 4096);
			if (linkLen == -1)
				perror("readlink");
			else
				buffer[linkLen] = '\0';
			ft_putstr_fd(tmp->_info->d_name, 1);
			ft_putstr_fd(" -> ", 1);
			ft_putstr_fd(buffer, 1);
		}
		ft_putchar_fd('\n', 1);
		tmp = tmp->_next;
	}
	if (max_lens)
		free(max_lens);
	while (has_flag(flags, FLAG_R) && files)
	{
		if (files->_info->d_type == DT_DIR && strcmp(files->_info->d_name, ".") != 0 && strcmp(files->_info->d_name, "..") != 0)
		{
			ft_putchar_fd('\n', 1);
			if (files->_child)
				write_files_l(files->_child, root, flags);
			else
				print_parent_path(files, root);
		}
		files = files->_next;
	}
}

void	write_files(t_file *files, char *root, unsigned char flags)
{
	t_file	*tmp;
	size_t	i;
	size_t	max_len;

	if (!files)
		return ;
	if (has_flag(flags, FLAG_T))
		files = sort_files_time(files);
	else
		files = sort_files_alph(files);
	if (has_flag(flags, FLAG_RR))
		files = sort_files_reverse(files);
	tmp = files;
	i = 0;
	max_len = find_max_lenght(files);
	if (has_flag(flags, FLAG_R) && tmp->_parent_dir != NULL)
		print_parent_path(tmp->_parent_dir, root);
	while (tmp)
	{
		ft_putstr_fd(tmp->_info->d_name, 1);
		i = ft_strlen(tmp->_info->d_name);
		while (i++ < max_len)
			ft_putchar_fd(' ', 1);
		tmp = tmp->_next;
	}
	ft_putchar_fd('\n', 1);
	while (has_flag(flags, FLAG_R) && files)
	{
		if (files->_info->d_type == DT_DIR && strcmp(files->_info->d_name, ".") != 0 && strcmp(files->_info->d_name, "..") != 0)
		{
			ft_putchar_fd('\n', 1);
			if (files->_child)
				write_files(files->_child, root, flags);
			else
				print_parent_path(files, root);
		}
		files = files->_next;
	}
}

void	print_err(char	*error)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
