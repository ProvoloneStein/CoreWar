/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:30:50 by pstein            #+#    #+#             */
/*   Updated: 2020/03/01 15:31:13 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

int	ft_and(t_pars *parser, char **bytecode)
{
	int	size;

	size = 0;
	parser->token = parser->token->next;
	int_to_byte(*bytecode, parser->i, 0x06, NAME_SIZE);
	parser->i += NAME_SIZE;
	if (!(arg_type(parser, 3, bytecode)))
		return (0);
	if (next_arg(parser, 7, 4, bytecode))
		size++;
	if (next_arg(parser, 7, 4, bytecode) && size == 1)
		size++;
	if (next_arg(parser, 3, 4, bytecode) && size == 2)
		return (1);
	return (0);
}

int	ft_or(t_pars *parser, char **bytecode)
{
	int	size;

	size = 0;
	parser->token = parser->token->next;
	int_to_byte(*bytecode, parser->i, 0x07, NAME_SIZE);
	parser->i += NAME_SIZE;
	if (!(arg_type(parser, 3, bytecode)))
		return (0);
	if (next_arg(parser, 7, 4, bytecode))
		size++;
	if (next_arg(parser, 7, 4, bytecode) && size == 1)
		size++;
	if (next_arg(parser, 3, 4, bytecode) && size == 2)
		return (1);
	return (0);
}

int	ft_xor(t_pars *parser, char **bytecode)
{
	int size;

	size = 0;
	parser->token = parser->token->next;
	int_to_byte(*bytecode, parser->i, 0x08, NAME_SIZE);
	parser->i += NAME_SIZE;
	if (!(arg_type(parser, 3, bytecode)))
		return (0);
	if (next_arg(parser, 7, 4, bytecode))
		size++;
	if (next_arg(parser, 7, 4, bytecode) && size == 1)
		size++;
	if (next_arg(parser, 3, 4, bytecode) && size == 2)
		return (1);
	return (0);
}

int	ft_zjmp(t_pars *parser, char **bytecode)
{
	parser->token = parser->token->next;
	int_to_byte(*bytecode, parser->i, 0x09, NAME_SIZE);
	parser->i += NAME_SIZE;
	if (next_arg(parser, 1, 2, bytecode))
		return (1);
	return (0);
}

int	ft_ldi(t_pars *parser, char **bytecode)
{
	int size;

	size = 0;
	parser->token = parser->token->next;
	int_to_byte(*bytecode, parser->i, 0x0a, NAME_SIZE);
	parser->i += NAME_SIZE;
	if (!(arg_type(parser, 3, bytecode)))
		return (0);
	if (next_arg(parser, 7, 2, bytecode))
		size++;
	if (next_arg(parser, 5, 2, bytecode) && size == 1)
		size++;
	if (next_arg(parser, 3, 2, bytecode) && size == 2)
		return (1);
	return (0);
}
