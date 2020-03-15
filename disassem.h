/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassem.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 19:40:59 by galiza            #+#    #+#             */
/*   Updated: 2020/03/15 22:16:42 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASSEM_H
# define DISASSEM_H
# include <fcntl.h>
# include "ft_printf.h"
# include "libft.h"
# include "op.h"
# include <stdint.h>
# include "assem.h"
# include <stdbool.h>

typedef struct			s_read
{
	char				*name;
	char				*comment;
	int					code_size;
	uint8_t				*code;
	uint8_t				arg_types;
	int					i;
	char				*filename;
}						t_read;

char					*d_errors(int error);
void					read_codefile(t_read *reader, int fd);
char					*ft_d_live(t_read *reader);
char					*ft_d_ld(t_read *reader);
char					*ft_d_st(t_read *reader);
char					*ft_d_add(t_read *reader);
char					*ft_d_sub(t_read *reader);
char					*ft_d_and(t_read *reader);
char					*ft_d_or(t_read *reader);
char					*ft_d_xor(t_read *reader);
char					*ft_d_zjmp(t_read *reader);
char					*ft_d_ldi(t_read *reader);
char					*ft_d_sti(t_read *reader);
char					*ft_d_fork(t_read *reader);
char					*ft_d_lld(t_read *reader);
char					*ft_d_lldi(t_read *reader);
char					*ft_d_lfork(t_read *reader);
char					*ft_d_aff(t_read *reader);
char					*print_dir(t_read *reader, int size);
char					*print_indir(t_read *reader);
char					*print_reg(t_read *reader);
char					*hero_func(t_read *reader);
char					*print_arg(t_read *reader,
		int size, int type, int num);
int32_t					code_to_int(t_read *reader, size_t size);
int						disassembler(char *filename);
void					hero_code(t_read *reader, char **code);
t_read					*reader_init(char *progname);
char					*ft_progname1(char *name);

#endif
