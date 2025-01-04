/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:17:40 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/13 13:56:38 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void collect_files_l(t_file *file, const char *path, u_int8_t is_last)
{
	static t_file	*head = NULL;
	t_file			*files;

	ft_strlcpy(file->_name, path, sizeof(file->_name));
	if (head == NULL)
		head = file;
	else
	{
		files = head;
		while (files->_next)
			files = files->_next;
		files->_next = file;
	}
	if (is_last & 1)
	{
		_write_files_l(head, is_last);
		/* while (files)
		{
			//FREE FLANA
		} */
	}
}

static u_int8_t	collect_write_file(const char *path, unsigned char flags, u_int8_t is_last)
{
	t_file	*file;

	file = ft_file_new();
	if (!file)
		return (1);
	file->_info = (struct dirent *) malloc(sizeof(struct dirent));
	if (!file->_info)
		return (1);
	ft_strlcpy(file->_info->d_name, path, sizeof(file->_info->d_name));
	file->_info->d_type = DT_REG;
	file->_stat = (struct stat *) malloc(sizeof(struct stat));
	if (!file->_stat)
		return (1);
	lstat(path, file->_stat);
	if (has_flag(flags, FLAG_L))
		collect_files_l(file, path, is_last);
	else
		_write_files(file, is_last);
	return (0);
}


static u_int8_t	collect(t_file **_files, const char *path, t_file *parent_file, unsigned char flags, u_int8_t is_last)
{
	t_file			*files;
	t_file			*tmp;
	DIR				*dir;
	struct dirent	*entry;
	char			new_path[PATH_MAX];

	dir = opendir(path);
	if (!dir)
	{
		struct stat	buffer;
		if (stat(path, &buffer) == -1)
			return (1);
		if (buffer.st_mode & S_IFREG)
			return (collect_write_file(path, flags, is_last));
	}
	files = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!has_flag(flags, FLAG_A) && ft_strncmp(entry->d_name, ".", 1) == 0){
			entry = readdir(dir);
			continue ;
		}
		ft_strlcpy(new_path, path, sizeof(new_path));
		ft_strlcat(new_path, "/", sizeof(new_path));
		ft_strlcat(new_path, entry->d_name, sizeof(new_path));
		if (files == NULL)
		{
			files = ft_file_new();
			if (!files)
			{
				closedir(dir);
				return (1);
			}
			files->_info = (struct dirent *) malloc(sizeof(struct dirent));
			files->_info = ft_memcpy(files->_info, entry, sizeof(struct dirent));
			files->_stat = (struct stat *) malloc(sizeof(struct stat));
			lstat(new_path, files->_stat);
			if (parent_file)
			{
				parent_file->_child = files;
				files->_parent_dir = parent_file;
			}
		}
		else
		{
			tmp = ft_file_new();
			if (!tmp)
			{
				closedir(dir);
				return (1);
			}
			tmp->_info = (struct dirent *) malloc(sizeof(struct dirent));
			tmp->_info = ft_memcpy(tmp->_info, entry, sizeof(struct dirent));
			tmp->_stat = (struct stat *) malloc(sizeof(struct stat));
			lstat(new_path, tmp->_stat);
			tmp->_prev = files;
			files->_next = tmp;
			files = tmp;
			if (parent_file)
				files->_parent_dir = parent_file;
		}
		if (has_flag(flags, FLAG_R) && entry->d_type == DT_DIR)
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
				collect(NULL, new_path, files, flags, 0);
		entry = readdir(dir);
	}
	if (parent_file == NULL)
		*_files = files;
	closedir(dir);
	return (0);
}

t_list	*collect_data(char **paths, unsigned char flags, size_t last_file_idx)
{
	int		j;
	u_int8_t	ret;
	t_list	*p_list;
	t_list	*head;

	j = -1;
	if (!paths)
		return (NULL);
	while (paths[++j])
	{
		if (j == 0)
		{
			p_list = ft_lstnew(NULL);
			if (!p_list)
				return (NULL);
			head = p_list;
		}
		u_int8_t i = ((size_t)j == (last_file_idx & ~((size_t)1 << (sizeof(size_t) * 8 - 1)))) ? 1 : 0;
		i |= (last_file_idx & ((size_t)1 << (sizeof(size_t) * 8 - 1))) ? 2 : 0;
		ret = collect((t_file **)(&(p_list->content)), paths[j], NULL, flags, i);
		if (ret == 0)
		{
			ft_strlcat(p_list->root, paths[j], PATH_MAX);
			if (j + 1 != (int) arr_len((const char **)paths))
			{
				ft_lstadd_back(&p_list, ft_lstnew(NULL));
				p_list = p_list->next;
			}
		}
		else
			return (NULL);
	}
	return (head);
}
