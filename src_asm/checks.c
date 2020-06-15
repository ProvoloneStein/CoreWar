/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 19:34:06 by pstein            #+#    #+#             */
/*   Updated: 2020/03/14 19:47:45 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

int		g_line;
int		g_column;
int		g_end;
int		g_byte;
char	*g_link_chars;

char	*find_oper(char *str)
{
	if (!ft_strcmp1(str, "or"))
		return ("or");
	else if (!ft_strcmp1(str, "xor"))
		return ("xor");
	else if (!ft_strcmp1(str, "zjmp"))
		return ("zjmp");
	else if (!ft_strcmp1(str, "fork"))
		return ("fork");
	else if (!ft_strcmp1(str, "lldi"))
		return ("lldi");
	else if (!ft_strcmp1(str, "lld"))
		return ("lld");
	else if (!ft_strcmp1(str, "lfork"))
		return ("lfork");
	else if (!ft_strcmp1(str, "aff"))
		return ("aff");
	return (0);
}

char	*find_operation(char *str)
{
	if (!ft_strcmp1(str, "live"))
		return ("live");
	else if (!ft_strcmp1(str, "ldi"))
		return ("ldi");
	else if (!ft_strcmp1(str, "ld"))
		return ("ld");
	else if (!ft_strcmp1(str, "sti"))
		return ("sti");
	else if (!ft_strcmp1(str, "st"))
		return ("st");
	else if (!ft_strcmp1(str, "add"))
		return ("add");
	else if (!ft_strcmp1(str, "sub"))
		return ("sub");
	else if (!ft_strcmp1(str, "and"))
		return ("and");
	return (find_oper(str));
}

int		if_digits(char *str)
{
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	if (str[i] && str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		i++;
		flag = 1;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if ((!str[i] || str[i] == SEPARATOR_CHAR || str[i] == '\n'
				|| str[i] == COMMENT_CHAR) && flag)
		return (1);
	return (0);
}

int		if_register(char *str)
{
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9') && i < 2)
	{
		i++;
		flag = 1;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if ((!str[i] || str[i] == SEPARATOR_CHAR || str[i] == '\n'
				|| str[i] == COMMENT_CHAR) && flag)
		return (1);
	return (0);
}

int		if_label(char *str)
{
	int		i;

	i = 0;
	while (ft_strchr(g_link_chars, str[i]))
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i] || str[i] == SEPARATOR_CHAR || str[i] == '\n'
			|| str[i] == COMMENT_CHAR)
		return (1);
	return (0);
}
