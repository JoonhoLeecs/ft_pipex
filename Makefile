CC = cc
CFLAGS = -Wall -Wextra -Werror
DIR_LIBFT = ./libft/
LIBFT = libft.a
SRC = pipex.c
# SRC_BONUS = pipex_bonus.c
OBJECTS = $(SRC:.c=.o)
# OBJECTS_BONUS = $(SRC_BONUS:.c=.o)
HEADER = pipex.h libft/libft.h
# HEADER_BONUS = pipex_bonus.h getnextline/get_next_line.h
NAME = pipex
# NAME_BONUS = pipex_bonus

.PHONY: all clean fclean re

all : $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(LIBFT) $(OBJECTS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -L. -lft

$(LIBFT) :
	$(MAKE) bonus -C $(DIR_LIBFT)
	cp $(DIR_LIBFT)/$(LIBFT) $(LIBFT)

# bonus : $(NAME_BONUS)

# $(NAME_BONUS) : $(LIBFT) $(OBJECTS_BONUS) $(HEADER_BONUS)
# 			$(CC) $(CFLAGS) $(OBJECTS_BONUS) -o $(NAME_BONUS) -L. -lft

clean :
	$(MAKE) clean -C $(DIR_LIBFT)
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_BONUS)
	rm -f $(LIBFT)
# rm -f make_all

fclean :
	$(MAKE) fclean -C $(DIR_LIBFT)
	$(MAKE) clean
	rm -f $(NAME)
# rm -f $(NAME_BONUS)

re :
	$(MAKE) fclean
	$(MAKE) all
