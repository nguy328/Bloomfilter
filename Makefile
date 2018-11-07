CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: BloomFilter.o

BloomFilter.o: BloomFilter.h BloomFilter.cpp 
	$(CXX) $(CPPFLAGS) -c BloomFilter.cpp -o BloomFilter.o