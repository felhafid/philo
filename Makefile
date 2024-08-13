NAME = philo
CC = cc 
CFLAGS = -Wall -Wextra -Werror 
SRC = main.c philo_utils.c philo_parser.c philos_routines.c \
	philos_routines1.c threads.c
OBJ = ${SRC:.c=.o}

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c philo.h
	@$(CC) $(CFLAGS) -c  -o $@ $<

clean :
	@rm -rf $(OBJ)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re