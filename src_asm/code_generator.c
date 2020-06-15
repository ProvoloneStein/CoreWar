/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_generator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:48:51 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 16:46:38 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

int	writing_in_file(t_pars *pars)
{
	int		fd;
	char	*bytecode;
	int		len;

	len = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4 + pars->code_size;
	if (!(bytecode = ft_strnew((size_t)len)))
		return (-1);
	check_commands(pars);
	int_to_byte(bytecode, pars->i, COREWAR_EXEC_MAGIC, 4);
	pars->i += 4;
	ft_memcpy(&bytecode[pars->i], pars->name, (ft_strlen(pars->name)));
	pars->i = pars->i + 4 + PROG_NAME_LENGTH;
	int_to_byte(bytecode, pars->i, pars->code_size, 4);
	pars->i += 4;
	ft_memcpy(&bytecode[pars->i], pars->comment, ft_strlen(pars->comment));
	pars->i = pars->i + 4 + COMMENT_LENGTH;
	if (!(make_code(pars, &bytecode)))
		return (-1);
	if ((fd = open(pars->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		return (-1);
	ft_printf("Writing in file %s\n", pars->filename);
	write(fd, bytecode, len);
	close(fd);
	free(bytecode);
	return (1);
}
