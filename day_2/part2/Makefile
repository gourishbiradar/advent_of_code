CXX=g++
CXXFLAGS = -c -g -std=c++11 -Werror -pedantic
IDIR= solver.h
LDFLAGS= 


driver: driver.o solver.o
	$(CXX) $(LDFLAGS) driver.o solver.o -o driver

solver.o : solver.cpp solver.h
	$(CXX) $(CXXFLAGS) solver.cpp

driver.o : driver.cpp solver.h
	$(CXX) $(CXXFLAGS) driver.cpp

.PHONY : clean 
clean:
	rm -f solver driver *.o $(ODIR)/*.o *~ core $(INCDIR)/*~
