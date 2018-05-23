firstTask: t3f1.o t3f2.o t3f3.o
	g++ t3f1.o t3f2.o t3f3.o -o firstTask.out
t3f1.o: t3f1.cpp 
	g++ -c t3f1.cpp
t3f2.o: t3f2.cpp
	g++ -c t3f2.cpp
t3f3.o: t3f3.cpp
	g++ -c t3f3.cpp
clean:
	rm -rf *.o firstTask.out
