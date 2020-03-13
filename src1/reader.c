static int32_t	read_int(int fd)
{
	ssize_t	size;
	uint8_t	buffer[4];

	size = read(fd, &buffer, 4);
	if (size == -1)
		terminate(ERR_READ_FILE);
	if (size < 4)
		terminate(ERR_INVALID_FILE);
	return (bytecode_to_int32(buffer, 4));
}

static int32_t	parse_int32(int fd)
{
	ssize_t	size;
	uint8_t	buffer[4];

	size = read(fd, &buffer, 4);
	if (size == -1)
		terminate(ERR_READ_FILE);
	if (size < 4)
		terminate(ERR_INVALID_FILE);
	return (bytecode_to_int32(buffer, 4));
}

static char *read_commands(int fd, size_t len)
{
    ssize_t	size;
	char	*buffer;
    size_t i;

	if (!(buffer = ft_strnew(len)))
		terminate(ERR_STR_INIT);
	size = read(fd, buffer, len);
	if (size == -1)
		terminate(ERR_READ_FILE);
	if (size < (ssize_t)len)
		terminate(ERR_INVALID_FILE);
    i = ft_strlen(buffer);
    while (i < len)
	{
		if (buffer[i])
			terminate(WRONG_COMMAND);
		i++;
	}
	return (buffer);
}


static uint8_t	*parse_code(int fd, size_t len)
{
	ssize_t	size;
	uint8_t	*buffer;
	uint8_t	byte;

	if (!(buffer = ft_memalloc(len)))
		terminate(ERR_CODE_INIT);
	size = read(fd, buffer, len);
	if (size == -1)
		terminate(ERR_READ_FILE);
	if (size < (ssize_t)len || read(fd, &byte, 1) != 0)
		terminate(ERR_INVALID_FILE);
	return (buffer);
}



void			read_codefile(t_read *reader, int fd)
{
	if (read_int(fd) != COREWAR_EXEC_MAGIC)
		terminate(ERR_INVALID_MAGIC);
	reader->name = read_commands(fd, PROG_NAME_LENGTH);
	if (read_int(fd) != 0)
		terminate(ERR_NO_NULL);
	if ((reader->code_size = read_int(fd)) < 0)
		terminate(ERR_INVALID_CODE_SIZE);
	reader->comment = read_commands(parser->fd, COMMENT_LENGTH);
	if (read_int(fd) != 0)
		terminate(ERR_NO_NULL);
	reader->code = parse_code(fd, (size_t)parser->code_size);
}
