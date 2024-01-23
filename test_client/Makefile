NAME		=	client
SRCS		=	main.cpp  Client.cpp
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
				$(RM) $(OBJS) $(DEPS)

fclean		:	clean
				$(RM) $(NAME)

re:			fclean all