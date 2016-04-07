/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 17:16:33 by tbeauman          #+#    #+#             */
/*   Updated: 2016/02/08 14:28:16 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_round(float x)
{
	return ((int)(x + 0.5));
}

void	ft_putpixel(int x, int y, t_eve *e, int height)
{
	int		*keepitreal;
	int		color;

	color = e->max_h ? height * 100 / e->max_h : 0;
	if (x + y * 1000 > 1000 * 1000 || x > 999 || y > 999 || x < 0 || y < 0)
		return ;
	keepitreal = (int*)e->img_address;
	if (color < 0)
		keepitreal[x + y * 1000] = 0x001E7FCB;
	else if (color < 10)
		keepitreal[x + y * 1000] = 0x00FDF1B8;
	else if (color < 30)
		keepitreal[x + y * 1000] = 0x0057D53B;
	else if (color < 60)
		keepitreal[x + y * 1000] = 0x005A6521;
	else if (color < 90)
		keepitreal[x + y * 1000] = 0x007C5725;
	else
		keepitreal[x + y * 1000] = 0x00ffffff;
	e->img_address = (char*)keepitreal;
}

void	draw_line2(t_point *p1, t_point *p2, t_eve *e)
{
	float	x;
	float	y;
	float	m;
	int		h;

	h = p1->z == 0 ? p2->z : p1->z;
	x = p1->px;
	y = p1->py;
	m = ((float)(p2->py - p1->py)) / ((float)(p2->px - p1->px));
	if (m >= 1.0)
		while (y <= p2->py)
		{
			ft_putpixel(ft_round(x), y, e, p2->z == e->max_h ? p2->z : h);
			y++;
			x += (1.0 / m);
		}
	else if (m <= -1.0)
		while (y >= p2->py)
		{
			ft_putpixel(ft_round(x), y, e, p2->z == e->max_h ? p2->z : h);
			y--;
			x -= (1.0 / m);
		}
}

void	draw_line(t_point *p1, t_point *p2, t_eve *e)
{
	float	x;
	float	y;
	float	m;
	int		h;

	if (p1->px > p2->px)
	{
		draw_line(p2, p1, e);
		return ;
	}
	h = p1->z == 0 ? p2->z : p1->z;
	x = p1->px;
	y = p1->py;
	m = ((float)(p2->py - p1->py)) / ((float)(p2->px - p1->px));
	if (fabsf(m) < 1)
		while (x <= p2->px)
		{
			ft_putpixel(x, ft_round(y), e, p2->z == e->max_h ? p2->z : h);
			y += m;
			x++;
		}
	else
		draw_line2(p1, p2, e);
}

void	draw_in_im(t_eve *e)
{
	t_point	*pts;
	t_point	*pts2;

	pts = e->ens;
	pts2 = e->ens;
	while (pts)
	{
		while (pts2)
		{
			if ((pts->x == pts2->x && pts->y == pts2->y + 1)
				|| (pts->y == pts2->y && pts->x == pts2->x + 1))
				draw_line(pts, pts2, e);
			pts2 = pts2->next;
		}
		pts2 = e->ens;
		pts = pts->next;
	}
}
