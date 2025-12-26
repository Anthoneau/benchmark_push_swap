NAME	=	average
FLAGS	=	-Wall -Wextra -Werror
FILES	=	main.cpp Args.cpp Exec.cpp

all : ${NAME}

${NAME} : ${FILES}
	g++ ${FLAGS} ${FILES} -o ${NAME}

clean :
	rm -rf ${NAME}

fclean : clean

re : fclean all

.PHONY:	all clean fclean re