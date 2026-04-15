/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:53:58 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/15 03:05:55 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_end(t_env *env)
{
	pthread_mutex_lock(&env->lock);
	if (env->stop)
	{
		pthread_mutex_unlock(&env->lock);
		return (1);
	}
	pthread_mutex_unlock(&env->lock);
	return (0);
}

void	add_finish(t_env *env)
{
	pthread_mutex_lock(&env->lock);
	env->thread_finish += 1;
	pthread_mutex_unlock(&env->lock);
}

int	check_compil_end(t_env *env)
{
	pthread_mutex_lock(&env->lock);
	if (env->thread_finish == env->pars.compiles_required)
	{
		pthread_mutex_unlock(&env->lock);
		stop_simul(env);
		return (1);
	}
	pthread_mutex_unlock(&env->lock);
	return (0);
}

void	stop_simul(t_env *env)
{
	pthread_mutex_lock(&env->lock);
	env->stop = 1;
	pthread_mutex_unlock(&env->lock);
}
