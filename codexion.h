/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:04:04 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/15 00:25:52 by mobenhab         ###   ########.fr       */
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

typedef struct s_env	t_env;

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
	int				id;
	pthread_mutex_t	mutex;
	long			last_use;
	int				free;
}		t_dongles;

typedef struct s_coders
{
	int				id;
	int				compile;
	int				in_compile;
	int				finish;
	long			last_compile;
	t_dongles		*r_dongle;
	t_dongles		*l_dongle;
	pthread_t		thread;
	t_env			*env;
}		t_coders;

typedef struct s_env
{
	t_coders		*coders;
	t_dongles		*dongles;
	t_pars			pars;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_t		monitor;
	long			start;
	int				stop;
	int				thread_finish;
}		t_env;

//parsing
int		pars_input(t_env *env, char **arg);

//time
long	get_time(void);
long	ft_time(long start);

//threads
void	*routine(void *arg);
void	*monitor(void	*arg);
void	add_finish(t_env *env);
void	stop_simul(t_env *env);
int		start_threads(t_env *env);
int		create_threads(t_env *env);
int		check_end(t_env *env);
int		check_burnout(t_coders *coder);

//env
int		init_env(t_env *env);
int		init_mutex_env(t_env *env);
int		check_compil_end(t_env *env);

//compile
int		check_compile(void *arg);
int		compile(void *arg);

//dongle
int		check_dongles(void *arg);
void	take_dongle(t_coders *coder);
void	put_dongle(t_coders *coder);
int		dongle_left(void *arg);
int		dongle_right(void *arg);
int		check_burnout(t_coders *coder);

//debug
int		debug(void *arg);

//refactor
int		refctor(void *arg);

//burnout
void	burnout(void *arg, int i);
void	how_take(t_coders *coder);

#endif