#ifndef FT_LS_H
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
# define HAS_FLAG(x, y) ((x) & (y))
# define OW_RD(m) {if (m & S_IRUSR) write(1, "r", 1); else write(1, "-", 1);}
# define OW_WR(m) {if (m & S_IWUSR) write(1, "w", 1); else write(1, "-", 1);}
# define OEX_Q1(m) {if (m & S_IXUSR) write(1, "s", 1); else write(1, "S", 1);}
# define OEX_Q2(m) {if (m & S_IXUSR) write(1, "x", 1); else write(1, "-", 1);}
# define OW_EX(m) {if (m & S_ISUID) OEX_Q1(m) else OEX_Q2(m);}
# define GR_RD(m) {if (m & S_IRGRP) write(1, "r", 1); else write(1, "-", 1);}
# define GR_WR(m) {if (m & S_IWGRP) write(1, "w", 1); else write(1, "-", 1);}
# define GEX_Q1(m) {if (m & S_IXGRP) write(1, "s", 1); else write(1, "S", 1);}
# define GEX_Q2(m) {if (m & S_IXGRP) write(1, "x", 1); else write(1, "-", 1);}
# define GR_EX(m) {if (m & S_ISGID) GEX_Q1(m) else GEX_Q2(m);}
# define OTH_RD(m) {if (m & S_IROTH) write(1, "r", 1); else write(1, "-", 1);}
# define OTH_WR(m) {if (m & S_IWOTH) write(1, "w", 1); else write(1, "-", 1);}
# define OT_Q1(m) {if (m & S_IXOTH) write(1, "t", 1); else write(1, "T", 1);}
# define OT_Q2(m) {if (m & S_IXOTH) write(1, "x", 1); else write(1, "-", 1);}
# define OTH_EX(m) {if (m & S_ISVTX) OT_Q1(m) else OT_Q2(m);}


enum e_type {
	FT_FILE,
	FT_DIR,
	FT_LINK,
	FT_CHR,
	FT_BLK,
	FT_FIFO,
	FT_SOCK,
	FT_UNKNOWN
};

enum e_print {
	NO_PRINT_ERR,
	PRINT_ERR
};


typedef struct s_file {
	unsigned short	_type;
	struct dirent	*_info;
	struct stat		*_stat;
	unsigned int	_totalsize;
	char			_name[256];
	struct s_file	*_child;
	struct s_file	*_parent_dir;
	struct s_file	*_next;
	struct s_file	*_prev;
} t_file;

unsigned char	check_args(int argc, char **argv);
t_list			*collect_data(char **paths, unsigned char flags);
void			free_double_pointer(char ***str);
t_file			*ft_file_new(void);
t_file			*get_head_file(t_file *file);
void			stringSort(char **arr, int n, uint8_t reverse);
void			string_sort_time(char **arr, int n, uint8_t reverse);
void			ft_file_clear(t_file **lst);
void			write_files(t_file *files, char *root, unsigned char flags);
void	write_files_l(t_file *files, char*root, unsigned char flags);
void			write_paths(t_list *path_list, char **paths, int dir_count, unsigned char flags);
char			**path_parser(int ac, char **av, int *err, unsigned char flags);
uint8_t			find_max_lenght(t_file *files);
uint8_t			complete_to_eight(const char *name);
t_file 			*sort_files_alph(t_file *head);
t_file 			*sort_files_time(t_file *head);
t_file 			*sort_files_reverse(t_file *head);
size_t			arr_len(const char **arr);
void			print_err(char *error);
void			print_errors(char **av, int i, int error_count);
/* char			**sep_arr(char ***stack, char *needle); */
size_t			get_err_count(char **av, int i);
#endif