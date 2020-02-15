/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assem.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 08:37:44 by pstein            #+#    #+#             */
/*   Updated: 2020/02/09 00:14:23 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEM_H
# define ASSEM_H
# include <fcntl.h>
# include "ft_printf.h"
# include "libft.h"

typedef struct			s_pars
{
   // char				*name;
   // char                *comment;
	t_token				*token;
    int					column;
    int					line;
}						t_pars;

typedef struct			s_token
{
	char				*content;
	t_type				type;
	unsigned			line;
	unsigned			column;
	struct s_token		*next;
}						t_token;

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}	t_type;



static char				*g_type[] = {
	"COMMAND",
	"STRING",
	"LABEL",
	"OPERATOR",
	"REGISTER",
	"DIRECT",
	"DIRECT_LABEL",
	"INDIRECT",
	"INDIRECT_LABEL",
	"SEPARATOR",
	"NEW_LINE",
	"END"
};

/*
** Mention
*/

/*
** row    — row, where mention was found in assemble-file
** column — column, where mention was found in assemble-file
** pos    — number of byte where mention is placed
** op_pos — number of byte where operator code is placed
** size   — number of bytes which store a value of mention at pos
** next   — pointer to the next mention
*/

typedef struct			s_mention
{
	unsigned			row;
	unsigned			column;
	int32_t				pos;
	int32_t				op_pos;
	size_t				size;
	struct s_mention	*next;
}						t_mention;

/*
** Label
*/

/*
** name     — name of label
** op_pos   — number of byte, at which label points
** mentions — list of mentions
** next     — pointer to the next label
*/

typedef struct			s_label
{
	char				*name;
	int32_t				op_pos;
	t_mention			*mentions;
	struct s_label		*next;
}						t_label;

/*
** Assembler's Parser
*/

/*
** fd        — file descriptor of assemble-file
** row       — row of assemble-file, which parser processes now
** column    — column of assemble-file, which parser processes now
** tokens    — list of tokens
** pos       — number of byte, at which parser writes now
** op_pos    — number of byte, at which op_code of current statement is placed
** name      — name of champion
** comment   — comment of champion
** code      — executable code of champion
** code_size — size of champion's executable code
** labels    — list of labels
*/

typedef struct			s_parser
{
	int					fd;
	unsigned			row;
	unsigned			column;
	t_token				*tokens;
	int32_t				pos;
	int32_t				op_pos;
	char				*name;
	char				*comment;
	char				*code;
	int32_t				code_size;
	t_label				*labels;
}						t_parser;

int read_tok(int fd, t_pars *pars);
char			*ft_strplus_c(char *s1, char s2, int x);

#endif
