#include "lem_in.h"
#include <errno.h>

int		main(int argc, char **argv)
{
	errno = 0;
	if (argc == 2 && is_filename(*(argv + 1), ".s"))
		assemble(*(argv + 1));
	else if (argc == 2 && is_filename(*(argv + 1), ".cor"))
		disassemble(*(argv + 1));
	else
		print_help();
	return (0);
}