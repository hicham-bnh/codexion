/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:16:25 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/10 00:04:08 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	create_threads(t_env *env)
{
	int	i;

	i = 0 ;
	while (i < env->pars.number_coders)
	{
		env->coders[i].env = env;
		env->coders[i].id = i + 1;
		env->coders[i].compile = 0;
		env->coders[i].l_dongle = &env->dongles[i];
		env->coders[i].r_dongle = &env->dongles[(i + 1) % env->pars.number_coders];
		
		if (pthread_create(&env->coders[i].thread, NULL, &routine, &env->coders[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < env->pars.number_coders)
	{
		if (pthread_join(env->coders[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}
void	*routine(void *arg)
{
	t_coders	*coders;
	coders = (t_coders *)arg;
	while (1)
	{
		if (coders->compile == coders->env->pars.compiles_required)
			break;
		pthread_mutex_lock(&coders->env->lock);
		while (coders->l_dongle->free || coders->r_dongle->free)
			pthread_cond_wait(&coders->env->dongles->cond, &coders->env->lock);
		pthread_mutex_unlock(&coders->env->lock);
		pthread_mutex_lock(&coders->l_dongle->mutex);
		coders->l_dongle->free = 1;
		pthread_mutex_lock(&coders->r_dongle->mutex);
		coders->r_dongle->free = 1;
		printf("%ld %d  has taken a dongle\n", ft_time(coders->env->start), coders->id);
		printf("%ld %d  has taken a dongle\n", ft_time(coders->env->start), coders->id);
		coders->last_compile = get_time();
		printf("%ld %d is compiling\n", ft_time(coders->env->start), coders->id);
		coders->compile++;
		usleep(coders->env->pars.to_compile * 1000);
		coders->l_dongle->free = 0;
		pthread_mutex_unlock(&coders->l_dongle->mutex);
		coders->r_dongle->free = 0;
		pthread_mutex_unlock(&coders->r_dongle->mutex);
		pthread_cond_broadcast(&coders->env->dongles->cond);
		printf("%ld %d is debugging\n", ft_time(coders->env->start), coders->id);
		usleep(coders->env->pars.to_debug * 1000);
		printf("%ld %d is refactoring\n", ft_time(coders->env->start), coders->id);
		usleep(coders->env->pars.to_refactor * 1000);
	}
	return (NULL);
}
