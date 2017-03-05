# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdelabro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/15 15:37:25 by gdelabro          #+#    #+#              #
#    Updated: 2017/02/14 18:50:21 by gdelabro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_PATH = src
SRC_NAME = main.c option.c info.c print.c print2.c search.c triage.c triage2.c

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:.c=.o)

CC = clang
CFLAGS = -g -Wall -Werror -Wextra

CPPFLAGS = -I includes -I libft/includes

LDFLAGS = -L libft
LDLIBS = -lft

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "Compilation of $(NAME):	\033[1;32mOK\033[m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "$(NAME): Removing Objs"

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)
	@echo "$(NAME): Removing $(NAME)"

re: fclean all

.PHONY: all clean fclean re
