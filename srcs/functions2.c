/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 16:24:42 by pstein            #+#    #+#             */
/*   Updated: 2020/03/08 22:02:32 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

void		int_to_byte(char *bytecode, int32_t pos, int32_t num, size_t size)
{
	int8_t	i;

	i = 0;
	while (size)
	{
		bytecode[pos + size - 1] = (uint8_t)((num >> i) & 0xFF);
		i += 8;
		size--;
	}
}

static int	change_bit(int *i, int *num, t_pars *parser)
{
	if (parser->token->type == DIRECT || parser->token->type == DIRECT_LABEL)
	{
		parser->token = parser->token->next;
		*num = *num | (1 << *i);
		*i -= 2;
	}
	else if (parser->token->type == INDIRECT
			|| parser->token->type == INDIRECT_LABEL)
	{
		parser->token = parser->token->next;
		*num = *num | (1 << *i);
		*num = *num | (1 << (*i - 1));
		*i -= 2;
	}
	else if (parser->token->type == REGISTER)
	{
		parser->token = parser->token->next;
		*num = *num | (1 << (*i - 1));
		*i -= 2;
	}
	else
		return (0);
	return (1);
}

int			arg_type(t_pars *parser, int size, char **code)
{
	int		num;
	t_token	*head;
	int		i;

	head = parser->token;
	num = 0;
	i = 7;
	while (size > 0)
	{
		if (change_bit(&i, &num, parser))
		{
			size--;
			continue;
		}
		return (errors_handler(5, head->line, head->column));
	}
	parser->token = head;
	int_to_byte(*code, parser->i, num, 1);
	parser->i += 1;
	return (1);
}
