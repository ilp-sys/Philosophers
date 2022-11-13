/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:57:59 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/13 17:01:08 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		set_table(
		t_collector *clct,
		t_printer *printer,
		t_table *table,
		t_input *input
		)
{
	int	i;
	
	//init clct
	clct->input = input;
	clct->table = table;
	clct->printer = printer;

	//init printer
	printer->ate_all = 0;
	printer->eat_cnt = (int *)malloc(sizeof(int) * input->philo_num);
	i = 0;
	while (i < input->philo_num)
		printer->eat_cnt[i++] = 0;
	printer->last_eat = (struct timeval **)malloc(sizeof(struct timeval) * input->philo_num);
	i = 0;
	while (i < input->philo_num)
		printer->last_eat[i++] = (struct timeval *)malloc(sizeof(struct timeval));
	printer->print_mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(printer->print_mut, NULL);
	printer->ate_all_mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(printer->ate_all_mut, NULL);

	//init table
	table->flag = PAUSE;
	table->fork = (char *)malloc(sizeof(char) * input->philo_num);
	memset(table->fork, AVAIL, input->philo_num);
	table->flag_mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->flag_mut, NULL);
	table->fork_mut = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * input->philo_num);
	i = 0;
	while (i < input->philo_num)
	{
		table->fork_mut[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(table->fork_mut[i++], NULL);
	}
	table->philo = (pthread_t **)malloc(sizeof(pthread_t *) * input->philo_num);
	i = 0;
	while (i < input->philo_num)
	{
		clct->self = i;
		table->philo[i] = (pthread_t *)malloc(sizeof(pthread_t));
		pthread_create(table->philo[i], NULL, routine, clct);
		timer(1);
		i++;
	}

	//set table flag and timeval
	gettimeofday(&printer->start_time, NULL);
	set_table_flag(table, RUN);
	i = 0;
	while (i < input->philo_num)
		gettimeofday(printer->last_eat[i++], NULL);
}
