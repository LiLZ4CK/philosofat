/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:42:22 by zwalad            #+#    #+#             */
/*   Updated: 2022/04/16 01:58:30 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
#define	PHILO_H

# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<sys/time.h>
# include	"libft/libft.h"
# include	<pthread.h>
# include	<string.h>

typedef struct s_data
{
	int	last_eat;
	int	much_eat;
	int	mode_eat;
	int	id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	struct t_philo *philo;
} t_data;

typedef struct	t_philo
{
	pthread_mutex_t	*mforks;
	pthread_mutex_t	write;
	pthread_t		*phlilo;
	long long		*last_eat;
	long long		start;
	int				num_philo;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	t_data			*data;
	int				n;
	
}t_philo;


void    print_out(t_data *p, char *str);
long long timeInMilliseconds(void);

#endif