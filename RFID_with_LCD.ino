/*
 * MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
 * Released into the public domain.
 *
 * Sample program showing how to read data from a PICC using a MFRC522 reader on the Arduino SPI interface.
 *----------------------------------------------------------------------------- empty_skull 
 * Aggiunti pin per arduino Mega
 * add pin configuration for arduino mega
 * http://mac86project.altervista.org/
 ----------------------------------------------------------------------------- Nicola Coppola
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin
 *            Arduino Uno      Arduino Mega      MFRC522 board
 * ------------------------------------------------------------
 * Reset      9                5                 RST
 * SPI SS     10               53                SDA
 * SPI MOSI   11               52                MOSI
 * SPI MISO   12               51                MISO
 * SPI SCK    13               50                SCK
 * SPI VCC    3.3vø
 * SPI GND    GND
 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com. 
 * ===============================================================
 * ========================= LCD ================================
 * To wire your LCD screen to your Arduino, connect the following pins:
 * LCD 1  ->  GND
 * LCD 2  ->  5V
 * LCD 3  ->  center pin of potentiometer
 * LCD 4  ->  digital pin 7
 * LCD 5  ->  GND
 * LCD 6  ->  digital pin 6
 * LCD 11 ->  digital pin 5
 * LCD 12 ->  digital pin 4
 * LCD 13 ->  digital pin 3
 * LCD 14 ->  digital pin 2
 * LCD 15 ->  connect power through 220-phm resistor
 * LCD 16 ->  GND
 */

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance.
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
	Serial.begin(9600);	// Initialize serial communications with the PC
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();	// Init MFRC522 card
        lcd.begin(16,2);
        lcd.print("Please scan..");
	Serial.println("Scan PICC to see UID and type...");
}

void loop() {
  
	// Look for new cards

	if ( ! mfrc522.PICC_IsNewCardPresent()) {
                
                lcd.clear();
                lcd.print("Please scan..");
                delay(500);
                lcd.setCursor(0,1);
                lcd.print("Your Card or Key");
                delay(500);
                
                
		return;//go to start of loop if there is no card present
	}

        
	//Select one of the cards
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;//if ReadCardSerial returns 1, the "uid" struct (see MFRC522.h lines 238-45)) contains the ID of the read card.
	}
        
	// Dump debug info about the card. PICC_HaltA() is automatically called.
	//mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

        
        // to convert uid of the device into a string
        String rfidUid = "";

        for (byte i = 0; i < mfrc522.uid.size; i++) {
          rfidUid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
          rfidUid += String(mfrc522.uid.uidByte[i], HEX);
        }

        // Tag
        if(rfidUid == "939a6f9a"){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Hello Mr.Pax!!");
          lcd.setCursor(0,1);
          lcd.print("Have a Nice Day");
        }
        // Card
        else if(rfidUid == "15aa55b3"){
          for(int i = 0; i < 5; i++){
            lcd.clear();
            delay(50);
            lcd.setCursor(0,0);
            lcd.print("HACKER ALERT!!");
            delay(250);
          }
        }
          
        //Serial.println("Hello Sam!!!!");
        //Serial.println("How are you today?!!");
        //Serial.println("Enjoy......");

        delay(2500); 
}


