# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hel-haia <hel-haia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/27 19:37:41 by hel-haia          #+#    #+#              #
#    Updated: 2024/01/09 23:02:00 by hel-haia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c \
		parsing.c \
		ph_tools.c \
		initialise.c \
		to_die_thread.c

FLAGS = -Wall -Werror -Wextra

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