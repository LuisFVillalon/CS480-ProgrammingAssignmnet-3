CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14
TARGET = simarm
SRCS = simarm.cpp request_generator.cpp fcfs_scheduler.cpp sstf_scheduler.cpp scan_scheduler.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = constants.h disk_scheduler.h request_generator.h fcfs_scheduler.h sstf_scheduler.h scan_scheduler.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) *.o
