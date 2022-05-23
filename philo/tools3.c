/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 03:00:36 by zwalad            #+#    #+#             */
/*   Updated: 2022/05/23 04:48:47 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_init(t_philo *p, int ac, char **av, int i)
{
	p->phlilo = malloc(sizeof(pthread_t) * p->n_ph);
	p->waiter = malloc(sizeof(pthread_t) * 1);
	p->mforks = malloc(sizeof(pthread_mutex_t) * p->n_ph);
	p->data = malloc(sizeof(t_data) * p->n_ph);
	while (i < p->n_ph)
	{
		p->data[i].l_ea = 0;
		p->data[i].id = i + 1;
		p->data[i].philo = p;
		pthread_mutex_init(&p->mforks[i], NULL);
		p->data[i].r_fork = &p->mforks[i];
		p->data[i].l_fork = &p->mforks[(i + 1) % p->n_ph];
		p->data[i].go_away = 1;
		if (ac == 6)
			p->data[i].mu_ea = ft_atoi(av[5]);
		i++;
	}
	pthread_mutex_init(&p->write, NULL);
	pthread_mutex_init(&p->incr, NULL);
	pthread_mutex_init(&p->incr2, NULL);
	pthread_mutex_init(&p->clean, NULL);
	pthread_mutex_init(&p->watcher, NULL);
	return (p);
}

int	mutex_locker(t_data *p, int i)
{
	if (i == 9)
	{
		pthread_mutex_lock(&p->philo->incr);
		p->l_ea = g_time() - p->philo->start;
		pthread_mutex_unlock(&p->philo->incr);
	}
	if (i == 0)
	{
		pthread_mutex_lock(&p->philo->incr);
		p->mo_ea = 0;
		pthread_mutex_unlock(&p->philo->incr);
	}
	if (i == 1)
	{
		pthread_mutex_lock(&p->philo->incr);
		p->mo_ea = 1;
		pthread_mutex_unlock(&p->philo->incr);
	}
	return (1);
}
