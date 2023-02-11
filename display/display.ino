#include <LiquidCrystal.h>
LiquidCrystal LiquidCrystal(8, 9, 4, 5, 6, 7);

class Display {
	private:
	public:
	byte lines = 1;
	byte topLine = 1;
	byte bottomLine = 2;
	byte leftTopBracket = 3;
	byte rightTopBracket = 4;
	byte leftBottomBracket = 5;
	byte rightBottomBracket = 6;
	byte delta = 7;
	byte brackets = 8;
	byte box = 9;

	void begin(byte lcd_columns, byte lcd_lines) {
		LiquidCrystal.begin(lcd_columns, lcd_lines);

		byte charTopLine[8] = {B11111, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
		byte charBottomLine[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B11111};
		byte charLeftTopBracket[8] = {B01111, B10000, B10000, B10000, B10000, B10000, B10000, B10000};
		byte charRightTopBracket[8] = {B11110, B00001, B00001, B00001, B00001, B00001, B00001, B00001};
		byte charLeftBottomBracket[8] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B01111};
		byte charRightBottomBracket[8] = {B00001, B00001, B00001, B00001, B00001, B00001, B00001, B11110};
		byte charDelta[8] = {B00000, B00100, B01010, B01010, B01010, B10001, B11111, B00000};

		LiquidCrystal.createChar(1, charTopLine);
		LiquidCrystal.createChar(2, charBottomLine);
		LiquidCrystal.createChar(3, charLeftTopBracket);
		LiquidCrystal.createChar(4, charRightTopBracket);
		LiquidCrystal.createChar(5, charLeftBottomBracket);
		LiquidCrystal.createChar(6, charRightBottomBracket);
		LiquidCrystal.createChar(7, charDelta);

		// drawChar(box, 0, 0);	
	}

	void setCursor(byte column, byte line) {
		LiquidCrystal.setCursor(column, line);
	}

	void print(String content, byte column, byte line) {
		drawChar(box, 0, 0);
		LiquidCrystal.setCursor(column, line);
		LiquidCrystal.print(content);
	}

	void printCentered(String content, byte line, byte correction) {
		drawChar(box, 0, 0);
		LiquidCrystal.setCursor(((abs(17 - content.length()) / 2) - correction), line);
		LiquidCrystal.print(content);
	}

	void printDelta(String content, byte line, byte correction) {
		drawChar(box, 0, 0);
		LiquidCrystal.setCursor(((abs(17 - content.length()) / 2) - correction), line);
		LiquidCrystal.print(content);
		drawChar(delta, (((abs(17 - content.length()) / 2) - correction) - 1), line);
	}

	void clear() {
		drawChar(box, 0, 0);
	}

	void drawChar(byte character, byte column, byte line) {
		if(character == brackets) {
			LiquidCrystal.setCursor(0, 0);
			LiquidCrystal.write(leftTopBracket);

			LiquidCrystal.setCursor(15, 0);
			LiquidCrystal.write(rightTopBracket);

			LiquidCrystal.setCursor(0, 1);
			LiquidCrystal.write(leftBottomBracket);

			LiquidCrystal.setCursor(15, 1);
			LiquidCrystal.write(rightBottomBracket);
		}
		else if(character == box) {
			LiquidCrystal.setCursor(0, 0);
			LiquidCrystal.write(leftTopBracket);

			LiquidCrystal.setCursor(15, 0);
			LiquidCrystal.write(rightTopBracket);

			LiquidCrystal.setCursor(0, 1);
			LiquidCrystal.write(leftBottomBracket);

			LiquidCrystal.setCursor(15, 1);
			LiquidCrystal.write(rightBottomBracket);

			for(byte i = 1; i < 15; i++) {
				LiquidCrystal.setCursor(i, 0);
				LiquidCrystal.write(topLine);
				LiquidCrystal.setCursor(i, 1);
				LiquidCrystal.write(bottomLine);
			}
		}
		else {
			LiquidCrystal.setCursor(column, line);
			LiquidCrystal.write(character);
		}
	}

	void drawLines(byte character) {
		if(character == lines) {
			for(byte i = 1; i < 15; i++) {
				LiquidCrystal.setCursor(i, 0);
				LiquidCrystal.write(topLine);
				LiquidCrystal.setCursor(i, 1);
				LiquidCrystal.write(bottomLine);
			}
		}
		else if(character == topLine) {
			for(byte i = 1; i < 15; i++) {
				LiquidCrystal.setCursor(i, 0);
				LiquidCrystal.write(topLine);
			}
		}
		else if(character == bottomLine) {
			for(byte i = 1; i < 15; i++) {
				LiquidCrystal.setCursor(i, 1);
				LiquidCrystal.write(bottomLine);
			}
		}
	}
}
Display;

void setup() {
	Display.begin(16, 2);
}

void loop() {
	//
}