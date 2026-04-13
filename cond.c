/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:00:14 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/13 23:45:45 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_dongles(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	pthread_mutex_lock(&coder->env->lock);
	if (dongle_left(coder) && dongle_right(coder))
	{
		pthread_mutex_unlock(&coder->env->lock);
		return (1);
	}
	pthread_mutex_unlock(&coder->env->lock);
	return (0);
}

int	dongle_left(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	pthread_mutex_lock(&coder->l_dongle->mutex);
	if (coder->l_dongle->free == 1)
	{
		pthread_mutex_unlock(&coder->l_dongle->mutex);
		return (0);
	}
	if (coder->l_dongle->free == 0)
	{
		if (ft_time(coder->l_dongle->last_use)
			< coder->env->pars.dongle_cooldown)
		{
			pthread_mutex_unlock(&coder->l_dongle->mutex);
			return (0);
		}
	}
	pthread_mutex_unlock(&coder->l_dongle->mutex);
	return (1);
}

int	dongle_right(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	pthread_mutex_lock(&coder->r_dongle->mutex);
	if (coder->r_dongle->free == 1)
	{
		pthread_mutex_unlock(&coder->r_dongle->mutex);
		return (0);
	}
	if (coder->r_dongle->free == 0)
	{
		if (ft_time(coder->r_dongle->last_use)
			< coder->env->pars.dongle_cooldown)
		{
			pthread_mutex_unlock(&coder->r_dongle->mutex);
			return (0);
		}
	}
	pthread_mutex_unlock(&coder->r_dongle->mutex);
	return (1);
}
