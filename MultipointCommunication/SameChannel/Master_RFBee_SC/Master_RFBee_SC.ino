        /* 
        This sketch for master node of wireless communication between 
        RFBee module using same channel to communicate each other
        */
                
        // include the library code:
        #include <LiquidCrystal.h>
        // initialize the library with the numbers of the interface pins
        LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
        
        void setup()
        {
         // set up the LCD's number of columns and rows: 
          lcd.begin(16, 2);
         // initialize the serial communications:
          Serial.begin(9600);
        }
        
        void loop()
        {
        Serial.print("T");
        delay(200);
        {
          // when characters arrive over the serial port...
          if (Serial.available()) {
            // wait a bit for the entire message to arrive
            delay(100);
            // clear the screen
            lcd.clear();
            while (Serial.available() > 0) {
              // display each character to the LCD
              lcd.write(Serial.read());
            }
           delay(1000);
          }
           
           else 
           {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Temp A: ");
            lcd.setCursor(0,1);
            lcd.print("NO REPLY");
            Serial.println("Temp A : NO REPLY !!");
            delay(1000);
            }
          }
       }
