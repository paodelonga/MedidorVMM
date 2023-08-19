#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal LiquidCrystal(8, 9, 4, 5, 6, 7);
Servo Servo;

// Difinindo os pinos dos atuadores
const byte RELEASE_GATE_PIN = A5;
const byte FIRST_IR_SENSOR_PIN = A1;
const byte SECOND_IR_SENSOR_PIN = A2;
const byte THIRD_IR_SENSOR_PIN = A3;

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

class Properties {
 public:
  class Project {
   public:
    const char *AUTHORS_FULLNAME[2] = {"Jotaquerles do Nascimento França", "Abiel Mendes dos Santos"};
    const char *AUTHORS_SURNAME[2] = {"Jotaquerles N", "Abiel M"};
    const char *REVISION_DATE = "Thursday, 10 August, 2023; 10/08/2023 - 08:16:17";
    const char *REPO_URL = "https://github.com/paodelonga/medidor-vmm";
    const char *VERSION = "1.0.0";
  } Project;

  void begin() {
    Display.printWait(F("Autores"), 0, 0);
    Display.printWait((Project.AUTHORS_SURNAME[0]), 0, 0);
    Display.printWait((Project.AUTHORS_SURNAME[1]), 0, 0);

    Serial.println((String)F("MedidorVMM :: Autores: ") + Project.AUTHORS_FULLNAME[0]);
    Serial.println((String)F("MedidorVMM :: Autores: ") + Project.AUTHORS_FULLNAME[1]);

    Serial.print(F("MedidorVMM :: Versao: "));
    Serial.println(Project.VERSION);

    Display.printWait((String)F("Versao: ") + Project.VERSION, 0, 1);

    Serial.print(F("MedidorVMM :: Revisao: "));
    Serial.println(Project.REVISION_DATE);

    Display.printWait(F("git@paodelonga"), 0, 0);

    Serial.print(F("MedidorVMM :: Repositorio: "));
    Serial.println(Project.REPO_URL);

    Serial.println(F(""));

    Display.printWait(F("Iniciando"), 0, 1);

    const char *message = "Iniciando";
    byte tryCount = random(10);
    byte lineCount = tryCount;
    byte length = strlen(message) + 3;

    for (byte i = 0; i < tryCount; i++) {
      Serial.print(F("MedidorVMM :: Iniciando em: "));
      Serial.print(lineCount);
      Serial.print(F("s"));

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

class ReleaseGate {
 private:
  byte servoPin;

 public:
  bool open() {
    Servo.write(65);
    delay(100);

    Servo.write(63);
    delay(100);

    Servo.write(65);
    delay(100);

    Servo.write(63);
    delay(100);
    return true;
  }

  bool close() {
    Servo.write(20);
    delay(100);

    Servo.write(10);
    delay(100);

    Servo.write(20);
    delay(100);

    Servo.write(10);
    delay(100);
    return true;
  }

  void begin(byte servoPin) { Servo.attach(servoPin); }
} ReleaseGate;

class Reading {
 public:
  class Data {
   public:
    const byte maxReading = 10;
    const byte minReading = 0;
    byte currentReading;

    float initialPosition;
    float finalPosition;

    float sensorPosition[10][2];
    float sensorTimestamps[10][3];
    float timeIntervals[10][3];
    float meanVelocity[10][3];
    float distanceVariation[10];

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

    Serial.println(F("MedidorVMM :: Para iniciar posicione o objeto"));
    Serial.println(F("MedidorVMM :: e pressione left."));

    long messageTimer = millis();
    byte messageIndex = 0;
    while (1) {
      if ((millis() - messageTimer) > 1900) {
        if (messageIndex == 0) {
          Display.printCentered(F("Posicione o"), 0, 0);
          Display.printCentered(F("objeto e"), 1, 0);
          messageTimer = millis();
          messageIndex++;
        }
      }
      if (millis() - messageTimer > 2600) {
        if (messageIndex == 1) {
          Display.printCentered(F("pressione"), 0, 1);
          Display.printCentered(F("left"), 1, 0);
          messageTimer = millis();
          messageIndex = 0;
        }
      }

      if (KeypadButtons.Pressed() == KeypadButtons.Left) {
        Data.increaseReading();
        ReleaseGate.close();

        Serial.println(F("MedidorVMM :: Objeto posicionado."));
        Serial.println(F("MedidorVMM :: Posicionamento Completo.\n"));

        for (byte seconds = random(0, 10); seconds > 0; seconds--) {
          Serial.println((String)F("MedidorVMM :: Iniciando a leitura em: ") + seconds + F("s"));
          Display.printCentered(F("Iniciando em "), 0, 0);
          Display.printCentered((String)seconds + "s", 1, 0);
          delay(1000);
        }

        Serial.println(F("\nMedidorVMM :: Iniciando leitura."));

        if (ReleaseGate.open()) {
          Data.sensorTimestamps[Data.currentReading][0] = millis();
          Serial.println(F("\nMedidorVMM :: Objeto liberado."));
        }
        while (1) {
          Display.printCentered(F("Sensores"), 0, 0);
          Display.printCentered(F("Iniciados"), 1, 1);

          if (analogRead(FIRST_IR_SENSOR_PIN) > 920) {
            Data.sensorTimestamps[Data.currentReading][1] = millis();

            Serial.println(F("MedidorVMM :: Primeiro sensor detectado."));
            Display.printCentered(F("Primeiro IR"), 0, 0);
            Display.printCentered(F("detectado"), 1, 0);

            while (1) {
              if (analogRead(SECOND_IR_SENSOR_PIN) > 920) {
                Data.sensorTimestamps[Data.currentReading][2] = millis();

                Serial.println(F("MedidorVMM :: Segundo sensor detectado."));
                Display.printCentered(F("Segundo IR"), 0, 0);
                Display.printCentered(F("detectado"), 1, 0);

                while (1) {
                  if (analogRead(THIRD_IR_SENSOR_PIN) > 920) {
                    Data.sensorTimestamps[Data.currentReading][3] = millis();

                    Serial.println(F("MedidorVMM :: Terceiro sensor detectado."));
                    Display.printCentered(F("Terceiro IR"), 0, 0);
                    Display.printCentered(F("detectado"), 1, 0);

                    Display.printCentered(F("Processando"), 0, 0);
                    Display.printCentered(F("leitura"), 1, 0);

                    ReleaseGate.close();

                    Serial.println(F("\nMedidorVMM :: Iniciando calculo dos dados.\n"));

                    Serial.println(F("MedidorVMM :: Calculando a variação de distância.\n"));
                    Data.distanceVariation[Data.currentReading] = (Data.finalPosition - Data.initialPosition);

                    Serial.println(F("MedidorVMM :: Calculando o primeiro intervalo."));
                    Data.timeIntervals[Data.currentReading][0] = (Data.sensorTimestamps[Data.currentReading][1] - Data.sensorTimestamps[Data.currentReading][0]);

                    Serial.println(F("MedidorVMM :: Calculando o segundo intervalo."));
                    Data.timeIntervals[Data.currentReading][1] = (Data.sensorTimestamps[Data.currentReading][2] - Data.sensorTimestamps[Data.currentReading][1]);

                    Serial.println(F("MedidorVMM :: Calculando o terceiro intervalo.\n"));
                    Data.timeIntervals[Data.currentReading][2] = (Data.sensorTimestamps[Data.currentReading][3] - Data.sensorTimestamps[Data.currentReading][2]);

                    Serial.println(F("MedidorVMM :: Calculando a primeira velocidade."));
                    Data.meanVelocity[Data.currentReading][0] = (Data.distanceVariation[Data.currentReading] / Data.timeIntervals[Data.currentReading][0]);

                    Serial.println(F("MedidorVMM :: Calculando a segunda velocidade."));
                    Data.meanVelocity[Data.currentReading][1] = (Data.distanceVariation[Data.currentReading] / Data.timeIntervals[Data.currentReading][1]);

                    Serial.println(F("MedidorVMM :: Calculando a terceira velocidade.\n"));
                    Data.meanVelocity[Data.currentReading][2] = (Data.distanceVariation[Data.currentReading] / Data.timeIntervals[Data.currentReading][2]);

                    Serial.println(F("MedidorVMM :: Calculando o intervalo total."));
                    Data.timeIntervals[Data.currentReading][3] = (Data.sensorTimestamps[Data.currentReading][3] - Data.sensorTimestamps[Data.currentReading][0]);

                    Serial.println(F("MedidorVMM :: Calculando a velocidade total.\n"));
                    Data.meanVelocity[Data.currentReading][3] = (Data.distanceVariation[Data.currentReading] / Data.timeIntervals[Data.currentReading][3]);

                    Serial.println(F("MedidorVMM :: Dados calculados e processados."));
                    Serial.println(F("MedidorVMM :: Processamento de dados completo.\n"));
                    Display.printCentered(F("Leitura"), 0, 0);
                    Display.printCentered(F("Completa."), 1, 0);
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

class Menu {
 public:
  // class Options {
  // byte NONE = 0;
  // byte _MIN_PREFS = 1;
  // byte _MAX_PREFS = 3;
  //
  // byte _FOCUSED_PREFS;
  // byte _SELECTED_PREFS;
  // const char *_OPTIONS_LABEL[4][2] = {{}, {"INICIAR NOVA", "LEITURA"}, {"EXIBIR DADOS", "DA LEITURA"}, {"ALTERAR", "CONFIGS"}};
  // long switcherTime;
  //
  // } Options;

  byte _STANDBY = 0;
  byte _READ = 1;
  byte _DISPLAY = 2;
  byte _PREFERENCES = 3;
  byte _MIN_MENU = 1;
  byte _MAX_MENU = 3;

  byte _FOCUSED_MENU;
  byte _SELECTED_MENU;
  const char *_MENUS_LABELS[4][2] = {{}, {"INICIAR NOVA", "LEITURA"}, {"EXIBIR DADOS", "DA LEITURA"}, {"ALTERAR", "PREFS"}};
  long switcherTime;

  void switchFocusedMenus() {
    if (_FOCUSED_MENU < _MAX_MENU) {
      _FOCUSED_MENU++;
    } else if (_FOCUSED_MENU == _MAX_MENU) {
      _FOCUSED_MENU = _MIN_MENU;
    }
    Display.printCentered(_MENUS_LABELS[_FOCUSED_MENU][0], 0, 0);
    Display.printCentered(_MENUS_LABELS[_FOCUSED_MENU][1], 1, 0);
    switcherTime = millis();
  }

  long messageTimer = millis();
  byte messageIndex = 0;
  void loop() {
    if (_FOCUSED_MENU == _STANDBY) {
      if ((millis() - messageTimer) > 1900) {
        if (messageIndex == 0) {
          Display.printCentered(F("UP/RIGHT"), 0, 0);
          Display.printCentered(F("PARA NAVEGACAO"), 1, 0);
          messageTimer = millis();
          messageIndex++;
        }
      }
      if (millis() - messageTimer > 2900) {
        if (messageIndex == 1) {
          Display.printCentered(F("LEFT/RIGHT"), 0, 0);
          Display.printCentered(F("PARA SELECAO"), 1, 0);
          messageTimer = millis();
          messageIndex = 0;
        }
      }
    }
    switch (KeypadButtons.Pressed()) {
      case KeypadButtons.Up:
        delay(250);
        break;
      case KeypadButtons.Down:
        delay(250);
        break;
      case KeypadButtons.Right:
        delay(250);
        if (_FOCUSED_MENU == _READ) {
          Reading.read();
        }
        break;
      case KeypadButtons.Left:
        delay(250);
        if (_SELECTED_MENU == _STANDBY) {
          _FOCUSED_MENU = _STANDBY;
        }
        break;
      case KeypadButtons.Select:
        delay(250);
        switchFocusedMenus();
        break;
    }
    if (millis() > (switcherTime + 15000)) {
      _FOCUSED_MENU = _STANDBY;
      switcherTime = millis();
    }
  }
} Menu;

void setup() {
  Reading.Data.initialPosition = 0;
  Reading.Data.finalPosition = 120;

  pinMode(FIRST_IR_SENSOR_PIN, INPUT);
  pinMode(SECOND_IR_SENSOR_PIN, INPUT);
  pinMode(THIRD_IR_SENSOR_PIN, INPUT);

  Display.begin(16, 2);
  Serial.begin(9600);

  while (!Serial) {
    delay(250);
  }

  ReleaseGate.begin(RELEASE_GATE_PIN);
  Properties.begin();
}
void loop() {
  Menu.loop();
}
