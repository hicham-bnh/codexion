/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:04:04 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/09 20:28:12 by mobenhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_pars
{
	int		number_coders;
	long	to_burnout;
	long	to_compile;
	long	to_debug;
	long	to_refactor;
	int		compiles_required;
	long	dongle_cooldown;
	char	*shceduler;
}		t_pars;

typedef struct s_dongles
{
	int		id;
	pthread_mutex_t	mutex;
	long	last_use;
}		t_dongles;

typedef struct s_coders
{
	int		id;
	int		compile;
	long		last_compile;
	t_dongles	*r_dongle;
	t_dongles	*l_dongle;
	pthread_t	thread;
}		t_coders;

typedef struct s_env
{
	t_coders *coders;
	t_dongles *dongles;
	t_pars pars;
	long	start;
}		t_env;


//parsing
int	pars_input(t_env *env, char **arg);

#endif