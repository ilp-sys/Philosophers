# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/13 14:17:39 by jiwahn            #+#    #+#              #
#    Updated: 2022/11/13 16:38:50 by jiwahn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#
NAME			:= philo

CC 				:= cc
CFLAGS  		:= -Wall -Wextra -Werror

RM				:= rm
RMFLAGS 		:= -rf

SRCS 			:= main.c \
				   cs_hdlr.c \
				   printer.c \
				   routine.c \
				   timer.c \
				   utils.c \
				   set_table.c

OBJDIR			:= ./obj/
OBJNAME			:= $(SRCS:.c=.o)
OBJS			:= $(addprefix $(OBJDIR), $(OBJNAME))

.PHONY			: all
all				: $(NAME)

$(NAME) 		:  $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY			: clean
clean			:
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) $(OBJDIR)

.PHONY			: fclean
fclean			: clean
	$(RM) $(RMFLAGS) $(NAME)

.PHONY			: re
re				: fclean all

$(OBJDIR)%.o	: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
