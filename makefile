CXX = g++
CXXFLAGS = -Wall

test: elevator.o mytest.cpp
	$(CXX) $(CXXFLAGS) elevator.o mytest.cpp -o test

driver: elevator.o driver.cpp
	$(CXX) $(CXXFLAGS) elevator.o driver.cpp -o driver

hist.o: elevator.h elevator.cpp
	$(CXX) $(CXXFLAGS) -c elevator.cpp

run:
	./test

run2:
	./driver
	
val:
	valgrind ./driver

clean:
	rm *~
	rm *.o