/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:07:13 by tbeauman          #+#    #+#             */
/*   Updated: 2016/02/08 14:53:20 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotates(int kc, t_eve *e)
{
	if (kc == 86)
		e->omega += M_PI / 6;
	if (kc == 88)
		e->omega -= M_PI / 6;
	if (kc == 91)
		e->alpha -= M_PI / 8;
	if (kc == 84)
		e->alpha += M_PI / 8;
	if (kc == 82 || kc == 87)
		e->t[1] += kc == 82 ? -M_PI / 80 : M_PI / 80;
	if (kc == 92 || kc == 89)
		e->t[0] += kc == 92 ? -M_PI / 80 : M_PI / 80;
	if (kc == 83 || kc == 85)
		e->t[2] += kc == 83 ? -M_PI / 80 : M_PI / 80;
	if (e->iso)
		init_matrice_proj(e);
}

void	change_proj(int kc, t_eve *e)
{
	if (kc == 35)
	{
		e->p[0][0] = 1;
		e->p[0][1] = -0.5;
		e->p[0][2] = -0.25;
		e->p[1][0] = 0;
		e->p[1][1] = 1;
		e->p[1][2] = -0.25;
		e->para = 1;
		e->iso = 0;
		e->persp = 0;
	}
	if (kc == 34)
	{
		init_matrice_proj(e);
		e->iso = 1;
		e->para = 0;
		e->persp = 0;
	}
	if (kc == 8)
	{
		e->persp = 1;
		e->iso = 0;
		e->para = 0;
	}
}

int		key_pressed(int kc, t_eve *e)
{
	if (kc == 53)
		exit(1);
	if (kc == 69)
		e->zfact *= 1.5;
	if (kc == 78)
		e->zfact /= e->zfact > 0.005 ? 1.5 : 1;
	if (kc == 125 || kc == 126)
		e->y0 += kc == 125 ? 20 : -20;
	if (kc == 123 || kc == 124)
		e->x0 += kc == 123 ? -20 : 20;
	if (kc >= 82 && kc <= 92)
		rotates(kc, e);
	if (kc == 35 || kc == 34 || kc == 8)
		change_proj(kc, e);
	if (!e->persp)
		recalc_coords(e);
	else
		recalc_persp_coords(e);
	clear_image(&e->img_address);
	draw_in_im(e);
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	if (kc == 71)
		mlx_clear_window(e->mlx, e->win);
	return (1);
}

int		mouse_button(int button, int x, int y, t_eve *e)
{
	if (button == 1)
	{
		e->x0 = x;
		e->y0 = y;
	}
	if (button == 4)
		e->ec = ft_round(e->ec * 0.75);
	if (button == 5)
		e->ec = ft_round(e->ec * 1.25);
	if (!e->persp)
		recalc_coords(e);
	else
		recalc_persp_coords(e);
	clear_image(&e->img_address);
	draw_in_im(e);
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (1);
}
