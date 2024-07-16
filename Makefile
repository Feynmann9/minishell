# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 14:36:58 by gmarquis          #+#    #+#              #
#    Updated: 2024/07/16 13:54:35 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC_PATH = exec/
PARSE_PATH = parse/
MINISHELL_PATH = merge/

all : exec parse minishell

exec :
	@make all -C $(EXEC_PATH)

parse :
	@make all -C $(PARSE_PATH)

minishell :
	@make all -C $(MINISHELL_PATH)

clean :
	@make clean -C $(EXEC_PATH)
	@make clean -C $(PARSE_PATH)
	@make clean -C $(MINISHELL_PATH)
	$(RM) objs/

fclean : clean
	@make fclean -C $(EXEC_PATH)
	@make fclean -C $(PARSE_PATH)
	@make fclean -C $(MINISHELL_PATH)

re : fclean all

.PHONY : all exec parse minishell clean fclean re
