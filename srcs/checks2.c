/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 19:47:58 by pstein            #+#    #+#             */
/*   Updated: 2020/03/14 20:04:37 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assem.h"

int		if_name(char *str)
{
	int		i;

	i = 0;
	if (ft_strcmp1(str, NAME_CMD_STRING))
		return (0);
	i = i + ft_strlen(NAME_CMD_STRING);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	if (!str[i] || str[i] != '"')
		return (0);
	i++;
	while (str[i] && str[i] != '"')
		i++;
	if (str[i])
		return (1);
	return (0);
}

int		if_comment(char *str)
{
	int		i;

	i = 0;
	if (ft_strcmp1(str, COMMENT_CMD_STRING))
		return (0);
	i = i + ft_strlen(COMMENT_CMD_STRING);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	if (!str[i] || str[i] != '"')
		return (0);
	i++;
	while (str[i] && str[i] != '"')
		i++;
	if (str[i])
		return (1);
	return (0);
}

int		if_operation(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	temp = find_operation(str);
	if (!temp)
		return (0);
	i = ft_strlen(temp);
	if (str[i] == ' ' || str[i] == '\t' || str[i] == '%')
		return (1);
	return (0);
}

int		check_map(char *map)
{
	int		i;

	i = 0;
	while (map[i])
		i++;
	while (i > 0 && map[i] != '\n')
		i--;
	i++;
	while (map[i] == ' ' || map[i] == '\t')
		i++;
	if (!map[i] || map[i] == COMMENT_CHAR)
		return (1);
	return (0);
}

int		check_commas(char *map)
{
	int	i;

	i = 0;
	while (map[i] == ' ' || map[i] == '\t')
		i--;
	if (map[i] == SEPARATOR_CHAR)
		return (1);
	return (0);
}
