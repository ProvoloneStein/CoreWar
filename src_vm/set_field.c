/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 18:55:10 by student           #+#    #+#             */
/*   Updated: 2020/04/06 11:26:15 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	set_separator(WINDOW *field, int *x, int *y, int width)
{
	if (*x + 3 < width - 1)
	{
		mvwprintw(field, *y, *x, " ");
		*x += 1;
	}
	else
	{
		mvwprintw(field, *y, *x, "\n");
		(*y)++;
		*x = 1;
	}
}

static void	set_vars(int *width, int *x, int *y, int *i)
{
	*width = 194;
	*x = 1;
	*y = 1;
	*i = 0;
}

static int	set_color(int i, unsigned char *color_mem)
{
	int color;

	if (color_mem[i] != 0)
		color = (color_mem[i] >= 6) ? 16 : color_mem[i] + 11;
	else
		color = 20;
	return (COLOR_PAIR(color));
}

static void	set_cursor_color(WINDOW *field, t_cursor *cursor,
		unsigned char *mem)
{
	int i;
	int y;
	int x;
	int width;
	int color;

	width = 194;
	y = 1;
	x = 1;
	while (cursor)
	{
		i = cursor->position;
		if (cursor->player_id > 6)
			color = 6;
		else
			color = cursor->player_id + 1;
		color = COLOR_PAIR(color);
		wattron(field, color);
		y = i / 64 + 1;
		x = i % 64 * 3 + 1;
		mvwprintw(field, y, x, "%.2hhx", mem[i]);
		wattroff(field, color);
		cursor = cursor->next;
	}
}

void		set_field(WINDOW *field, t_cursor *cursor, unsigned char *mem,
		unsigned char *color_mem)
{
	int y;
	int x;
	int i;
	int width;
	int color;

	set_vars(&width, &x, &y, &i);
	while (i < MEM_SIZE)
	{
		color = set_color(i, color_mem);
		if (x + 2 < width - 1)
		{
			wattron(field, color);
			mvwprintw(field, y, x, "%.2hhx", mem[i]);
			wattroff(field, color);
			i++;
			x += 2;
		}
		set_separator(field, &x, &y, width);
	}
	set_cursor_color(field, cursor, mem);
	box(field, 0, 0);
	wrefresh(field);
}
