/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:34:25 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/11 03:01:02 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*routine(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	while(1)
	{
		pthread_mutex_lock(&coder->env->lock);
		if (check_compile(coder))
		{
			pthread_mutex_unlock(&coder->env->lock);
			break;
		}
		pthread_mutex_unlock(&coder->env->lock);
		take_dongle(coder);
		compile(coder);
		put_dongle(coder);
		pthread_cond_broadcast(&coder->env->dongles->cond);
		debug(coder);
		refctor(coder);
	}
	return (NULL);
}
