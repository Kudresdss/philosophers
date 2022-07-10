# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/30 13:49:23 by ymirna            #+#    #+#              #
#    Updated: 2022/07/10 17:11:41 by ymirna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus

PATH_M		=	bonus/

PATH_H		=	headers/

SRC_M		=	main_bonus.c philo_bonus.c philo_init_bonus.c philo_functs_bonus.c philo_routine_bonus.c \
				 ft_atoi_bonus.c

HEADER		=	philo_bonus.h

SRC_M_P		=	$(addprefix $(PATH_M), $(SRC_M))

HEADER_P	=	$(addprefix $(PATH_H), $(HEADER))

OBJS_M		=	$(SRC_M_P:%.c=%.o)

CC			=	cc

FLAGS		=	-Wall -Werror -Wextra -pthread

.PHONY:		all re clean fclean

%.o : %.c	$(HEADER_P)
			$(CC) $(FLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS_M) Makefile
			$(CC) $(FLAGS) $(OBJS_M) -o $(NAME)

clean:		
			rm -f $(OBJS_M)

fclean:		clean
			rm -f $(NAME)

re:			fclean all