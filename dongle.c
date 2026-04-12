/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:51:07 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/12 20:45:28 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	take_dongle(t_coders *coder)
{
	if (coder->id % 2 == 0)
	{
		pthread_mutex_lock(&coder->l_dongle->mutex);
		coder->l_dongle->free = 1;
		pthread_mutex_unlock(&coder->l_dongle->mutex);
		pthread_mutex_lock(&coder->r_dongle->mutex);
		coder->r_dongle->free = 1;
		pthread_mutex_unlock(&coder->r_dongle->mutex);
	}
	else
	{
		pthread_mutex_lock(&coder->r_dongle->mutex);
		coder->r_dongle->free = 1;
		pthread_mutex_unlock(&coder->r_dongle->mutex);
		pthread_mutex_lock(&coder->l_dongle->mutex);
		coder->l_dongle->free = 1;
		pthread_mutex_unlock(&coder->l_dongle->mutex);
	}
	pthread_mutex_lock(&coder->env->write);
	printf("%ld %d  has taken a dongle\n",
		ft_time(coder->env->start), coder->id);
	printf("%ld %d  has taken a dongle\n",
		ft_time(coder->env->start), coder->id);
	pthread_mutex_unlock(&coder->env->write);
}

void	put_dongle(t_coders *coder)
{
	pthread_mutex_lock(&coder->l_dongle->mutex);
	coder->l_dongle->free = 0;
	coder->l_dongle->last_use = get_time();
	pthread_mutex_unlock(&coder->l_dongle->mutex);
	pthread_mutex_lock(&coder->r_dongle->mutex);
	coder->r_dongle->free = 0;
	coder->r_dongle->last_use = get_time();
	pthread_mutex_unlock(&coder->r_dongle->mutex);
}
