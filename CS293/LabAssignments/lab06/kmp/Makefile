CXX = g++
CXXFLAGS = -std=c++20

TARGET = kmp
SOURCES = kmp.cpp main.cpp

all: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

test:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	./$(TARGET) < inputs/input0.txt > output0.txt
	diff outputs/output0.txt output0.txt

clean:
	rm -f $(TARGET) output0.txt