#*******************************************************************************#
#                                                                               #
#                                                          :::      ::::::::    #
#    Makefile                                            :+:      :+:    :+:    #
#                                                      +:+ +:+         +:+      #
#    by: acontass <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                  +#+#+#+#+#+   +#+            #
#    Created: 2014/03/30 08:35:11 by acontass           #+#    #+#              #
#    Updated: 2014/04/08 00:22:02 by acontass          ###   ########.fr        #
#                                                                               #
#*******************************************************************************#
NAME		=	capb_42

INCLUDES	=	-I includes

SRCPATH		=	srcs/

SRCS		=	capb_42.c

SRC			=	$(addprefix $(SRCPATH), $(SRCS))

OBJ			=	$(SRC:.c=.o)

CFLAGS		+=	-Wall -Wextra -Werror $(INCLUDES)

CC			=	gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re