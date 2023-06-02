#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal LiquidCrystal(8, 9, 4, 5, 6, 7);
Servo Servo;

// Difinindo os pinos dos atuadores
const byte RELEASE_GATE_PIN = A5;      // PONTO A (CANCELA)
const byte FIRST_IR_SENSOR_PIN = A1;   // PONTO B (SENSOR)
const byte SECOND_IR_SENSOR_PIN = A2;  // PONTO C (SENSOR)
const byte THIRD_IR_SENSOR_PIN = A3;   // PONTO D (SENSOR)

// Valores dos sensores
uint16_t stateFirstIRSensor;   // PONTO B (SENSOR)
uint16_t stateSecondIRSensor;  // PONTO C (SENSOR)
uint16_t stateThirdIRSensor;   // PONTO D (SENSOR)

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

    byte charTopLine[8] = { B11111, B00000, B00000, B00000, B00000, B00000, B00000, B00000 };
    byte charBottomLine[8] = { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B11111 };
    byte charLeftTopBracket[8] = { B01111, B10000, B10000, B10000, B10000, B10000, B10000, B10000 };
    byte charRightTopBracket[8] = { B11110, B00001, B00001, B00001, B00001, B00001, B00001, B00001 };
    byte charLeftBottomBracket[8] = { B10000, B10000, B10000, B10000, B10000, B10000, B10000, B01111 };
    byte charRightBottomBracket[8] = { B00001, B00001, B00001, B00001, B00001, B00001, B00001, B11110 };
    byte charDelta[8] = { B00000, B00100, B01010, B01010, B01010, B10001, B11111, B00000 };

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
    if (character == brackets) {
      LiquidCrystal.setCursor(0, 0);
      LiquidCrystal.write(leftTopBracket);

      LiquidCrystal.setCursor(15, 0);
      LiquidCrystal.write(rightTopBracket);

      LiquidCrystal.setCursor(0, 1);
      LiquidCrystal.write(leftBottomBracket);

      LiquidCrystal.setCursor(15, 1);
      LiquidCrystal.write(rightBottomBracket);
    } else if (character == box) {
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
    } else {
      LiquidCrystal.setCursor(column, line);
      LiquidCrystal.write(character);
    }
  }

  void drawLines(byte character) {
    if (character == lines) {
      for (byte i = 1; i < 15; i++) {
        LiquidCrystal.setCursor(i, 0);
        LiquidCrystal.write(topLine);
        LiquidCrystal.setCursor(i, 1);
        LiquidCrystal.write(bottomLine);
      }
    } else if (character == topLine) {
      for (byte i = 1; i < 15; i++) {
        LiquidCrystal.setCursor(i, 0);
        LiquidCrystal.write(topLine);
      }
    } else if (character == bottomLine) {
      for (byte i = 1; i < 15; i++) {
        LiquidCrystal.setCursor(i, 1);
        LiquidCrystal.write(bottomLine);
      }
    }
  }
} Display;

class Properties {
public:
  class Project {
  public:
    const char* NAME = "MedidorVMM";
    const char* AUTHOR = "Abiel (Paodelonga) Mendes dos Santos";
    const char* VERSION = "1.0.0.";
    const char* REVISION = "Terça-Feira, 30 de Maio de 2023 - 06:12 PM";
    const char* GITHUB = "https://github.com/OphiuchusTeam/MedidorVMM";
    const char* HEADER[4] = { "Medidor de", "Velocidade", "Media no", "Movimento." };
  } Project;

