/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edessain <edessain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 18:04:21 by edessain          #+#    #+#             */
/*   Updated: 2021/02/25 13:39:06 by edessain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_three.h"

void	eating(t_data *three, int i)
{
	long int	time;

	time = get_time(three);
	three->last_eat = time;
	if (i)
	{
        three->iter++;
		ft_print_str(time, i + 1, ft_strdup(" is eating\n"));
		ft_sleep(three, three->time_to_eat);
	}
}

void	sleeping(t_data *three, int i)
{
	long int	time;

	time = get_time(three);
	if (three->statut == -1)
	{
		ft_print_str(time, i + 1, ft_strdup(" is sleeping\n"));
		ft_sleep(three, three->time_to_sleep);
	}
}

void	*check_time(void *arg)
{
	t_data			*three;
	long int		time;
	int				nb;

	three = *static_struct();
	nb = 0;
	arg = 0;
	pthread_detach(three->check_dead);
	while (three->statut == -1)
	{
		while (nb < three->number_of_philo)
		{
			time = get_time(three);
			if (three->time_to_die < time - three->last_eat)
			{
				three->statut = nb;
				ft_print_dead(time, three->statut + 1);
				return (NULL);
			}
			nb++;
		}
		nb = 0;
		usleep(4000);
	}
	return (NULL);
}

int 	*routine(t_data *three, int i)
{
	three->last_eat = get_time(three);
	while (three->statut == -1)
	{
		if (three->number_of_time != -1 && three->iter < three->number_of_time)
			break ;
		if (three->statut == -1)
			ft_print_think(get_time(three), i + 1);
		sem_wait(three->fork);
		sem_wait(three->fork);
		if (three->statut == -1)
			ft_print_fork(get_time(three), i + 1);
		eating(three, i);
		sem_post(three->fork);
		sem_post(three->fork);
		sleeping(three, i);
	}
    // ft_exit(three);
	return (0);
}