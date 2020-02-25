/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:51:31 by pstein            #+#    #+#             */
/*   Updated: 2020/02/22 15:33:33 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"
#include "op.h"
#include <stdint.h>

void	int32_to_byte(char *data,
							int32_t pos,
							int32_t value,
							size_t size)
{
	int8_t		i;

	i = 0;
	while (size)
	{
		data[pos + size - 1] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		size--;
	}
}

static void		free_all(char *s1, int x)
{
	if (x)
		free(s1);
}

char			*ft_strplus_c(char *s1, char s2, int x)
{
	char			*new_s;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	new_s = ft_strnew(ft_strlen(s1) + 2);
	if (new_s == NULL)
		return (NULL);
	while (s1[i])
		new_s[j++] = s1[i++];
	new_s[j++] = s2;
	new_s[j] = '\0';
	free_all(s1,x);
	return (new_s);
}


//t_pars *parser_init()
//{
//	t_pars *pars;
//
//	pars = (t_pars*)malloc(sizeof(t_pars));
//	pars->comment = NULL;
//	pars->name = NULL;
//	pars->line = 0;
//	pars->column = 0;
//	return(pars);
//}
//
//void make_tok(t_pars *parser)
//{
//    parser->token = (t_token*)malloc(sizeof(t_token));
//    parser->token->type = LABEL;
//    parser->token->content = "live";
//    parser->token->next = (t_token*)malloc(sizeof(t_token));
//    parser->token->next->type = DIRECT;
//    parser->token->next->content = "1";
//    parser->token->next->next = NULL;
//}

void assembler()
{
	t_pars *parser;

//	parser = parser_init();
//	make_tok(parser);
//	read_tok(fd, parser);
//	ft_printf("%s\n", parser->token->content);
//	cteate(parser);
}

int main(int argc, char** argv) {
    int fd;
    t_token *list;
    char *bytecode;
    int32_t len = 4;

    /*if ((fd = open("filename.s", O_RDONLY)) == -1)
        return(-1);*/
    if (argc != 2)
    {
        ft_printf("usage: ./assembler map");
    }
    list = create_list(argv[1]);
	assembler();
	if ((fd = open("filename.cor", O_CREAT | O_WRONLY, 0644)) == -1)
		return(-1);
	if (!(bytecode = ft_strnew((size_t)len)))
		return(1);
	int32_to_byte(bytecode, 0, COREWAR_EXEC_MAGIC, 4);
	write(fd, bytecode, (size_t)len);	
	return(1);
}
