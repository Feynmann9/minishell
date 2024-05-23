# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 14:36:58 by gmarquis          #+#    #+#              #
#    Updated: 2024/05/23 10:27:55 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c $\
srcs/pour_les_tests.c $\
srcs/sighandler.c $\
srcs/token_utils.c $\
srcs/tokenize.c

LIBFT_PATH = ../includes/libft/

NAME = parse

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
LDFLAGS = -L/usr/lib -lreadline
CPPFLAGS = -I/usr/include/readline
RM = rm -rf

OBJS_DIR = objs/
OBJS = $(notdir $(SRCS:>C=.o))
OBJS_PREF = $(addprefix $(OBJS_DIR), $(OBJS:.c=.o))
DEPENDENCIES = $(patsubst %.o,%.d,$(OBJS_PREF))

all : libft $(NAME)

libft :
	@make all -C $(LIBFT_PATH)

bonus : libft $(NAME)

$(OBJS_DIR)%.o : srcs/%.c $(LIBFT_PATH)libft_bns.a 
	$(MK) -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME) : $(OBJS_PREF) $(LIBFT_PATH)libft_bns.a 
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LIBFT_PATH)libft_bns.a

clean :
	@make clean -C $(LIBFT_PATH)
	$(RM) objs/

fclean : clean
	@make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re : fclean
	make all

.PHONY : all bonus libft clean fclean re

-include $(DEPENDENCIES)
