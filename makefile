# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvets <jvets@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 17:09:05 by jvets             #+#    #+#              #
#    Updated: 2023/11/09 21:19:12 by jvets            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol
FILES	= main.c
SRCS	= $(addprefix sources/, $(FILES))
OBJS	= $(SRCS:.c=.o)
FLAGS	= -Wall -Wextra -Werror -g3
LFLAGS	= -lmlx -lX11 -lXext -Lprintf -lftprintf -Llibft -lft

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) -o $(NAME) $(OBJS) $(LFLAGS)
#posso simplesmente incluir a biblioteca ou devo compilá-la com o makefile dela?
#posso excluir os outros arquivos da printf e manter somente o arquivo .a e .h?

%.o:%.c
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
