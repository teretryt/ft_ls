#include "../includes/ft_ls.h"

uint8_t find_max_lenght(t_file *files)
{
	uint8_t i;

	i = 0;
	while (files)
	{
		if (i < (uint8_t) ft_strlen(files->_info->d_name) + complete_to_eight(files->_info->d_name))
			i = (uint8_t) ft_strlen(files->_info->d_name) + complete_to_eight(files->_info->d_name);
		files = files->_next;
	}
	return (i);
}

uint8_t complete_to_eight(const char *name)
{
	uint8_t len;

	len = (uint8_t) ft_strlen(name);
	return (len % 8 == 0 ? 8 : 8 - len % 8);
}

size_t  arr_len(const char **arr)
{
	size_t i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}