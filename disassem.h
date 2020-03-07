
#ifndef DISASSEM_H 
# define DISASSEM_H
# include <fcntl.h>
# include "ft_printf.h"
# include "libft.h"
# include "op.h"
#include <stdint.h>

#endif


typedef struct			s_reader
{
    char				*name;
    char                *comment;
    int					column;
    int					line;
	int					code_size;
	int 				i;
    int                 f_head;
    char                *filename;
}						t_reader;