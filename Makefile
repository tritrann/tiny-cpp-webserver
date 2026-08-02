CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror
SRCS = src/main.cpp src/socket_utils.cpp src/client_socket.cpp src/web_server.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = server	

all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)