/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:42:22 by zwalad            #+#    #+#             */
/*   Updated: 2022/05/23 17:10:47 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<sys/time.h>
# include	<pthread.h>
# include	<string.h>

typedef struct s_data
{
	int				mu_ea;
	int				mo_ea;
	long long		l_ea;
	int				id;
	pthread_mutex_t	eating;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct t_philo	*philo;
	int				go_away;
}	t_data;

typedef struct t_philo
{
	pthread_mutex_t	*mforks;
	pthread_mutex_t	incr;
	pthread_mutex_t	incr2;
	pthread_mutex_t	write;
	pthread_mutex_t	clean;
	pthread_mutex_t	watcher;
	pthread_t		*phlilo;
	pthread_t		*waiter;
	long long		start;
	int				n_ph;
	int				time_to_sleep;
	int				time_to_eat;
	int				to_die;
	int				me;
	int				much_to_eat;
	t_data			*data;
	int				n;
	int				ac;
	int				nn;
}	t_philo;

void		print_out(t_data *p, char *str);
long long	g_time(void);
t_philo		*philo_init(t_philo *p, int ac, char **av, int i);
long long	g_time(void);
void		uusleep(long long i);
int			ft_atoi(char *str);
void		*watcher(t_philo *p);
int			waiter(t_philo	*p);
void		the_free(t_philo *p);
int			checkerrrrr(int ac, t_philo *p);
t_philo		*atoi_init(t_philo *p, char **av, int ac);
int			mutex_locker(t_data *p, int i);

#endif