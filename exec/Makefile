# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matran-d <matran-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 14:36:58 by gmarquis          #+#    #+#              #
#    Updated: 2024/05/16 14:59:01 by matran-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = sources/init.c $\
sources/main.c $\
sources/utils.c $\
sources/cd.c $\
sources/env.c $\
sources/pwd.c $\
sources/export.c $\
sources/unset.c

LIBFT_PATH = ../includes/libft/

NAME = exec

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
RM = rm -rf

OBJS_DIR = objs/
OBJS = $(notdir $(SRCS:>C=.o))
OBJS_PREF = $(addprefix $(OBJS_DIR), $(OBJS:.c=.o))
DEPENDENCIES = $(patsubst %.o,%.d,$(OBJS_PREF))

all : libft $(NAME)

libft :
	@make all -C $(LIBFT_PATH)

bonus : libft $(NAME)

$(OBJS_DIR)%.o : sources/%.c $(LIBFT_PATH)libft_bns.a 
	$(MK) -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS_PREF) $(LIBFT_PATH)libft_bns.a 
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_PATH)libft_bns.a

clean :
	@make clean -C $(LIBFT_PATH)
	$(RM) objs/

fclean : clean
	@make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re : fclean all

.PHONY : all bonus libft clean fclean re

-include $(DEPENDENCIES)
