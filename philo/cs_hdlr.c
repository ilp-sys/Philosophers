/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cs_hdlr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:39:13 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/13 17:03:32 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		set_table_flag(t_table *table, int stat)
{
	pthread_mutex_lock(table->flag_mut);
	table->flag = stat;
	pthread_mutex_unlock(table->flag_mut);
}

int			check_table_flag(t_table *table, int stat)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(table->flag_mut);
	if (table->flag == stat)
		ret = 1;
	pthread_mutex_unlock(table->flag_mut);
	return (ret);
}

void	add_ate_all(t_printer *printer)
{
	pthread_mutex_lock(printer->ate_all_mut);
	printer->ate_all++;
	pthread_mutex_unlock(printer->ate_all_mut);
}

int		check_ate_all(t_printer *printer, int num)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(printer->ate_all_mut);
	if (printer->ate_all == num)
		ret = 1;
	pthread_mutex_unlock(printer->ate_all_mut);
	return (ret);
}
