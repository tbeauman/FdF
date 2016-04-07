/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbeauman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 14:14:40 by tbeauman          #+#    #+#             */
/*   Updated: 2016/02/04 19:34:44 by tbeauman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	debug(t_eve *e)
{
	int		i;
	t_point	*pts;

	i = 0;
	pts = e->ens;
	while (pts)
	{
		if (i == e->width)
		{
			ft_putchar('\n');
			i = 0;
		}
		ft_putnbr(pts->x);
		ft_putchar(':');
		ft_putnbr(pts->y);
		ft_putchar(':');
		ft_putnbr(pts->z);
		ft_putchar(' ');
		pts = pts->next;
		i++;
	}
}

int		main(int ac, char **av)
{
	t_eve	e;

	if (ac != 2)
		exit_with_msg("usage error: fdf needs one argument");
	if (!(e.mlx = mlx_init()))
		exit_with_msg("Connection to MLX server failed...");
	if (!(e.win = mlx_new_window(e.mlx, 1000, 1000, "fdf")))
		exit_with_msg("Failed to open window");
	if (!(e.img = mlx_new_image(e.mlx, 1000, 1000)))
		exit_with_msg("Failed to create image");
	init(&e, av[1]);
	draw_in_im(&e);
	mlx_put_image_to_window(e.mlx, e.win, e.img, 0, 0);
	mlx_key_hook(e.win, &key_pressed, &e);
	mlx_mouse_hook(e.win, &mouse_button, &e);
	mlx_loop(e.mlx);
	return (0);
}
