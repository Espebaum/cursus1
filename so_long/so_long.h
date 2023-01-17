/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:27:51 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/17 20:42:59 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include "gnl/get_next_line.h"
# include "ft_printf/ft_printf.h"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define BUTTON_X 17

typedef struct s_param
{
	int		fd;
	char	**map;
	int		en_num;
	int		ex_num;
	int		i_num;
	int		win_w;
	int		win_h;
	int		x;
	int		y;
	int		move;
	int		p_c;
	int		p_r;
	int		e_r;
	int		e_c;
	int		map_r;
	int		map_c;
	void	*mlx;
	void	*pimg;
	void	*cimg;
	void	*eimg;
	void	*img0;
	void	*img1;
	void	*win;
}	t_param;

typedef struct s_check
{
	int		**visited;
	int		cnt;
}	t_check;

void	free_param(t_param *par);
int		check_valid_path(t_param *par);
void	drawmap(t_param *par, void *mlx);
void	move_exit(t_param *par);
int		key_press(int keycode, t_param *par);
int		exit_game(t_param *par);
int		ft_strrncmp(char *s1, char *s2, int n);

#endif
