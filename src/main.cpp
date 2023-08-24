#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal LiquidCrystal(8, 9, 4, 5, 6, 7);
Servo Servo;

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
  static const byte selectedMark = 7;
  static const byte brackets = 8;
  static const byte box = 9;

  void begin(byte lcd_columns, byte lcd_lines) {
    byte charTopLine[8] = {B11111, B00000, B00000, B00000, B00000, B00000, B00000, B00000};
    byte charBottomLine[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B11111};
    byte charLeftTopBracket[8] = {B01111, B10000, B10000, B10000, B10000, B10000, B10000, B10000};
    byte charRightTopBracket[8] = {B11110, B00001, B00001, B00001, B00001, B00001, B00001, B00001};
    byte charLeftBottomBracket[8] = {B10000, B10000, B10000, B10000, B10000, B10000, B10000, B01111};
    byte charRightBottomBracket[8] = {B00001, B00001, B00001, B00001, B00001, B00001, B00001, B11110};
    byte charSelectedMark[8] = { B00000, B01000, B01100, B01110, B01110, B01100, B01000, B00000};

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
  const byte maxReading = 10;
  byte currentReading;

  float sensorPosition[10][2];
  float sensorTimestamps[10][3];
  float timeIntervals[10][3];
  float meanVelocity[10][3];
  float distanceVariation[10][3];

  void increaseReading() {
    if (currentReading < maxReading) {
      currentReading++;
    } else if (currentReading == maxReading) {
      currentReading = 0;
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

      ReleaseGate.open();
      Data.sensorTimestamps[Data.currentReading][0] = millis();
      Serial.println(F("\nMedidorVMM :: Objeto liberado."));

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

                  Serial.println(F("\nMedidorVMM :: INICIANDO CALCULO DOS DADOS.\n"));

                  Serial.println(F("MedidorVMM :: CALCULANDO VARIAÇÃO DE ESPAÇO.\n"));
                  Data.distanceVariation[Data.currentReading][0] = (Data.sensorPosition[Data.currentReading][0]); // S1 - LG
                  Data.distanceVariation[Data.currentReading][1] = abs(Data.sensorPosition[Data.currentReading][1] - Data.sensorPosition[Data.currentReading][0]); // S2 - S1
                  Data.distanceVariation[Data.currentReading][2] = abs(Data.sensorPosition[Data.currentReading][2] - Data.sensorPosition[Data.currentReading][1]); // S3 - S2
                  Data.distanceVariation[Data.currentReading][3] = abs(Data.sensorPosition[Data.currentReading][2]); // S3 - LG

                  Serial.println(F("MedidorVMM :: CALCULADO VARIAÇÃO DE TEMPO."));
                  Data.timeIntervals[Data.currentReading][0] = abs(Data.sensorTimestamps[Data.currentReading][1] - Data.sensorTimestamps[Data.currentReading][0]); // S1 - LG
                  Data.timeIntervals[Data.currentReading][1] = abs(Data.sensorTimestamps[Data.currentReading][2] - Data.sensorTimestamps[Data.currentReading][1]); // S2 - S1
                  Data.timeIntervals[Data.currentReading][2] = abs(Data.sensorTimestamps[Data.currentReading][3] - Data.sensorTimestamps[Data.currentReading][2]); // S3 - S2
                  Data.timeIntervals[Data.currentReading][3] = abs(Data.sensorTimestamps[Data.currentReading][3] - Data.sensorTimestamps[Data.currentReading][0]); // S3 - LG
                  
                  Serial.println(F("MedidorVMM :: CALCULANDO VELOCIDADE MÉDIA."));
                  Data.meanVelocity[Data.currentReading][0] = (Data.distanceVariation[Data.currentReading][0] / (Data.timeIntervals[Data.currentReading][0] / 1000)); // S1 - LG
                  Data.meanVelocity[Data.currentReading][1] = (Data.distanceVariation[Data.currentReading][1] / (Data.timeIntervals[Data.currentReading][1] / 1000)); // S2 - S1
                  Data.meanVelocity[Data.currentReading][2] = (Data.distanceVariation[Data.currentReading][2] / (Data.timeIntervals[Data.currentReading][2] / 1000)); // S3 - S2
                  Data.meanVelocity[Data.currentReading][3] = (Data.distanceVariation[Data.currentReading][3] / (Data.timeIntervals[Data.currentReading][3] / 1000)); // S3 - LG
                  
                  Serial.println(F("MedidorVMM :: DADOS PROCESSADOS E CALCULADOS."));
                  Serial.println(F("MedidorVMM :: PROCESSAMENTO COMPLETO.\n"));
                  Display.printCentered(F("LEITURA"), 0, 0);
                  Display.printCentered(F("COMPLETA."), 1, 0);
                  Data.increaseReading();
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
  String _top = (String)F("|======= LEITURA =======|");

  String messages[17] = {
    F("Variação de Distancia"),
    (String)F("Primeira: ") + Data.distanceVariation[Data.currentReading - 1][0] + F("cm"),
    (String)F("Segunda: ") + Data.distanceVariation[Data.currentReading - 1][1] + F("cm"),
    (String)F("Terceira: ") + Data.distanceVariation[Data.currentReading - 1][2] + F("cm"),
    (String)F("Total: ") + Data.distanceVariation[Data.currentReading - 1][3] + F("cm"),
    "",
    F("Intervalo de Tempo"),
    (String)F("Primeiro: ") + Data.timeIntervals[Data.currentReading - 1][0] + F("ms"),
    (String)F("Segundo: ") + Data.timeIntervals[Data.currentReading - 1][1] + F("ms"),
    (String)F("Terceiro: ") + Data.timeIntervals[Data.currentReading - 1][2] + F("ms"),
    (String)F("Total: ") + Data.timeIntervals[Data.currentReading - 1][3] + F("ms"),
    "",
    F("Velocidade Média"),
    (String)F("Primeira: ") + Data.meanVelocity[Data.currentReading - 1][0] + F("cm/ms"),
    (String)F("Segunda: ") + Data.meanVelocity[Data.currentReading - 1][1] + F("cm/ms"),
    (String)F("Terceira: ") + Data.meanVelocity[Data.currentReading - 1][2] + F("cm/ms"),
    (String)F("Total: ") + Data.meanVelocity[Data.currentReading - 1][3] + F("cm/ms"),
  };

  Serial.println(_top);
  for (byte line = 0; line < 16; line++) {
    for(byte line_size = 0; line_size < (abs(_top.length() - messages[line].length()) / 2); line_size++){
      Serial.print(F(" ")); 
      delay(10);
    }
    Serial.print(messages[line]);
    for(unsigned int line_size = 0; line_size < (abs(_top.length() - messages[line].length()) / 2); line_size++){
      Serial.print(F(" ")); 
      delay(10);
    }
    Serial.println(F(""));
    delay(10);  
  }
  Serial.print(F("|"));
  for(byte line_size = 0; line_size < _top.length(); line_size++){
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
        Display.printCentered(String(Reading.Data.sensorPosition[Reading.Data.currentReading][0]), 1, 0);

      } else if (_FOCUSED_PREFS == 2) {
        Display.printCentered(String(Reading.Data.sensorPosition[Reading.Data.currentReading][1]), 1, 0);
     
      } else if (_FOCUSED_PREFS == 3) {
        Display.printCentered(String(Reading.Data.sensorPosition[Reading.Data.currentReading][2]), 1, 0);
      }
    }

    void displaySelectedPref() {
      Display.printCentered((String)_OPTIONS_LABEL[_FOCUSED_PREFS], 0, 0);
      if (_FOCUSED_PREFS == 1) {
        Display.printCentered(String(Reading.Data.sensorPosition[Reading.Data.currentReading][0]), 1, 0);
        Display.drawChar(Display.selectedMark, (15 - String(Reading.Data.sensorPosition[Reading.Data.currentReading][0]).length()) / 2, 1);

      } else if (_FOCUSED_PREFS == 2) {
        Display.printCentered(String(Reading.Data.sensorPosition[Reading.Data.currentReading][1]), 1, 0);
        Display.drawChar(Display.selectedMark, (15 - String(Reading.Data.sensorPosition[Reading.Data.currentReading][1]).length()) / 2, 1);
      
      } else if (_FOCUSED_PREFS == 3) {
        Display.printCentered(String(Reading.Data.sensorPosition[Reading.Data.currentReading][2]), 1, 0);
        Display.drawChar(Display.selectedMark, (15 - String(Reading.Data.sensorPosition[Reading.Data.currentReading][2]).length()) / 2, 1);
      }
    }

    void selectPref() {
      _SELECTED_PREFS = _FOCUSED_PREFS;
      displaySelectedPref();
    }

    void increasePrefValue(float inc) {
      if (_FOCUSED_PREFS == 1) {
        if (Reading.Data.sensorPosition[Reading.Data.currentReading][0] < 190) {
          Reading.Data.sensorPosition[Reading.Data.currentReading][0] += inc;
        } else {
          Reading.Data.sensorPosition[Reading.Data.currentReading][0] = 10;
        }
      
      } else if (_FOCUSED_PREFS == 2) {
        if (Reading.Data.sensorPosition[Reading.Data.currentReading][1] < 190) {
          Reading.Data.sensorPosition[Reading.Data.currentReading][1] += inc;
        } else {
          Reading.Data.sensorPosition[Reading.Data.currentReading][1] = 20;
        }
      
      } else if (_FOCUSED_PREFS == 3) {
        if (Reading.Data.sensorPosition[Reading.Data.currentReading][2] < 190) {
          Reading.Data.sensorPosition[Reading.Data.currentReading][2] += inc;
        } else {
          Reading.Data.sensorPosition[Reading.Data.currentReading][2] = 60;
        }
      }
      displaySelectedPref();
    }

    void decreasePrefValue(float dec) {
      if (_FOCUSED_PREFS == 1) {
        if (Reading.Data.sensorPosition[Reading.Data.currentReading][0] > 0) {
          Reading.Data.sensorPosition[Reading.Data.currentReading][0] -= dec;
        } else {
          Reading.Data.sensorPosition[Reading.Data.currentReading][0] = 190;
        }
      
      } else if (_FOCUSED_PREFS == 2) {
        if (Reading.Data.sensorPosition[Reading.Data.currentReading][1] > 0) {
          Reading.Data.sensorPosition[Reading.Data.currentReading][1] -= dec;
        } else {
          Reading.Data.sensorPosition[Reading.Data.currentReading][1] = 190;
        }
      
      } else if (_FOCUSED_PREFS == 3) {
        if (Reading.Data.sensorPosition[Reading.Data.currentReading][2] > 0) {
          Reading.Data.sensorPosition[Reading.Data.currentReading][2] -= dec;
        } else {
          Reading.Data.sensorPosition[Reading.Data.currentReading][2] = 190;
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
      static const byte _MAX_PAGE = 3;
      static const byte _MIN_SUBPAGE = 0;
      static const byte _MAX_SUBPAGE = 1;
      byte _SELECTED_PAGE;
      byte _FOCUSED_PAGE;
      byte _FOCUSED_SUBPAGE;

      const char *_PAGE_LABELS[4][2] = {
        {},
        {"VARIACAO DE", "DISTANCIA (CM)"},
        {"INTERVALO DE", "TEMPO (MS)"},
        {"VELOCIDADE", "MEDIA (CM/S)"}
      };

      void displayFocusedPage() {
        Display.printCentered(_PAGE_LABELS[_FOCUSED_PAGE][0], 0, 0);
        Display.printCentered(_PAGE_LABELS[_FOCUSED_PAGE][1], 1, 0);
      }

      void displayFocusedSubpage() {
        _SELECTED_PAGE = _FOCUSED_PAGE;
        String _SUB_PAGE_LABEL[5][4] = {
          {},
          {
            (String)"V1: " + Reading.Data.distanceVariation[Reading.Data.currentReading - 1][0],
            (String)"V2: " + Reading.Data.distanceVariation[Reading.Data.currentReading - 1][1],
            (String)"V3: " + Reading.Data.distanceVariation[Reading.Data.currentReading - 1][2],
            (String)"V4: " + Reading.Data.distanceVariation[Reading.Data.currentReading - 1][3] },
          {
            (String)"I1 " + Reading.Data.timeIntervals[Reading.Data.currentReading - 1][0],
            (String)"I2 " + Reading.Data.timeIntervals[Reading.Data.currentReading - 1][1],
            (String)"I3 " + Reading.Data.timeIntervals[Reading.Data.currentReading - 1][2],
            (String)"I4 " + Reading.Data.timeIntervals[Reading.Data.currentReading - 1][3]
          },
          {
            (String)"V1 " + Reading.Data.meanVelocity[Reading.Data.currentReading - 1][0],
            (String)"V2 " + Reading.Data.meanVelocity[Reading.Data.currentReading - 1][1],
            (String)"V3 " + Reading.Data.meanVelocity[Reading.Data.currentReading - 1][2],
            (String)"V4 " + Reading.Data.meanVelocity[Reading.Data.currentReading - 1][3]
          }
        };
        if(_FOCUSED_SUBPAGE == _MIN_SUBPAGE) {
          Display.printCentered(_SUB_PAGE_LABEL[_SELECTED_PAGE][0], 0, 0);
          Display.printCentered(_SUB_PAGE_LABEL[_SELECTED_PAGE][1], 1, 0);
        } else if(_FOCUSED_SUBPAGE == _MAX_SUBPAGE){
          Display.printCentered(_SUB_PAGE_LABEL[_SELECTED_PAGE][2], 0, 0);
          Display.printCentered(_SUB_PAGE_LABEL[_SELECTED_PAGE][3], 1, 0);            
        }      }

      void focusNextSubpage() {
        if(_FOCUSED_SUBPAGE < _MAX_SUBPAGE){
            _FOCUSED_SUBPAGE++;
        }
        displayFocusedSubpage();
      }

      void focusPrevSubpage() {
        if(_FOCUSED_SUBPAGE > _MIN_SUBPAGE){
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
  const char *_MENUS_LABELS[4][2] = {{}, {"INICIAR NOVA", "LEITURA"}, {"ALTERAR", "CONFIGS"}, {"EXIBIR DADOS", "DA LEITURA"}};
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
        // Reading.display();
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

      // Aumenta a valor decimal de uma preferencia expecifica
      else if (_SELECTED_MENU == _PREFERENCES && Options._SELECTED_PREFS != _STANDBY) {
        Options.increasePrefValue(0.01);
        delay(250);
      } 

      // Exibe a subpagina anterior na pagina atual
      else if (_SELECTED_MENU == _DISPLAY && DisplayPage._SELECTED_PAGE != _STANDBY) {
        DisplayPage.focusPrevSubpage();
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
    }  else if (KeypadButtons.Pressed() == KeypadButtons.Left) {
      // Diminui o valor decimal de uma preferencia expecifica
      if (_SELECTED_MENU == _PREFERENCES && Options._SELECTED_PREFS != _STANDBY) {
        Options.decreasePrefValue(0.01);
        delay(180);
      }

      // Exibe a proxima subpagina da pagina atual
      else if (_SELECTED_MENU == _DISPLAY && DisplayPage._SELECTED_PAGE != _STANDBY) {
        DisplayPage.focusNextSubpage();
        delay(250);
      }
    }

    if (millis() > (switcherTime + 10000) and _SELECTED_MENU == _STANDBY) {
      _FOCUSED_MENU = _STANDBY;
      switcherTime = millis();
    }
  }
} Menu;

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
  // Properties.begin();
}
void loop() {
  Menu.loop();
}

/*

fix: the next, current and prev reading problem between display and reading
fix: memory overloading 
feat: switch between saved reads
fix: warnings during compilation
*/
