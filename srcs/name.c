#include "lem_in.h"
#include "op.h"

int make_name(char *str, char *name, t_pars *pars, int fd)
{
	while(str && str != '"')
		name = ft_strplus(name, *str, 1, 0);
		
}

int name_w_end(t_pars *pars, int fd)
{
    char *line;
    int i;

    i = 0;
    line = NULL;
    while(get_next_line(fd, &line) > 0)
    {
        free(line);
    }
}

int name_w(char *str, t_pars *pars, int fd)
{
	int i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '\n' || str[i] == '\0' || str[i] != '"')
		return (-1);
	pars->name = ft_strnew(0);
	while(str[i] && str[i] != '"')
	{
        pars->name = ft_strplus(pars->name, str[i], 1, 0);
		i++;
        pars->n_len += 1
	}
    if (PROG_NAME_LENGTH >= pars->n_len)
        return(-1);
	if (str[i] != '"')
    {
        pars->name = ft_strplus(pars->name, str[i], 1, 0)
		return(name_w_end(pars, fd));
    }
	i++;	
	while(str[i])
	{
		if (str[i] != '\t' || str[i] != ' ')
			return(-1);
		i++;	
	}
	pars->is_name = 1;
	return(1);
}

int checkline(char *str, t_pars *pars, int fd)
{
	int i;

	i = 0;
	while (str[i] == '\t' && str[i] == ' ')
		i++;
	if (str[i] == '\n' || str[i] == '\0')
		return (1);
	if (ft_strequ(NAME_CMD_STRING, str + i))
		return(name_w(str + i + strlen(NAME_CMD_STRING), pars, fd));
	else if(ft_strequ(COMMENT_CMD_STRING, str + i))
		return(com_w(str + i + strlen(COMMENT_CMD_STRING), pars, fd));

}

int read_tok(int fd, t_pars *pars)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		checkline(line, pars);
        free(line);
	}
}