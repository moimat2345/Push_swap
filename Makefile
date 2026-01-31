# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matnusko <matnusko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 19:09:35 by matnusko          #+#    #+#              #
#    Updated: 2025/11/25 07:55:17 by matnusko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = push_swap




SRCS_PATH = src/

INC_PATH = include

OBJ_DIR = obj



SRCS =	\
	src/main.c \
	src/stack_init.c \
	src/utils.c \
	src/sort_small.c \
	src/operations_stack_a.c \
	src/operations_stack_b.c \
	src/input_validation.c \
	src/sort_radix.c \
	src/input_special.c \

		
		


PATH_LIBFT = include/my_lib

LIBFT = $(PATH_LIBFT)/my_lib.a


CC = cc

CFLAGS = -Wall -Wextra -Werror

INCLUDE = -I $(INC_PATH) -I $(PATH_LIBFT)



OBJS = $(patsubst $(SRCS_PATH)/%.c,$(OBJ_DIR)/%.o,$(SRCS))






########## SCRIPT
all: $(NAME)

$(NAME):  $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@

$(OBJ_DIR)/%.o: $(SRCS_PATH)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_PATH) -c $< -o $@ $(INCLUDE) 

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C $(PATH_LIBFT) re
	
	
clean:
	rm -rf $(OBJ_DIR)
	make -C $(PATH_LIBFT) clean
	
fclean: clean
	rm -f $(NAME)
	make -C $(PATH_LIBFT) fclean
	
re: fclean all

.PHONY: all clean fclean re

