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

class Display {
 public:
  static const byte lines = 0;
  static const byte topLine = 1;
  static const byte bottomLine = 2;
  static const byte leftTopBracket = 3;
  static const byte rightTopBracket = 4;
  static const byte leftBottomBracket = 5;
  static const byte rightBottomBracket = 6;
  static const byte delta = 7;
  static const byte brackets = 8;
  static const byte box = 9;

  void begin(byte lcd_columns, byte lcd_lines) {
    static const byte charTopLine[8] = {B11111, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
    static const byte charBottomLine[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B11111};
    static const byte charLeftTopBracket[8] = {B01111, B10000, B10000, B10000, B10000, B10000, B10000, B10000};
    static const byte charRightTopBracket[8] = {B11110, B00001, B00001, B00001, B00001, B00001, B00001, B00001};
    static const byte charLeftBottomBracket[8] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B01111};
    static const byte charRightBottomBracket[8] = {B00001, B00001, B00001, B00001, B00001, B00001, B00001, B11110};
    static const byte charDelta[8] = {B00000, B00100, B01010, B01010, B10001, B11111, B00000};

    LiquidCrystal.begin(lcd_columns, lcd_lines);
    LiquidCrystal.createChar(1, charTopLine);
    LiquidCrystal.createChar(2, charBottomLine);
    LiquidCrystal.createChar(3, charLeftTopBracket);
    LiquidCrystal.createChar(4, charRightTopBracket);
    LiquidCrystal.createChar(5, charLeftBottomBracket);
    LiquidCrystal.createChar(6, charRightBottomBracket);
    LiquidCrystal.createChar(7, charDelta);

    drawChar(box, 0, 0);
  }

  void setCursor(byte column, byte line) {
    LiquidCrystal.setCursor(column, line);
  }

  void print(String content, byte column, byte line) {
    drawChar(box, 0, 0);
    LiquidCrystal.setCursor(column, line);
    LiquidCrystal.print(content);
  }

  void printWait(String content, byte line, byte correction) {
    byte cursorPos = (abs(17 - content.length()) / 2) - correction;

    LiquidCrystal.setCursor(cursorPos, line);
    LiquidCrystal.print(content);

    if (line == 0) {
      for (byte backwardCursorPos = 1; backwardCursorPos < cursorPos; backwardCursorPos++) {
        drawChar(topLine, backwardCursorPos, line);
      }
    } else if (line == 1) {
      for (byte backwardCursorPos = 1; backwardCursorPos < cursorPos; backwardCursorPos++) {
        drawChar(bottomLine, backwardCursorPos, line);
      }
    }

    if (line == 0) {
      for (byte forwardCursorPos = (abs((17 - content.length()) / 2) - correction) + content.length(); forwardCursorPos < 15; forwardCursorPos++) {
        drawChar(topLine, forwardCursorPos, line);
      }
    } else if (line == 1) {
      for (byte forwardCursorPos = (abs((17 - content.length()) / 2) - correction) + content.length(); forwardCursorPos < 15; forwardCursorPos++) {
        drawChar(bottomLine, forwardCursorPos, line);
      }
    }

    delay(140 * content.length());
  }
  void printCentered(String content, byte line, byte correction) {
    byte cursorPos = (abs(17 - content.length()) / 2) - correction;

    LiquidCrystal.setCursor(cursorPos, line);
    LiquidCrystal.print(content);

    if (line == 0) {
      for (byte backwardCursorPos = 1; backwardCursorPos < cursorPos; backwardCursorPos++) {
        drawChar(topLine, backwardCursorPos, line);
      }
    } else if (line == 1) {
      for (byte backwardCursorPos = 1; backwardCursorPos < cursorPos; backwardCursorPos++) {
        drawChar(bottomLine, backwardCursorPos, line);
      }
    }

    if (line == 0) {
      for (byte forwardCursorPos = (abs((17 - content.length()) / 2) - correction) + content.length(); forwardCursorPos < 15; forwardCursorPos++) {
        drawChar(topLine, forwardCursorPos, line);
      }
    } else if (line == 1) {
      for (byte forwardCursorPos = (abs((17 - content.length()) / 2) - correction) + content.length(); forwardCursorPos < 15; forwardCursorPos++) {
        drawChar(bottomLine, forwardCursorPos, line);
      }
    }
  }

  void printDelta(String content, byte line, byte correction) {
    drawChar(box, 0, 0);
    LiquidCrystal.setCursor(((abs(17 - content.length()) / 2) - correction), line);
    LiquidCrystal.print(content);
    drawChar(delta, (((abs(17 - content.length()) / 2) - correction) - 1), line);
  }

  void clear() { drawChar(box, 0, 0); }

  void drawChar(byte character, byte column, byte line) {
    switch (character) {
      case brackets:
        LiquidCrystal.setCursor(0, 0);
        LiquidCrystal.write(leftTopBracket);

        LiquidCrystal.setCursor(15, 0);
        LiquidCrystal.write(rightTopBracket);

        LiquidCrystal.setCursor(0, 1);
        LiquidCrystal.write(leftBottomBracket);

        LiquidCrystal.setCursor(15, 1);
        LiquidCrystal.write(rightBottomBracket);
        break;
      case box:
        LiquidCrystal.setCursor(0, 0);
        LiquidCrystal.write(leftTopBracket);

        LiquidCrystal.setCursor(15, 0);
        LiquidCrystal.write(rightTopBracket);

        LiquidCrystal.setCursor(0, 1);
        LiquidCrystal.write(leftBottomBracket);

        LiquidCrystal.setCursor(15, 1);
        LiquidCrystal.write(rightBottomBracket);
        for (byte i = 1; i < 15; i++) {
          LiquidCrystal.setCursor(i, 0);
          LiquidCrystal.write(topLine);
          LiquidCrystal.setCursor(i, 1);
          LiquidCrystal.write(bottomLine);
        }
        break;
      default:
        LiquidCrystal.setCursor(column, line);
        LiquidCrystal.write(character);
        break;
    }
  }

  void drawLines(byte character) {
    switch (character) {
      case lines:
        for (byte i = 1; i < 15; i++) {
          LiquidCrystal.setCursor(i, 0);
          LiquidCrystal.write(topLine);
          LiquidCrystal.setCursor(i, 1);
          LiquidCrystal.write(bottomLine);
        }
        break;
      case topLine:
        for (byte i = 1; i < 15; i++) {
          LiquidCrystal.setCursor(i, 0);
          LiquidCrystal.write(topLine);
        }
        break;
      case bottomLine:
        for (byte i = 1; i < 15; i++) {
          LiquidCrystal.setCursor(i, 1);
          LiquidCrystal.write(bottomLine);
        }
        break;
    }
  }
} Display;

void setup() {
  Display.begin(16, 2);
}

void loop() {
  //
}
