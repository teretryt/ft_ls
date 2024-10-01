#include "../includes/ft_ls.h"

static void	print_path_title(size_t j, char **arr, char *root)
{
	/* if (flag == 1)
		ft_putstr_fd("\n", 1); */
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
	char    **arr;
	t_file	*tmp;
	size_t  i;
	size_t  j;

	i = 0;
	tmp = file;
	while (tmp)
	{
		i++;
		tmp = tmp->_parent_dir;
	}
	arr = (char**)malloc(sizeof(char*) * (i + 1));
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

void    write_paths(t_list *path_list, char **paths, int dir_count, unsigned char flags)
{
	size_t i;

	i = 0;
	while (path_list)
	{
		if (dir_count > 1){
			ft_putstr_fd(paths[i++], 1);
			ft_putstr_fd(":\n", 1);
		}
		/* ft_putstr_fd(path_list->root, 1); */
		/* ft_putstr_fd("\n", 1); */
		write_files(get_head_file(path_list->content), path_list->root, flags);
		if (path_list->next && arr_len((const char **)paths) > 1)
			ft_putchar_fd('\n', 1);
		path_list = path_list->next;
	}
}

void	write_files(t_file *files, char *root, unsigned char flags)
{
	t_file	*tmp;
	size_t	i;
	size_t	max_len;

	if (!files)
		return ;
	if (HAS_FLAG(flags, FLAG_T))
		files = sort_files_time(files);
	else
		files = sort_files_alph(files);
	if (HAS_FLAG(flags, FLAG_RR))
		files = sort_files_reverse(files);
	tmp = files;
	i = 0;
	max_len = find_max_lenght(files);
	/* ft_putstr_fd(files->_info->d_name, 1);
	ft_putchar_fd(':', 1);
	if (files->_parent_dir != NULL)
		ft_putstr_fd(files->_parent_dir->_info->d_name, 1); */
	if (HAS_FLAG(flags, FLAG_R) && tmp->_parent_dir != NULL)
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
	while (HAS_FLAG(flags, FLAG_R) && files){
		if (files->_info->d_type == DT_DIR && strcmp(files->_info->d_name, ".") != 0 && strcmp(files->_info->d_name, "..") != 0){
			ft_putchar_fd('\n', 1);
			if (files->_child)
				write_files(files->_child, root, flags);
			else
				print_parent_path(files, root);
		}
		files = files->_next;
	}
}

void	print_err(char *error)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n" , 2);
}