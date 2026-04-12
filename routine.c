/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:34:25 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/13 01:17:17 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*routine(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	if (coder->id % 2 == 0)
		usleep(coder->env->pars.to_compile * 1000);
	while (coder->env->stop == 0)
	{
		pthread_mutex_lock(&coder->env->lock);
		if (check_compile(coder))
		{
			coder->env->thread_finish++;
			pthread_mutex_unlock(&coder->env->lock);
			break ;
		}
		while (!check_dongles(coder))
			continue ;
		pthread_mutex_unlock(&coder->env->lock);
		take_dongle(coder);
		compile(coder);
		put_dongle(coder);
		debug(coder);
		refctor(coder);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_env	*env;
	int		i;

	env = (t_env *)arg;
	while (env->stop == 0 && env->thread_finish != env->pars.compiles_required)
	{
		i = 0;
		while (i < env->pars.number_coders)
		{
			if (ft_time(env->coders[i].last_compile) > env->pars.to_burnout)
			{
				pthread_mutex_lock(&env->lock);
				env->stop++;
				pthread_mutex_unlock(&env->lock);
				pthread_mutex_lock(&env->write);
				printf("%ld %d  burned out\n",
					ft_time(env->start), env->coders[i].id);
				pthread_mutex_unlock(&env->write);
				break ;
			}
			else
				i++;
		}
	}
	return (NULL);
}
