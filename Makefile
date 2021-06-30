# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/01 19:28:45 by acaryn            #+#    #+#              #
#    Updated: 2021/02/19 04:29:49 by acaryn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src/
SRC_PARSDIR = $(SRCDIR)parse/
SRCS =	$(addprefix $(SRCDIR), \
		main.c \
		ft_parse.c \
		get_next_line.c \
		ft_envp.c \
		ft_envp_utils.c \
		ft_envp_others.c \
		ft_cd.c \
		ft_pwd.c \
		ft_export_main.c \
		ft_export_additional.c \
		ft_unset.c \
		ft_echo.c \
		ft_error.c \
		ft_external_comand.c \
		ft_exit.c \
		ft_redirects.c \
		ft_utils.c \
		ft_multi_command.c \
		ft_valid_string.c \
		ft_free_struct.c \
		ft_sing_command.c )

SRCS_PARS =	$(addprefix $(SRC_PARSDIR), \
		ft_parse_main.c \
		ft_parse_utils.c \
		ft_parse_replace.c \
		ft_parse_replace_2.c \
		ft_parse_processing.c \
		ft_parse_redirects.c \
		ft_parse_redirects_2.c \
		ft_parse_1.c \
		ft_parse_cycle.c )

FILE_HEAD = includes/mini.h
HEAD =	includes \
		includes/libft
HEADERS = $(addprefix -I , $(HEAD))
FLAG_LIBFT = libft.a

all: $(NAME)

$(NAME): $(SRCS) $(FILE_HEAD)
	@$(MAKE) -C includes/libft
	mv includes/libft/libft.a ./
	gcc $(CFLAGS) $(SRCS) $(SRCS_PARS) $(HEADERS) $(FLAG_LIBFT) -o $(NAME)

clean:
	rm -rf includes/libft/obj

fclean: clean
	rm -rf $(NAME)
	rm -rf libft.a

re: fclean all

.PHONY: all clean fclean re