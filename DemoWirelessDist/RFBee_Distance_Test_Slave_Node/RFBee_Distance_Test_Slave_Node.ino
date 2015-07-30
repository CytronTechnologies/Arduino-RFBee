        
        
        /*  
        This coding for slave node of wireless communication distance for RFBee, both 433MHz and 434MHz, outdoor and indoor.
        */
        void setup(){
          // initialize the serial communications:
          Serial.begin(9600);
        }
        
        void loop()
        {
          // when characters arrive over the serial port...
          if (Serial.available()) {
              // display each character to the LCD
              lcd.write(Serial.read());
            }
          }
        }
