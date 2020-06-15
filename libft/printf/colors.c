/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:26:17 by pstein            #+#    #+#             */
/*   Updated: 2020/03/24 15:54:45 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_cmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s1[i] != '\0') && (s2[i] != '\0') && (s1[i] == s2[i]))
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		init_col(char **str, int color, int len)
{
	while (len-- > 0)
		(*str)++;
	if (color == 1)
		return ((ft_putstrint(RED)));
	else if (color == 2)
		return ((ft_putstrint(GREEN)));
	else if (color == 3)
		return ((ft_putstrint(YELLOW)));
	else if (color == 4)
		return ((ft_putstrint(BLUE)));
	else if (color == 5)
		return ((ft_putstrint(MAGENTA)));
	else if (color == 6)
		return ((ft_putstrint(CYAN)));
	else if (color == 7)
		return ((ft_putstrint(WHITE)));
	else if (color == 0)
		return ((ft_putstrint(RESET)));
	return (0);
}

int		color_check(char **str, char buff[4096], int *b_i)
{
	if (**str == '{')
	{
		if (ft_cmp(*str, "{red}", 5) == 0)
			return (print_buff(buff, b_i, 1) + init_col(str, 1, 5));
		else if (ft_cmp(*str, "{green}", 7) == 0)
			return (print_buff(buff, b_i, 1) + init_col(str, 2, 7));
		else if (ft_cmp(*str, "{yellow}", 8) == 0)
			return (print_buff(buff, b_i, 1) + init_col(str, 3, 8));
		else if (ft_cmp(*str, "{blue}", 6) == 0)
			return (print_buff(buff, b_i, 1) + init_col(str, 4, 6));
		else if (ft_cmp(*str, "{magenta}", 9) == 0)
			return (print_buff(buff, b_i, 1) + init_col(str, 5, 9));
		else if (ft_cmp(*str, "{cyan}", 6) == 0)
			return (print_buff(buff, b_i, 1) + init_col(str, 6, 6));
		else if (ft_cmp(*str, "{white}", 7) == 0)
			return (print_buff(buff, b_i, 1) + init_col(str, 7, 7));
		else if (ft_cmp(*str, "{eoc}", 5) == 0)
			return (print_buff(buff, b_i, 1) + init_col(str, 0, 5));
	}
	return (0);
}
