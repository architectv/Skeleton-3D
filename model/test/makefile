test : test.o model.o
	g++ test.o model.o -o test.out
	./test.out

test.o : test.cpp
	g++ -c test.cpp

model.o : ../model.cpp
	g++ -c ../model.cpp

clean :
	rm *.o *.exe *.a *.out
