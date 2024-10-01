#include "../includes/ft_ls.h"


t_file    *ft_file_new(void)
{
    t_file	*nodes;

    nodes = (t_file *)malloc(sizeof(t_file));
    if (!nodes)
        return (NULL);
    nodes->_type = FT_UNKNOWN;
    nodes->_child = NULL;
    nodes->_next = NULL;
    nodes->_prev = NULL;
    nodes->_parent_dir = NULL;
    return (nodes);
}

t_file  *get_head_file(t_file *file)
{
    if (!file)
        return (NULL);
    while (file->_parent_dir != NULL || file->_prev != NULL)
    {
        if (file->_parent_dir != NULL)
            file = file->_parent_dir;
        else
            file = file->_prev;
    }
    return (file);
}

void	ft_file_clear(t_file **lst)
{
	t_file	*sup;

	if (!lst)
		return ;
	while (*lst)
	{
        if ((*lst)->_child)
            ft_file_clear(&((*lst)->_child));
		sup = (*lst)->_next;
		//del((*lst)->content);
        write(1, "free\n", 5);
		free(*lst);
        write(1, "freed\n", 6);
		*lst = sup;
	}
	*lst = NULL;
}

/* char    **sep_arr(char ***stack, char *needle)
{
    size_t  i;
    size_t  len;
    char    **ret;

    i = -1;
    if (!stack || !needle)
        return NULL;
    len = arr_len((const char **)(*stack));
    ret = (char **)malloc(sizeof(char *) * (len + 1));
    if (!ret)
        return NULL;
    while(++i < len)
        ret[i] = ft_strdup(*stack[i]);
    ret[i] = NULL;
    return (ret);
} */