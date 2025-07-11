NAME = philo

SRC = ft_strjoin.c init.c monitoring.c philosophers.c  simulation.c ft_split.c parsing.c utils.c
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3
CC = cc 

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) 	

%.o : %.c  philosophers.h
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

git :	fclean
		git add .
		git commit -m "philo"
		git push
