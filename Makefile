FLAGS		= -fsanitize=address -Wall -Wextra -Werror
#-fsanitize=address
COMP		= gcc
NAME		= pipex
INCLUDE		= include/pipex.h
RM			= /bin/rm -f

FUNC		= src/pipex.c src/pipex_utils.c src/pipex_utils2.c src/pipex_utils3.c src/error.c
			
OBJ			= $(FUNC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(COMP)  -g $(FUNC) -o $(NAME)  $(FLAGS)

clean:
			$(RM) $(OBJ) $(OBJ_B)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all re clean fclean