/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:51:31 by pstein            #+#    #+#             */
/*   Updated: 2020/01/27 21:34:47 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
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


t_pars *parser_init()
{
	t_pars *pars;

	pars = (t_pars*)malloc(sizeof(t_pars));
	pars->is_com = 0;
	pars->is_name = 0;
	pars->n_len = 0;
	pars->c_len = 0;
	pars->comment = NULL;
	pars->name = NULL;
	return(pars);
}

void assembler(int fd)
{
	t_pars *parser;

	parser = parser_init();
	read_tok(fd, parser);
	ft_printf("%s %s 123", parser->name, parser->comment);
}

int main()
{
	int fd;
	char *bytecode;
	int32_t len = 4;

	if ((fd = open("filename.s", O_RDONLY)) == -1)
		return(-1);
	assembler(fd);	
	if ((fd = open("filename.cor", O_CREAT | O_WRONLY, 0644)) == -1)
		return(-1);
	if (!(bytecode = ft_strnew((size_t)len)))
		return(1);
	int32_to_byte(bytecode, 0, COREWAR_EXEC_MAGIC, 4);
	write(fd, bytecode, (size_t)len);	
	return(1);
}