  void begin() {
    Display.printCentered(Project.NAME, 0, 0);
    delay((strlen(Project.NAME) * strlen(Project.NAME)) * 20);

    for (byte phrase = 0; phrase < (sizeof(Project.HEADER) / 2); phrase++) {
      byte cursorPos = (abs(16 - (strlen(Project.HEADER[phrase]))) / 2);
      for (byte wordPhrase = 0; wordPhrase < strlen(Project.HEADER[phrase]); wordPhrase++) {
        for (byte previousCursorPos = cursorPos; previousCursorPos < (17 - cursorPos); previousCursorPos++) {
          Display.drawChar(Display.topLine, previousCursorPos, 0);
        }
        LiquidCrystal.setCursor(cursorPos, 0);
        LiquidCrystal.print(Project.HEADER[phrase][wordPhrase]);
        Serial.print(Project.HEADER[phrase][wordPhrase]);
        delay((strlen(Project.HEADER[phrase]) * strlen(Project.HEADER[phrase])) * 2);
        cursorPos++;
      }
      Serial.print(' ');
      delay((strlen(Project.HEADER[phrase]) * strlen(Project.HEADER[phrase])) * 6);
      for (byte nextCursorPos = 1; nextCursorPos < cursorPos - 1; nextCursorPos++) {
        Display.drawChar(Display.topLine, nextCursorPos, 0);
      }
    }
    Serial.println(' ');

    Display.printCentered(F("Desenvolvido"), 0, 0);
    delay(1660);

    Display.printCentered(F("por"), 0, 0);
    delay(1390);

    Display.printCentered(Project.AUTHOR, 0, 0);
    Serial.print(F("ABOUT :: Author: "));
    Serial.println(Project.AUTHOR);
    delay(2320);

    Serial.print(F("ABOUT :: Version: "));
    Serial.println(Project.VERSION);

    Display.printCentered(F("Versao"), 0, 0);
    delay(1420);

    Display.printCentered(Project.VERSION, .0, 0);
    delay(1910);

    Serial.print(F("ABOUT :: Revision: "));
    Serial.println(Project.REVISION);

    Display.printCentered(F("git@paodelonga"), 0, 0);
    delay(2620);

    Serial.print(F("ABOUT :: GitHub: "));
    Serial.println(Project.GITHUB);

    Serial.println(F(""));

    const char* message = "Iniciando";
    Display.printCentered(F("Iniciando"), 3, 0);

    byte tryCount = random(1, 10);
    byte lineCount = tryCount;
    byte length = strlen(message) + 3;

    for (byte i = 0; i < tryCount; i++) {
      if (lineCount > 0) {
        Serial.print(F("MedidorVMM :: Iniciando em: "));
        Serial.print(lineCount);
        Serial.print(F("s"));
      }

      for (byte x = length; x < length + 3; x++) {
        LiquidCrystal.setCursor(x, 0);
        LiquidCrystal.print(F("."));
        if (lineCount > 0) {
          Serial.print(F("."));
        }

        delay(5 * 115 / 3.112);
        Display.drawChar(Display.topLine, x, 0);
      }

      if (lineCount > 0) {
        Serial.print(F("\n"));
        lineCount--;
      }
    }
    Serial.print(F("\n"));
    Display.printCentered(F("Iniciado!"), 3, 0);
  }
} Properties;

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
    if (buttonValue > 60 and buttonValue < 200) {
      pressedValue = Up;
    } else if (buttonValue > 200 and buttonValue < 400) {
      pressedValue = Down;
    } else if (buttonValue > 400 and buttonValue < 600) {
      pressedValue = Left;
    } else if (buttonValue > 0 and buttonValue < 60) {
      pressedValue = Right;
    } else if (buttonValue > 600 and buttonValue < 800) {
      pressedValue = Select;
    } else if (buttonValue > 800) {
      pressedValue = NONE;
    }
    return pressedValue;
  }
  int Toggled() {
    buttonValue = analogRead(0);
    if (buttonValue > 60 and buttonValue < 200) {
      toggledValue = Up;
    } else if (buttonValue > 200 and buttonValue < 400) {
      toggledValue = Down;
    } else if (buttonValue > 400 and buttonValue < 600) {
      toggledValue = Left;
    } else if (buttonValue > 0 and buttonValue < 60) {
      toggledValue = Right;
    } else if (buttonValue > 600 and buttonValue < 800) {
      toggledValue = Select;
    }
    return toggledValue;
  }
} KeypadButtons;

