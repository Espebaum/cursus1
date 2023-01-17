/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:30:49 by gyopark           #+#    #+#             */
/*   Updated: 2023/01/17 21:31:31 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_param *par)
{
	par->pimg = mlx_xpm_file_to_image(par->mlx, "imgs/P.xpm", &par->x, &par->y);
	par->cimg = mlx_xpm_file_to_image(par->mlx, "imgs/C.xpm", &par->x, &par->y);
	par->eimg = mlx_xpm_file_to_image(par->mlx, "imgs/E.xpm", &par->x, &par->y);
	par->img0 = mlx_xpm_file_to_image(par->mlx, "imgs/0.xpm", &par->x, &par->y);
	par->img1 = mlx_xpm_file_to_image(par->mlx, "imgs/1.xpm", &par->x, &par->y);
}
