# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 14:36:58 by gmarquis          #+#    #+#              #
#    Updated: 2024/07/15 22:38:08 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c $\
pour_les_tests

SRCS_BUIL = builtin/cd.c $\
builtin/echo.c $\
builtin/export.c $\
builtin/pwd.c $\
builtin/unset.c

SRCS_EXEC = exec_srcs/env.c $\
exec_srcs/exec.c $\
exec_srcs/init_exec.c $\
exec_srcs/path.c $\
exec_srcs/start_exec.c $\
exec_srcs/utils.c


SRCS_PARS = pars_srcs/ex_env.c $\
pars_srcs/heredoc.c $\
pars_srcs/init_parse.c $\
pars_srcs/make_tmp.c $\
pars_srcs/out.c $\
pars_srcs/pour_les_tests.c $\
pars_srcs/sighandler.c $\
pars_srcs/surcouche.c $\
pars_srcs/token_utils.c $\
pars_srcs/tokenize.c

LIBFT_PATH = ../includes/libft/

NAME = minishell

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

OBJS_BUIL_DIR = objs/builtin/
OBJS_BUIL = $(notdir $(SRCS_BUIL:>C=.o))
OBJS_BUIL_PREF = $(addprefix $(OBJS_BUIL_DIR), $(OBJS_BUIL:.c=.o))
DEPENDENCIES_BUIL = $(patsubst %.o,%.d,$(OBJS_BUIL_PREF))

OBJS_EXEC_DIR = objs/exec/
OBJS_EXEC = $(notdir $(SRCS_EXEC:>C=.o))
OBJS_EXEC_PREF = $(addprefix $(OBJS_EXEC_DIR), $(OBJS_EXEC:.c=.o))
DEPENDENCIES_EXEC = $(patsubst %.o,%.d,$(OBJS_EXEC_PREF))

OBJS_PARS_DIR = objs/pars/
OBJS_PARS = $(notdir $(SRCS_PARS:>C=.o))
OBJS_PARS_PREF = $(addprefix $(OBJS_PARS_DIR), $(OBJS_PARS:.c=.o))
DEPENDENCIES_PARS = $(patsubst %.o,%.d,$(OBJS_PARS_PREF))

all : libft $(NAME)

libft :
	@make all -C $(LIBFT_PATH)

bonus : libft $(NAME)

$(OBJS_DIR)%.o : srcs/%.c 
	$(MK) -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJS_BUIL_DIR)%.o : srcs/builtin/%.c 
	$(MK) -p $(OBJS_BUIL_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJS_EXEC_DIR)%.o : srcs/exec_srcs/%.c
	$(MK) -p $(OBJS_EXEC_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJS_PARS_DIR)%.o : srcs/pars_srcs/%.c
	$(MK) -p $(OBJS_PARS_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME) : $(OBJS_PREF) $(OBJS_BUIL_PREF) $(OBJS_EXEC_PREF) $(OBJS_PARS_PREF) $(LIBFT_PATH)libft_bns.a 
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
