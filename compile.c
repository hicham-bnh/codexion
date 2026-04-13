/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 20:37:50 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/13 05:44:39 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_compile(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	pthread_mutex_lock(&coder->lock_doc);
	if (coder->compile == coder->env->pars.compiles_required)
	{
		pthread_mutex_unlock(&coder->lock_doc);
		return (1);
	}
	pthread_mutex_unlock(&coder->lock_doc);
	return (0);
}

void	compile(void *arg)
{
	t_coders	*coder;

	coder = (t_coders *)arg;
	pthread_mutex_lock(&coder->env->write);
	printf("%ld %d is compiling\n", ft_time(coder->env->start), coder->id);
	pthread_mutex_unlock(&coder->env->write);
	usleep(coder->env->pars.to_compile * 1000);
	pthread_mutex_lock(&coder->env->lock);
	coder->last_compile = get_time();
	coder->compile++;
	pthread_mutex_unlock(&coder->env->lock);
}
