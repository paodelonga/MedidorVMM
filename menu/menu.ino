#include <LiquidCrystal.h>
LiquidCrystal LiquidCrystal(8, 9, 4, 5, 6, 7);

class KeypadButtons {
 private:
  int16_t buttonValue;
  byte pressedValue;
  byte toggledValue;

 public:
  static const byte Up = 1;
  static const byte Down = 2;
  static const byte Left = 3;
  static const byte Right = 4;
  static const byte Select = 5;
  static const byte NONE = 0;

  int Pressed() {
    buttonValue = analogRead(0);
    if (buttonValue > 0 and buttonValue < 50) {
      pressedValue = Right;
    } else if (buttonValue > 50 and buttonValue < 250) {
      pressedValue = Up;
    } else if (buttonValue > 250 and buttonValue < 450) {
      pressedValue = Down;
    } else if (buttonValue > 450 and buttonValue < 600) {
      pressedValue = Left;
    } else if (buttonValue > 600 and buttonValue < 900) {
      pressedValue = Select;
    } else if (buttonValue > 900) {
      pressedValue = NONE;
    }
    return pressedValue;
  }
  int Toggled() {
    buttonValue = analogRead(0);
    if (buttonValue > 0 and buttonValue < 50) {
      pressedValue = Right;
    } else if (buttonValue > 50 and buttonValue < 250) {
      pressedValue = Up;
    } else if (buttonValue > 250 and buttonValue < 450) {
      pressedValue = Down;
    } else if (buttonValue > 450 and buttonValue < 600) {
      pressedValue = Left;
    } else if (buttonValue > 600 and buttonValue < 900) {
      pressedValue = Select;
    }
    return toggledValue;
  }
} KeypadButtons;

class Menu {
 private:
  byte RootEntry = 0;
  byte PagesEntry = 1;
  byte currentEntry;

  class Root {
   private:
    byte minMenu = 0;
    byte maxMenu = 5;
    byte currentMenu;

   public:
    void display() {
      LiquidCrystal.setCursor(0, 0);
      LiquidCrystal.print((String) "Menu: " + currentMenu + " of " + maxMenu);
    }
    void next() {
      if (currentMenu < maxMenu) {
        currentMenu++;
      } else if (currentMenu == maxMenu) {
        currentMenu = minMenu;
      }
    }
    void previous() {
      if (currentMenu > minMenu) {
        currentMenu--;
      } else if (currentMenu == minMenu) {
        currentMenu = maxMenu;
      }
    }
  } Root;

  class Pages {
   private:
    byte minPage = 0;
    byte maxPage = 10;
    byte currentPage;

   public:
    void display() {
      LiquidCrystal.setCursor(0, 0);
      LiquidCrystal.print((String) "Page: " + currentPage + " of " + maxPage);
    }
    void next() {
      if (currentPage < maxPage) {
        currentPage++;
      } else if (currentPage == maxPage) {
        currentPage = minPage;
      }
    }
    void previous() {
      if (currentPage > minPage) {
        currentPage--;
      } else if (currentPage == minPage) {
        currentPage = maxPage;
      }
    }
  } Pages;

 public:
  void display() {
    if (currentEntry == RootEntry) {
      Root.display();
    } else if (currentEntry == PagesEntry) {
      Pages.display();
    }
  }
  void handler() {
    switch (KeypadButtons.Pressed()) {
      case KeypadButtons.Up:
        delay(250);
        Root.previous();
        currentEntry = RootEntry;
        display();
        break;
      case KeypadButtons.Down:
        delay(250);
        Root.next();
        currentEntry = RootEntry;
        display();
        break;
      case KeypadButtons.Left:
        delay(250);
        Pages.previous();
        currentEntry = PagesEntry;
        display();
        break;
      case KeypadButtons.Right:
        delay(250);
        Pages.next();
        currentEntry = PagesEntry;
        display();
        break;
    }
  }
} Menu;

void setup() {
  LiquidCrystal.begin(16, 2);
  Menu.display();
}

void loop() {
  Menu.handler();
}
