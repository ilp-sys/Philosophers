/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:38:45 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/13 14:51:27 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	timer(int elapse)
{
	struct timeval	start;

	if (elapse)
	{
		gettimeofday(&start, NULL);
		while (1)
		{
			if ((int)get_elapsed(start) >= elapse)
				return ;
			usleep(elapse);
		}
	}
}

long long	get_elapsed(struct timeval since)
{
	long long		elapsed;
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	elapsed = (cur.tv_sec * 1000 + cur.tv_usec / 1000) \
				- (since.tv_sec * 1000 + since.tv_usec / 1000);
	return (elapsed);
}
