#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SD.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
const static unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

const int POSFORCE = 0;
const int NEGFORCE = 1;
const String standardSpaces = "                                 ";
const String declaration = "Positive                          Negative                         Netforce";
const String seperator = "------------------------------------------------------------------------------";

void setup() {
  
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display(); // show splashscreen
  delay(1000);
  display.clearDisplay();   // clears the screen and buffer
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Sen. Proj. 2018");
  display.display();
  while (!Serial) {
     // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("Card failed, or not present");
  } else {
    Serial.println("card initialized.");
  }
  delay(3000);
}

void loop() {

  String dataString = "";

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(5);

  int POS = analogRead(POSFORCE);
  int NEG = analogRead(NEGFORCE) * -1;
  int NETFORCE = POS + NEG;

  display.print(NETFORCE);
  display.display();
  delay(50);

  dataString = POS + standardSpaces + NEG + standardSpaces + NETFORCE;

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(declaration);
    dataFile.println(dataString);
    dataFile.println(seperator);
    dataFile.close();
    // print to the serial port too:
    Serial.println(4);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
    Serial.println(declaration);
    Serial.println(dataString);
    Serial.println(seperator);

  // Serial.print(analogRead(NETFORCE), "/n/n");
  // Serial.print(analogRead(NEGFORCE), "/n/n");
  // Serial.println(analogRead(POSFORCE));
}
