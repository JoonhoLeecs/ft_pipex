CC = cc
CFLAGS = -Wall -Wextra -Werror
DIR_LIBFT = ./libft/
LIBFT = libft.a
SRC = pipex.c \
		pipex2.c
SRC_BONUS = pipex_bonus.c \
		pipex2_bonus.c \
		heredoc_bonus.c \
		getnextline/get_next_line.c \
		getnextline/get_next_line_utils.c \
		ft_strcmp_bonus.c
OBJECTS = $(SRC:.c=.o)
OBJECTS_BONUS = $(SRC_BONUS:.c=.o)
HEADER = pipex.h libft/libft.h
HEADER_BONUS = pipex_bonus.h libft/libft.h getnextline/get_next_line.h
NAME = pipex

.PHONY: all bonus clean fclean re

# all : $(NAME)
all : MAKE_ALL

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : MAKE_ALL

MAKE_ALL : $(LIBFT) $(OBJECTS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -L. -lft
			@touch MAKE_ALL
			@rm -f MAKE_BONUS

$(LIBFT) :
	$(MAKE) bonus -C $(DIR_LIBFT)
	cp $(DIR_LIBFT)/$(LIBFT) $(LIBFT)

bonus : MAKE_BONUS

MAKE_BONUS : $(LIBFT) $(OBJECTS_BONUS) $(HEADER_BONUS)
			cc $(CFLAGS) $(OBJECTS_BONUS) -o $(NAME) -L. -lft
			@touch MAKE_BONUS
			@rm -f MAKE_ALL

clean :
	$(MAKE) clean -C $(DIR_LIBFT)
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_BONUS)
	rm -f $(LIBFT)
	@rm -f MAKE_ALL MAKE_BONUS

fclean :
	$(MAKE) fclean -C $(DIR_LIBFT)
	$(MAKE) clean
	rm -f $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all
