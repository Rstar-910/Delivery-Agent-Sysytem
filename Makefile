CXX = g++

CXXFLAGS = -Wall -std=c++11 -I Source

TARGET = devilery_agent_system

OBJ = Source/main.o Source/customer.o Source/courierservice.o Source/admin.o

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

main.o: Source/main.cpp Source/customer.h Source/courierservice.h Source/admin.h
	$(CXX) $(CXXFLAGS) -c Source/main.cpp

customer.o: Source/customer.cpp Source/customer.h
	$(CXX) $(CXXFLAGS) -c Source/customer.cpp

courierservice.o: Source/courierservice.cpp Source/courierservice.h
	$(CXX) $(CXXFLAGS) -c Source/courierservice.cpp

admin.o: Source/admin.cpp Source/admin.h
	$(CXX) $(CXXFLAGS) -c Source/admin.cpp

clean: 
	del $(TARGET) $(OBJ)
