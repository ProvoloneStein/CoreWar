/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 12:51:31 by pstein            #+#    #+#             */
/*   Updated: 2020/01/27 18:38:26 by pstein           ###   ########.fr       */
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

i
t_pars parser_init(t_pars *parser)
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

	parser = parser_init(parser)
	read_tok(fd, parser);
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
