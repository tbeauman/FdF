/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:29:46 by tbeauman          #+#    #+#             */
/*   Updated: 2016/02/08 14:41:25 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*new_point(int x, int y, int z, t_eve *e)
{
	t_point	*ret;

	if (!(ret = malloc(sizeof(t_point))))
		exit_with_msg("oops, malloc fail");
	ret->x = x;
	ret->y = y;
	ret->z = z;
	if (z > e->max_h)
		e->max_h = z;
	if (z < e->min_h)
		e->min_h = z;
	ret->px = e->x0 + e->ec
		* (e->p[0][0] * x + e->p[0][1] * y + e->p[0][2] * z);
	ret->py = e->y0 + e->ec
		* (e->p[1][0] * x + e->p[1][1] * y + e->p[1][2] * z);
	ret->next = NULL;
	return (ret);
}

void	add_point(t_point **pt, t_point *new)
{
	t_point	*bgn;

	if (!(*pt))
	{
		*pt = new;
		return ;
	}
	bgn = *pt;
	while ((*pt)->next)
		*pt = (*pt)->next;
	(*pt)->next = new;
	*pt = bgn;
}

void	recalc_persp_coords(t_eve *e)
{
	t_point	*bgn;
	int		x;
	int		y;
	int		z;

	bgn = e->ens;
	while (e->ens)
	{
		CAPPUCCINO;
		e->d[0] = cos(e->t[1]) * (sin(e->t[2]) * y +
				cos(e->t[2]) * x) - sin(e->t[1]) * z;
		e->d[1] = sin(e->t[0]) * (cos(e->t[1]) * z +
				sin(e->t[1]) * (sin(e->t[2]) * y + cos(e->t[2]) * x))
			+ cos(e->t[0]) * (cos(e->t[2]) * y - sin(e->t[2]) * x);
		e->d[2] = cos(e->t[0]) * (cos(e->t[1]) * z + sin(e->t[1]) *
				(sin(e->t[2]) * y + cos(e->t[2]) * x)) -
			sin(e->t[0]) * (cos(e->t[2]) * y - sin(e->t[2]) * x);
		if (e->d[2] != 0 && (e->ens->py = e->y0 + e->ec * e->d[0] / e->d[2]))
			e->ens->px = e->x0 + e->ec * e->d[1] / e->d[2];
		else if ((e->ens->py = e->y0 + e->ec * e->d[0] / 0.01))
			e->ens->px = e->x0 + e->ec * e->d[1] / 0.01;
		e->ens = e->ens->next;
	}
	e->ens = bgn;
}

void	recalc_coords(t_eve *e)
{
	t_point	*bgn;
	int		x;
	int		y;
	int		z;

	bgn = e->ens;
	while (e->ens)
	{
		x = e->ens->x;
		y = e->ens->y;
		if (e->zfact == 0)
			e->ens->z = 0;
		z = e->ens->z * e->zfact;
		e->ens->px = e->x0 + e->ec
			* (e->p[0][0] * x + e->p[0][1] * y + e->p[0][2] * z);
		e->ens->py = e->y0 + e->ec
			* (e->p[1][0] * x + e->p[1][1] * y + e->p[1][2] * z);
		e->ens = e->ens->next;
	}
	e->ens = bgn;
}

void	clear_image(char **address)
{
	int		i;

	i = 0;
	while (i < 1000 * 1000 * 4)
		(*address)[i++] = 0;
}
