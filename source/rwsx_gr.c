/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rwsx_gr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:06:23 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/05 21:06:23 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	gr_rd(mode_t m)
{
	if (m & S_IRGRP)
		write(1, "r", 1);
	else
		write(1, "-", 1);
}

void	gr_wr(mode_t m)
{
	if (m & S_IWGRP)
		write(1, "w", 1);
	else
		write(1, "-", 1);
}

void	gr_ex(mode_t m)
{
	if (m & S_ISGID)
	{
		if (m & S_IXGRP)
			write(1, "s", 1);
		else
			write(1, "S", 1);
	}
	else
	{
		if (m & S_IXGRP)
			write(1, "x", 1);
		else
			write(1, "-", 1);
	}
}
