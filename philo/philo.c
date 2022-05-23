/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:42:24 by zwalad            #+#    #+#             */
/*   Updated: 2022/05/23 16:49:07 by zwalad           ###   ########.fr       */
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
	if (p->go_away != 0 && p->philo->n != 0)
	{
		pthread_mutex_lock(p->r_fork);
		print_out(p, "is taking a fork");
		if (p->l_fork == p->r_fork)
			return ;
		pthread_mutex_lock(p->l_fork);
		print_out(p, "is taking a fork");
		print_out(p, "is eating");
		mutex_locker(p, 1);
		uusleep(p->philo->time_to_eat);
		mutex_locker(p, 9);
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
	while (p->philo->n)
	{
		eat_n_sleep(p);
		if (p->l_fork == p->r_fork)
			return (NULL);
	}
	return (NULL);
}

void	*watcher(t_philo *p)
{
	long long	tmp;
	int			i;

	while (p->n)
	{
		i = 0;
		pthread_mutex_lock(&p->watcher);
		tmp = g_time() - p->start;
		pthread_mutex_unlock(&p->watcher);
		while (i < p->n_ph)
		{	
			pthread_mutex_lock(&p->incr);
			if (tmp - p->data[i].l_ea >= p->to_die && p->data[i].mo_ea != 1)
			{
				pthread_mutex_lock(&p->write);
				printf("%lld ms %d died\n", g_time() - p->start, p->data[i].id);
				p->n = 0;
				return (NULL);
			}
			pthread_mutex_unlock(&p->incr);
			i++;
		}
	}
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_philo	*p;
	int		i;

	p = malloc(sizeof(t_philo));
	p = atoi_init(p, av, ac);
	if (checkerrrrr(ac, p))
		return (0);
	p = philo_init(p, ac, av, 0);
	i = 0;
	p->start = g_time();
	while (i < p->n_ph)
	{
		pthread_create(p->phlilo + i, NULL, &philo_routine, &p->data[i]);
		usleep(222);
		i++;
	}
	if (ac == 6)
		return (waiter(p));
	watcher(p);
	the_free(p);
	return (0);
}
