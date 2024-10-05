/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcelik <tcelik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 20:49:39 by tcelik            #+#    #+#             */
/*   Updated: 2024/10/05 21:04:39 by tcelik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <termios.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include "../libft/libft.h"
# define PATH_MAX 4096
# define FLAG_A 0x01
# define FLAG_R 0x02
# define FLAG_L 0x04
# define FLAG_T 0x08
# define FLAG_RR 0x10

enum e_type
{
	FT_FILE,
	FT_DIR,
	FT_LINK,
	FT_CHR,
	FT_BLK,
	FT_FIFO,
	FT_SOCK,
	FT_UNKNOWN
};

enum e_print
{
	NO_PRINT_ERR,
	PRINT_ERR
};

typedef struct s_file
{
	unsigned short	_type;
	struct dirent	*_info;
	struct stat		*_stat;
	unsigned int	_totalsize;
	char			_name[256];
	struct s_file	*_child;
	struct s_file	*_parent_dir;
	struct s_file	*_next;
	struct s_file	*_prev;
}	t_file;

unsigned char	check_args(int argc, char **argv);
t_list			*collect_data(char **paths, unsigned char flags);
void			free_double_pointer(char ***str);
void			ft_clear_all(t_list **collected_data);
void			free_file(void **file);
t_file			*ft_file_new(void);
t_file			*get_head_file(t_file *file);
void			string_sort(char **arr, int n, uint8_t reverse);
void			string_sort_time(char **arr, int n, uint8_t reverse);
void			write_files(t_file *files, char *root, unsigned char flags);
void			write_files_l(t_file *files, char*root, unsigned char flags);
void			write_paths(t_list *path_list, char **paths, \
					int dir_count, unsigned char flags);
char			**path_parser(int ac, char **av, int *err, unsigned char flags);
uint8_t			find_max_lenght(t_file *files);
uint8_t			complete_to_eight(const char *name);
t_file			*sort_files_alph(t_file *head);
t_file			*sort_files_time(t_file *head);
t_file			*sort_files_reverse(t_file *head);
size_t			arr_len(const char **arr);
void			print_err(char *error);
void			print_errors(char **av, int i, int error_count);
size_t			get_err_count(char **av, int i);
int				has_flag(uint8_t x, uint8_t	y);
void			ow_rd(mode_t m);
void			ow_wr(mode_t m);
void			ow_ex(mode_t m);
void			gr_rd(mode_t m);
void			gr_wr(mode_t m);
void			gr_ex(mode_t m);
void			oth_rd(mode_t m);
void			oth_wr(mode_t m);
void			oth_ex(mode_t m);
#endif
