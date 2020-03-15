/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 20:25:52 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 21:46:05 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

void		ft_free_str(t_pars *parser)
{
	t_token	*head_t;
	t_ment	*head_m;

	while (parser->mention)
	{
		head_m = parser->mention->next;
		free(parser->mention->name);
		free(parser->mention);
		parser->mention = head_m;
	}
	while (parser->token)
	{
		head_t = parser->token->next;
		if (parser->token->content)
			free(parser->token->content);
		free(parser->token);
		parser->token = head_t;
	}
	if (parser->filename)
		free(parser->filename);
	free(parser);
}

static char	*create_file(char *filename)
{
	int		i;
	char	*name;

	name = (char*)ft_memalloc(sizeof(char) * (ft_strlen(filename) + 3));
	ft_strcpy(name, filename);
	i = 0;
	while (name[i] != '\0')
		i++;
	name[i - 1] = 'c';
	name[i] = 'o';
	name[i + 1] = 'r';
	name[i + 2] = '\0';
	return (name);
}

t_pars		*parser_init(char *progname)
{
	t_pars	*pars;

	if (!(pars = (t_pars*)malloc(sizeof(t_pars))))
		return (NULL);
	pars->comment = NULL;
	pars->name = NULL;
	pars->token = NULL;
	pars->mention = NULL;
	pars->line = 0;
	pars->i = 0;
	pars->column = 0;
	pars->code_size = 0;
	pars->f_head = 0;
	pars->filename = create_file(progname);
	return (pars);
}

int			assembler(char *fd_map)
{
	t_pars	*parser;

	if (!(parser = parser_init(fd_map)))
		return (-1);
	create_list(fd_map, parser);
	writing_in_file(parser);
	ft_free_str(parser);
	return (1);
}
