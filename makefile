# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvets <jvets@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 17:09:05 by jvets             #+#    #+#              #
#    Updated: 2023/11/17 23:15:01 by jvets            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol
LIBMLX	= ./MLX42
HEADERS	= -I $(LIBMLX)/include
FILES	= main.c
SRCS	= $(addprefix sources/, $(FILES))
OBJS	= $(SRCS:.c=.o)
FLAGS	= -Wall -Wextra -Werror -g3
LFLAGS	= -Lprintf -lftprintf -Llibft -lft

all: libmlx $(NAME)

libmlx:
	@cmake -DDEBUG=1 $(LIBMLX) -B $(LIBMLX)/build 1> /dev/null && make -C $(LIBMLX)/build -j4 1> /dev/null

%.o:%.c
	cc $(CFLAGS) -c $< -o $@  $(HEADERS)

$(NAME): $(OBJS)
	cc $(FLAGS) -o $(NAME) $(OBJS) $(LFLAGS) $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(HEADERS)

clean:
	rm -f $(OBJS)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx
