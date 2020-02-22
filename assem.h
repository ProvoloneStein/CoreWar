/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assem.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 08:37:44 by pstein            #+#    #+#             */
/*   Updated: 2020/02/22 20:49:57 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEM_H
# define ASSEM_H
# include <fcntl.h>
# include "ft_printf.h"
# include "libft.h"

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
typedef struct			s_token
{
	char				*content;
	t_type				type;
	unsigned			line;
	unsigned			column;
	struct s_token		*next;
}						t_token;
typedef struct			s_pars
{
    char				*name;
    char                *comment;
	t_token				*token;
    int					column;
    int					line;
	int					code_size;
}						t_pars;
/*
** row    — row, where mention was found in assemble-file
** column — column, where mention was found in assemble-file
** pos    — number of byte where mention is placed
** op_pos — number of byte where operator code is placed
** size   — number of bytes which store a value of mention at pos
** next   — pointer to the next mention
*/

int cteate(t_pars *parser);
char *ft_live(t_pars *parser);
int read_tok(int fd, t_pars *pars);
char			*ft_strplus_c(char *s1, char s2, int x);

#endif
