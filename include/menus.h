#ifndef MENUS_H
#define MENUS_H

#include <string>

class MainMenu {
	private:
		int selectedOption;
	public:
		MainMenu(int opt = 1) : selectedOption(opt) {}
		void printMenu(void) const;
		void input(void);
		bool optSelected(void) const;
		int opt(void) const;
};

std::string gameMenu();

#endif //MENUS_H