#include <iomanip>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "..\include\menus.h"
#include "..\include\constants.h"

//MAIN MENU
void MainMenu::printMenu(void) const {
	std::cout << std::endl;
	std::cout << std::setw(26) << "|\\/|  |||  |\\  |  |  |" << std::endl;
	std::cout << std::setw(26) << "|  |  |-   | \\ |  |  |" << std::endl;
	std::cout << std::setw(26) << "|  |  |||  |  \\|  |__|" << std::endl;
	std::cout << std::setfill('-');
	std::cout << std::setw(30) << "-" << std::endl;
	std::cout << std::setfill(' ');
	
	if (selectedOption == 1) {
		std::cout << ">>";
	}
	std::cout << std::setw(17) << "PLAY" << std::endl;
	if (selectedOption == 2) {
		std::cout << ">>";
	}
	std::cout << std::setw(18) << "QUIT" << std::endl;
}
void MainMenu::input(void) {
	if (_kbhit()) {
		char ch = getch();
		switch (ch) {
			case 'w':
				if (selectedOption == 1);
				else selectedOption--;
				break;
			case 's':
				if (selectedOption == 2);
				else selectedOption++;
				break;
			case char(32) :
				selectedOption = 0;
				break;
		}
	}
}
bool MainMenu::optSelected() const {
	if (selectedOption == 0) return true;
	else return false;
}
int MainMenu::opt() const {
	return this->selectedOption;
}

//GAME MENU
std::string gameMenu() {
	system("cls");
	std::string name;
	std::cout << std::endl;
	std::cout << std::setw(21) << " ENTER NAME " << std::endl;
	std::cout << std::setw(10) << " ";
	std::getline(std::cin, name, '\n');
	return name;
}