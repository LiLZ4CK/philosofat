/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:50:29 by zwalad            #+#    #+#             */
/*   Updated: 2022/05/24 04:11:56 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	the_free(t_philo *p)
{
	free(p->phlilo);
	free(p->mforks);
	free(p->data);
}

void	*waiter(t_philo *p)
{
	int		i;

	i = 0;
	while (i < p->n_ph)
	{
		pthread_mutex_lock(&p->incr2);
		if (p->data[i].mu_ea == 0)
		{
			p->data[i].go_away = 0;
			i++;
		}
		pthread_mutex_unlock(&p->incr2);
	}
	mutex_locker(p->data, 11);
	return (0);
}

int	checkerrrrr(int ac, t_philo *p)
{
	if (ac == 6 && p->me == 0)
		return (1);
	if (p->to_die <= 0 || p->time_to_eat <= 0 || p->time_to_sleep <= 0
		|| p->n_ph <= 0)
	{
		printf("error : wrong value of arguments\n");
		return (1);
	}
	return (0);
}

int	atoi_init(t_philo *p, char **av, int ac)
{
	int	i;

	i = 0;
	if (!(ac == 5 || ac == 6))
	{
		printf("error : wrong number of arguments\n");
		return (1);
	}
	p->ac = ac;
	p->n_ph = ft_atoi(av[1]);
	p->n = 1;
	p->to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		p->me = ft_atoi(av[5]);
	return (0);
}
