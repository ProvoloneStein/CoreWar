/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:14:42 by pstein            #+#    #+#             */
/*   Updated: 2020/03/05 17:24:36 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

int	ft_live(t_pars *parser, char **bytecode)
{
	parser->token = parser->token->next;
	int_to_byte(*bytecode, parser->i, 0x01, NAME_SIZE);
	parser->i += NAME_SIZE;
	if (next_arg(parser, 1, 4, bytecode))
		return (1);
	return (0);
}

int	ft_ld(t_pars *parser, char **bytecode)
{
	int	size;

	size = 0;
	parser->token = parser->token->next;
	int_to_byte(*bytecode, parser->i, 0x02, NAME_SIZE);
	parser->i += NAME_SIZE;
	if (!(arg_type(parser, 2, bytecode)))
		return (0);
	if (next_arg(parser, 4, 4, bytecode))
		size++;
	if (next_arg(parser, 3, 4, bytecode) && size == 1)
		return (1);
	return (0);
}

int	ft_st(t_pars *parser, char **bytecode)
{
	int	size;

	size = 0;
	parser->token = parser->token->next;
	int_to_byte(*bytecode, parser->i, 0x03, NAME_SIZE);
	parser->i += NAME_SIZE;
	if (!(arg_type(parser, 2, bytecode)))
		return (0);
	if ((next_arg(parser, 3, 4, bytecode)))
		size++;
	if ((next_arg(parser, 6, 4, bytecode)) && size == 1)
		return (1);
	return (0);
}

int	ft_add(t_pars *parser, char **bytecode)
{
	int	size;

	size = 0;
	parser->token = parser->token->next;
	int_to_byte(*bytecode, parser->i, 0x04, NAME_SIZE);
	parser->i += NAME_SIZE;
	if (!(arg_type(parser, 3, bytecode)))
		return (0);
	if (next_arg(parser, 3, 4, bytecode))
		size++;
	if ((next_arg(parser, 3, 4, bytecode)) && size == 1)
		size++;
	if ((next_arg(parser, 3, 4, bytecode)) && size == 2)
		return (1);
	return (0);
}

int	ft_sub(t_pars *parser, char **bytecode)
{
	int	size;

	size = 0;
	parser->token = parser->token->next;
	int_to_byte(*bytecode, parser->i, 0x05, NAME_SIZE);
	parser->i += NAME_SIZE;
	if (!(arg_type(parser, 3, bytecode)))
		return (0);
	if ((next_arg(parser, 3, 4, bytecode)))
		size++;
	if ((next_arg(parser, 3, 4, bytecode)) && size == 1)
		size++;
	if ((next_arg(parser, 3, 4, bytecode)) && size == 2)
		return (1);
	return (0);
}
