/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshanaha <lshanaha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:56:05 by lshanaha          #+#    #+#             */
/*   Updated: 2019/04/12 14:41:50 by lshanaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *needle)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		if (str[i] == needle[0])
		{
			j = 0;
			while (needle[j] && (str[i + j] == needle[j]))
				j++;
			if (!needle[j])
				return ((char *)(str + i));
		}
		i++;
	}
	if (*needle)
		return (NULL);
	else
		return ((char *)str);
}
