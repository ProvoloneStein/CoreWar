/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edgar_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galiza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:45:36 by galiza            #+#    #+#             */
/*   Updated: 2020/03/15 18:51:46 by galiza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

char	*g_link_chars;
int		g_line;
int		g_column;
int		g_end;
int		g_byte;

void	scr_lin(char *c)
{
	if (c[g_end - 1] == '\n')
	{
		g_column = 0;
		while (c[g_end + g_column] != '\n')
			g_column++;
		g_column++;
		g_line--;
	}
	else
		g_column--;
	g_end--;
}

void	score_line(char *c, int value, int ascending)
{
	while (value)
	{
		if (ascending)
		{
			if (c[g_end] == '\n')
			{
				g_column = 1;
				g_line++;
			}
			else
				g_column++;
			g_end++;
		}
		else
			scr_lin(c);
		value--;
	}
}

char	*get_name_com(char *map)
{
	char	*temp;
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	while (*map && i != 2)
	{
		if (map[start + g_end] == '"' && i == 0)
			i = 1;
		else if (i == 0)
			start++;
		if (i == 1)
			len++;
		if (map[start + len + g_end] == '"' && i == 1)
			i = 2;
	}
	temp = ft_strsub(map, start + g_end + 1, len - 1);
	score_line(map, start + len + 1, 1);
	return (temp);
}

char	*get_content(char *map, t_oken token)
{
	if (token == NAME || token == COMMENT)
		return (get_name_com(map));
	else if (token == INSTRUCTION)
		return (ft_strdup(find_operation(map + g_end)));
	return (0);
}

void	skip_space(char *c)
{
	while ((c[g_end] == ' ' || c[g_end] == '\t' || c[g_end] == '\n'
				|| c[g_end] == COMMENT_CHAR ||
				c[g_end] == SEPARATOR_CHAR) && c[g_end])
	{
		if (c[g_end] == COMMENT_CHAR)
			while (c[g_end] != '\n' && c[g_end])
				score_line(c, 1, 1);
		else
			score_line(c, 1, 1);
	}
}
