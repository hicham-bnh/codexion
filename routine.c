/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:34:25 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/11 16:33:35 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*routine(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	if (coder->id % 2 == 0)
		usleep(coder->env->pars.to_compile * 1000);
	while(1)
	{
		pthread_mutex_lock(&coder->env->lock);
		if (check_compile(coder))
		{
			pthread_mutex_unlock(&coder->env->lock);
			break;
		}
		while (!check_dongles(coder))
			continue;
		pthread_mutex_unlock(&coder->env->lock);
		take_dongle(coder);
		compile(coder);
		put_dongle(coder);
		debug(coder);
		refctor(coder);
	}
	return (NULL);
}
