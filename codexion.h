/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:15:10 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/08 14:23:35 by mobenhab         ###   ########.fr       */
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
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	*scheduler;
}			t_pars;

typedef struct s_dongle
{
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	long long		last_usage;
	bool		dispo;
}		t_dongle;

typedef struct s_coders
{
	int			id;
	int			compil_count;
	long long	last_compile;
	long long	dead_line;
	pthread_t	thread;
	t_dongle	*l_dongle;
	t_dongle	*r_dongle;
	pthread_mutex_t	coder_lock;
}			t_coders;

typedef struct s_env
{
	t_pars	*params;
	t_dongle	*dongles;
	t_coders	*coders;
	pthread_mutex_t	log_lock;
	pthread_mutex_t	status_lock;
	int		stop;
	long long	start;
}		t_env;


//parsing
int		parsing_input(t_env *env, char **str);
int			check_parsing(t_env *env);

//thread management
pthread_t	*create_threads(t_env *env);

// dongle management
pthread_mutex_t *create_mutex(t_env *env);

#endif
