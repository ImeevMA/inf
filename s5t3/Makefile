firstTask: t3f1.o t3f2.o t3f3.o
	g++ t3f1.o t3f2.o t3f3.o -o s5t3.out -lm -lpthread
	rm -rf *.o
t3f1.o: t3f1.cpp 
	g++ -c t3f1.cpp -lm -lpthread
t3f2.o: t3f2.cpp
	g++ -c t3f2.cpp -lm -lpthread
t3f3.o: t3f3.cpp
	g++ -c t3f3.cpp -lm -lpthread
clean:
	rm -rf *.o *.out
