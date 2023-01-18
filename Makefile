# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeluiz4 <jeffluiz97@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/27 10:29:53 by jeluiz4           #+#    #+#              #
#    Updated: 2023/01/17 22:52:09 by jeluiz4          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c \
		signal.c \
		init.c \
		heredoc.c \
		exit.c \
		pwd.c \
		echo.c \
		exec.c \
		env.c \
		env_utils.c \
		cd.c \
		free.c \
		lexer.c \
		expand.c \
		expand_utils.c \
		pipes.c \
		pipes_utils.c \
		parse_utils.c \
		parse.c \
		export.c \
		unset.c \
		clean_export_unset.c

FLAGS = -Wall -Wextra -Werror -g

#Criei Essa Flags_Sa pra quando precisar usar o sanitize mudar so botando um _SA
FLAGS_SA = -Wall -Wextra -Werror -g -fsanitize=address

RM = rm -f

NAME = minishell

LIBD = "libft/"

LIBA = "libft/libft.a"

LREADLINE = -lreadline


RIBA = -I /Users/jeluiz4/.brew/Cellar/readline/8.2.1/include

HIBA = -L /Users/jeluiz4/.brew/Cellar/readline/8.2.1/lib

CC = cc

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
	@printf "\e[1;94m=======================\e[0m\n"
	@printf "Waves in the ocean\n"
	@printf "\e[1;32m=======================\n"
	@cd $(LIBD) && make
	@$(CC) $(FLAGS) $(RIBA) -c $(SRCS)
	@$(CC) $(OBJS) $(FLAGS_SA) $(LREADLINE) $(LIBA) -o $(NAME) $(HIBA) $(RIBA)
	@printf "\e[1;32m=======================\e[0m\n"
	@printf "\e[1;93mThe shell is ready\e[0m\n"
	@printf "\e[1;94m=======================\e[0m\n"

clean:
	@echo 'clean rule'
	@cd $(LIBD) && make clean
	@$(RM) $(OBJS)

fclean:
	@echo 'fclean rule'
	@cd $(LIBD) && make fclean
	@$(RM) $(OBJS) $(NAME)

re: fclean all
