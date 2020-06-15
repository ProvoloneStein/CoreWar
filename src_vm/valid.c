/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:04:30 by student           #+#    #+#             */
/*   Updated: 2020/03/25 12:08:02 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	check_header(unsigned char data[], char *file)
{
	unsigned char	*a;
	int				i;
	int				j;
	int				need;

	i = 3;
	j = 0;
	need = COREWAR_EXEC_MAGIC;
	a = (unsigned char*)&need;
	while (i >= 0)
	{
		if (data[j] != a[i])
			check_error(file, "invalid header");
		i--;
		j++;
	}
}

void	check_null(unsigned char data[], int tocheck, char *file)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (data[tocheck + i] != 0)
			check_error(file, "bad null");
		i++;
	}
}

void	check_valid_data(unsigned char data[], char *file)
{
	check_header(data, file);
	check_null(data, 4 + PROG_NAME_LENGTH, file);
	check_null(data, 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH, file);
}
