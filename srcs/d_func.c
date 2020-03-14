/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_func.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 15:20:50 by pstein            #+#    #+#             */
/*   Updated: 2020/03/14 16:08:27 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "assem.h"

char *print_dir(t_read *reader, int size)
{
    char *arg;

    if (reader->i + size > reader->code_size)
        exit(0);
    arg = ft_strplus("%", ft_itoa(code_to_int(reader, size)), 0, 1);
    reader->i += size;
    return(arg);
}

char *print_indir(t_read *reader)
{
    char *arg;

    if (reader->i + IND_SIZE > reader->code_size)
        exit(0);
    arg = ft_itoa(code_to_int(reader, IND_SIZE));
    reader->i += IND_SIZE;
    return(arg);
}

char *print_reg(t_read *reader)
{
    char *arg;

    if (reader->i + 1 > reader->code_size)
        exit(0);
    arg = ft_strplus("r", ft_itoa(code_to_int(reader, 1)), 0, 1);
    reader->i += 1;
    return(arg);
}


char	*hero_func2(t_read *reader)
{
	if (reader->code[reader->i]  == 0x09)
		return (ft_d_xor(reader));
	else if (reader->code[reader->i]  == 0x0a)
		return (ft_d_zjmp(reader));
	else if (reader->code[reader->i]  == 0x0b)
		return (ft_d_sti(reader));
	else if (reader->code[reader->i]  == 0x0c)
		return (ft_d_fork(reader));
	else if (reader->code[reader->i]  == 0x0d)
		return (ft_d_lldi(reader));
	else if (reader->code[reader->i]  == 0x0e)
		return (ft_d_lld(reader));
	else if (reader->code[reader->i]  == 0x0f)
		return (ft_d_lfork(reader));
	else if (reader->code[reader->i]  == 0x10)
		return (ft_d_aff(reader));
	exit(0);
}

char		*hero_func(t_read *reader)
{
	if (reader->code[reader->i]  == 0x01)
		return (ft_d_live(reader));
	else if (reader->code[reader->i]  == 0x02)
		return (ft_d_ldi(reader));
	else if (reader->code[reader->i]  == 0x03)
		return (ft_d_ld(reader));
	else if (reader->code[reader->i]  == 0x04)
		return (ft_d_st(reader));
	else if (reader->code[reader->i]  == 0x05)
		return (ft_d_add(reader));
	else if (reader->code[reader->i]  == 0x06)
		return (ft_d_sub(reader));
	else if (reader->code[reader->i]  == 0x07)
		return (ft_d_and(reader));
	else if (reader->code[reader->i]  == 0x08)
		return (ft_d_or(reader));
	return (hero_func2(reader));
}




/*
** arg types
** DIR = 1
** INDIR = 2
** REG = 3
** DIR || INDIR = 4
** DIR || REG = 5
** INDIR || REG = 6
** DIR || INDIR || REG = 7
*/


char *print_arg(t_read  *reader, int size, int type, int num)
{
    int bit;

    bit = 8 - 2 * num;

    if ((reader->arg_types) & (uint8_t)3)
        exit(1);
    if ((type == 1 || type == 4 || type == 5 || type == 7) && ((reader->arg_types >> bit) & (uint8_t)3) == (uint8_t)2)
        return(print_dir(reader, size));
    else if(((type == 2 || type == 4 || type == 6 || type == 7) && ((reader->arg_types >> bit) & (uint8_t)3) == (uint8_t)3))
        return(print_indir(reader));
    else if(((type == 3 || type == 5 || type == 6 || type == 7) && ((reader->arg_types >> bit) & (uint8_t)3) == (uint8_t)1))
        return(print_reg(reader));
    else if (type == 0 && ((reader->arg_types >> bit) & (uint8_t)3) == (uint8_t)0)
        return(NULL);
    else
        exit(0);
}



int32_t		code_to_int(t_read *reader, size_t size)
{
	int32_t	result;
	_Bool	sign;
	int		i;

	result = 0;
	sign = (_Bool)(reader->code[reader->i] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((reader->code[reader->i + size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += reader->code[reader->i + size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

