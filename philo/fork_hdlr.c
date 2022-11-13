/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_hdlr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:48:03 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/13 18:49:15 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_fork_up(t_table *table, int pos, char *flag, int flag_op)
{
	pthread_mutex_lock(table->fork_mut[pos]);
	if (table->fork[pos] == AVAIL)
	{
		table->fork[pos] = TAKEN;
		*flag |= flag_op;
	}
	pthread_mutex_unlock(table->fork_mut[pos]);
}

void	put_fork_down(t_table *table, int pos, char *flag, int flag_op)
{
	pthread_mutex_lock(table->fork_mut[pos]);
	if (table->fork[pos] == TAKEN)
	{
		table->fork[pos] = AVAIL;
		*flag ^= flag_op;
	}
	pthread_mutex_unlock(table->fork_mut[pos]);
}
