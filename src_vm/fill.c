/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:24:34 by student           #+#    #+#             */
/*   Updated: 2020/04/06 10:50:42 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	fill_sizeof_code(unsigned char data[])
{
	int				i;
	unsigned char	*size;
	unsigned char	*s;
	int				size_int;

	size = data + 4 + PROG_NAME_LENGTH + 4;
	size_int = 0;
	s = (unsigned char*)&size_int;
	i = 0;
	while (i < 4)
	{
		s[3 - i] = size[i];
		i++;
	}
	if (size_int > CHAMP_MAX_SIZE || size_int <= 0)
		return (-1);
	return (size_int);
}

static void	check_errno(int fd, char *file)
{
	if (errno)
	{
		close(fd);
		check_error(file, NULL);
	}
}

void		fill_champ(t_champ *champ, char *file)
{
	int				fd;
	unsigned char	data[DATA_SIZE];

	fd = open(file, O_RDONLY);
	check_errno(fd, file);
	read(fd, data, DATA_SIZE);
	check_errno(fd, file);
	check_valid_data(data, file);
	ft_strncpy(champ->name, (char*)(data + 4), PROG_NAME_LENGTH);
	ft_strncpy(champ->comment,
			(char*)(data + 4 + PROG_NAME_LENGTH + 4 + 4), COMMENT_LENGTH);
	champ->sizeof_code = fill_sizeof_code(data);
	if (champ->sizeof_code == -1)
	{
		close(fd);
		check_error(file, "bad code size");
	}
	ft_memcpy(champ->code,
			(data + DATA_SIZE - CHAMP_MAX_SIZE), CHAMP_MAX_SIZE);
	close(fd);
}
