# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 14:12:50 by mohammoh          #+#    #+#              #
#    Updated: 2024/05/25 01:20:06 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = ./src/philo.c ./src/parsing.c ./src/safe_handle.c ./src/operations.c ./src/simulation.c ./src/free.c \
	 ./src/utils/utils.c ./src/init.c ./src/utils/ft_atoi.c ./src/utils/time.c ./src/utils/message.c \
	 ./src/death.c \

OBJECTS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror  -g3 -pthread 

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re