/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:50:29 by zwalad            #+#    #+#             */
/*   Updated: 2022/04/25 16:53:51 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	the_free(t_philo *p)
{
	free(p->phlilo);
	free(p->mforks);
	free(p->data);
}

void	*waiter(void *q)
{
	int		i;
	t_philo	*p;

	p = (t_philo *)q;
	i = 0;
	while (i < p->n_ph)
	{
		if (p->data[i].mu_ea == 0)
		{
			p->data[i].go_away = 0;
			i++;
		}
	}
	pthread_mutex_lock(&p->write);
	p->n = 0;
	return (NULL);
}

int	checkerrrrr(int ac, t_philo *p)
{
	int	i;

	i = 0;
	if (!(ac == 5 || ac == 6))
	{
		printf("error : wrong number of arguments\n");
		return (1);
	}
	if (p->to_die <= 0 || p->time_to_eat <= 0 || p->time_to_sleep <= 0
		|| p->n_ph <= 0)
	{
		printf("error : wrong value of arguments\n");
		return (1);
	}
	return (0);
}

t_philo	*atoi_unit(t_philo *p, char **av)
{
	int	i;

	i = 0;
	p->n_ph = ft_atoi(av[1]);
	p->n = 1;
	p->to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	return (p);
}
