/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:49:30 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/13 14:49:58 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_collector clct, int stat)
{
	const struct timeval	start_time = clct.start_time;
	const int				self = clct.self;

	pthread_mutex_lock(clct.printer->print_mut);
	if (stat == FORK)
		printf("%lld %d %s\n", get_elapsed(start_time), self, FORK_MSG);
	else if (stat == EAT)
		printf("%lld %d %s\n", get_elapsed(start_time), self, EAT_MSG);
	else if (stat == SLEEP)
		printf("%lld %d %s\n", get_elapsed(start_time), self, SLEEP_MSG);
	else if (stat == THINK)
		printf("%lld %d %s\n", get_elapsed(start_time), self, THINK_MSG);
	else
		printf("%lld %d %s\n", get_elapsed(start_time), self, DEAD_MSG);
	if (stat != DEAD)
		pthread_mutex_unlock(clct.printer->print_mut);
}
