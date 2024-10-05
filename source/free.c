/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:24:12 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/05 20:24:28 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_clear_all(t_list **collected_data)
{
	t_list	*current;
	t_list	*next;

	current = *collected_data;
	while (current)
	{
		next = current->next;
		if (current->content)
			free_file((void **)&(current->content));
		free(current);
		current = next;
	}
	*collected_data = NULL;
}

void	free_file(void **file)
{
	t_file	*tmp;
	t_file	*next;

	while (*file && ((t_file *)(*file))->_prev)
		*file = ((t_file *)(*file))->_prev;
	tmp = (t_file *)(*file);
	while (tmp)
	{
		next = tmp->_next;
		if (tmp->_info)
			free(tmp->_info);
		if (tmp->_stat)
			free(tmp->_stat);
		if (tmp->_child)
			free_file((void **) &(tmp->_child));
		tmp->_next = NULL;
		tmp->_prev = NULL;
		tmp->_parent_dir = NULL;
		free(tmp);
		tmp = next;
	}
	*file = NULL;
}

void	free_double_pointer(char ***str)
{
	int	i;

	i = 0;
	if ((*str) == NULL)
		return ;
	while ((*str)[i])
		free((*str)[i++]);
	free(*str);
}
