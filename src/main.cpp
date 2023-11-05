#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <avr/pgmspace.h>
#include <math.h>

LiquidCrystal LiquidCrystal(8, 9, 4, 5, 6, 7);
Servo Servo;

#define FIRST_IR_SENSOR_PIN A1
#define SECOND_IR_SENSOR_PIN A2
#define THIRD_IR_SENSOR_PIN A3
#define RELEASE_GATE_PIN A4

class Display {
 public:
  static const uint8_t lines = 0;
  static const uint8_t topLine = 1;
  static const uint8_t bottomLine = 2;
  static const uint8_t leftTopBracket = 3;
  static const uint8_t rightTopBracket = 4;
  static const uint8_t leftBottomBracket = 5;
  static const uint8_t rightBottomBracket = 6;
  static const uint8_t selectedMark = 7;
  static const uint8_t brackets = 8;
  static const uint8_t box = 9;

  void begin(byte lcd_columns, byte lcd_lines) {
    byte charTopLine[8] = {B11111, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
    byte charBottomLine[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B11111};
    byte charLeftTopBracket[8] = {B01111, B10000, B10000, B10000, B10000, B10000, B10000, B10000};
    byte charRightTopBracket[8] = {B11110, B00001, B00001, B00001, B00001, B00001, B00001, B00001};
    byte charLeftBottomBracket[8] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B01111};
    byte charRightBottomBracket[8] = {B00001, B00001, B00001, B00001, B00001, B00001, B00001, B11110};
    byte charSelectedMark[8] = {B00000, B01000, B01100, B01110, B01110, B01100, B01000, B00000};

    LiquidCrystal.begin(lcd_columns, lcd_lines);
    LiquidCrystal.createChar(1, charTopLine);
    LiquidCrystal.createChar(2, charBottomLine);
    LiquidCrystal.createChar(3, charLeftTopBracket);
    LiquidCrystal.createChar(4, charRightTopBracket);
    LiquidCrystal.createChar(5, charLeftBottomBracket);
    LiquidCrystal.createChar(6, charRightBottomBracket);
    LiquidCrystal.createChar(7, charSelectedMark);
    drawChar(box, 0, 0);
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
      drawChar(leftTopBracket, 0, line);
      for (byte backwardCursorPos = 1; backwardCursorPos < cursorPos; backwardCursorPos++) {
        drawChar(topLine, backwardCursorPos, line);
      }
      drawChar(rightTopBracket, 15, line);
    } else if (line == 1) {
      drawChar(leftBottomBracket, 0, line);
      for (byte backwardCursorPos = 1; backwardCursorPos < cursorPos; backwardCursorPos++) {
        drawChar(bottomLine, backwardCursorPos, line);
      }
      drawChar(rightBottomBracket, 15, line);
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
} Display;

class Properties {
 public:
  void begin() {
    const char *AUTHORS_FULLNAME[2] = {"Jotaquerles do Nascimento França", "Abiel Mendes dos Santos"};
    const char *AUTHORS_SURNAME[2] = {"Jotaquerles N", "Abiel M"};
    const char *VERSION = "2.0.0";
    const char *REVISION_DATE = "Sunday, 05 November, 2023; 05/11/2023 - 01:09:39";
    const char *REPO_URL = "https://github.com/paodelonga/aemf-01";

    Display.printWait(F("AUTORES"), 0, 0);
    Display.printWait((AUTHORS_SURNAME[0]), 0, 0);
    Display.printWait((AUTHORS_SURNAME[1]), 0, 0);

    Serial.print(F("AEMF :: Autores: "));
    Serial.println(AUTHORS_FULLNAME[0]);
    Serial.print(F("AEMF :: Autores: "));
    Serial.println(AUTHORS_FULLNAME[1]);

    Display.printWait((String)F("VERSAO: ") + VERSION, 0, 1);

    Serial.print(F("AEMF :: Revisao: "));
    Serial.println(REVISION_DATE);

    Display.printWait(F("git@paodelonga"), 0, 0);
    Display.printWait(F("MNPEF: AEMF-01"), 0, 0);

    Serial.print(F("AEMF :: Repositorio: "));
    Serial.println(REPO_URL);

    Serial.print(F("AEMF :: Versao: "));
    Serial.println(VERSION);

    Serial.println(F(""));

    const char *message = "INICIANDO";
    Display.printWait(message, 0, 1);

    for (byte i = 0; i < random(10); i++) {
      for (byte x = (strlen(message) + 3); x < (strlen(message) + 3) + 3; x++) {
        LiquidCrystal.setCursor(x, 0);
        LiquidCrystal.print(F("."));

        delay(5 * 115 / 3.112);
        Display.drawChar(Display.topLine, x, 0);
      }
    }
  }
} Properties;

class KeypadButtons {
 private:
  uint16_t buttonValue;
  byte unsigned pressedValue;
  byte unsigned toggledValue;

