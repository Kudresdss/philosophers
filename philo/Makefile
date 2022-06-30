# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/30 13:49:23 by ymirna            #+#    #+#              #
#    Updated: 2022/06/22 17:53:02 by ymirna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

PATH_M		=	mandatory/

PATH_B		=	bonus/

PATH_H		=	headers/

SRC_M		=	main.c ft_atoi.c philo.c

SRC_B		= 	main_bonus.c

HEADER		=	philo.h

SRC_M_P		=	$(addprefix $(PATH_M), $(SRC_M))

SRC_B_P		=	$(addprefix $(PATH_B), $(SRC_B))

HEADER_P	=	$(addprefix $(PATH_H), $(HEADER))

OBJS_M		=	$(SRC_M_P:%.c=%.o)

OBJS_B		=	$(SRC_B_P:%.c=%.o)

CC			=	cc

FLAGS		=	-Wall -Werror -Wextra -pthread

.PHONY:		all bonus re clean fclean

%.o : %.c	$(HEADER_P)
			$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS_M) Makefile
			$(CC) $(FLAGS) $(OBJS_M) -o $(NAME)

bonus:		
			@make OBJS_M="$(OBJS_B)" all

clean:		
			rm -f $(OBJS_M)
			rm -f $(OBJS_B)

fclean:		clean
			rm -f $(NAME)

re:			fclean all