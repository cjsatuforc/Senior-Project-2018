#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SD.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

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
  Serial.print("Initializing SD card...");
  if (!SD.begin(53)) {
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
    Serial.println(53);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
    Serial.println(declaration);
    Serial.println(dataString);
    Serial.println(seperator);
}
