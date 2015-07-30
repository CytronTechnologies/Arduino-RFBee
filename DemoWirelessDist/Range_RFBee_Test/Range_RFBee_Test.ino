    /*  This Coding for master node to test the wireless communication distance for 
        RFBee, both 433MHz and 434MHz, outdoor and indoor.
    */
    
    #include <LiquidCrystal.h>   // include the library code:
    
    LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // initialize the library with the numbers of the interface pins

    void setup()
    {
      Serial.begin(9600);      // initialize the serial communications:
      lcd.begin(16, 2);     // set up the LCD's number of columns and rows: 
    }
    
    void loop()
    {
      for(int i = 0 ; i<=255 ; i++)    // count i in one byte
      {
Serial.write(i);                          // Serial write one byte of data
             delay(100);
        {
          if (Serial.available())        // when characters arrive over the serial port...
            {    
             delay(100);                            // wait a bit for the entire message to arrive
             while (Serial.available() > 0)             // read all the available characters
              {    
                if (Serial.read() == i)     // is byte that send is same as receive from slave node
                {   
                  lcd.clear();       // clear the screen
                  lcd.setCursor(0, 0);
                  lcd.print("GOT SAME DATA "); 
                  delay(1000);  
                }
              
            else
              {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("MIXED DATA ");  // the byte receive to master node could mixed with other bytes
                delay(1000);
               }
             }
           }
            
            else
             {
              lcd.clear();
              lcd.setCursor(0, 1);
              lcd.print("DATA LOST ");  // lost of byte or connection
              delay(1000);
            }
          }
        }
      }
