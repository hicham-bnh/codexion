/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobenhab <mobenhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 10:15:10 by mobenhab          #+#    #+#             */
/*   Updated: 2026/04/06 03:40:23 by mobenhab         ###   ########.fr       */
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
}		t_dongle;

typedef struct s_coders
{
	int			id;
	pthread_t	thread;
	long long	ast_compile;
	int			compil_count;
	t_dongle	*l_dongle;
	t_dongle	*r_dongle;
}			t_coders;

typedef struct s_env
{
	t_pars	*params;
	t_dongle	*dongles;
	pthread_mutex_t	*log_lock;
	int		stop;
	long long	start;
}		t_env;


//parsing
void		parsing_input(t_pars *test, char **str);
int			check_parsing(t_pars *stock);

//thread management
pthread_t	*create_threads(t_pars *stock);

#endif
