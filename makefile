

main: main.o
	g++ -std=c++11 -g -o main main.o -framework sfml-graphics -framework sfml-audio -framework sfml-window -framework sfml-system -framework SFML
	
main.o: 
	g++ -std=c++11 main.cpp -c $(INC)



# Commands
clean:
	rm main.o
	rm main




