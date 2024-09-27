#include "../includes/ft_ls.h"

void	stringSort(char **arr, int n) {
	char temp[4096];

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			// strcmp kullanarak stringleri karşılaştırıyoruz
			if (ft_strcmp(arr[i], arr[j]) > 0) {
				ft_strlcpy(temp, arr[i], 4096);
				ft_strlcpy(arr[i], arr[j], 4096);
				ft_strlcpy(arr[j], temp, 4096);
			}
		}
	}
}

static void	collect(const char *path, unsigned char flags)
{
	DIR				*dir;
	struct dirent	*entry;
	
	(void) flags;
	dir = opendir(path);
	if (dir == NULL) {
		printf("ft_ls: %s\n", strerror(errno));
		return;
	}
	
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_DIR) {
			char new_path[1024];
			if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0) {
				continue;
			}
			snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
			printf("Dizin: %s\n", new_path);
			/* collect(new_path, flags); */
		} else {
			printf("Dosya: %s/%s\n", path, entry->d_name);
		}
	}
	closedir(dir);
}

t_file	**collect_data(int ac, char **av, unsigned char flags)
{
	int		i;
	int		j;
	char**	paths;

	i = 1;
	while (av[i] && av[i][0] && av[i][0] == '-')
		i++;
	if (i == ac)
	{
		collect(".", flags);
		return (NULL);
	}
	paths = malloc(sizeof(char *) * (ac - i + 1));
	j = -1;
	while (++j < ac - i){
		write(1, "Toplanacak pathler sıralanıyor...\n", 34);
		ft_putnbr_fd(ac - i, 1);ft_putchar_fd('\n', 1);
		paths[j] = ft_strdup(av[i + j]);
	}
	paths[j] = NULL;
	stringSort(paths, ac - i);
	j = 0;
	while(j < ac - i)
	{
		ft_putstr_fd("Toplanacak path:", 1);
		ft_putstr_fd(paths[j],1);ft_putchar_fd('\n', 1);
		collect(paths[j++], flags);
	}
	free_double_pointer(&paths);
	return (NULL);
}

