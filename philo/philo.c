/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:42:24 by zwalad            #+#    #+#             */
/*   Updated: 2022/05/24 04:44:33 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

long long	g_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
}

void	eat_n_sleep(t_data *p)
{
	if (mutex_locker(p, 10))
	{
		pthread_mutex_lock(p->r_fork);
		print_out(p, "is taking a fork");
		if (p->l_fork == p->r_fork)
			return ;
		pthread_mutex_lock(p->l_fork);
		print_out(p, "is taking a fork");
		print_out(p, "is eating");
		mutex_locker(p, 1);
		mutex_locker(p, 9);
		uusleep(p->philo->time_to_eat);
		mutex_locker(p, 0);
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		print_out(p, "is sleeping");
		uusleep(p->philo->time_to_sleep);
		print_out(p, "is thinking");
	}
}

void	*philo_routine(void *d)
{
	t_data	*p;

	p = (t_data *)d;
	while (mutex_locker(p, 10))
	{
		eat_n_sleep(p);
		if (p->l_fork == p->r_fork)
			return (NULL);
	}
	return (NULL);
}

int	watcher(t_philo *p)
{
	long long	tmp;
	int			i;

	while (1)
	{
		i = 0;
		tmp = g_time() - p->start;
		if (mutex_locker(p->data, 10) == 0)
			return (0);
		while (i < p->n_ph)
		{	
			pthread_mutex_lock(&p->incr);
			if (tmp - p->data[i].l_ea >= p->to_die && p->data[i].mo_ea != 1)
			{
				pthread_mutex_lock(&p->write);
				printf("%lld ms %d died\n", g_time() - p->start, p->data[i].id);
				//p->n = 0;
				return (0);
			}
			pthread_mutex_unlock(&p->incr);
			i++;
		}
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_philo	*p;
	int		i;

	i = 0;
	p = malloc(sizeof(t_philo));
	if (atoi_init(p, av, ac) || checkerrrrr(ac, p))
		return (0);
	p = philo_init(p, ac, av, 0);
	p->start = g_time();
	while (i < p->n_ph)
	{
		pthread_create(p->phlilo + i, NULL, &philo_routine, &p->data[i]);
		usleep(222);
		i++;
	}
	if (ac == 6)
		pthread_create(p->waiter, NULL, (void *)&waiter, p);
	watcher(p);
	the_free(p);
	i = 0;
	while (i < p->n)
		pthread_detach(p->phlilo[i++]);
	return (0);
}
