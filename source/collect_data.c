#include "../includes/ft_ls.h"



/*
Example directory structure:
	- file0.txt
	- dir1
		- file1.txt
		- file2.txt
		- subdir1
			- file3.txt
	- dir2
		- file4.txt
	- file5.txt
	- file6.txt
*/



static void	collect(t_file **_files, const char *path, t_file *parent_file, unsigned char flags)
{
	t_file			*files;
	t_file			*tmp;
	DIR				*dir;
	struct dirent	*entry;
	
	(void) flags;
	dir = opendir(path);
	if (dir == NULL) {
		printf("ft_ls: %s\n", strerror(errno));
		return;
	}
	files = NULL;
	while ((entry = readdir(dir)) != NULL) {
		if ((flags & 0x01) == 0 && ft_strncmp(entry->d_name, ".", 1) == 0)
			continue;
		if (files == NULL)
		{
			files = ft_file_new();
			if (!files)
				return ;
			files->_info = (struct dirent *) malloc(sizeof(struct dirent));
			files->_info = ft_memcpy(files->_info, entry, sizeof(struct dirent));
			if (parent_file){
				parent_file->_child = files;
				files->_parent_dir = parent_file;
			}
		}
		else
		{
			tmp = ft_file_new();
			if (!tmp)
				return ;
			tmp->_info = malloc(sizeof(struct dirent));
			tmp->_info = ft_memcpy(tmp->_info, entry, sizeof(struct dirent));
			tmp->_prev = files;
			files->_next = tmp;
			files = tmp;
			if (parent_file)
				files->_parent_dir = parent_file;
		}
		if ((flags & 0x02) == 0x02 && entry->d_type == DT_DIR) {
			char new_path[4096];
			ft_strlcpy(new_path, path, sizeof(new_path));
			ft_strlcat(new_path, "/", sizeof(new_path));
			ft_strlcat(new_path, entry->d_name, sizeof(new_path));
			/*printf("Dizin: %s\n", new_path);*/
			collect(NULL, new_path, files, flags);
		} 
		if (entry->d_type == DT_REG)
		{
			/*printf("Dosya: %s/%s\n", path, entry->d_name);*/
		}
	}
	if (parent_file == NULL)
		*_files = files;
	closedir(dir);
}

t_list	*collect_data(int ac, char **av, char **paths, unsigned char flags)
{
	int		i;
	int		j;
	t_list	*p_list;
	t_list 	*head;

	i = 1;
	while (av[i] && av[i][0] && av[i][0] == '-')
		i++;
	if (i == ac)
	{
		p_list = ft_lstnew((void *) malloc(sizeof(t_file)));
		collect((t_file **) (&(p_list->content)), ".", NULL, flags);
		ft_putstr_fd("Toplanacak path yok, mevcut dizin toplanıyor...\n", 1);
		return (p_list);
	}
	j = 0;
	while(j < ac - i)
	{
		if (j == 0)
		{
			p_list = ft_lstnew((void *) malloc(sizeof(t_file)));
			head = p_list;
		}
		ft_putstr_fd("Toplanacak path:", 1);
		ft_putstr_fd(paths[j],1);ft_putchar_fd('\n', 1);
		collect((t_file **) (&(p_list->content)), paths[j], NULL, flags);
		if (++j != ac - i)
		{
			ft_lstadd_back(&p_list, ft_lstnew((void *) malloc(sizeof(t_file))));
			p_list = p_list->next;
		}
	}
	return (head);
}