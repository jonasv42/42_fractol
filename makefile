# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvets <jvets@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 17:09:05 by jvets             #+#    #+#              #
#    Updated: 2023/11/09 19:32:25 by jvets            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol
FILES	= main.c
SRCS	= $(addprefix sources/, $(FILES))
OBJS	= $(SRCS:.c=.o)
FLAGS	= -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) -o $(NAME) $(OBJS) -lmlx -lX11 -lXext

%.o:%.c
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
