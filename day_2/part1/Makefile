CXX=g++
CXXFLAGS = -c -g -std=c++11 -Werror -pedantic
IDIR=
LDFLAGS= 

solver: solver.o
	$(CXX) $(LDFLAGS) solver.o -o solver

solver.o : solver.cpp
	$(CXX) $(CXXFLAGS) solver.cpp

.PHONY : clean 
clean:
	rm -f solver *.o $(ODIR)/*.o *~ core $(INCDIR)/*~
