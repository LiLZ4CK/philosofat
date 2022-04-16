/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:42:24 by zwalad            #+#    #+#             */
/*   Updated: 2022/04/16 02:38:18 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include	"philo.h"
#include	"libft/libft.h"

long long timeInMilliseconds(void) 
{
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

void	uusleep(t_philo *p,long long i)
{
	long long usl;

	usl = timeInMilliseconds();
	while (p->n)
	{
		if (i <= timeInMilliseconds() - usl)
			break;
	}	
}


void	eat(t_data *p)
{
	pthread_mutex_lock(p->left_fork);
	print_out(p, "is taking a fork");
	if	(p->left_fork == p->right_fork)
		return;
	pthread_mutex_lock(p->right_fork);
	print_out(p, "is taking a fork");
	print_out(p, "is eating");
	p->mode_eat = 1;
	p->last_eat = timeInMilliseconds() - p->philo->start;
	uusleep(p->philo,p->philo->time_to_eat);
	p->much_eat++;
	p->mode_eat = 0;
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	p->much_eat++;
}

void	ft_sleep(t_data *p)
{
	print_out(p, "is sleeping");
	uusleep(p->philo, p->philo->time_to_sleep);
}
void	*philo_routine(void *d)
{
	int i;
	t_data *p;
	p = (t_data *)d;
	i = 0;
	if(p->id % 2)
		usleep(1500);
	while(p->philo->n)
	{
		if(!p->philo->n)
			break;
		eat(p);
		if (p->left_fork == p->right_fork)
			return (NULL);
		if(!p->philo->n)
			break;
		ft_sleep(p);
	}
	return (NULL);
}

void	watcher(t_philo *p)
{
	int	i;
	long long	tmp;

	while(p->n)
	{
		i = 0;
		while (i < p->num_philo)
		{
			tmp = timeInMilliseconds() - p->start;
			if(tmp - p->data[i].last_eat >= p->time_to_die && p->data[i].mode_eat != 1)
			{
				pthread_mutex_lock(&p->write);
				printf("%lld ms %d died\n", timeInMilliseconds() - p->start, p->data[i].id);
				pthread_mutex_unlock(&p->write);

				p->n = 0;
				break;
			}
			i++;
		}	
	}
}

int	main(int ac, char *av[])
{
	t_philo			p;
	int				k;
	int				i;
	int				j;
	struct timeval	time;
	int secs = 0;
	
	p.n = 1;

	i = 0;
	p.num_philo = ft_atoi(av[1]);
	/* if (p.num_philo == 1)
	{
		printf("%lld : 1 died\n", p.start);
		return (0);
	} */
	p.n = 1;
	p.time_to_die = ft_atoi(av[2]);
	p.time_to_eat = ft_atoi(av[3]);
	p.time_to_sleep  = ft_atoi(av[4]);
	p.phlilo = malloc(sizeof(pthread_t) * p.num_philo);
	p.mforks = malloc(sizeof(pthread_mutex_t) * p.num_philo);
	p.start = timeInMilliseconds();
	p.data = malloc(sizeof(t_data) * p.num_philo);
	p.data->last_eat = 0;
	p.data->much_eat = 0;
	p.data->mode_eat = 0;
	pthread_mutex_init(&p.write, NULL);
 	while (i < p.num_philo)
	{
		p.data[i].id = i + 1;
		p.data[i].philo = malloc(sizeof(t_philo));
		p.data[i].philo = &p;
		pthread_mutex_init(&p.mforks[i], NULL);
		i++;
	}
	i = 0;
	while(i < p.num_philo)
	{
		p.data[i].left_fork = &p.mforks[p.data[i].id % p.num_philo];
		p.data[i].right_fork = &p.mforks[(p.data[i].id - 1) % p.num_philo];
		i++;
	}
	i = 0;
	while(i < p.num_philo)
	{
		pthread_create(p.phlilo + i, NULL, &philo_routine, &p.data[i]);
		i++;
	}
	watcher(&p);
	i = 0;
	while(i < p.num_philo)
	{
		pthread_join(p.phlilo[i], NULL);
		i++;
	}
	return (0);
}