 public:
  static const byte Up = 1;
  static const byte Down = 2;
  static const byte Left = 3;
  static const byte Right = 4;
  static const byte Select = 5;
  static const byte NONE = 0;

  int Pressed() {
    buttonValue = analogRead(0);
    if (buttonValue < 50) {
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
  }

  void begin(byte servoPin) { Servo.attach(servoPin); }
} ReleaseGate;

class Reading {
 public:
  class Data {
   public:
    double sensorPosition[3];
    double sensorTimestamps[4];
    double timeIntervals[4];
    double meanVelocity[4];
    double distanceVariation[4];
  } Data;

  void read() {
    ReleaseGate.open();

    Serial.println(F("AEMF :: PARA INICIAR POSICIONE O OBJETO"));
    Serial.println(F("AEMF :: E PRESSIONE RIGHT PARA RETENCAO.\n"));

    long messageTimer = millis();
    byte messageIndex = 0;
    while (1) {
      if ((millis() - messageTimer) > 1900) {
        if (messageIndex == 0) {
          Display.printCentered(F("POSICIONE O"), 0, 0);
          Display.printCentered(F("OBJETO"), 1, 0);
          messageTimer = millis();
          messageIndex++;
        }
      }
      if (millis() - messageTimer > 2600) {
        if (messageIndex == 1) {
          Display.printCentered(F("E PRESSIONE"), 0, 0);
          Display.printCentered(F("RIGHT."), 1, 0);
          messageTimer = millis();
          messageIndex = 0;
        }
      }

      if (KeypadButtons.Pressed() == KeypadButtons.Right) {
        ReleaseGate.close();
        Serial.println(F("AEMF :: OBJETO RETIDO!"));

        for (byte seconds = random(0, 10); seconds > 0; seconds--) {
          Serial.print(F("AEMF :: LIBERANDO OBJETO EM: "));
          Serial.print(seconds);
          Serial.println(F("s"));
          Display.printCentered(F("LIBERANDO EM"), 0, 0);
          Display.printCentered((String)seconds + "s", 1, 0);
          delay(1000);
        }

        Serial.println(F("AEMF :: INICIANDO LEITURA DOS SENSORES.\n"));
        ReleaseGate.open();
        Data.sensorTimestamps[0] = millis();

        while (1) {
          Display.printCentered(F("SENSORES"), 0, 0);
          Display.printCentered(F("INICIADOS."), 1, 0);

          if (analogRead(FIRST_IR_SENSOR_PIN) < 600) {
            Data.sensorTimestamps[1] = millis();

            Serial.println(F("AEMF :: PRIMEIRO SENSOR INTERROMPIDO."));
            Display.printCentered(F("PRIMEIRO IR"), 0, 0);

            while (1) {
              if (analogRead(SECOND_IR_SENSOR_PIN) < 600) {
                Data.sensorTimestamps[2] = millis();

                Serial.println(F("AEMF :: SEGUNDO SENSOR INTERROMPIDO."));
                Display.printCentered(F("SEGUNDO IR"), 0, 0);

                while (1) {
                  if (analogRead(THIRD_IR_SENSOR_PIN) < 600) {
                    Data.sensorTimestamps[3] = millis();

                    Serial.println(F("AEMF :: TERCEIRO SENSOR INTERROMPIDO.\n"));
                    Display.printCentered(F("TERCEIRO IR"), 0, 0);
                    ReleaseGate.close();

                    Display.printCentered(F("PROCESSANDO"), 0, 0);
                    Display.printCentered(F("A LEITURA."), 1, 0);

                    Serial.println(F("AEMF :: INICIANDO CALCULO DOS DADOS."));

                    Serial.println(F("AEMF :: CALCULANDO VARIAÇÃO DE ESPAÇO."));

                    Data.distanceVariation[0] = Data.sensorPosition[0] + 0.11;                                      // S1 - LG
                    Data.distanceVariation[1] = (Data.sensorPosition[1] + 0.11) - (Data.sensorPosition[0] + 0.11);  // S2 - S1
                    Data.distanceVariation[2] = (Data.sensorPosition[2] + 0.11) - (Data.sensorPosition[1] + 0.11);  // S3 - S2
                    Data.distanceVariation[3] = Data.sensorPosition[2];                                             // S3 - LG

                    Serial.println(F("AEMF :: CALCULADO VARIAÇÃO DE TEMPO."));
                    Data.timeIntervals[0] = Data.sensorTimestamps[1] - Data.sensorTimestamps[0];  // S1 - LG
                    Data.timeIntervals[1] = Data.sensorTimestamps[2] - Data.sensorTimestamps[1];  // S2 - S1
                    Data.timeIntervals[2] = Data.sensorTimestamps[3] - Data.sensorTimestamps[2];  // S3 - S2
                    Data.timeIntervals[3] = Data.sensorTimestamps[3] - Data.sensorTimestamps[0];  // S3 - LG

                    Serial.println(F("AEMF :: CALCULANDO VELOCIDADE MÉDIA."));
                    Data.meanVelocity[0] = Data.distanceVariation[0] / (Data.timeIntervals[0] / 1000.00);  // S1 - LG
                    Data.meanVelocity[1] = Data.distanceVariation[1] / (Data.timeIntervals[1] / 1000.00);  // S2 - S1
                    Data.meanVelocity[2] = Data.distanceVariation[2] / (Data.timeIntervals[2] / 1000.00);  // S3 - S2
                    Data.meanVelocity[3] = Data.distanceVariation[3] / (Data.timeIntervals[3] / 1000.00);  // S3 - LG

                    Serial.println(F("AEMF :: DADOS PROCESSADOS E CALCULADOS."));
                    Serial.println(F("AEMF :: PROCESSAMENTO COMPLETO.\n"));

                    Serial.println(F("AEMF :: PRESSIONE SELECT E SELICIONE"));
                    Serial.println(F("AEMF :: O MODO DE EXIBICAO PARA VISUALIZAR OS DADOS.\n"));
                    Display.printCentered(F("LEITURA"), 0, 0);
                    Display.printCentered(F("COMPLETA."), 1, 0);
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

  void display() {
    String _top = (String)F("|========= LEITURA =========|");

    String messages[30] = {
        "",
        F("Posicao do Sensor"),
        (String)F("Primeiro: ") + (Data.sensorPosition[0] + 0.11) + F("cm"),
        (String)F("Segundo: ") + (Data.sensorPosition[1] + 0.11) + F("cm"),
        (String)F("Terceiro: ") + (Data.sensorPosition[2] + 0.11) + F("cm"),
        "",
        F("Tempo do Sensor"),
        (String)F("Primeiro: ") + Data.sensorTimestamps[0] + F("ms"),
        (String)F("Segundo: ") + Data.sensorTimestamps[1] + F("ms"),
        (String)F("Terceiro: ") + Data.sensorTimestamps[2] + F("ms"),
        (String)F("Total: ") + Data.sensorTimestamps[3] + F("ms"),
        "",
        F("Variacao de Distancia"),
        (String)F("Primeira: ") + Data.distanceVariation[0] + F("cm"),
        (String)F("Segunda: ") + Data.distanceVariation[1] + F("cm"),
        (String)F("Terceira: ") + Data.distanceVariation[2] + F("cm"),
        (String)F("Total: ") + Data.distanceVariation[3] + F("cm"),
        "",
        F("Intervalo de Tempo"),
        (String)F("Primeiro: ") + Data.timeIntervals[0] + F("ms"),
        (String)F("Segundo: ") + Data.timeIntervals[1] + F("ms"),
        (String)F("Terceiro: ") + Data.timeIntervals[2] + F("ms"),
        (String)F("Total: ") + Data.timeIntervals[3] + F("ms"),
        "",
        F("Velocidade Media"),
        (String)F("Primeira: ") + Data.meanVelocity[0] + F("cm/s"),
        (String)F("Segunda: ") + Data.meanVelocity[1] + F("cm/s"),
        (String)F("Terceira: ") + Data.meanVelocity[2] + F("cm/s"),
        (String)F("Total: ") + Data.meanVelocity[3] + F("cm/s"),
        "",
    };

    Serial.println(_top);
    for (byte line = 0; line < 30; line++) {
      for (byte line_size = 0; line_size < (abs(_top.length() - messages[line].length()) / 2); line_size++) {
        Serial.print(F(" "));
        delay(10);
      }
      Serial.print(messages[line]);
      for (unsigned int line_size = 0; line_size < (abs(_top.length() - messages[line].length()) / 2); line_size++) {
        Serial.print(F(" "));
        delay(10);
      }
      Serial.println(F(""));
      delay(10);
    }
    Serial.print(F("|"));
    for (byte line_size = 0; line_size < _top.length(); line_size++) {
      Serial.print(F("="));
    }
    Serial.print(F("|\n"));
    return;
  }

} Reading;

class Menu {
 public:
  class Options {
   public:
    static const byte _MIN_PREFS = 1;
    static const byte _MAX_PREFS = 3;
    byte _FOCUSED_PREFS;
    byte _SELECTED_PREFS;
    const char *_OPTIONS_LABEL[4] = {
        "",
        "POS SENSOR 1",
        "POS SENSOR 2",
        "POS SENSOR 3"};

    void displayFocusedPref() {
      Display.printCentered((String)_OPTIONS_LABEL[_FOCUSED_PREFS], 0, 0);
      if (_FOCUSED_PREFS == 1) {
        Display.printCentered(String(Reading.Data.sensorPosition[0]), 1, 0);

      } else if (_FOCUSED_PREFS == 2) {
        Display.printCentered(String(Reading.Data.sensorPosition[1]), 1, 0);

      } else if (_FOCUSED_PREFS == 3) {
        Display.printCentered(String(Reading.Data.sensorPosition[2]), 1, 0);
      }
    }

    void displaySelectedPref() {
      Display.printCentered((String)_OPTIONS_LABEL[_FOCUSED_PREFS], 0, 0);
      if (_FOCUSED_PREFS == 1) {
        Display.printCentered(String(Reading.Data.sensorPosition[0]), 1, 0);
        Display.drawChar(Display.selectedMark, (15 - String(Reading.Data.sensorPosition[0]).length()) / 2, 1);

      } else if (_FOCUSED_PREFS == 2) {
        Display.printCentered(String(Reading.Data.sensorPosition[1]), 1, 0);
        Display.drawChar(Display.selectedMark, (15 - String(Reading.Data.sensorPosition[1]).length()) / 2, 1);

      } else if (_FOCUSED_PREFS == 3) {
        Display.printCentered(String(Reading.Data.sensorPosition[2]), 1, 0);
        Display.drawChar(Display.selectedMark, (15 - String(Reading.Data.sensorPosition[2]).length()) / 2, 1);
      }
    }

    void selectPref() {
      _SELECTED_PREFS = _FOCUSED_PREFS;
      displaySelectedPref();
    }

    void increasePrefValue(float inc) {
      if (_FOCUSED_PREFS == 1) {
        if (Reading.Data.sensorPosition[0] < 75) {
          if (Reading.Data.sensorPosition[0] < 20) {
            Reading.Data.sensorPosition[0] = 20;
          } else {
            Reading.Data.sensorPosition[0] += inc;
          }
        } else {
          Reading.Data.sensorPosition[0] = 20;
        }

      } else if (_FOCUSED_PREFS == 2) {
        if (Reading.Data.sensorPosition[1] < 80) {
          if (Reading.Data.sensorPosition[1] < 25) {
            Reading.Data.sensorPosition[1] = 25;
          } else {
            Reading.Data.sensorPosition[1] += inc;
          }
        } else {
          Reading.Data.sensorPosition[1] = 25;
        }

      } else if (_FOCUSED_PREFS == 3) {
        if (Reading.Data.sensorPosition[2] < 85) {
          if (Reading.Data.sensorPosition[2] < 30) {
            Reading.Data.sensorPosition[2] = 30;
          } else {
            Reading.Data.sensorPosition[2] += inc;
          }
        } else {
          Reading.Data.sensorPosition[2] = 30;
        }
      }
      displaySelectedPref();
    }

    void decreasePrefValue(float dec) {
      if (_FOCUSED_PREFS == 1) {
        if ((Reading.Data.sensorPosition[0] -= dec) < 20) {
          Reading.Data.sensorPosition[0] = 75;
        } else {
          Reading.Data.sensorPosition[0] -= dec;
        }
      } else if (_FOCUSED_PREFS == 2) {
        if ((Reading.Data.sensorPosition[1] -= dec) < 25) {
          Reading.Data.sensorPosition[1] = 80;
        } else {
          Reading.Data.sensorPosition[1] -= dec;
        }

      } else if (_FOCUSED_PREFS == 3) {
        if ((Reading.Data.sensorPosition[2] -= dec) < 30) {
          Reading.Data.sensorPosition[2] = 85;
        } else {
          Reading.Data.sensorPosition[2] -= dec;
        }
      }
      displaySelectedPref();
    }

    void focusNextPrefs() {
      if (_FOCUSED_PREFS < _MAX_PREFS) {
        _FOCUSED_PREFS++;
        displayFocusedPref();
      }
    }

    void focusPrevPrefs() {
      if (_FOCUSED_PREFS > _MIN_PREFS) {
        _FOCUSED_PREFS--;
        displayFocusedPref();
      }
    }

  } Options;

  class DisplayPage {
   private:
   public:
    static const byte _STANDBY = 0;
    static const byte _MIN_PAGE = 1;
    static const byte _MAX_PAGE = 5;
    static const byte _MIN_SUBPAGE = 0;
    static const byte _MAX_SUBPAGE = 1;
    byte _SELECTED_PAGE;
    byte _FOCUSED_PAGE;
    byte _FOCUSED_SUBPAGE;

    const char *_PAGE_LABELS[7][2] = {
        {},
        {"POSICAO DO", "SENSOR (CM)"},
        {"TEMPO DO", "SENSOR (MS)"},
        {"VARIACAO DE", "DISTANCIA (CM)"},
        {"INTERVALO DE", "TEMPO (MS)"},
        {"VELOCIDADE", "MEDIA (CM/S)"}};

    void displayFocusedPage() {
      Display.printCentered(_PAGE_LABELS[_FOCUSED_PAGE][0], 0, 0);
      Display.printCentered(_PAGE_LABELS[_FOCUSED_PAGE][1], 1, 0);
    }

    void displayFocusedSubpage() {
      _SELECTED_PAGE = _FOCUSED_PAGE;
      String _SUB_PAGE_LABEL[7][4] = {
          {},
          {(String) "POS1 " + (Reading.Data.sensorPosition[0] + 0.11),
           (String) "POS2 " + (Reading.Data.sensorPosition[1] + 0.11),
           (String) "POS3 " + (Reading.Data.sensorPosition[2] + 0.11),
           (String) "NO SENSOR"},

          {(String) "TS1 " + Reading.Data.sensorTimestamps[0],
           (String) "TS2 " + Reading.Data.sensorTimestamps[1],
           (String) "TS3 " + Reading.Data.sensorTimestamps[2],
           (String) "TS4 " + Reading.Data.sensorTimestamps[3]},

          {(String) "VD1: " + Reading.Data.distanceVariation[0],
           (String) "VD2: " + Reading.Data.distanceVariation[1],
           (String) "VD3: " + Reading.Data.distanceVariation[2],
           (String) "VD4: " + Reading.Data.distanceVariation[3]},

          {(String) "IT1 " + Reading.Data.timeIntervals[0],
           (String) "IT2 " + Reading.Data.timeIntervals[1],
           (String) "IT3 " + Reading.Data.timeIntervals[2],
           (String) "IT4 " + Reading.Data.timeIntervals[3]},

          {(String) "VM1 " + Reading.Data.meanVelocity[0],
           (String) "VM2 " + Reading.Data.meanVelocity[1],
           (String) "VM3 " + Reading.Data.meanVelocity[2],
           (String) "VM4 " + Reading.Data.meanVelocity[3]}};

      if (_FOCUSED_SUBPAGE == _MIN_SUBPAGE) {
        Display.printCentered(_SUB_PAGE_LABEL[_SELECTED_PAGE][0], 0, 0);
        Display.printCentered(_SUB_PAGE_LABEL[_SELECTED_PAGE][1], 1, 0);
      } else if (_FOCUSED_SUBPAGE == _MAX_SUBPAGE) {
        Display.printCentered(_SUB_PAGE_LABEL[_SELECTED_PAGE][2], 0, 0);
        Display.printCentered(_SUB_PAGE_LABEL[_SELECTED_PAGE][3], 1, 0);
      }
    }

    void focusNextSubpage() {
      if (_FOCUSED_SUBPAGE < _MAX_SUBPAGE) {
        _FOCUSED_SUBPAGE++;
      }
      displayFocusedSubpage();
    }

    void focusPrevSubpage() {
      if (_FOCUSED_SUBPAGE > _MIN_SUBPAGE) {
        _FOCUSED_SUBPAGE--;
      }
      displayFocusedSubpage();
    }

    void focusNextPage() {
      if (_FOCUSED_PAGE < _MAX_PAGE) {
        _FOCUSED_PAGE++;
      }
      displayFocusedPage();
    }

    void focusPrevPage() {
      if (_FOCUSED_PAGE > _MIN_PAGE) {
        _FOCUSED_PAGE--;
      }
      displayFocusedPage();
    }
  } DisplayPage;

  static const byte _STANDBY = 0;
  static const byte _READ = 1;
  static const byte _PREFERENCES = 2;
  static const byte _DISPLAY = 3;
  static const byte _MIN_MENU = 1;
  static const byte _MAX_MENU = 3;

  byte _FOCUSED_MENU;
  byte _SELECTED_MENU;
  const char *_MENUS_LABELS[4][2] = {{}, {"INICIAR NOVA", "LEITURA"}, {"POSICIONAMENTO", "DOS SENSORES"}, {"EXIBIR DADOS", "DA LEITURA"}};
  long switcherTime;

  void displayFocusedMenu() {
    Display.printCentered(_MENUS_LABELS[_FOCUSED_MENU][0], 0, 0);
    Display.printCentered(_MENUS_LABELS[_FOCUSED_MENU][1], 1, 0);
    switcherTime = millis();
  }

  void switchFocusedMenus() {
    if (_FOCUSED_MENU < _MAX_MENU) {
      _FOCUSED_MENU++;
    } else if (_FOCUSED_MENU == _MAX_MENU) {
      _FOCUSED_MENU = _MIN_MENU;
    }
    displayFocusedMenu();
  }

  void selectMenu() {
    switch (_FOCUSED_MENU) {
      case _READ:
        Reading.read();
        break;
      case _DISPLAY:
        _SELECTED_MENU = _DISPLAY;
        DisplayPage._FOCUSED_PAGE = DisplayPage._MIN_PAGE;
        DisplayPage.displayFocusedPage();
        if (Serial) {
          Reading.display();
        }
        break;
      case _PREFERENCES:
        _SELECTED_MENU = _PREFERENCES;
        Options._FOCUSED_PREFS = Options._MIN_PREFS;
        Options.displayFocusedPref();

        break;
    }
  }

  long messageTimer = millis();
  byte messageIndex = 0;

  void loop() {
    if (_FOCUSED_MENU == _STANDBY) {
      if ((millis() - messageTimer) > 1900) {
        if (messageIndex == 0) {
          Display.printCentered(F("USE SELECT"), 0, 0);
          Display.printCentered(F("PARA NAVEGACAO"), 1, 0);
          messageTimer = millis();
          messageIndex++;
        }
      }
      if (millis() - messageTimer > 2900) {
        if (messageIndex == 1) {
          Display.printCentered(F("USE RIGHT"), 0, 0);
          Display.printCentered(F("PARA SELECAO"), 1, 0);
          messageTimer = millis();
          messageIndex = 0;
        }
      }
    }

    if (KeypadButtons.Pressed() == KeypadButtons.Select) {
      // Navegacao principal entre os menus
      if (_SELECTED_MENU == _STANDBY) {
        switchFocusedMenus();
        delay(250);
      }

      // Voltar para escolha de menus apos somente focar em uma preferencia
      else if (_SELECTED_MENU == _PREFERENCES && Options._SELECTED_PREFS == _STANDBY) {
        Options._FOCUSED_PREFS = _STANDBY;
        _SELECTED_MENU = _STANDBY;
        displayFocusedMenu();
        delay(250);
      }

      // Voltar para escolha de menus apos somente focar em uma pagina da exibicao
      else if (_SELECTED_MENU == _DISPLAY && DisplayPage._SELECTED_PAGE == _STANDBY) {
        DisplayPage._FOCUSED_PAGE = _STANDBY;
        _SELECTED_MENU = _STANDBY;
        displayFocusedMenu();
        delay(250);
      }

      // Diminui o valor decimal de uma preferencia expecifica
      else if (_SELECTED_MENU == _PREFERENCES && Options._SELECTED_PREFS != _STANDBY) {
        Options.decreasePrefValue(0.01);
        delay(250);
      }
    } else if (KeypadButtons.Pressed() == KeypadButtons.Right) {
      // Escolha de um menu especifico durante a navegacao entre os menus
      if (_SELECTED_MENU == _STANDBY && _FOCUSED_MENU != _STANDBY) {
        selectMenu();
        delay(250);
      }

      // Escolha de uma preferencia
      else if (_SELECTED_MENU == _PREFERENCES && Options._FOCUSED_PREFS != _STANDBY && Options._SELECTED_PREFS == _STANDBY) {
        Options.selectPref();
        delay(250);
      }

      // Escolha de uma pagina
      else if (_SELECTED_MENU == _DISPLAY && DisplayPage._FOCUSED_PAGE != _STANDBY && DisplayPage._SELECTED_PAGE == _STANDBY) {
        DisplayPage.displayFocusedSubpage();
        delay(250);
      }

      // Voltar para a escolha de preferencias
      else if (_SELECTED_MENU == _PREFERENCES && Options._SELECTED_PREFS != _STANDBY) {
        Options._SELECTED_PREFS = _STANDBY;
        Options.displayFocusedPref();
        delay(250);
      }
      // Voltar para a escolha de paginas
      else if (_SELECTED_MENU == _DISPLAY && DisplayPage._SELECTED_PAGE != _STANDBY) {
        DisplayPage._SELECTED_PAGE = _STANDBY;
        DisplayPage._FOCUSED_SUBPAGE = _STANDBY;
        DisplayPage.displayFocusedPage();
        delay(250);
      }
    } else if (KeypadButtons.Pressed() == KeypadButtons.Up) {
      // Foca na preferencia anterior somente se estiver no menu de preferencias e nenhuma for selecionada
      if (_SELECTED_MENU == _PREFERENCES && Options._SELECTED_PREFS == _STANDBY) {
        Options.focusPrevPrefs();
        delay(250);
      }

      // Aumenta o valor inteiro de uma preferencia
      else if (_SELECTED_MENU == _PREFERENCES && Options._SELECTED_PREFS != _STANDBY) {
        Options.increasePrefValue(1.00);
        delay(90);
      }

      // Focaliza na pagina anterior
      if (_SELECTED_MENU == _DISPLAY && DisplayPage._SELECTED_PAGE == _STANDBY) {
        DisplayPage.focusPrevPage();
        delay(250);
      }

      // Exibe a subpagina anterior na pagina atual
      if (_SELECTED_MENU == _DISPLAY && DisplayPage._SELECTED_PAGE != _STANDBY) {
        DisplayPage.focusPrevSubpage();
        delay(250);
      }
    } else if (KeypadButtons.Pressed() == KeypadButtons.Down) {
      // Focaliza na proxima preferencia
      if (_SELECTED_MENU == _PREFERENCES && Options._SELECTED_PREFS == _STANDBY) {
        Options.focusNextPrefs();
        delay(250);
      }

      // Diminui o valor inteiro de uma preferencia expecifica
      else if (_SELECTED_MENU == _PREFERENCES && Options._SELECTED_PREFS != _STANDBY) {
        Options.decreasePrefValue(1.00);
        delay(90);
      }

      // Focaliza na proxima pagina
      if (_SELECTED_MENU == _DISPLAY && DisplayPage._SELECTED_PAGE == _STANDBY) {
        DisplayPage.focusNextPage();
        delay(250);
      }

      // Exibe a proxima subpagina da pagina atual
      if (_SELECTED_MENU == _DISPLAY && DisplayPage._SELECTED_PAGE != _STANDBY) {
        DisplayPage.focusNextSubpage();
        delay(250);
      }
    } else if (KeypadButtons.Pressed() == KeypadButtons.Left) {
      // Aumenta a valor decimal de uma preferencia expecifica
      if (_SELECTED_MENU == _PREFERENCES && Options._SELECTED_PREFS != _STANDBY) {
        Options.increasePrefValue(0.01);
        delay(180);
      }
    }

    if (uint16_t(millis()) > uint16_t(switcherTime + 10000) and _SELECTED_MENU == _STANDBY) {
      _FOCUSED_MENU = _STANDBY;
      switcherTime = millis();
    }
  }
} Menu;

// cppcheck-suppress unusedFunction
void setup() {
  pinMode(FIRST_IR_SENSOR_PIN, INPUT);
  pinMode(SECOND_IR_SENSOR_PIN, INPUT);
  pinMode(THIRD_IR_SENSOR_PIN, INPUT);

  Display.begin(16, 2);
  Serial.begin(115200);

  while (!Serial) {
    delay(250);
  }

  ReleaseGate.begin(RELEASE_GATE_PIN);
  Properties.begin();
}

// cppcheck-suppress unusedFunction
void loop() {
  Menu.loop();
}
