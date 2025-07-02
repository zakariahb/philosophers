NAME = philo

SRC = ft_strjoin.c init.c monitoring.c philosophers.c  simulation.c ft_split.c parsing.c utils.c
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3
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

#./philo 200 800 2000000 200 

#meals eating shoud be accurate
#Recommendation: Yes, you should add a separate mutex for eating. 
#It’s important to have proper synchronization for this variable, 
#especially if the monitoring thread is frequently checking whether 
#the philosopher is eating, and if multiple threads might be reading and writing this status.
