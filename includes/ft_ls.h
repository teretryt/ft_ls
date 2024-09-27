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
# include <string.h>
# include "../libft/libft.h"

// Dosya tipini belirleyen makro tanımı

enum F_TYPES {
	FT_FILE,
	FT_DIR,
	FT_LINK,
	FT_CHR,
	FT_BLK,
	FT_FIFO,
	FT_SOCK,
	FT_UNKNOWN
};

# define TRUE 1
# define FALSE 0
# define RETURN_TYPE(st) ({						\
	enum F_TYPES answer;						\
	if ((st.st_mode & S_IFMT) == S_IFREG)		\
		answer = FT_FILE;						\
	else if ((st.st_mode & S_IFMT) == S_IFDIR)	\
		answer = FT_DIR;						\
	else if ((st.st_mode & S_IFMT) == S_IFLNK)	\
		answer = FT_LINK;						\
	else if ((st.st_mode & S_IFMT) == S_IFCHR)	\
		answer = FT_CHR;						\
	else if ((st.st_mode & S_IFMT) == S_IFBLK)	\
		answer = FT_BLK;						\
	else if ((st.st_mode & S_IFMT) == S_IFIFO)	\
		answer = FT_FIFO;						\
	else if ((st.st_mode & S_IFMT) == S_IFSOCK)	\
		answer = FT_SOCK;						\
	else {										\
		answer  = FT_UNKNOWN;					\
	}											\
	answer;										\
})


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

#endif