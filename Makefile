CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
LDFLAGS = 

SRC_DIR = src
SOURCES = $(SRC_DIR)/ladder_main.cpp $(SRC_DIR)/ladder.cpp $(SRC_DIR)/dijkstras_main.cpp $(SRC_DIR)/dijkstras.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLES = ladder dijkstras

all: $(EXECUTABLES)

ladder: $(SRC_DIR)/ladder_main.o $(SRC_DIR)/ladder.o
	$(CXX) $(CXXFLAGS) -o ladder $(SRC_DIR)/ladder_main.o $(SRC_DIR)/ladder.o $(LDFLAGS)

dijkstras: $(SRC_DIR)/dijkstras_main.o $(SRC_DIR)/dijkstras.o
	$(CXX) $(CXXFLAGS) -o dijkstras $(SRC_DIR)/dijkstras_main.o $(SRC_DIR)/dijkstras.o $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/ladder.h $(SRC_DIR)/dijkstras.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

student_gtests: $(SRC_DIR)/student_gtests.cpp $(SRC_DIR)/ladder.cpp $(SRC_DIR)/dijkstras.cpp
	$(CXX) $(CXXFLAGS) -o student_gtests $(SRC_DIR)/student_gtests.cpp $(SRC_DIR)/ladder.cpp $(SRC_DIR)/dijkstras.cpp -lgtest -lgtest_main -pthread

clean:
	rm -f $(OBJECTS) $(EXECUTABLES) student_gtests
