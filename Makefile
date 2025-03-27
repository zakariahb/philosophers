NAME = philo

SRC = ft_atoi.c list.c ft_strjoin.c ft_split.c parsing.c philosophers.c 
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
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

git :
		git add .
		git commit -m "philo"
		git push