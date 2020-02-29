/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assem.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 08:37:44 by pstein            #+#    #+#             */
/*   Updated: 2020/02/28 16:22:29 by pstein           ###   ########.fr       */
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
	INDIRECT_LABEL,
	INDIRECT,
    REGISTER, //регистер
    END,
    ERROR
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
	int					code_size;
	int 				i;
}						t_pars;


/*
** main.c
*/
t_pars *parser_init(); //инициация парсера ТВОЕГО
int is_s_file(char *str); // пока чекает что .s  подали и все
int assembler(char *fd_map); // собсна наш ассемблер! еще дисасемблер можно ебнуть
int writing_in_file(t_pars *parser); // Непосредственно Каха! Пишет байткод в файл

/*
** read_struct.c
*/
int make_com(t_pars *parser); // подфункция чек команд
int make_name(t_pars *parser); // подфункция чек команд
int check_commands(t_pars *parser); //считываю токены комментом, валидирует и записываю их
int what_function(t_pars *parser, char **bytecode); // по токенам функций запускаю соответствующую валидацию и запись в байткод
int make_code(t_pars *parser, char **bytecode); // считываю токены функций
/*
** functions.c
*/
void	int_to_byte(char *data,int32_t pos, int32_t value, size_t size); //переводит число в байткод
int		arg_type(t_pars *parser, int size, char **code); //записывает байт с типами аргументов
int		next_arg(t_pars *parser, int type, int size, char **bytecode); //кушает аргументы и выдает их оутпутом  (type надо бы сделать структурой хз как)
int		find_value(t_pars *parser); //находит расположение метки и выдает на соклько байтов сдвинуться
int		write_dir(t_pars *parser, size_t size, char **bytecode);
int		write_indir(t_pars *parser, char **bytecode);
int		write_reg(t_pars *parser, char **bytecode);// возвращают строку с кодом аргумента

/*
** funct1.c
*/
int ft_live(t_pars *parser, char **bytecode);
int	ft_ld(t_pars *parser, char **bytecode);
int	ft_st(t_pars *parser, char **bytecode);
int	ft_add(t_pars *parser, char **bytecode);
int	ft_sub(t_pars *parser, char **bytecode);
/*
** funct2.c
*/
int	ft_and(t_pars *parser, char **bytecode);
int	ft_or(t_pars *parser, char **bytecode);
int	ft_xor(t_pars *parser, char **bytecode);
int	ft_zjmp(t_pars *parser, char **bytecode);
int	ft_ldi(t_pars *parser, char **bytecode);
/*
** funct3.c
*/
int	ft_sti(t_pars *parser, char **bytecode);
int	ft_fork(t_pars *parser, char **bytecode);
int	ft_lld(t_pars *parser, char **bytecode);
int	ft_lldi(t_pars *parser, char **bytecode);
int	ft_lfork(t_pars *parser, char **bytecode);
/*
** funct4.c
*/
int ft_aff(t_pars *parser, char **bytecode);
/*
 * create_list.c
 */
t_token *create_list(char* fd_map, t_pars* pars);
void    score_line(char* c, int value, int ascending);
t_token *create_elem();
/*
 * operations.c
 */
void    plus2bytes(char *str);
void    plus_byte(char *str);
int    check_unique_label(t_pars* pars, t_ment* ment);
/*
 * variables.c
 */
t_oken  find_variables(char* c, t_token** tok);
void    add_variables(t_token** token, char* map);
char    *get_variables(char *map, t_oken token);
/*
 * checks.c
 */
char    *find_operation(char* str);
int     if_digits(char* str);
int     if_register(char* str);
int     if_label(char* str);
#endif
