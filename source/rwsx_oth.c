/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rwsx_oth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:06:20 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/05 21:06:21 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	oth_rd(mode_t m)
{
	if (m & S_IROTH)
		write(1, "r", 1);
	else
		write(1, "-", 1);
}

void	oth_wr(mode_t m)
{
	if (m & S_IWOTH)
		write(1, "w", 1);
	else
		write(1, "-", 1);
}

void	oth_ex(mode_t m)
{
	if (m & S_ISVTX)
	{
		if (m & S_IXOTH)
			write(1, "t", 1);
		else
			write(1, "T", 1);
	}
	else
	{
		if (m & S_IXOTH)
			write(1, "x", 1);
		else
			write(1, "-", 1);
	}
}
