CXX = g++

CXXFLAGS = -Wall -std=c++11 -I Source
LDFLAGS = -lsqlite3

TARGET = delivery_agent_system

OBJ = Source/main.o Source/customer.o Source/courierservice.o Source/admin.o Source/common.o

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

Source/main.o: Source/main.cpp Source/customer.h Source/courierservice.h Source/admin.h Source/common.h
	$(CXX) $(CXXFLAGS) -c Source/main.cpp -o Source/main.o

Source/customer.o: Source/customer.cpp Source/customer.h Source/common.h
	$(CXX) $(CXXFLAGS) -c Source/customer.cpp -o Source/customer.o

Source/courierservice.o: Source/courierservice.cpp Source/courierservice.h Source/common.h
	$(CXX) $(CXXFLAGS) -c Source/courierservice.cpp -o Source/courierservice.o

Source/admin.o: Source/admin.cpp Source/admin.h Source/common.h
	$(CXX) $(CXXFLAGS) -c Source/admin.cpp -o Source/admin.o

Source/common.o: Source/common.cpp Source/common.h
	$(CXX) $(CXXFLAGS) -c Source/common.cpp -o Source/common.o

clean: 
	rm -f $(TARGET) $(OBJ)

.PHONY: clean
