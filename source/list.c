/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:27:56 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/05 20:28:51 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file	*ft_file_new(void)
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

t_file	*get_head_file(t_file *file)
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
