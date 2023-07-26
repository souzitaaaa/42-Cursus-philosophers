# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 18:28:51 by dinoguei          #+#    #+#              #
#    Updated: 2023/07/13 15:16:17 by dinoguei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c \
	args.c \
	init.c \
	routine.c \
	utils.c \
	utils2.c \
	utils3.c \
	threads.c \
	sleep_think.c \
	eat.c

OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -pthread -Wall -Wextra -Werror -Wreturn-type -g -o3 #-fsanitize=thread -fno-omit-frame-pointer
AR = ar rc
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all