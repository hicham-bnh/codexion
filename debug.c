/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:11:31 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/14 01:19:33 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	debug(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	pthread_mutex_lock(&coder->env->lock);
	if (coder->env->stop)
	{
		pthread_mutex_unlock(&coder->env->lock);
		return (1);
	}
	pthread_mutex_unlock(&coder->env->lock);
	pthread_mutex_lock(&coder->env->write);
	printf("%ld %d is debugging\n", ft_time(coder->env->start), coder->id);
	pthread_mutex_unlock(&coder->env->write);
	usleep(coder->env->pars.to_debug * 1000);
	return (0);
}
