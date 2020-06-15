/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:23:19 by gwyman-m          #+#    #+#             */
/*   Updated: 2020/04/06 11:23:54 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <ncurses.h>
# include "libft.h"
# include "op.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef struct		s_champ
{
	int				num;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	int				sizeof_code;
	unsigned char	code[CHAMP_MAX_SIZE + 1];
}					t_champ;

typedef struct		s_flags
{
	int				for_dump;
	int				dump_size;
	int				order[MAX_PLAYERS];
	int				count;
	char			visual;
	char			aff;
}					t_flags;

typedef struct		s_cursor
{
	int				cursor_id;
	int				player_id;
	int				delay;
	int				last_live_cycle;
	int				carry;
	int				position;
	char			command;
	int				bytes_for_next_command;
	int				r[REG_NUMBER + 1];
	struct s_cursor	*next;
}					t_cursor;

typedef struct		s_cmd_info
{
	unsigned char	id;
	unsigned char	dir_size;
	unsigned char	n_args;
	unsigned char	arg1;
	unsigned char	arg2;
	unsigned char	arg3;
}					t_cmd_info;

typedef struct		s_mem_cursor
{
	unsigned char	*mem;
	t_cursor		*cursor;
}					t_mem_cursor;

typedef struct		s_ncurses
{
	char			pause;
	char			game_over;
	WINDOW			*win_main;
	WINDOW			*win_field;
	WINDOW			*win_info;
	int				last_press;
	t_champ			*champs;
	unsigned char	*mem;
	t_cursor		**cursor_list;
}					t_ncurses;

typedef struct		s_game_info
{
	int				current_cycle;
	int				cycles_to_die;
	int				check_counter;
	int				last_alive;
	int				n_players;
	int				n_cursors;
	t_cursor		**orig_cursor_list;
	int				live_count;
	char			is_aff_flag;
	int				dump;
	int				next_cur_id;
	unsigned char	*color_mem;
	t_ncurses		visual;
}					t_game_info;

# define DATA_SIZE 16 + PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE

/*
**	main.c
*/

void				free_them_all(void *cell, char *what);

/*
**	error_usage.c
*/

void				print_usage(void);
void				check_error(char *name, char *text);
void				free_and_usage(char *tmp);

/*
**	init_champs.c
*/

void				init_champs(t_champ *champs,
					t_flags *flags, int argc, char **argv);

/*
**	detect_flags.c
*/

void				detect_flags(t_flags *flags, int argc, char **argv);

/*
**	detect_n_flag.c
*/

void				detect_n(int argc, char **argv, t_flags *flags, char *tmp);

/*
**	detect_dump_vis_flags.c
*/

void				detect_dump_vis(int argc,
					char **argv, t_flags *flags, char *tmp);

/*
**	init_vm.c
*/

void				init_vm(unsigned char *mem, t_champ *champs, int count);

/*
**	fill.c
*/

void				fill_champ(t_champ *champ, char *file);
void				check_valid_data(unsigned char data[], char *file);

/*
**	memory_buffer.c
*/

unsigned char		*mem_buff_init(void);

/*
**	mem_buff_print.c
*/

void				mem_buff_print(unsigned char *mem, int row);
void				mem_buff_print_w_cur(unsigned char *mem,
					t_cursor *cursor_list, int row);

/*
**	color_mem.c
*/

unsigned char		*color_mem_init(int n_players, t_champ *champs);
void				change_color_mem(int place, int size,
					unsigned char *mem, unsigned char player_num);

/*
**	cursor.c
*/

t_cursor			*cursor_list_init(int n_players);
t_cursor			*cursor_list_new(int position, int cur_id, int player_id);
t_cursor			*cursor_list_add(t_cursor *list, t_cursor *new);
void				cursor_list_free(t_cursor *list);
void				cursor_list_del(t_cursor **orig, t_cursor **list,
						t_cursor *prev);

/*
**	cursor_change_position.c
*/

void				cursor_change_position(t_cursor *list, int shift);

/*
**	cycle.c
*/

int					do_cycle(unsigned char *memory, t_game_info *info);

/*
**	perform_command.c
*/

void				perform_command(unsigned char *mem, t_cursor *cursor,
					t_game_info *game_info);

