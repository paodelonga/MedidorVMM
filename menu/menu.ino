#include <LiquidCrystal.h>
LiquidCrystal LiquidCrystal(8, 9, 4, 5, 6, 7);

class KeypadButtons {
	private:
	int16_t buttonValue;
	byte pressedValue;
	byte toggledValue;

	public:
	static const byte UP = 1;
	static const byte DOWN = 2;
	static const byte LEFT = 3;
	static const byte RIGHT = 4;
	static const byte SELECT = 5;
	static const byte NONE = 0;

	int Pressed() {
		buttonValue = analogRead(0);
		if(buttonValue > 60 and buttonValue < 200) { pressedValue = UP; }
		else if(buttonValue > 200 and buttonValue < 400) { pressedValue = DOWN; }
		else if(buttonValue > 400 and buttonValue < 600) { pressedValue = LEFT; }
		else if(buttonValue > 0 and buttonValue < 60) { pressedValue = RIGHT; }
		else if(buttonValue > 600 and buttonValue < 800) { pressedValue = SELECT; }
		else if(buttonValue > 800) { pressedValue = NONE; }
		return pressedValue;
	}
	int Toggled() {
		buttonValue = analogRead(0);
		if(buttonValue > 60 and buttonValue < 200) { toggledValue = UP; }
		else if(buttonValue > 200 and buttonValue < 400) { toggledValue = DOWN; }
		else if(buttonValue > 400 and buttonValue < 600) { toggledValue = LEFT; }
		else if(buttonValue > 0 and buttonValue < 60) { toggledValue = RIGHT; }
		else if(buttonValue > 600 and buttonValue < 800) { toggledValue = SELECT; }
		return toggledValue;
	}
}
KeypadButtons;

class Menu {
	private:
	static const byte ROOT_ENTRY = 0;
	static const byte PAGE_ENTRY = 1;
	byte currentEntry;

	class Root {
		private:
		static const byte MIN_MENU = 0;
		static const byte MAX_MENU = 5;
		byte currentMenu;

		public:
		void display() {
			LiquidCrystal.setCursor(0, 0);
			LiquidCrystal.print((String)"Menu: "  + currentMenu + " of " + MAX_MENU);
		}
		void next() {
			if(currentMenu < MAX_MENU) { currentMenu++; }
			else if(currentMenu == MAX_MENU) { currentMenu = MIN_MENU; }
		}
		void previous() {
			if(currentMenu > MIN_MENU) { currentMenu--; }
			else if(currentMenu == MIN_MENU) { currentMenu = MAX_MENU; }
		}
	}
	Root;

	class Pages {
		private:
		static const byte MIN_PAGE = 0;
		static const byte MAX_PAGE = 10;
		byte currentPage;

		public:
		void display() {
			LiquidCrystal.setCursor(0, 0);
			LiquidCrystal.print((String)"Page: "  + currentPage + " of " + MAX_PAGE);
		}
		void next() {
			if(currentPage < MAX_PAGE) { currentPage++; }
			else if(currentPage == MAX_PAGE) { currentPage = MIN_PAGE; }
		}
		void previous() {
			if(currentPage > MIN_PAGE) { currentPage--; }
			else if(currentPage == MIN_PAGE) { currentPage = MAX_PAGE; }
		}
	}
	Pages;


	public:
	void display() {
		if(currentEntry == ROOT_ENTRY) { Root.display(); }
		else if(currentEntry == PAGE_ENTRY) { Pages.display(); }
	}
	void handler() {
		switch(KeypadButtons.Pressed()) {
			case KeypadButtons.UP:
				delay(250);
				Root.previous();
				currentEntry = ROOT_ENTRY;
				display();
				break;
			case KeypadButtons.DOWN:
				delay(250);
				Root.next();
				currentEntry = ROOT_ENTRY;
				display();
				break;
			case KeypadButtons.LEFT:
				delay(250);
				Pages.previous();
				currentEntry = PAGE_ENTRY;
				display();
				break;
			case KeypadButtons.RIGHT:
				delay(250);
				Pages.next();
				currentEntry = PAGE_ENTRY;
				display();
				break;
		}
	}
}
Menu;

void setup() {
	LiquidCrystal.begin(16, 2);
	Menu.display();
}

void loop() {
	Menu.handler();
}
