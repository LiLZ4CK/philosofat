/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:19:56 by zwalad            #+#    #+#             */
/*   Updated: 2022/04/25 17:00:56 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	signe(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	int		j;
	long	n;
	long	c;

	i = 0;
	j = 1;
	n = 0;
	c = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	j = signe(str[i]);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + str[i] - '0';
		if (n < c && j == -1)
			return (0);
		if (n < c)
			return (-1);
		c = n;
		i++;
	}
	return (j * n);
}

void	uusleep(t_philo *p, long long i)
{
	long long	t;

	t = g_time();
	while (p->n && i > g_time() - t)
	{
		usleep(77);
	}	
}

void	print_out(t_data *p, char *str)
{
	if (p->philo->n == 0)
		return ;
	pthread_mutex_lock(&p->philo->write);
	printf("%lld ms %d %s\n", g_time() - p->philo->start, p->id, str);
	pthread_mutex_unlock(&p->philo->write);
}

t_philo	*philo_unit(t_philo *p, int ac, char **av)
{
	int	i;

	i = 0;
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
	pthread_mutex_init(&p->clean, NULL);
	pthread_mutex_init(&p->watcher, NULL);
	return (p);
}
