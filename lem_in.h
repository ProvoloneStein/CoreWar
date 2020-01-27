/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstein <pstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 08:37:44 by pstein            #+#    #+#             */
/*   Updated: 2020/01/27 20:45:19 by pstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <fcntl.h>
# include "ft_printf.h"
# include "libft.h"

typedef struct			s_pars
{
    int                 is_name;
    char				*name;
    int                 n_len;
    int                 is_com;
    char                *comment;
    int                 c_len;
}						t_pars;

int read_tok(int fd, t_pars *pars);
char			*ft_strplus_c(char *s1, char s2, int x);

#endif
