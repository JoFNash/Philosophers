# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdursley <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/29 22:50:31 by pdursley          #+#    #+#              #
#    Updated: 2022/06/29 22:50:32 by pdursley         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo_bonus

LIST_INCL = ./src/

LIST_FUNC = main.c init.c philosopher.c units.c parse.c

HDR_INCL = ./include/

HDR = philosopher_bonus.h

HDR_PHILO = ${addprefix ${HDR_INCL}, ${HDR}}

CC = gcc

FLAGS = -Wall -Werror -Wextra -pthread

LIST = ${addprefix ${LIST_INCL}, ${LIST_FUNC}}

OBJ1 = $(LIST:.c=.o)

${NAME}:	${OBJ1}
				${CC} ${FLAGS} $^ -o $@

%.o : %.c ${HDR_PHILO} Makefile
	${CC} ${FLAGS} -c $< -o $@

all: ${NAME}

clean:
	rm -f ${OBJ1}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONNY : all bonus clean fclean re

