/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:42:24 by zwalad            #+#    #+#             */
/*   Updated: 2022/04/25 17:12:52 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo_bonus.h"

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
		p->mo_ea = 1;
		pthread_mutex_lock(p->l_fork);
		print_out(p, "is taking a fork");
		print_out(p, "is eating");
		p->l_ea = g_time() - p->philo->start;
		uusleep(p->philo, p->philo->time_to_eat);
		p->mu_ea--;
		p->mo_ea = 0;
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
		if (p->philo->n != 0 && p->go_away != 0)
		{
			print_out(p, "is sleeping");
			uusleep(p->philo, p->philo->time_to_sleep);
			print_out(p, "is thinking");
		}
	}
}

void	*philo_routine(void *d)
{
	int		i;
	t_data	*p;

	p = (t_data *)d;
	i = 0;
	if (p->id % 2)
		usleep(100);
	while (p->philo->n)
	{
		eat_n_sleep(p);
		if (p->l_fork == p->r_fork)
			return (NULL);
	}
	return (NULL);
}

void	watcher(t_philo *p)
{
	int			i;
	long long	tmp;

	while (p->n)
	{
		i = 0;
		while (i < p->n_ph)
		{
			pthread_mutex_lock(&p->watcher);
			tmp = g_time() - p->start;
			pthread_mutex_unlock(&p->watcher);
			if (tmp - p->data[i].l_ea >= p->to_die && p->data[i].mo_ea != 1)
			{
				pthread_mutex_lock(&p->write);
				printf("%lld ms %d died\n", g_time() - p->start, p->data[i].id);
				p->n = 0;
				break ;
			}
			i++;
		}	
	}
}

int	main(int ac, char *av[])
{
	t_philo	p;
	int		i;

	p = *atoi_unit(&p, av);
	if (checkerrrrr(ac, &p))
		return (0);
	p = *philo_unit(&p, ac, av);
	i = 0;
	p.start = g_time();
	while (i < p.n_ph && p.n != 0)
	{
		pthread_create(p.phlilo + i, NULL, &philo_routine, &p.data[i]);
		i++;
	}
	if (ac == 6)
		pthread_create(p.waiter, NULL, &waiter, &p);
	watcher(&p);
	i = 0;
	while (i < p.n_ph)
		pthread_join(p.phlilo[i++], NULL);
	the_free(&p);
	return (0);
}
