# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/14 14:27:04 by aubertra          #+#    #+#              #
#    Updated: 2024/11/20 11:14:09 by aubertra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS= main.c\
	 handle_cmd.c\
	 handle_errors.c\
	 parsing.c\
	 processes.c\

SRCS_BONUS = main_bonus.c\
	 		handle_cmd_bonus.c\
	 		handle_errors_bonus.c\
	 		parsing_bonus.c\
	 		processes_bonus.c\
			free_close.c\

OBJ_DIR= OBJ

NAME= pipex

OBJS= $(SRCS:.c=.o)
OBJS_BONUS= $(SRCS_BONUS:.c=.o)

CC= cc

CFLAGS = -Wall -Werror -Wextra -g3 -I libft/

all: $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

bonus: $(addprefix srcs_bonus/,$(OBJS_BONUS))
		make -C libft
		$(CC) $(CFLAGS) $^ -L libft -l ft -o $(NAME)

$(NAME): $(addprefix srcs/,$(OBJS))
		make -C libft
		$(CC) $(CFLAGS) $^ -L libft -l ft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(addprefix srcs/,$(OBJS)) $(addprefix srcs_bonus/,$(OBJS_BONUS)) 
		make clean -C libft

fclean: clean
		rm -f $(NAME)
		make fclean -C libft

re:
	make fclean
	make all

.PHONY: fclean clean re bonus
