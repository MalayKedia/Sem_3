CXX = g++
CXXFLAGS = -std=c++20

TARGET = trie
SOURCES = trie.cpp kmp.cpp main.cpp

all: $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

test:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	./$(TARGET) < inputs/input0.txt > output0.txt
	./$(TARGET) < inputs/input1.txt > output1.txt
	./$(TARGET) < inputs/input2.txt > output2.txt
	./$(TARGET) < inputs/input3.txt > output3.txt
	./$(TARGET) < inputs/input4.txt > output4.txt
	diff outputs/output0.txt output0.txt
	diff outputs/output1.txt output1.txt
	diff outputs/output2.txt output2.txt
	diff outputs/output3.txt output3.txt
	diff outputs/output4.txt output4.txt

clean:
	rm -f $(TARGET) output*.txt