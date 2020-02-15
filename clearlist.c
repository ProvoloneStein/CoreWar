/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 21:14:39 by pstein            #+#    #+#             */
/*   Updated: 2020/02/07 21:49:00 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "op.h"

void	skip_whitespaces(t_pars *parser, const char *line)
{
	while (line[parser->column] == '\t' || line[parser->column] == ' ')
		parser->column++;   //скипаем вайтспейсы 
}

void	skip_comment(t_parser *parser, const char *line)
{
	if (line[parser->column] == COMMENT_CHAR
		|| line[parser->column] == ALT_COMMENT_CHAR)
		while (line[parser->column] && line[parser->column] != '\n')
			parser->column++;     //под сомнением 
}
void ft_clear_line(t_pars *parser, const char *line)
{
	skip_whitespaces(parser, line);
	skip_comment(parser, line);
}