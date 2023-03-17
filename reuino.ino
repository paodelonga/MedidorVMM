#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal LiquidCrystal(8, 9, 4, 5, 6, 7);
Servo Servo;

// Difinindo os pinos dos atuadores
#define pinFirstIRSensor A1
#define pinSecondIRSensor A2
#define pinThirdIRSensor A3
#define pinTriggerGate A5

// Valores dos sensores
uint16_t stateFirstIRSensor;
uint16_t stateSecondIRSensor;
uint16_t stateThirdIRSensor;

class Display {
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

class Properties {
public:
	class Project {
	public:
		const char* Name = "MedidorVMM";
		const char* Author = "Abiel Mendes";
		const char* Version = "1.0.0.";
		const char* Revision = "Sabado, 11 de Fevereiro de 2023 - 06:45 PM";
		const char* Github = "https://github.com/CEM-AT/MedidorVMM";
		const char* Description[4] = {"Medidor de", "Velocidade", "Media no", "Movimento."};
	}
	Project;

	void begin() {
		Display.printCentered(Project.Name, 0, 0);
		delay((strlen(Project.Name) * strlen(Project.Name)) * 20);

		for(byte phrase = 0; phrase < (sizeof(Project.Description) / 2); phrase++) {
			byte cursorPos = (abs(16 - (strlen(Project.Description[phrase]))) / 2);
			for(byte wordPhrase = 0; wordPhrase < strlen(Project.Description[phrase]); wordPhrase++) {
				for(byte previousCursorPos = cursorPos; previousCursorPos < (17 - cursorPos); previousCursorPos++) {
					Display.drawChar(Display.topLine, previousCursorPos, 0);
				}
				LiquidCrystal.setCursor(cursorPos, 0);
				LiquidCrystal.print(Project.Description[phrase][wordPhrase]);
				Serial.print(Project.Description[phrase][wordPhrase]);
				delay((strlen(Project.Description[phrase]) * strlen(Project.Description[phrase])) * 2);
				cursorPos++;
			}
			Serial.print(' ');
			delay((strlen(Project.Description[phrase]) * strlen(Project.Description[phrase])) * 6);
			for(byte nextCursorPos = 1; nextCursorPos < cursorPos - 1; nextCursorPos++) {
				Display.drawChar(Display.topLine, nextCursorPos, 0);
			}
		}
		Serial.println(' ');

		Display.printCentered(F("Desenvolvido"), 0, 0);
		delay(1660);

		Display.printCentered(F("por"), 0, 0);
		delay(1390);

		Display.printCentered(Project.Author, 0, 0);
		Serial.print(F("PROJETO :: Author: "));
		Serial.println(Project.Author);
		delay(2320);

		Serial.print(F("PROJETO :: Version: "));
		Serial.println(Project.Version);

		Display.printCentered(F("Versao"), 0, 0);
		delay(1420);

		Display.printCentered(Project.Version, .0, 0);
		delay(1910);

		Serial.print(F("PROJETO :: Revisao: "));
		Serial.println(Project.Revision);

		Display.printCentered(F("git@paodelonga"), 0, 0);
		delay(2620);

		Serial.print(F("PROJETO :: Github: "));
		Serial.println(Project.Github);

		Serial.println(F("\n"));

		const char* message = "Iniciando";
		Display.print(F("Iniciando"), 3, 0);

		byte tryCount = random(1, 10);
		byte lineCount = tryCount;
		byte length = strlen(message) + 3;

		for (byte i = 0; i < tryCount; i++) {
			if(lineCount > 0) {
				Serial.print(F("PROJETO :: Iniciando em: "));
				Serial.print(lineCount);
				Serial.print(F("s"));
			}

			for (byte x = length; x < length+3; x++) {
				LiquidCrystal.setCursor(x, 0);
				LiquidCrystal.print(F("."));
				if(lineCount > 0) {
					Serial.print(F("."));
				}

				delay(5*115/3.112);
				Display.drawChar(Display.topLine, x, 0);
			}

			if(lineCount > 0) {
				Serial.print(F("\n"));
				lineCount--;
			}
		}
		Serial.println(F("PROJETO :: Iniciado."));
	}
}
Properties;

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
		if(buttonValue > 60 and buttonValue < 200) { pressedValue = Up; }
		else if(buttonValue > 200 and buttonValue < 400) { pressedValue = Down; }
		else if(buttonValue > 400 and buttonValue < 600) { pressedValue = Left; }
		else if(buttonValue > 0 and buttonValue < 60) { pressedValue = Right; }
		else if(buttonValue > 600 and buttonValue < 800) { pressedValue = Select; }
		else if(buttonValue > 800) { pressedValue = NONE; }
		return pressedValue;
	}
	int Toggled() {
		buttonValue = analogRead(0);
		if(buttonValue > 60 and buttonValue < 200) { toggledValue = Up; }
		else if(buttonValue > 200 and buttonValue < 400) { toggledValue = Down; }
		else if(buttonValue > 400 and buttonValue < 600) { toggledValue = Left; }
		else if(buttonValue > 0 and buttonValue < 60) { toggledValue = Right; }
		else if(buttonValue > 600 and buttonValue < 800) { toggledValue = Select; }
		return toggledValue;
	}
}
KeypadButtons;

// class Menu {
// public:
// }
// Menu;

void setup() {
	Serial.begin(9600);
	delay(250);

	Display.begin(16, 2);
	Properties.begin();
	// Menu.begin();
}
void loop() {
	// Menu.loop();
	return;
}

/*
TODO:
	Menu class
	Fix indent
	Refactor classes
	Reader class
*/
