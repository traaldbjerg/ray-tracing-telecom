# makefile pour le code de télécom, à modifier avec les différents éléments qu'on y rajoutera

COPT = -O3 -Wall -march=native -fno-math-errno # options de compilation non standard mais code plus rapide

default: main

clean: 
	rm *.o 
	rm main

main: main.cpp wall.o vectormath.o reflections.o ray.o time.o progressbar.o transmissions.o addrcoef.o distance.o antenna.o
	g++ -g $(COPT) $^ -o $@

%.o: %.cpp
	g++ -g $(COPT) -c $< -o $@
