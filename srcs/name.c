#include "lem_in.h"
#include "op.h"

int name_w_end(t_pars *pars, int fd)
{
    char *line;
    int i;

    line = NULL;
    while(get_next_line(fd, &line) > 0 && pars->is_name == 0)
    {
        i = 0;
        while(line[i] && line[i] != '"')
	    {
           pars->name = ft_strplus_c(pars->name, line[i], 1);
	    	i++;
           pars->n_len += 1;
	    }
        if (line[i])
        {
            i++;
            while(line[i])
	        {
	        	if (line[i] != '\t' || line[i] != ' ')
	        		return(-1);
	        	i++;	
	        }
	        pars->is_name = 1;
        }
        else
            pars->name = ft_strplus_c(pars->name, '\n', 1);
        free(line);
    }
    return(1);
}

int name_w(char *str, t_pars *pars, int fd)
{
	int i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '\n' || str[i] == '\0' || str[i++] != '"')
		return (-1);
	pars->name = ft_strnew(0);
	while(str[i] && str[i] != '"')
	{
        pars->name = ft_strplus_c(pars->name, str[i], 1);
		i++;
        pars->n_len += 1;
	}
    if (PROG_NAME_LENGTH <= pars->n_len)
        return(-1);
	if (str[i] != '"')
    {
        pars->name = ft_strplus_c(pars->name, '\n', 1);
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

int name_c_end(t_pars *pars, int fd)
{
    char *line;
    int i;

    line = NULL;
    while(get_next_line(fd, &line) > 0 && pars->is_com == 0)
    {
        i = 0;
        while(line[i] && line[i] != '"')
	    {
           pars->comment = ft_strplus_c(pars->comment, line[i], 1);
	    	i++;
           pars->c_len += 1;
	    }
        if (line[i])
        {
            i++;
            while(line[i])
	        {
	        	if (line[i] != '\t' || line[i] != ' ')
	        		return(-1);
	        	i++;	
	        }
	        pars->is_com = 1;
        }
        else
            pars->comment = ft_strplus_c(pars->comment, '\n', 1);
        free(line);
    }
    return(1);
}

int com_w(char *str, t_pars *pars, int fd)
{
	int i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '\n' || str[i] == '\0' || str[i++] != '"')
		return (-1);
	pars->comment = ft_strnew(0);
	while(str[i] && str[i] != '"')
	{
        pars->comment = ft_strplus_c(pars->comment, str[i], 1);
		i++;
        pars->c_len += 1;
	}
    if (COMMENT_LENGTH <= pars->c_len)
        return(-1);
	if (str[i] != '"')
    {
        pars->comment = ft_strplus_c(pars->comment, '\n', 1);
		return(name_c_end(pars, fd));
    }
	i++;	
	while(str[i])
	{
		if (str[i] != '\t' || str[i] != ' ')
			return(-1);
		i++;	
	}
	pars->is_com = 1;
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
	if (ft_strncmp(NAME_CMD_STRING, (str + i), ft_strlen(NAME_CMD_STRING)) == 0  && pars->is_name != 1)
		return(name_w(str + i + strlen(NAME_CMD_STRING), pars, fd));
	else if(ft_strncmp(COMMENT_CMD_STRING, str + i, ft_strlen(COMMENT_CMD_STRING)) && pars->is_com != 1)
		return(com_w(str + i + strlen(COMMENT_CMD_STRING), pars, fd));
    return(-1);    

}

int read_tok(int fd, t_pars *pars)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		checkline(line, pars, fd);
        free(line);
	}
return(1);
}