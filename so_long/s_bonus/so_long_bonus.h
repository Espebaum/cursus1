/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:27:51 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/18 15:43:05 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../mlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../gnl/get_next_line.h"
# include "../ft_printf/ft_printf.h"

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
	int		b_r[2];
	int		b_c[2];
	int		map_r;
	int		map_c;
	void	*mlx;
	void	*pimg[5];
	void	*bimg[5];
	void	*cimg;
	void	*eimg;
	void	*img0;
	void	*img1;
	void	*win;
	int		cnt;
}	t_param;

typedef struct s_check
{
	int		**visited;
	int		**item_check;
	int		cnt;
}	t_check;

void	free_param(t_param *par);
void	put_image(t_param *par);
int		check_valid_path(t_param *par);
void	drawmap(t_param *par, void *mlx);
void	move_exit(t_param *par);
int		key_press(int keycode, t_param *par);
int		exit_game(t_param *par);
int		ft_strrncmp(char *s1, char *s2, int n);
int		frame_map(t_param *par);
void	check_valid_path_sub(t_param *par, int r, int c, t_check *t);
int		check_valid_item(t_param *par, t_check *t, int i, int j);
int		place_b(t_param *par, int i, int j, int *cnt);
void	free_check(t_param *par, t_check *t);

#endif
