# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/10 08:23:40 by achauvea          #+#    #+#              #
#    Updated: 2017/01/07 23:38:39 by vdarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAGS = -Wall -Wextra -Werror
LIBDIR = ./libft/
SRCDIR = ./src/
INCDIR = ./include/

SRC = main.c display.c elem.c error.c ls_core.c print.c recursion.c \
			size.c sort.c sort_ft.c time.c util.c

SRCS = $(addprefix $(SRCDIR), $(SRC))

all: $(NAME)

$(NAME):
	@make -C $(LIBDIR)
	@echo "libft - Compilation Done"	
	@gcc $(FLAGS) $(SRCS) -I$(INCDIR) -o $(NAME) -L $(LIBDIR) -l ft -g
	@echo "ft_ls - Compilation Done"

clean:
	@make clean -C $(LIBDIR)
	@echo "libft - Clean Done"
	@echo "ft_ls - Clean Done"

fclean: clean
	@make fclean -C $(LIBDIR)
	@rm -rf $(NAME)
	@echo "ft_ls - Fclean Done"

re: fclean all

.PHONY: $(NAME) $(clean) $(fclean) $(re)
