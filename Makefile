# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgraf <jgraf@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 08:26:08 by jgraf             #+#    #+#              #
#    Updated: 2024/12/05 16:51:16 by jgraf            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
NAME = philo

INIT_SRC = $(addprefix init/, init.c ft_atoi.c)
SIM_SRC = $(addprefix sim/, time_management.c start_sim.c simulation.c monitor.c)
UTILS_SRC = $(addprefix utils/, error_handle.c message.c thread_fail.c)
SRC = $(addprefix src/, main.c $(INIT_SRC) $(SIM_SRC) $(UTILS_SRC))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
