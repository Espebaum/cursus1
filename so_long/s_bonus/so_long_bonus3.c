/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:11:06 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/18 15:21:39 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	exit_game(t_param *par)
{
	int		idx;

	idx = -1;
	while (++idx < 5)
	{
		mlx_destroy_image(par->mlx, par->pimg[idx]);
		mlx_destroy_image(par->mlx, par->bimg[idx]);
	}
	mlx_destroy_image(par->mlx, par->cimg);
	mlx_destroy_image(par->mlx, par->eimg);
	mlx_destroy_image(par->mlx, par->img1);
	mlx_destroy_image(par->mlx, par->img0);
	mlx_destroy_window(par->mlx, par->win);
	free_param(par);
	exit(0);
	return (0);
}

void	move_exit(t_param *par)
{
	int		idx;

	idx = -1;
	if (par->i_num == 0)
	{
		ft_printf("%s\n", "game clear!");
		while (++idx < 5)
		{
			mlx_destroy_image(par->mlx, par->pimg[idx]);
			mlx_destroy_image(par->mlx, par->bimg[idx]);
		}
		mlx_destroy_image(par->mlx, par->cimg);
		mlx_destroy_image(par->mlx, par->eimg);
		mlx_destroy_image(par->mlx, par->img1);
		mlx_destroy_image(par->mlx, par->img0);
		mlx_destroy_window(par->mlx, par->win);
		free_param(par);
		exit(0);
	}
	else
		return ;
}

void	check_valid_path_sub(t_param *par, int r, int c, t_check *t)
{
	const int	dr[4] = {0, 0, -1, 1};
	const int	dc[4] = {-1, 1, 0, 0};
	int			nr;
	int			nc;
	int			i;

	t->visited[r][c] = 1;
	if (par->map[r][c] == 'C' || par->map[r][c] == 'E')
	{
		if (t->item_check[r][c] == 0)
		{
			t->cnt--;
			t->item_check[r][c] = 1;
		}
	}
	i = -1;
	while (++i < 4)
	{
		nr = r + dr[i];
		nc = c + dc[i];
		if (!t->visited[nr][nc] && par->map[nr][nc] != '1')
			check_valid_path_sub(par, nr, nc, t);
	}
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

int	check_valid_path(t_param *par)
{
	t_check		t;
	int			i;
	int			j;

	t.visited = (int **) malloc(sizeof(int *) * par->map_r);
	t.item_check = (int **) malloc(sizeof(int *) * par->map_r);
	i = -1;
	while (++i < par->map_r)
	{
		t.visited[i] = (int *) malloc(sizeof(int) * par->map_c);
		t.item_check[i] = (int *) malloc(sizeof(int) * par->map_c);
	}
	i = -1;
	while (++i < par->map_r)
	{
		j = -1;
		while (++j < par->map_c)
			t.item_check[i][j] = 0;
	}
	t.cnt = par->i_num + 1;
	return (check_valid_item(par, &t, i, j));
}
