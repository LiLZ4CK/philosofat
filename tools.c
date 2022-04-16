/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwalad <zwalad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 23:19:56 by zwalad            #+#    #+#             */
/*   Updated: 2022/04/15 23:44:11 by zwalad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_out(t_data *p, char *str)
{
    pthread_mutex_lock(&p->philo->write);
   printf("%lld ms %d %s\n", timeInMilliseconds() - p->philo->start, p->id, str);
   pthread_mutex_unlock(&p->philo->write);
}