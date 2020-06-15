/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assem.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 08:37:44 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 21:11:10 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEM_H
# define ASSEM_H
# include <fcntl.h>
# include "ft_printf.h"
# include "libft.h"
# include "op.h"
# include "disassem.h"
# include <stdint.h>
# define NAME_SIZE		1

typedef struct			s_ment
{
	char				*name;
	int					byte;
	struct s_ment		*next;
}						t_ment;

typedef enum
{
	NAME,
	COMMENT,
	LABEL,
	INSTRUCTION,
	DIRECT_LABEL,
	DIRECT,
	INDIRECT_LABEL,
	INDIRECT,
	REGISTER,
	END,
	ERROR
}	t_oken;

typedef struct			s_token
{
	char				*content;
	t_oken				type;
	unsigned			line;
	unsigned			column;
	int					byte;
	struct s_token		*next;
}						t_token;

typedef struct			s_pars
{
	char				*name;
	char				*comment;
	t_token				*token;
	t_ment				*mention;
	int					column;
	int					line;
	int					code_size;
	int					i;
	int					f_head;
	char				*filename;
}						t_pars;

/*
** ===>>>   assembler.c   <<<===
*/

void					ft_free_str(t_pars *parser);
t_pars					*parser_init(char *progname);
int						assembler(char *fd_map);

/*
** ===>>>   errors.c   <<<===
*/

int						errors_handler(int i, int x, int y);
int						err_handler(int i, int y, int x);

/*
** main.c
*/

int						is_cor_file(char *str);
int						is_s_file(char *str);

/*
**=====================FILE_READER=======================
*/

/*
** ===>>>   checks.c   <<<===
*/

char					*find_oper(char *str);
char					*find_operation(char *str);
int						if_digits(char *str);
int						if_register(char *str);
int						if_label(char *str);

/*
** ===>>>   checks2.c   <<<===
*/

int						if_name(char *str);
int						if_comment(char *str);
int						if_operation(char *str);
int						check_map(char *map);
int						check_commas(char *map);

/*
** ===>>>   create_list.c   <<<===
*/

int						read_map(char **map, char *fd_map);
t_oken					find_token(char *c, t_token **tok, t_pars *pars);
t_token					*create_elem(void);
void					get_next_metion(t_pars *pars,
		char *map, t_ment **temp1);
int						create_list(char *fd_map, t_pars *pars);

/*
** ===>>>   variables.c   <<<===
*/

void					add_variables(t_token **token, char *map);
t_oken					find_variables(char *c, t_token **tok);
char					*qwe1(char *map, t_oken token, char *temp, int len);
char					*qwe(char *map, t_oken token, char *temp, int len);
char					*get_variables(char *map, t_oken token);

/*
** ===>>>   edgar_func.c   <<<===
*/

void					scr_lin(char *c);
void					score_line(char *c, int value, int ascending);
char					*get_name_com(char *map);
char					*get_content(char *map, t_oken token);
void					skip_space(char *c);

/*
** ===>>>   edgar_func1.c   <<<===
*/

t_oken					get_tok(char *c);
void					skip_sp(char *map);
void					take_label(t_pars *pars, char *map, t_ment **temp1);
void					take_ins(t_pars *pars, char *map);

/*
** ===>>>   operations.c   <<<===
*/

void					plus2bytes(char *str);
void					plus_byte(char *str);
void					check_unique_label(t_ment *ment);

/*
** ====================CODE GENERATOR====================
*/

/*
** ===>>>   code_generator.c   <<<===
*/

int						writing_in_file(t_pars *pars);

/*
** read from token struct and validate CHAMPIONS NAME AND COMMENT
** ===>>>   read_commands.c   <<<===
*/

int						make_com(t_pars *parser, int *i);
int						make_name(t_pars *parser, int *i);
int						check_commands(t_pars *parser);

/*
** read tokens from struct and opens instruction writers
** ===>>>   read_struct.c   <<<===
*/

int						what_function(t_pars *parser, char **bytecode);
int						make_code(t_pars *pars, char **bytecode);

/*
** writers for every function
** ===>>>   funct1.c funct2.c funct3.c funct4.c <<< ===
*/

/*
** funct1.c
*/
int						ft_live(t_pars *parser, char **bytecode);
int						ft_ld(t_pars *parser, char **bytecode);
int						ft_st(t_pars *parser, char **bytecode);
int						ft_add(t_pars *parser, char **bytecode);
int						ft_sub(t_pars *parser, char **bytecode);
/*
** funct2.c
*/
int						ft_and(t_pars *parser, char **bytecode);
int						ft_or(t_pars *parser, char **bytecode);
int						ft_xor(t_pars *parser, char **bytecode);
int						ft_zjmp(t_pars *parser, char **bytecode);
int						ft_ldi(t_pars *parser, char **bytecode);
/*
** funct3.c
*/
int						ft_sti(t_pars *parser, char **bytecode);
int						ft_fork(t_pars *parser, char **bytecode);
int						ft_lld(t_pars *parser, char **bytecode);
int						ft_lldi(t_pars *parser, char **bytecode);
int						ft_lfork(t_pars *parser, char **bytecode);
/*
** funct4.c
*/
int						ft_aff(t_pars *parser, char **bytecode);

/*
** convertin int to bytecode function and making
** "code of instruction params info" function
** In other words - all bitwise operations functions LMAO
** ===>>>   functions2.c   <<<===
*/

void					int_to_byte(char *bytecode, int32_t pos,
		int32_t num, size_t size);
int						arg_type(t_pars *parser, int size, char **code);

/*
** T_DIR T_INDIR T_REG generating functions and instruction validator there
** ===>>>   functions.c   <<<===
*/

int						next_arg(t_pars *parser, int type,
		int size, char **bytecode);
int						find_value(t_pars *parser);
int						write_dir(t_pars *pars, size_t size, char **code);
int						write_indir(t_pars *pars, char **code);
int						write_reg(t_pars *pars, char **code);

#endif
