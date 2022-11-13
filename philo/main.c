/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:18:52 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/13 16:47:34 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_invalid_input(t_input *input, int argc)
{
	return (input->philo_num <= 0
		|| input->time_die <= 0
		|| input->time_eat <= 0
		|| input->time_sleep <= 0
		|| (argc == 6 && input->must_eat <= 0));
}

static void	get_input(t_input *input, int argc, char *argv[])
{
	input->philo_num = ft_atoi(argv[1]);
	input->time_die = ft_atoi(argv[2]);
	input->time_eat = ft_atoi(argv[3]);
	input->time_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		input->must_eat = -1;
	else
		input->must_eat = ft_atoi(argv[5]);
}

static void	clean_up(t_collector *clct)
{
	int	i;

	i = 0;
	while (i < clct->input->philo_num)
	{
		pthread_join(*clct->table->philo[i], NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_input		input;
	t_table		table;
	t_printer	printer;
	t_collector	clct;

	if (argc != 5 && argc != 6)
	{
		write(STDERR_FILENO, "Wrong Input!\n", 14);
		return (EXIT_FAILURE);
	}
	get_input(&input, argc, argv);
	if (is_invalid_input(&input, argc))
	{
		write(STDERR_FILENO, "Wrong Input!\n", 14);
		return (EXIT_FAILURE);
	}
	set_table(&clct, &printer, &table, &input);
	while (check_table_flag(&table, RUN))
		;
	clean_up(&clct);
	return (EXIT_SUCCESS);
}
