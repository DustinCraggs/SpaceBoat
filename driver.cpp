#include "Control.hpp"

#include <iostream>

int main(int argc, char **argv){
	std::cout << "Start" << std::endl;
	Control control;
	std::cout << "Control created" << std::endl;
	control.startGame();
	std::cout << "Game ended" << std::endl;
}