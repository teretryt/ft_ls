#ifndef FT_LS_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <termios.h>
# include <time.h>
# include <errno.h>
# include <stdio.h>
# include "../libft/libft.h"

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

typedef struct s_file {
	unsigned short	_type;
	struct dirent	_info;
	unsigned int	_totalsize;
	char			_name[256];
	char			*_owner;
	struct s_file	*_inner;
	struct s_file	*_parent_dir;
	struct s_file	*_next;
	struct s_file	*_prev;
} t_file;

unsigned char	check_args(int argc, char **argv);
t_file			**collect_data(int ac, char **av, unsigned char flags);
void			free_double_pointer(char ***str);
#endif