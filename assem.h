/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assem.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 08:37:44 by pstein            #+#    #+#             */
/*   Updated: 2020/02/26 19:24:26 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEM_H
# define ASSEM_H
# include <fcntl.h>
# include "ft_printf.h"
# include "libft.h"
# include "op.h"
#include <stdint.h>
# define  NAME_SIZE 1


typedef struct			s_ment
{
	char				*name;
	int					byte;
	struct s_ment		*next;
}						t_ment;

typedef enum
{
    NAME, //.name
    COMMENT, //.comment
    LABEL, //метка
    INSTRUCTION, //оператор
    DIRECT_LABEL, //ссылка на метку
    DIRECT, //цифра
    REGISTER, //регистер
    END
}	t_oken;

typedef struct			s_token
{
	char				*content;
    t_oken				type;
	unsigned			line;
	unsigned			column;
	int                 byte;
	struct s_token		*next;
}						t_token;

typedef struct			s_pars
{
    char				*name;
    char                *comment;
	t_token				*token;
	t_ment				*mention;
    int					column;
    int					line;
	char 				*code;
	int					code_size;
}						t_pars;


/*
** functions.c
*/
void	int_to_byte(char *data,int32_t pos, int32_t value, size_t size); //переводит число в байткод
int arg_type(t_pars *parser, int size, char *code); //записывает байт с типами аргументов
char *next_arg(t_pars *parser, int type, int size); //кушает аргументы и выдает их оутпутом  (type надо бы сделать структурой хз как)
int find_value(t_pars *parser); //находит расположение метки и выдает на соклько байтов сдвинуться
char *write_dir(t_pars *parser, size_t size);
char *write_indir(t_pars *parser);
char *write_reg(t_pars *parser);// возвращают строку с кодом аргумента

/*
** funct1.c
*/
char *ft_live(t_pars *parser);
char *ft_ld(t_pars *parser);
char *ft_st(t_pars *parser);
char *ft_add(t_pars *parser);
char *ft_sub(t_pars *parser);
/*
** funct2.c
*/
char *ft_and(t_pars *parser);
char *ft_or(t_pars *parser);
char *ft_xor(t_pars *parser);
char *ft_zjmp(t_pars *parser);
char *ft_ldi(t_pars *parser);
/*
** funct3.c
*/
char *ft_sti(t_pars *parser);
char *ft_fork(t_pars *parser);
char *ft_lld(t_pars *parser);
char *ft_lldi(t_pars *parser);
char *ft_lfork(t_pars *parser);
/*
** funct4.c
*/
char *ft_aff(t_pars *parser);






char *next_arg(t_pars *parser, int type, int size);
int arg_type(t_pars *parser, int size, char *code);
int cteate(t_pars *parser);
char *ft_live(t_pars *parser);
int read_tok(int fd, t_pars *pars);
char			*ft_strplus_c(char *s1, char s2, int x);
void	int_to_byte(char *data,
							int32_t pos,
							int32_t value,
							size_t size);
#endif
