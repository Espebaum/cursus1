/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:12:55 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/17 14:11:08 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "so_long.h"

void	free_param(t_param *par)
{
	int		idx;

	idx = -1;
	while (++idx < par->map_r)
		free(par->map[idx]);
	free(par->map);
}

void	move_char(t_param *par, int dr, int dc)
{
	int		nr;
	int		nc;

	nr = par->p_r + dr;
	nc = par->p_c + dc;
	if (par->map[nr][nc] == '1')
		return ;
	if (par->map[nr][nc] == 'E')
		move_exit(par);
	else if (par->map[nr][nc] == 'C')
		par->i_num--;
	ft_printf("%d\n", ++par->move);
	par->map[nr][nc] = 'P';
	par->map[par->p_r][par->p_c] = '0';
	if (par->p_r == par->e_r && par->p_c == par->e_c)
		par->map[par->p_r][par->p_c] = 'E';
	par->p_r = nr;
	par->p_c = nc;
}

int	key_press(int keycode, t_param *par)
{
	if (keycode == KEY_W)
		move_char(par, -1, 0);
	else if (keycode == KEY_A)
		move_char(par, 0, -1);
	else if (keycode == KEY_S)
		move_char(par, 1, 0);
	else if (keycode == KEY_D)
		move_char(par, 0, 1);
	else if (keycode == KEY_ESC)
	{
		free_param(par);
		exit(0);
	}
	drawmap(par, par->mlx);
	return (0);
}

void	draw_img(t_param *par, void *mlx, int r, int c)
{
	if (par->map[r][c] == '0')
		mlx_put_image_to_window(mlx, par->win, par->img0, c * par->x,
			r * par->y);
	else if (par->map[r][c] == '1')
		mlx_put_image_to_window(mlx, par->win, par->img1, c * par->x,
			r * par->y);
	else if (par->map[r][c] == 'C')
		mlx_put_image_to_window(mlx, par->win, par->cimg, c * par->x,
			r * par->y);
	else if (par->map[r][c] == 'E')
		mlx_put_image_to_window(mlx, par->win, par->eimg, c * par->x,
			r * par->y);
	else if (par->map[r][c] == 'P')
		mlx_put_image_to_window(mlx, par->win, par->pimg, c * par->x,
			r * par->y);
}

void	drawmap(t_param *par, void *mlx)
{
	int		r;
	int		c;
	char	*s;

	r = -1;
	mlx_clear_window(mlx, par->win);
	while (++r < par->map_r)
	{
		c = -1;
		while (++c < par->map_c)
			draw_img(par, mlx, r, c);
	}
	s = ft_itoa(par->move);
	mlx_string_put(mlx, par->win, 10, 10, 0xFFFFFF, s);
	free(s);
}
