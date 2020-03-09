/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_generator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:48:51 by pstein            #+#    #+#             */
/*   Updated: 2020/03/08 20:15:43 by pstein           ###   ########.fr       */
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
	if (!check_commands(pars))
		return (-1);
	int_to_byte(bytecode, pars->i, COREWAR_EXEC_MAGIC, 4);
	pars->i += 4;
	ft_memcpy(&bytecode[pars->i], pars->name, (ft_strlen(pars->name)));
	pars->i += PROG_NAME_LENGTH;
	pars->i += 4;
	int_to_byte(bytecode, pars->i, pars->code_size, 4);
	pars->i += 4;
	ft_memcpy(&bytecode[pars->i], pars->comment, ft_strlen(pars->comment));
	pars->i += COMMENT_LENGTH;
	pars->i += 4;
	if (!(make_code(pars, &bytecode)))
		return (-1);
	if ((fd = open(pars->filename, O_CREAT | O_WRONLY, 0644)) == -1)
		return (-1);
    ft_printf("Writing in file %s\n", pars->filename);
	write(fd, bytecode, len);
	free(bytecode);
	return (1);
}
