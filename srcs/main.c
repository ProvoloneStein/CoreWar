/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:51:31 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 19:23:35 by galiza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"


void ft_free_str(t_pars *parser)
{
	t_token *head_t;
	t_ment *head_m;

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

static char *create_file(char *filename)
{
	int i;
	char	*out_name;

	out_name = (char*)ft_memalloc(sizeof(char) * (ft_strlen(filename) + 3));
	ft_strcpy(out_name, filename);
	i = 0;
	while (out_name[i] != '\0')
		i++;
	out_name[i - 1] = 'c';
	out_name[i] = 'o';
	out_name[i + 1] = 'r';
	out_name[i + 2] = '\0';
	return(out_name);
}

t_pars *parser_init(char *progname)
{
	t_pars *pars;

	pars = (t_pars*)malloc(sizeof(t_pars));
	pars->comment = NULL;
	pars->name = NULL;
	pars->token = NULL;
	pars->mention = NULL;
	pars->line = 0;
	pars->i = 0;//это для печати
	pars->column = 0;
	pars->code_size = 0;
	pars->f_head = 0;
	pars->filename = create_file(progname);
	return(pars);
}

int assembler(char *fd_map)
{
	t_pars *parser;

	if (!(parser = parser_init(fd_map)))
		return(-1);	
	if (!(create_list(fd_map, parser)))
		return(ft_printf("Error"));  // прога в случае невалидного вода должна вылетать с ошибкой и показывать строчку и +- место в котором обнаружена ошибка/ внутри парсера должны быть заполнены токены и метки после твоей функции
	/*while(parser->token)
	{
		ft_printf("%i %i %s\n", parser->token->type, parser->token->byte, parser->token->content);
		parser->token = parser->token->next;
	}*/
	/*while(parser->mention)
	{
		ft_printf("%s\n", parser->mention->name);
		parser->mention = parser->mention->next;
	}*/
	writing_in_file(parser);
	ft_free_str(parser);
	return(1);
}

int is_s_file(char *str)
{
	int i;

	i = ft_strlen(str);
	if (i >= 3 && str[i - 2] == '.' && str[i - 1] == 's')
		return (1);
	return(0);	

}


int is_cor_file(char *str)
{
	int i;

	i = ft_strlen(str);
	if (i >= 5 && str[i - 2] == 'o' && str[i - 1] == 'r' && str[i - 3] == 'c' && str[i - 4] == '.')
		return (1);
	return(0);	

}
/*
static int		check_for_valid_file(char *filename)
{
	int			i;
	int			len;

	i = 0;
	len = (int)ft_strlen(filename);
	while (i < len - 4)
		i++;
	if (i == len - 4)
	{
		if (!ft_strcmp(".cor", filename + i) && len != 4)
			return (1);
	}
	ft_printf("Invalid file as input: %s\n", filename);
	return (0);
}*/


int main(int argc, char **argv)
{
	if (argc == 2 && is_s_file(argv[1]))
		assembler(argv[1]);
	else if (argc == 2 && is_cor_file(argv[1]))
		disassembler(argv[1]);
	else
		ft_printf("usage: ./assembler map");
	return(0);
}
