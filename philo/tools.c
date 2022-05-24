/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:19:56 by zwalad            #+#    #+#             */
/*   Updated: 2022/05/24 02:40:35 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < (n - 1) && str1[i] == str2[i] && str1[i] && str2[i])
		i++;
	return (str1[i] - str2[i]);
}

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
		if ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
			return (0);
	}
	return (j * n);
}

void	uusleep(long long t_to_eat)
{
	long long	t;

	t = g_time();
	while (t_to_eat > g_time() - t)
	{
		usleep(300);
	}
}

void	print_out(t_data *p, char *str)
{
	pthread_mutex_lock(&p->philo->write);
	printf("%lld ms %d %s\n", g_time() - p->philo->start, p->id, str);
	pthread_mutex_unlock(&p->philo->write);
	if ((ft_strncmp(str, "is eating", 9) == 0) && p->mu_ea > 0)
	{
		pthread_mutex_lock(&p->philo->incr2);
		p->mu_ea--;
		pthread_mutex_unlock(&p->philo->incr2);
	}
}
