/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:19:39 by jiwahn            #+#    #+#             */
/*   Updated: 2022/11/13 19:01:08 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define L_FORK		0x01
# define R_FORK		0x02

# define FORK_MSG	"has taken a fork"
# define EAT_MSG	"is eating"
# define SLEEP_MSG	"is sleeping"
# define THINK_MSG	"is thinking"
# define DEAD_MSG	"died"

enum	e_flag
{
	PAUSE = 0,
	RUN
};

enum	e_fork
{
	AVAIL = 0,
	TAKEN
};

enum	e_state
{
	DEAD = 0,
	SLEEP,
	THINK,
	EAT,
	FORK
};

typedef struct s_input
{
	int				philo_num;
	int				time_die;
	int				time_sleep;
	int				time_eat;
	int				must_eat;
}t_input;

typedef struct s_printer
{
	int				ate_all;
	int				*eat_cnt;
	struct timeval	start_time;
	struct timeval	**last_eat;
	pthread_mutex_t	*print_mut;
	pthread_mutex_t	*ate_all_mut;
}t_printer;

typedef struct s_table
{
	int				flag;
	char			*fork;
	pthread_t		**philo;
	pthread_mutex_t	*flag_mut;
	pthread_mutex_t	**fork_mut;
}t_table;

typedef struct s_collector
{
	int				self;
	t_input			*input;
	t_table			*table;
	t_printer		*printer;
}t_collector;

//main.c
int			main(int argc, char *argv[]);

//utils.c
int			ft_atoi(const char *str);

//set_table.c
void		set_table(t_collector *clct, t_printer *printer, \
		t_table *table, t_input *input);

//routine.c
void		*routine(void *arg);

//cs_hdlr.c
void		set_table_flag(t_table *table, int stat);
int			check_table_flag(t_table *table, int stat);
void		add_ate_all(t_printer *printer);
int			check_ate_all(t_printer *printer, int num);

//fork_hdlr.c
void		pick_fork_up(t_table *table, int pos, char *flag, int flag_op);
void		put_fork_down(t_table *table, int pos, char *flag, int flag_op);

//tiemr.c
void		timer(int elapse);
long long	get_elapsed(struct timeval since);

//printer.c
int			printer(t_collector *clct, int stat);

#endif
