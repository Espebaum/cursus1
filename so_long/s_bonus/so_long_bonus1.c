/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:13:13 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/19 17:29:09 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	param_init(char *argv1, t_param *par)
{
	par->fd = open(argv1, O_RDONLY);
	if (par->fd <= 0)
		return ;
	par->mlx = mlx_init();
	par->map = NULL;
	par->i_num = 0;
	par->win_w = 0;
	par->win_h = 0;
	par->x = 64;
	par->y = 64;
	par->move = 0;
	par->p_c = 0;
	par->p_r = 0;
	par->map_r = 0;
	par->map_c = 0;
	par->e_r = 0;
	par->e_c = 0;
	par->win = NULL;
	par->cnt = 0;
	par->b_r[0] = 0;
	par->b_r[1] = 0;
	par->b_c[0] = 0;
	par->b_c[1] = 0;
}

int	read_map(t_param *par, int i, int j, int *cnt)
{
	if (par->map[i][j] != '0' && par->map[i][j] != '1'
			&& par->map[i][j] != 'C' && par->map[i][j] != 'E'
			&& par->map[i][j] != 'P' && par->map[i][j] != 'B')
		return (0);
	if ((i == 0 || i == par->map_r - 1 || j == 0
			|| j == par->map_c - 1) && par->map[i][j] != '1')
		return (0);
	if (par->map[i][j] == 'P')
	{
		par->p_r = i;
		par->p_c = j;
	}
	if (par->map[i][j] == 'E')
	{
		par->e_r = i;
		par->e_c = j;
	}
	if (par->map[i][j] == 'B')
		if (place_b(par, i, j, cnt) == 0)
			return (0);
	if (par->map[i][j] == 'C')
		par->i_num++;
	cnt[(int) par->map[i][j]]++;
	return (1);
}

int	check_map(t_param *par)
{
	int		i;
	int		j;
	int		cnt[128];

	if (par->map == NULL)
		return (0);
	i = -1;
	while (++i < 128)
		cnt[i] = 0;
	i = -1;
	while (++i < par->map_r)
	{
		if (ft_strlen(par->map[i]) != (size_t) par->map_c + 1)
			return (0);
		j = -1;
		while (++j < par->map_c)
			if (read_map(par, i, j, cnt) == 0)
				return (0);
	}
	if (cnt['C'] == 0 || cnt['E'] != 1 || cnt['P'] != 1 || cnt['B'] != 2)
		return (0);
	return (check_valid_path(par));
}

void	map_read(t_param *par)
{
	char	*line;
	char	**tmp_map;
	int		idx;

	while (1)
	{
		line = get_next_line(par->fd);
		if (!line)
			break ;
		par->map_c = ft_strlen(line) - 1;
		tmp_map = par->map;
		par->map = (char **) malloc(sizeof(char *) * (par->map_r + 1));
		idx = -1;
		while (++idx < par->map_r)
			par->map[idx] = tmp_map[idx];
		par->map[idx] = line;
		if (tmp_map)
			free(tmp_map);
		par->map_r++;
	}
	par->win_h = par->y * par->map_r;
	par->win_w = par->x * par->map_c;
}

int	main(int argc, char **argv)
{
	t_param		par;
	int			mapstat;

	if (argc != 2 || ft_strrncmp(argv[1], ".ber", 4))
		return (write(2, "Invalid Argument!\n", 18) * 0 + 1);
	param_init(argv[1], &par);
	if (par.fd <= 0)
		return (write(2, "Invalid Map File\n", 17) * 0 + 1);
	map_read(&par);
	mapstat = check_map(&par);
	if (!mapstat)
	{
		write(2, "map error!\n", 11);
		free_param(&par);
		return (1);
	}
	put_image(&par);
	par.win = mlx_new_window(par.mlx, par.win_w, par.win_h, "so_long");
	mlx_key_hook(par.win, &key_press, &par);
	mlx_hook(par.win, BUTTON_X, 0, &exit_game, &par);
	mlx_loop_hook(par.mlx, &frame_map, &par);
	mlx_loop(par.mlx);
	return (0);
}
