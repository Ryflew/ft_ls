# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdarmaya <vdarmaya@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/09 03:19:57 by vdarmaya          #+#    #+#              #
#    Updated: 2016/12/12 21:32:41 by vdarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
FLAGS = -Wall -Wextra -Werror
LIBDIR = ./libft/
SRCDIR = ./srcs/
INCDIR = ./includes/

SRC = main.c \
		core.c \
		error.c \
		list.c \
		print.c \
		sort.c \
		treat.c \
		rmaj_opt.c \
		sort_two.c

SRCS = $(addprefix $(SRCDIR), $(SRC))

all: $(NAME)

$(NAME):
	@make -C $(LIBDIR)
	@gcc $(FLAGS) $(SRCS) -I$(INCDIR) -o $(NAME) -L $(LIBDIR) -l ft -g
	@echo "ft_ls - Compilation Done"

clean:
	@make clean -C $(LIBDIR)
	@echo "ft_ls - Clean Done"

fclean: clean
	@make fclean -C $(LIBDIR)
	@rm -rf $(NAME)
	@echo "ft_ls - Fclean Done"

re: fclean all

.PHONY: $(NAME) $(clean) $(fclean) $(re)
