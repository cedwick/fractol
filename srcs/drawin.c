/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 11:25:39 by cbarbier          #+#    #+#             */
/*   Updated: 2017/03/02 17:57:01 by cbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void				put_pxl_img(int t, t_fract *f, t_coord *p, unsigned int c)
{
	char		*d;

	d = (f->data[t] + (f->sizeline * p->y + p->x * f->bpp / 8));
	d[0] = (c & 0xFF0000) >> 16;
	d[1] = (c & 0x00FF00) >> 8;
	d[2] = (c & 0xFF);
}

int			map_pixels(t_env *e)
{
	int			i;
	pthread_t	th[NB_THREAD];

	i = 0;
	while (i < NB_THREAD)
	{
		e->params[i].f = e->fract;
		e->params[i].index = i;
		if (pthread_create(th + i, 0, map_a_quarter, (e->params + i)))
			return (0);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
		pthread_join(th[i++], 0);
	return (1);
}
