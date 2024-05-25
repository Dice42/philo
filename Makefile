# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 14:12:50 by mohammoh          #+#    #+#              #
#    Updated: 2024/05/25 13:11:49 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	src/death.c src/free.c src/get_fork.c src/init.c src/operations.c src/parsing.c \
		src/parsing_utils.c src/philo.c src/safe_handle.c src/simulation.c \
		src/simulation_utils.c src/utils/ft_atoi.c src/utils/message.c \
		src/utils/time.c src/utils/utils.c

OBJECTS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re