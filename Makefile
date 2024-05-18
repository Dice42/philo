# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 14:12:50 by mohammoh          #+#    #+#              #
#    Updated: 2024/05/17 17:34:41 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c parsing.c utils.c init.c ft_atoi.c safe_handle.c simulation.c

OBJECTS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror  -fsanitize=address -g3 #-lpthread

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re