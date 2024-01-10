# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 19:37:41 by hel-haia          #+#    #+#              #
#    Updated: 2024/01/10 16:01:18 by hel-haia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = philo_bonus.c \
		ph_tools_bonus.c \
		parsing_bonus.c \
		initialise_bonus.c \
		to_die_thread_bonus.c

FLAGS = -Wall -Werror -Wextra #-g -fsanitize=thread

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		cc $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
		cc $(FLAGS) -c $< -o $@


clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all