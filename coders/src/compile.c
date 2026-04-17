/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:37:50 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/17 00:47:03 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	finish_compile(t_coders *coder)
{
	pthread_mutex_lock(&coder->env->time_mutex);
	coder->in_compile = 0;
	pthread_mutex_unlock(&coder->env->time_mutex);
}

int	check_compile(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	pthread_mutex_lock(&coder->env->time_mutex);
	if (coder->compile == coder->env->pars.compiles_required)
	{
		pthread_mutex_unlock(&coder->env->time_mutex);
		return (1);
	}
	pthread_mutex_unlock(&coder->env->time_mutex);
	return (0);
}

static void	time_compile(t_coders *coder)
{
	pthread_mutex_lock(&coder->env->time_mutex);
	coder->last_compile = get_time();
	pthread_mutex_unlock(&coder->env->time_mutex);
}

int	compile(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	pthread_mutex_lock(&coder->env->lock);
	if (coder->env->stop)
	{
		pthread_mutex_unlock(&coder->env->lock);
		return (1);
	}
	coder->compile++;
	if (coder->compile == coder->env->pars.compiles_required)
		coder->env->thread_finish++;
	pthread_mutex_lock(&coder->env->write);
	if (coder->env->thread_finish == coder->env->pars.number_coders)
		coder->env->write_stop = 1;
	pthread_mutex_unlock(&coder->env->write);
	coder->in_compile = 1;
	pthread_mutex_unlock(&coder->env->lock);
	time_compile(coder);
	pthread_mutex_lock(&coder->env->write);
	printf("%ld %d is compiling\n", ft_time(coder->env->start), coder->id);
	pthread_mutex_unlock(&coder->env->write);
	usleep(coder->env->pars.to_compile * 1000);
	finish_compile(coder);
	return (0);
}
