cad_prog:	ModelPart.o main.o
	g++ ModelPart.o main.o -o $@ 

ModelPart.o:	ModelPart.cpp ModelPart.h
	g++  -c $< -o $@ 

main.o:	main.cpp ModelPart.h 
	g++ -c $< -o $@ 

clean:
	rm -f cad_prog *.o core *~
