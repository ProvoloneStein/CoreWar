/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:21:45 by pstein            #+#    #+#             */
/*   Updated: 2020/03/15 20:17:39 by pstein           ###   ########.fr       */
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
	t_read	*rd;

	rd = (t_read*)malloc(sizeof(t_read));
	rd->comment = NULL;
	rd->name = NULL;
	rd->i = 0;
	rd->arg_types = 0;
	rd->code_size = 0;
	rd->code = NULL;
	rd->filename = create_file_s(progname);
	return (rd);
}

static void	only_writer(int fd, t_read *reader, char *code)
{
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

int			disassembler(char *filename)
{
	t_read	*reader;
	char	*code;
	int		fd;

	code = ft_strnew(0);
	if ((fd = open(filename, O_RDONLY)) == -1)
		d_errors(1);
	reader = reader_init(filename);
	read_codefile(reader, fd);
	close(fd);
	hero_code(reader, &code);
	ft_printf("%s", reader->filename);
	if ((fd = open(reader->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		d_errors(2);
	ft_printf("Writing in file %s\n", reader->filename);
	only_writer(fd, reader, code);
	close(fd);
	free_read(reader);
	free(code);
	return (1);
}
