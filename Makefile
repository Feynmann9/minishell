# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmarquis <gmarquis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/12 14:36:58 by gmarquis          #+#    #+#              #
#    Updated: 2024/05/14 17:26:44 by gmarquis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC_PATH = exec/
PARSE_PATH = parse/

all : exec parse

exec :
	@make all -C $(EXEC_PATH)

parse :
	@make all -C $(PARSE_PATH)

clean :
	@make clean -C $(EXEC_PATH)
	@make clean -C $(PARSE_PATH)
	$(RM) objs/

fclean : clean
	@make fclean -C $(EXEC_PATH)
	@make fclean -C $(PARSE_PATH)

re : fclean all

.PHONY : all exec parse clean fclean re
