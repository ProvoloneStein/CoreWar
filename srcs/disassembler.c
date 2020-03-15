/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:21:45 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 14:43:04 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassem.h"

static char	*create_file_s(char *filename)
{
	int		i;
	char	*name;

	name = ft_strdup(filename);
	i = 0;
	while (name[i] != '\0')
		i++;
	name[i - 1] = '\0';
	name[i - 2] = '\0';
	name[i - 3] = 's';
	return (name);
}

t_read		*reader_init(char *progname)
{
	t_read	*pars;

	pars = (t_read*)malloc(sizeof(t_read));
	pars->comment = NULL;
	pars->name = NULL;
	pars->i = 0;
	pars->arg_types = 0;
	pars->code_size = 0;
	pars->code = NULL;
	pars->filename = create_file_s(progname);
	return (pars);
}

void		free_read(t_read *reader)
{
	if (reader->name)
		free(reader->name);
	if (reader->comment)
		free(reader->comment);
	if (reader->code)
		free(reader->code);
	if (reader->filename)
		free(reader->filename);
	free(reader);
}

void		hero_code(t_read *reader, char **code)
{
	while (reader->i < reader->code_size)
	{
		if (reader->code[reader->i] >= 0x01 && reader->code[reader->i] <= 0x10)
			*code = ft_strplus(*code, hero_func(reader), 1, 1);
		else
			exit(0);
	}
}

int			disassembler(char *filename)
{
	t_read	*reader;
	char	*code;
	int		fd;

	code = ft_strnew(0);
	if ((fd = open(filename, O_RDONLY)) == -1)
		exit(1);
	reader = reader_init(filename);
	read_codefile(reader, fd);
	close(fd);
	hero_code(reader, &code);
	ft_printf("%s", reader->filename);
	if ((fd = open(reader->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		return (-1);
	write(fd, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING));
	write(fd, " \"", 2);
	write(fd, reader->name, ft_strlen(reader->name));
	write(fd, "\"\n", 2);
	write(fd, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING));
	write(fd, " \"", 2);
	write(fd, reader->comment, ft_strlen(reader->comment));
	write(fd, "\"\n", 2);
	write(fd, code, ft_strlen(code));
	write(fd, "\n", 1);
	close(fd);
	free_read(reader);
	free(code);
	return (1);
}
