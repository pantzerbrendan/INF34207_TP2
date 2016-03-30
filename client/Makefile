
RM			=	rm -vf
CXX			=	g++
GXX			=	g++ -g

LOCAL_INC	=	./include
COMMON_INC	=	../common/include

LOCAL_SRC	=	./source
COMMON_SRC	=	../common/source

NAME		=	INF34207TP1_client
DEBUG		=	INF34207TP1_client_debug

## Release
SRC			=	$(LOCAL_SRC)/main.cpp \
				$(COMMON_SRC)/Parameters.cpp \
				$(COMMON_SRC)/Environment.cpp \

OBJS		=	$(SRC:.cpp=.o)
## !Release

## Debug
D_SRC		=	$(SRC)

D_OBJS		=	$(D_SRC:.cpp=_debug.o)
## !Debug

CXXFLAGS	+=	-W -Wall -Wextra
CXXFLAGS	+=	-std=c++11 -O3
LDFLAGS		+=	-I$(LOCAL_INC) -I$(COMMON_INC)


%.o : 			%.cpp
				$(CXX) $(LDFLAGS) -c -o $@ $<

%_debug.o : 	%.cpp
				$(GXX) $(LDFLAGS) -c -o $@ $<

$(NAME):		CXXFLAGS += -Werror $(LDFLAGS)
$(NAME):		$(OBJS)
				$(CXX) $(OBJS) -o $(NAME)

$(DEBUG):		$(D_OBJS)
				$(GXX) $(D_OBJS) -o $(DEBUG)

all:			$(NAME)

debug:			CXXFLAGS += -DDEBUG=1 $(LDFLAGS)
debug:			$(DEBUG)

clean:
				@$(RM) $(OBJS)
				@$(RM) $(D_OBJS)

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) $(DEBUG)

re:				fclean all
re_debug:		fclean debug

.PHONY:			clean fclean all re debug
