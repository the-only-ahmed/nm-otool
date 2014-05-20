# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/25 02:16:49 by jyim              #+#    #+#              #
#    Updated: 2014/04/27 22:45:16 by ael-kadh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_nm = ft_nm

NAME_O = ft_otool

SRC_nm = nm_64.c nm_main.c things.c get_sections.c new_thing.c offlist.c\
		 fat_ar.c swp_catch.c

SRC_O = ft_otool.c ot_print.c ot_check.c swp_catch.c offlist_tool.c fat_tool.c

OBJ_nm = $(SRC_nm:.c=.o)

OBJ_O = $(SRC_O:.c=.o)

FLAGS = -g3 -Wall -Wextra -Werror

all: $(NAME_nm) $(NAME_O)

$(NAME_nm): $(OBJ_nm)
	@make -C libft
	@cc $(OBJ_nm) -L libft -lft libft/printf/libftprintf.a -o $(NAME_nm)

$(NAME_O): $(OBJ_O)
	@cc $(OBJ_O) -L libft -lft libft/printf/libftprintf.a -o $(NAME_O)

%.o: %.c
	@cc $(FLAGS) -c -I libft/ -I libft/printf/includes $<

clean:
	@/bin/rm -f $(OBJ_nm)
	@/bin/rm -f $(OBJ_O)
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME_nm) 
	@/bin/rm -f $(NAME_O)
	@make -C libft/ fclean

re: fclean all
