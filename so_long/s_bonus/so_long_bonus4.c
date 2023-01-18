/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:30:49 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/18 14:41:07 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	put_image(t_param *par)
{
	par->pimg[0] = mlx_xpm_file_to_image(par->mlx,
			"imgs/p0.xpm", &par->x, &par->y);
	par->pimg[1] = mlx_xpm_file_to_image(par->mlx,
			"imgs/p1.xpm", &par->x, &par->y);
	par->pimg[2] = mlx_xpm_file_to_image(par->mlx,
			"imgs/p2.xpm", &par->x, &par->y);
	par->pimg[3] = mlx_xpm_file_to_image(par->mlx,
			"imgs/p3.xpm", &par->x, &par->y);
	par->pimg[4] = mlx_xpm_file_to_image(par->mlx,
			"imgs/p4.xpm", &par->x, &par->y);
	par->bimg[0] = mlx_xpm_file_to_image(par->mlx,
			"imgs/b0.xpm", &par->x, &par->y);
	par->bimg[1] = mlx_xpm_file_to_image(par->mlx,
			"imgs/b1.xpm", &par->x, &par->y);
	par->bimg[2] = mlx_xpm_file_to_image(par->mlx,
			"imgs/b2.xpm", &par->x, &par->y);
	par->bimg[3] = mlx_xpm_file_to_image(par->mlx,
			"imgs/b3.xpm", &par->x, &par->y);
	par->bimg[4] = mlx_xpm_file_to_image(par->mlx,
			"imgs/b4.xpm", &par->x, &par->y);
	par->cimg = mlx_xpm_file_to_image(par->mlx, "imgs/C.xpm", &par->x, &par->y);
	par->eimg = mlx_xpm_file_to_image(par->mlx, "imgs/E.xpm", &par->x, &par->y);
	par->img0 = mlx_xpm_file_to_image(par->mlx, "imgs/0.xpm", &par->x, &par->y);
	par->img1 = mlx_xpm_file_to_image(par->mlx, "imgs/1.xpm", &par->x, &par->y);
}

void	free_check(t_param *par, t_check *t)
{
	int		i;

	i = -1;
	while (++i < par->map_r)
	{
		free(t->visited[i]);
		free(t->item_check[i]);
	}
	free(t->visited);
	free(t->item_check);
}

int	place_b(t_param *par, int i, int j, int *cnt)
{
	if (cnt['B'] == 2)
		return (0);
	if (cnt['B'] == 1)
	{
		if (par->map[i][j - 1] != 'B' && par->map[i - 1][j]
				!= 'B' && par->map[i + 1][j] != 'B'
				&& par->map[i][j + 1] != 'B')
			return (0);
	}
	par->b_r[cnt['B']] = i;
	par->b_c[cnt['B']] = j;
	return (1);
}

int	check_valid_item(t_param *par, t_check *t, int i, int j)
{
	int		k;
	int		is_valid;

	k = -1;
	while (++k < 2)
	{
		par->map[par->b_r[k]][par->b_c[k]] = '1';
		par->map[par->b_r[k ^ 1]][par->b_c[k ^ 1]] = '0';
		i = -1;
		while (++i < par->map_r)
		{
			j = -1;
			while (++j < par->map_c)
				t->visited[i][j] = 0;
		}
		check_valid_path_sub(par, par->p_r, par->p_c, t);
	}
	is_valid = (t->cnt == 0);
	free_check(par, t);
	return (is_valid);
}

int	frame_map(t_param *par)
{
	int		i;

	i = par->cnt / 30;
	if (par->b_r[i] == par->p_r && par->b_c[i] == par->p_c)
	{
		ft_printf("%s\n", "game over!");
		exit_game(par);
	}
	else
		par->map[par->b_r[i]][par->b_c[i]] = 'B';
	if (par->b_r[i ^ 1] == par->p_r && par->b_c[i ^ 1] == par->p_c)
		par->map[par->p_r][par->p_c] = 'P';
	else
		par->map[par->b_r[i ^ 1]][par->b_c[i ^ 1]] = '0';
	drawmap(par, par->mlx);
	par->cnt = (par->cnt + 1) % 60;
	return (0);
}
