NAME := ./philo_bonus

CC := @gcc

FLAGS := -Wall -Wextra -Werror

RM = @rm -f

SRC := philo_bonus.c \
		tools_bonus.c \
		tools2_bonus.c \


SRCO = $(subst .c,.o,$(SRC))


bonus: $(NAME)

$(NAME): $(SRCO)
	$(CC) $(SRC) -o $(NAME) $(FLAGS)

clean:
	$(RM) $(SRCO)

fclean: clean
	$(RM) $(NAME)

re: fclean all