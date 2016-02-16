firstTask: t2f1.o t2f2.o t2f3.o
	g++ t2f1.o t2f2.o t2f3.o -o s5t2.out -lm
	rm -rf *.o
t2f1.o: t2f1.cpp 
	g++ -c t3f1.cpp -lm
t2f2.o: t2f2.cpp
	g++ -c t3f2.cpp -lm
t2f3.o: t2f3.cpp
	g++ -c t3f3.cpp -lm
clean:
	rm -rf *.o *.out
