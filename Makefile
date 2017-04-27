# définition des variables utilise pour la compilatio7
CXX= g++
SOURCE=fractal.cpp
EXEC= main
SUP=rm -rf
CXXFLAGS= -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core -DWITH_THREAD -lpthread -DNB_THREAD=16#-lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11 -lpthread 
all:	
	$(CXX) -Wall $(SOURCE) -o $(EXEC) $(CXXFLAGS)
	./main

mrproper:clean
	$(SUP) *.o
clean:
	 $(SUP) *.o



