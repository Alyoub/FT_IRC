CXX = c++

CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

SRCS = main.cpp client.cpp server.cpp

OBJS = $(SRCS:.cpp=.o)

EXEC = ircserv

all: $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

clean:
	rm -fr $(OBJS) $(EXEC) 

fclean: clean
	rm -fr $(EXEC)

re: fclean all