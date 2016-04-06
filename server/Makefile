
RM		=	rm -vf
CXX		=	g++

INCLUDE	=	./include
SOURCE	=	./source

NAME	=	server

SRC 	=	main.cpp \
			$(SOURCE)/Socket.cpp \
			$(SOURCE)/Client.cpp \
			$(SOURCE)/client_handle.cpp \
			$(SOURCE)/exceptions/exception.cpp \
			$(SOURCE)/exceptions/network_exception.cpp

OBJ		=	$(SRC:.cpp=.o)

LDFLAGS		+=	-I$(INCLUDE)
CXXFLAGS	+=	-W -Wall -Wextra
CXXFLAGS	+=	-O3 -std=c++11 $(LDFLAGS)

$(NAME):	$(OBJ)
			$(CXX) $(LDFLAGS) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
			@$(RM) $(OBJ)

fclean:		clean
			@$(RM) $(NAME)

re: 		fclean all

.PHONY:		clean fclean all re