/*
**	load_cmd_info.c
*/

int					load_cmd_info(t_cmd_info *info, unsigned char *mem,
					t_cursor *cursor);

/*
**	count_shift.c
*/

int					count_shift(t_cmd_info *cmd_info);

/*
**	check.c
*/

int					do_check(t_cursor **cursor_list,
						int *cycles_to_die, t_game_info *info);

/*
**	draw.c
*/

void				draw(t_game_info *game);

/*
**	set_field.c
*/

void				set_field(WINDOW *field, t_cursor *cursor,
		unsigned char *mem, unsigned char *color_mem);

/*
**	set_info.c
*/

void				set_info(WINDOW *info, t_game_info *game, t_champ *champs);

/*
**	init_ncurses.c
*/

int					init_ncurses(t_ncurses *visual, t_game_info *game,
					unsigned char *mem);

/*
**	game.c
*/

int					start_game(unsigned char *memory, t_cursor **cursor_list,
					t_flags *flags);

/*
**	game_with_vis.c
*/

int					start_game_vis(unsigned char *memory,
						t_cursor **cursor_list,
						t_flags *flags, t_champ *champs);

/*
**	do_cmd
*/

int					do_cmd_w_args(unsigned char *mem, t_cursor *cursor,
					t_cmd_info *info, t_game_info *game_info);
int					do_cmd_no_args(unsigned char *mem, t_cursor *cursor,
					t_game_info *game_info);

# define LOG_MODE 0

/*
**	cmd_... .c
*/

int					cmd_live(unsigned char *mem, t_cursor *cursor,
						t_game_info *game_info);
int					cmd_zjmp(unsigned char *mem, t_cursor *cursor);
int					cmd_fork(unsigned char *mem, t_cursor *cursor,
						t_game_info *game_info);
int					cmd_lfork(unsigned char *mem, t_cursor *cursor,
						t_game_info *game_info);

void				cmd_ld(unsigned char *mem, t_cursor *cursor,
						t_cmd_info *cmd_info);
void				cmd_lld(unsigned char *mem, t_cursor *cursor,
						t_cmd_info *cmd_info);
void				cmd_st(unsigned char *mem, t_cursor *cursor,
						t_cmd_info *cmd_info, t_game_info *game_info);
void				cmd_add(unsigned char *mem, t_cursor *cursor);
void				cmd_sub(unsigned char *mem, t_cursor *cursor);
void				cmd_and(unsigned char *mem, t_cursor *cursor,
						t_cmd_info *cmd_info);
void				cmd_or(unsigned char *mem, t_cursor *cursor,
						t_cmd_info *cmd_info);
void				cmd_xor(unsigned char *mem, t_cursor *cursor,
						t_cmd_info *cmd_info);
void				cmd_ldi(unsigned char *mem, t_cursor *cursor,
						t_cmd_info *cmd_info);
void				cmd_sti(unsigned char *mem, t_cursor *cursor,
						t_cmd_info *cmd_info, t_game_info *game_info);
void				cmd_lldi(unsigned char *mem,
						t_cursor *cursor, t_cmd_info *cmd_info);
void				cmd_aff(unsigned char *mem,
						t_cursor *cursor, t_game_info *game_info);

/*
**	cmd_funcs.c
*/

int					correct_pos(int pos);
int					is_right_reg(unsigned char reg);

/*
**	cmd_get.c
*/

long int			get_t_dir4(unsigned char *mem, int pos);
long int			get_t_dir4_inplace(unsigned char *mem, int pos);
short int			get_t_dir2(unsigned char *mem, int pos);
unsigned char		get_t_reg(unsigned char *mem, int pos);

/*
**	cmd_load.c
*/

int					load_arg_info(t_mem_cursor *mc, unsigned char arg,
						long int *arg_info, int *pos);
int					load_arg_info2(t_mem_cursor *mc, unsigned char arg,
						long int *arg_info, int *pos);
void				load_from_reg(int reg_info, unsigned char *mem, int place);

/*
**	free_game.c
*/

void				free_game(t_cursor **cursor_list,
						t_game_info *game, unsigned char **mem);
void				free_game_exit(t_game_info *game, unsigned char **mem);

#endif
