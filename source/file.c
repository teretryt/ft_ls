/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:23:22 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/05 20:23:58 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

uint8_t	file_type(struct stat st)
{
	if ((st.st_mode & S_IFMT) == S_IFREG)
		return (FT_FILE);
	else if ((st.st_mode & S_IFMT) == S_IFDIR)
		return (FT_DIR);
	else if ((st.st_mode & S_IFMT) == S_IFLNK)
		return (FT_LINK);
	else if ((st.st_mode & S_IFMT) == S_IFCHR)
		return (FT_CHR);
	else if ((st.st_mode & S_IFMT) == S_IFBLK)
		return (FT_BLK);
	else if ((st.st_mode & S_IFMT) == S_IFIFO)
		return (FT_FIFO);
	else if ((st.st_mode & S_IFMT) == S_IFSOCK)
		return (FT_SOCK);
	else
		return (FT_UNKNOWN);
}
