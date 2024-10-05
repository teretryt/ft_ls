/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rwsx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:59:08 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/05 21:04:45 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	has_flag(uint8_t x, uint8_t	y)
{
	return ((x) & (y));
}

void	ow_rd(mode_t m)
{
	if (m & S_IRUSR)
		write(1, "r", 1);
	else
		write(1, "-", 1);
}

void	ow_wr(mode_t m)
{
	if (m & S_IWUSR)
		write(1, "w", 1);
	else
		write(1, "-", 1);
}

void	ow_ex(mode_t m)
{
	if (m & S_ISUID)
	{
		if (m & S_IXUSR)
			write(1, "s", 1);
		else
			write(1, "S", 1);
	}
	else
	{
		if (m & S_IXUSR)
			write(1, "x", 1);
		else
			write(1, "-", 1);
	}
}
