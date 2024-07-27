# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 14:36:58 by gmarquis          #+#    #+#              #
#    Updated: 2024/07/27 18:18:24 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c $\
srcs/pour_les_tests.c

SRCS_BUIL = srcs/builtin/cd.c $\
srcs/builtin/echo.c $\
srcs/builtin/export.c $\
srcs/builtin/pwd.c $\
srcs/builtin/unset.c $\
srcs/builtin/exit.c

SRCS_EXEC = srcs/exec_srcs/env.c $\
srcs/exec_srcs/exec.c $\
srcs/exec_srcs/start.c $\
srcs/exec_srcs/path.c $\
srcs/exec_srcs/init_exec.c $\
srcs/exec_srcs/utils.c


SRCS_PARS = srcs/pars_srcs/ex_env.c $\
srcs/pars_srcs/heredoc.c $\
srcs/pars_srcs/init_parse.c $\
srcs/pars_srcs/make_tmp.c $\
srcs/pars_srcs/out.c $\
srcs/pars_srcs/sighandler.c $\
srcs/pars_srcs/surcouche.c $\
srcs/pars_srcs/token_utils.c $\
srcs/pars_srcs/tokenize.c $\
srcs/pars_srcs/verif.c 

LIBFT_PATH = ../includes/libft/

NAME = minishell

MK = mkdir
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -g3
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
-include $(DEPENDENCIES_BUIL)
-include $(DEPENDENCIES_EXEC)
-include $(DEPENDENCIES_PARS)