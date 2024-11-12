# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aubertra <aubertra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 08:40:05 by aubertra          #+#    #+#              #
#    Updated: 2024/11/12 17:10:16 by aubertra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc -ggdb
FLAGS = -Wall -Wextra -Werror -g3

# Target executable
NAME = pipex

# Source and object files
SRCS =  main.c\
		parsing.c\
		processes.c\
		handle_cmd.c\
		handle_errors.c\

OBJS = $(addprefix objs/,$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

# Default rule
all: $(NAME)

# Link target executable
$(NAME): $(OBJS)
	make -C libft/
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) libft/libft.a

# Rule for object files
objs/%.o: srcs/%.c | objs
	$(CC) $(FLAGS) -MMD -c $< -o $@ -I includes/ -I/usr/include

# Create objs directory if it doesn’t exist
objs:
	@mkdir -p objs

# Clean up object files and dependencies
clean:
	make -C libft/ clean
	rm -rf objs/

# Clean up everything
fclean: clean
	make -C libft/ fclean
	rm -f $(NAME)

# Rebuild all
re: fclean all

# Include dependencies
-include $(DEPS)

.PHONY: all clean fclean re

