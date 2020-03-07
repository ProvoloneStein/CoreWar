/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:51:31 by pstein            #+#    #+#             */
/*   Updated: 2020/03/07 17:28:53 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

char *ft_progname(char *name)
{
    char *str;
    int i;
    int j;

     j = 0;
     i = ft_strlen(name);
     str = (char*)malloc(sizeof(char) * (i - 2));
     while(j != i - 2)
     {
         str[j] = name[j];
		 j++;
     }
	 str[j] = '\0';
     str = ft_strplus(str, ".cor", 1, 0);
     return(str);
}

void ft_free_str(t_pars *parser)
{
	t_token *head_t;
	t_ment *head_m;

	while (parser->mention)
	{
		head_m = parser->mention->next;
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
	if (parser->comment)
		free(parser->comment);
	if (parser->name)	
		free(parser->name);
	free(parser);
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
	pars->filename = ft_progname(progname);
	ft_printf("%s\n", pars->filename);
	return(pars);
}

int assembler(char *fd_map)
{
	t_pars *parser;

	if (!(parser = parser_init(fd_map)))
		return(-1);	
	if (!(create_list(fd_map, parser)))
		return(-1);  // прога в случае невалидного вода должна вылетать с ошибкой и показывать строчку и +- место в котором обнаружена ошибка/ внутри парсера должны быть заполнены токены и метки после твоей функции
	/*while(parser->token)
	{
		ft_printf("%i %s\n", parser->token->type, parser->token->content);
		parser->token = parser->token->next;
	}*/
	/*while(parser->mention)
	{
		ft_printf("%s\n", parser->mention->name);
		parser->mention = parser->mention->next;
	}*/
	writing_in_file(parser);
	//ft_free_str(parser);
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


int main(int argc, char **argv)
{
	if (argc == 2 && is_s_file(argv[1]))
		assembler(argv[1]);
	/*else if (argc == 2 && is_cor_file(argv[1]))	
		disassembler(argv[1]);*/
	else
		ft_printf("usage: ./assembler map");
	return(0);	
}
