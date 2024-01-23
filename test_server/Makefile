NAME		=	server
SRCS		=	main.cpp  Server.cpp
OBJS		=	$(SRCS:.cpp=.o)
DEPS		=	$(SRCS:.cpp=.d)
CC			=	clang++
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror

.cpp.o			:
				$(CC) $(CFLAGS) -c $< -o $@ -MD

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) -o $(NAME) $(OBJS) 

clean		:
				rm -f log.txt
				$(RM) $(OBJS) $(DEPS)

fclean		:	clean
				$(RM) $(NAME)

re:			fclean all