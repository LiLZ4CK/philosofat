#include	"philo.h"
#include	"libft/libft.h"

long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

void	philo_routine(t_philo *p)
{
	struct timeval	time;
	int				j;
	int				i;
	int				k;

	gettimeofday(&time, NULL);
	i = 0;
	k = timeInMilliseconds();
	while(1)
	{
		i = 0;
		while (i < p->num_philo)
		{
			if (p->forks[i] == '1' && p->forks[(i + 1) % p->num_philo] == '1')
			{
				pthread_mutex_lock(&p->mutex);
				printf("%d: %d has taken a fork               %d\n", k, p->i, time.tv_usec);
				printf("%d: %d is eating                      %d\n", k, p->i, time.tv_usec);
			 	printf("      ___p0____\n");
				printf("    / f%c      f%c\\   \n", p->forks[4], p->forks[0]);
				printf("p4 /              \\ p1\n");
				printf("  |  f%c       f%c  |\n", p->forks[3], p->forks[1]);
				printf("   \\              /\n");
				printf("p3  \\   %c       /p2\n", p->forks[2]);
				printf("       ---------\n");
				j = p->time_to_eat * 1000;
				usleep(j);
				pthread_mutex_unlock(&p->mutex);
			}
				pthread_mutex_lock(&p->mutex);
				printf("%d: %d is thinking\n", k, p->i);
				pthread_mutex_unlock(&p->mutex);

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

	i = 0;
	pthread_mutex_init(&p.mutex, NULL);
	gettimeofday(&time, NULL);
	p.forks = malloc(sizeof (char *) * p.num_philo);
	memset(p.forks, '1', p.num_philo);
	p.num_philo = ft_atoi(av[1]);
	p.time_to_die = ft_atoi(av[2]);
	p.time_to_eat = ft_atoi(av[3]);
	p.time_to_sleep  = ft_atoi(av[4]);
	p.phlilo = malloc(p.num_philo);
	while(i <= p.num_philo)
	{
		if (i == p.num_philo)
			i = 0;
		p.i = i;
		pthread_create(p.phlilo + i, NULL, (void *) &philo_routine, &p);
		usleep(100);
		i++;
	}
	i = 0;
	while(i < p.num_philo)
	{
		pthread_join(p.phlilo[i], NULL);
		i++;
	}
	pthread_mutex_unlock(&p.mutex);
	return (0);
}