/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/19 14:38:56 by tbeauman          #+#    #+#             */
/*   Updated: 2016/02/08 14:53:19 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_line(t_point **pts, char **s, int l, t_eve *e)
{
	int		i;

	i = 0;
	while (s[i])
	{
		add_point(pts, new_point(i, l, ft_atoi(s[i]), e));
		i++;
	}
	if (e->width == -1 || i > e->width)
		e->width = i;
}

t_point	*parse(t_eve *e, char *filename)
{
	char	*line;
	char	**s;
	int		fd[2];
	int		l;
	t_point	*pts;

	l = 0;
	pts = NULL;
	fd[1] = 0;
	if ((fd[0] = open(filename, O_RDONLY)) < 0)
		exit_with_msg("oops, open failed");
	while ((fd[1] = (get_next_line(fd[0], &line))))
	{
		if (fd[1] == -1)
			exit_with_msg("oops, gnl failed");
		s = ft_strsplit(line, ' ');
		get_line(&pts, s, l, e);
		free(s);
		l++;
	}
	e->length = l;
	s = NULL;
	close(fd[1]);
	ft_strdel(&line);
	return (pts);
}

void	init_matrice_proj(t_eve *e)
{
	e->p[0][0] = cos(e->omega);
	e->p[0][1] = -1 * sin(e->omega);
	e->p[0][2] = 0;
	e->p[1][0] = sin(e->omega) * sin(e->alpha);
	e->p[1][1] = cos(e->omega) * sin(e->alpha);
	e->p[1][2] = -1 * cos(e->alpha);
	e->c[0] = 0;
	e->c[1] = 0;
	e->c[2] = 0;
	e->t[0] = -0.235619 - 5 * M_PI / 80;
	e->t[1] = 1.570796;
	e->t[2] = 0.274889;
}

void	init(t_eve *e, char *filename)
{
	e->ec = 32;
	e->x0 = 400;
	e->y0 = 400;
	e->max_h = 0;
	e->min_h = 0;
	e->width = -1;
	e->length = -1;
	e->zfact = 1;
	e->omega = M_PI / 6;
	e->alpha = M_PI / 4;
	e->iso = 1;
	e->para = 0;
	init_matrice_proj(e);
	e->persp = 0;
	e->ens = parse(e, filename);
	e->img_address = mlx_get_data_addr(e->img, &e->bpp, &e->sline, &e->end);
}
