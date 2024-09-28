#include "../includes/ft_ls.h"

void    write_paths(t_list *path_list, char **paths, unsigned char flags)
{
	(void)flags;
    while (path_list)
    {
		if (paths){
			ft_putstr_fd(*paths, 1);
			ft_putstr_fd("-------------------\n", 1);
			paths++;
		}
        write_files(get_head_file(path_list->content));
        path_list = path_list->next;
    }
}

void	write_files(t_file *files)
{
	t_file	*tmp;

	tmp = files;
	while (tmp)
	{
        if (tmp->_info->d_type == DT_DIR)
            ft_putstr_fd("DIR: ", 1);
        else if (tmp->_parent_dir != NULL && tmp->_info->d_type == DT_REG)
            ft_putstr_fd("\t- ", 1);
		ft_putstr_fd(tmp->_info->d_name, 1);
		ft_putchar_fd('\n', 1);
		if (tmp->_child)
			write_files(tmp->_child);
		tmp = tmp->_next;
	}
}