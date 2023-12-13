# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvets <jvets@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 17:09:05 by jvets             #+#    #+#              #
#    Updated: 2023/12/12 21:18:45 by jvets            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol
LIBMLX	=	./MLX42
HEADERS	=	-I $(LIBMLX)/include
FILES	=	main.c math_utils.c events.c
SRCS	=	$(addprefix sources/, $(FILES))
OBJS	=	$(SRCS:.c=.o)
FLAGS	=	-Wall -Wextra -Werror -g3
LFLAGS	=	-Lprintf -lftprintf -Llibft -lft

all: printf libft libmlx $(NAME)

libmlx:
	@cmake -DDEBUG=1 $(LIBMLX) -B $(LIBMLX)/build 1> /dev/null && make -C $(LIBMLX)/build -j4 1> /dev/null

%.o:%.c
	cc $(CFLAGS) -c $< -o $@  $(HEADERS)

$(NAME): $(OBJS)
	cc $(FLAGS) -o $(NAME) $(OBJS) $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LFLAGS) $(HEADERS)

libft:
	make -C ./libft --no-print-directory

printf:
	make -C ./printf --no-print-directory

clean:
	make clean -C ./libft
	make clean -C ./printf
	rm -f $(OBJS)
	rm -rf $(LIBMLX)/build

fclean: clean
	make fclean -C ./libft
	make fclean -C ./printf
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx printf libft
