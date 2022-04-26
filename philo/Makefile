NAME := ./philo

CC := @gcc

FLAGS := -Wall -Wextra -Werror

RM = @rm -f

SRC := philo.c \
		tools.c \
		tools2.c \


SRCO = $(subst .c,.o,$(SRC))


all: $(NAME)

$(NAME): $(SRCO)
	$(CC) $(SRC) -o $(NAME) $(FLAGS)

clean:
	$(RM) $(SRCO)

fclean: clean
	$(RM) $(NAME)

re: fclean all