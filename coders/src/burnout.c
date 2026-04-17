/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnout.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 00:09:45 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/16 23:55:45 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	burnout(void *arg, int i)
{
	t_env	*env;

	env = (t_env *)arg;
	pthread_mutex_lock(&env->lock);
	if (env->thread_finish == env->pars.number_coders)
	{
		pthread_mutex_unlock(&env->lock);
		return ;
	}
	pthread_mutex_unlock(&env->lock);
	pthread_mutex_lock(&env->write);
	printf("%ld %d burned out\n",
		ft_time(env->start), env->coders[i].id);
	pthread_mutex_unlock(&env->write);
}

int	check_burnout(t_coders *coder, int i)
{
	pthread_mutex_lock(&coder->env->time_mutex);
	if (ft_time(coder->last_compile) > coder->env->pars.to_burnout
		&& !coder->in_compile
		&& coder->compile != coder->env->pars.compiles_required)
	{
		coder->env->thread_finish = coder->env->pars.number_coders * 2;
		pthread_mutex_unlock(&coder->env->time_mutex);
		pthread_mutex_lock(&coder->env->write);
		coder->env->write_stop = 1;
		pthread_mutex_unlock(&coder->env->write);
		stop_simul(coder->env);
		burnout(coder->env, i);
		return (1);
	}
	pthread_mutex_unlock(&coder->env->time_mutex);
	return (0);
}
