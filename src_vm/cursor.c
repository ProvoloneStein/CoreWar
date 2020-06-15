/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 12:33:29 by student           #+#    #+#             */
/*   Updated: 2020/03/27 19:10:15 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_cursor	*cursor_list_new(int position, int cursor_id, int player_id)
{
	t_cursor	*new;
	int			i;

	if (!(new = (t_cursor*)malloc(sizeof(t_cursor))))
		return (NULL);
	position %= MEM_SIZE;
	new->position = position;
	new->cursor_id = cursor_id;
	new->player_id = player_id;
	new->delay = 0;
	new->last_live_cycle = 0;
	new->carry = 0;
	new->command = 0;
	new->bytes_for_next_command = 0;
	new->next = NULL;
	new->r[1] = -player_id;
	i = 2;
	while (i <= REG_NUMBER)
	{
		new->r[i] = 0;
		++i;
	}
	return (new);
}

t_cursor	*cursor_list_init(int n_players)
{
	int			i;
	int			gap;
	int			position;
	t_cursor	*cursor_list;
	t_cursor	*cursor;

	i = 0;
	gap = MEM_SIZE / n_players;
	position = 0;
	cursor_list = NULL;
	while (i < n_players)
	{
		if (!(cursor = cursor_list_new(position, i + 1, i + 1)))
		{
			cursor_list_free(cursor_list);
			check_error("Cursor list", "bad malloc");
		}
		position += gap;
		cursor_list = cursor_list_add(cursor_list, cursor);
		i++;
	}
	return (cursor_list);
}

t_cursor	*cursor_list_add(t_cursor *list, t_cursor *new)
{
	if (!list)
		return (new);
	new->next = list;
	return (new);
}

void		cursor_list_free(t_cursor *list)
{
	t_cursor *tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void		cursor_list_del(t_cursor **list, t_cursor **to_del, t_cursor *prev)
{
	t_cursor	*tmp_del;

	if (!list || !to_del)
		return ;
	tmp_del = *to_del;
	if (*list == *to_del)
	{
		*list = (*list)->next;
		free(tmp_del);
		*to_del = *list;
	}
	else
	{
		prev->next = tmp_del->next;
		free(tmp_del);
		*to_del = prev->next;
	}
}