class ReleaseGate {
private:
  byte servoPin;
public:

  void open() {
    Servo.write(65);
    delay(100);

    Servo.write(63);
    delay(100);

    Servo.write(65);
    delay(100);

    Servo.write(63);
    delay(100);
    Serial.println(F("MedidorVMM :: Abrindo a cancela."));
  }

  void close() {
    Servo.write(20);
    delay(100);

    Servo.write(10);
    delay(100);

    Servo.write(20);
    delay(100);

    Servo.write(10);
    delay(100);
    Serial.println(F("MedidorVMM :: Fechando a cancela."));
  }

  void begin(byte servoPin) {
    Servo.attach(servoPin);
  }
} ReleaseGate;

class Reading {
public:
  class Data {
  public:  // -- WARN: Talvez seja um problema definir o limite dos arrays utilizando variaveis
    const uint8_t maxReading = 10;
    const uint8_t minReading = 1;
    uint8_t currentReading = 0;

    uint8_t initialPosition;
    uint8_t finalPosition;

    double sensorTimestamps[10][3];
    double timeIntervals[10][3];
    double timeVariations[10];
    double meanVelocity[10][3];
    double distanceVariation;

    void increaseReading() {
      if (currentReading < maxReading) {
        currentReading++;
      } else if (currentReading >= maxReading) {
        currentReading = minReading;
      }
    }
  } Data;

