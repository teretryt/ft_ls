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

static uint8_t	collect(t_file **_files, const char *path, t_file *parent_file, unsigned char flags)
{
	t_file			*files;
	t_file			*tmp;
	DIR				*dir;
	struct dirent	*entry;
	char new_path[PATH_MAX];
	
	(void) flags;
	dir = opendir(path);
	files = NULL;
	while ((entry = readdir(dir)) != NULL) {
		if (!HAS_FLAG(flags, FLAG_A) && ft_strncmp(entry->d_name, ".", 1) == 0)
			continue;
		ft_strlcpy(new_path, path, sizeof(new_path));
		ft_strlcat(new_path, "/", sizeof(new_path));
		ft_strlcat(new_path, entry->d_name, sizeof(new_path));
/* 		ft_putstr_fd("New PATH: ", 1);
		ft_putstr_fd(new_path, 1); */
		if (files == NULL)
		{
			files = ft_file_new();
			if (!files)
				return (1);
			files->_info = (struct dirent *) malloc(sizeof(struct dirent));
			files->_info = ft_memcpy(files->_info, entry, sizeof(struct dirent));
			files->_stat = (struct stat *) malloc(sizeof(struct stat));
			lstat(new_path, files->_stat);
			if (parent_file){
				parent_file->_child = files;
				files->_parent_dir = parent_file;
			}
		}
		else
		{
			tmp = ft_file_new();
			if (!tmp)
				return (1);
			tmp->_info = malloc(sizeof(struct dirent));
			tmp->_info = ft_memcpy(tmp->_info, entry, sizeof(struct dirent));
			tmp->_stat = (struct stat *) malloc(sizeof(struct stat));
			lstat(new_path, tmp->_stat);
			tmp->_prev = files;
			files->_next = tmp;
			files = tmp;
			if (parent_file)
				files->_parent_dir = parent_file;
		}
		
		if (HAS_FLAG(flags, FLAG_R) && entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0){
				ft_putstr_fd("Recursing into: ", 1);
				collect(NULL, new_path, files, flags);
			}
		} 
		if (entry->d_type == DT_REG)
		{
			/*printf("Dosya: %s/%s\n", path, entry->d_name);*/
		}
	}
	if (parent_file == NULL)
		*_files = files;
	closedir(dir);
	return (0);
}

t_list	*collect_data(char **paths, unsigned char flags)
{
	int		j;
	uint8_t	ret;
	t_list	*p_list;
	t_list 	*head;

	j = -1;
	if (!paths)
		return (NULL);
	while(paths[++j])
	{
		if (j == 0)
		{
			p_list = ft_lstnew((void *) malloc(sizeof(t_file)));
			head = p_list;
		}
		ret = collect((t_file **) (&(p_list->content)), paths[j], NULL, flags);
		if (ret == 0)
		{
			ft_strlcat(p_list->root, paths[j], PATH_MAX);
			if (j + 1 != (int) arr_len((const char **)paths))
			{
				ft_lstadd_back(&p_list, ft_lstnew((void *) malloc(sizeof(t_file))));
				p_list = p_list->next;
			}
		}
	}
	return (head);
}