  void read() {
    ReleaseGate.open();

    long messageTimer = millis();
    byte messageIndex = 0;

    Serial.println(F("MedidorVMM :: Iniciando posicionamento."));
    Serial.println(F("MedidorVMM :: Posicione o objeto e pressione left."));

    while (1) {
      if ((millis() - messageTimer) > 1600) {
        if (messageIndex == 0) {
          Display.printCentered(F("Posicione o"), 0, 1);
          messageTimer = millis();
          messageIndex++;
        }
      }
      if ((millis() - messageTimer) > 1250) {
        if (messageIndex == 1) {
          Display.printCentered(F("Objeto e"), 0, 0);
          messageTimer = millis();
          messageIndex++;
        }
      }
      if ((millis() - messageTimer) > 1200) {
        if (messageIndex == 3) {
          Display.printCentered(F("Left."), 0, 0);
          messageTimer = millis();
          messageIndex = 0;
        }
      }
      if (KeypadButtons.Pressed() == KeypadButtons.Left) {
        Data.increaseReading();
        ReleaseGate.close();

        Serial.println(F("MedidorVMM :: Objeto posicionado."));
        Serial.println(F("MedidorVMM :: Posicionamento Completo.\n"));

        for (byte seconds = 5; seconds > 0; seconds--) {
          Serial.println((String)F("MedidorVMM :: Iniciando a leitura em: ") + seconds + F("s."));
          Display.printCentered((String)F("Iniciando em ") + seconds, 0, 0);
          delay(1000);
        }

        Serial.print(F("\n"));

        ReleaseGate.open();
        Data.sensorTimestamps[Data.currentReading][0] = millis();

        Serial.println(F("MedidorVMM :: Iniciando leitura."));

        messageTimer = millis();
        messageIndex = 0;

        while (1) {
          if ((millis() - messageTimer) > 1250) {
            Display.printCentered(F("Iniciando"), 0, 0);
            messageTimer = millis();
            messageIndex++;
          }
          if ((millis() - messageTimer) > 1200) {
            Display.printCentered(F("Leitura."), 0, 0);
            messageTimer = millis();
            messageIndex++;
          }

          if (digitalRead(FIRST_IR_SENSOR_PIN) == HIGH) {
            Data.sensorTimestamps[Data.currentReading][1] = millis();

            Serial.println(F("MedidorVMM :: Primeiro sinal interrompido."));
            Display.printCentered(F("Primeiro IR"), 0, 0);

            while (1) {
              if (digitalRead(SECOND_IR_SENSOR_PIN) == HIGH) {
                Data.sensorTimestamps[Data.currentReading][2] = millis();

                Serial.println(F("MedidorVMM :: Segundo sinal interrompido."));
                Display.printCentered(F("Segundo IR"), 0, 0);

                while (1) {
                  if (digitalRead(THIRD_IR_SENSOR_PIN) == HIGH) {
                    Data.sensorTimestamps[Data.currentReading][3] = millis();

                    Serial.println(F("MedidorVMM :: Terceiro sinal interrompido."));
                    Display.printCentered(F("Terceiro IR"), 0, 0);

                    Serial.println(F("MedidorVMM :: Leitura completa."));
                    Display.printCentered(F("Leitura completa"), 0, 0);

                    ReleaseGate.close();

                    Serial.print(F("\n"));

                    Serial.println(F("MedidorVMM :: Iniciando calculo dos dados."));
                    Display.printCentered(F("Calculando..."), 0, 0);

                    // S(Final) - S(Inicial)
                    Serial.println(F("MedidorVMM :: Calculando a variação de distância.\n"));
                    Data.distanceVariation = abs(Data.finalPosition - Data.initialPosition);

                    // A ==> B | (B - A)
                    Serial.println(F("MedidorVMM :: Calculando o primeiro intervalo."));
                    Data.timeIntervals[Data.currentReading][0] = abs(Data.sensorTimestamps[Data.currentReading][1] - Data.sensorTimestamps[Data.currentReading][0]);

                    Serial.println(F("MedidorVMM :: Calculando a primeira velocidade.\n"));
                    Data.meanVelocity[Data.currentReading][0] = abs(Data.distanceVariation / Data.timeIntervals[Data.currentReading][0]);

                    // B ==> C | (C - B)
                    Serial.println(F("MedidorVMM :: Calculando o segundo intervalo."));
                    Data.timeIntervals[Data.currentReading][1] = abs(Data.sensorTimestamps[Data.currentReading][2] - Data.sensorTimestamps[Data.currentReading][1]);

                    Serial.println(F("MedidorVMM :: Calculando a segunda velocidade.\n"));
                    Data.meanVelocity[Data.currentReading][0] = abs(Data.distanceVariation / Data.timeIntervals[Data.currentReading][1]);

                    // C ==> D | (D - C)
                    Serial.println(F("MedidorVMM :: Calculando o terceiro intervalo."));
                    Data.timeIntervals[Data.currentReading][2] = abs(Data.sensorTimestamps[Data.currentReading][3] - Data.sensorTimestamps[Data.currentReading][2]);

                    Serial.println(F("MedidorVMM :: Calculando a terceira velocidade.\n"));
                    Data.meanVelocity[Data.currentReading][0] = abs(Data.distanceVariation / Data.timeIntervals[Data.currentReading][2]);

                    // (D - A) | (D - A)
                    Serial.println(F("MedidorVMM :: Calculando a variação de tempo."));
                    Data.timeVariations[Data.currentReading] = abs(Data.sensorTimestamps[Data.currentReading][3] - Data.sensorTimestamps[Data.currentReading][0]);

                    Serial.println(F("MedidorVMM :: Calculando a velocidade media.\n"));
                    Data.meanVelocity[Data.currentReading][0] = abs(Data.distanceVariation / Data.timeIntervals[Data.currentReading][2]);

                    Serial.println(F("MedidorVMM :: Dados calculados e processados."));
                    Serial.println(F("MedidorVMM :: Processamento de dados completo.\n"));
                    Display.printCentered(F("Processado."), 0, 0);

                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
} Reading;

void setup() {
  Serial.begin(9600);
  delay(250);

  ReleaseGate.begin(RELEASE_GATE_PIN);
  Display.begin(16, 2);
  Properties.begin();

  Reading.read();
}
void loop() {
  //
}

/*
TODO:
	Reader class
	Menu class

TODOING:
	Reader class

*/
