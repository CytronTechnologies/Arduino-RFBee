    
    /* This sketch for Master node that modified of wireless communication between 
       RFBee module using Different channel to communicate with slave node */
    
    #include <LiquidCrystal.h> // include the library code:
    LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // initialize the library with the numbers of the interface pins
    int PIN = 12;      
    
    void setup()
    {     
      pinMode(PIN, OUTPUT);  // initialize the PIN as an output:
      Serial.begin(9600);              // 9600 baud rate
      lcd.begin(16, 2);      // set up the LCD's number of columns and rows: 
    }
    
    void loop()
    {
      digitalWrite(PIN, LOW);      // turn the PIN off by making the voltage LOW
      delay(200);
      Serial.println("AT+C007");       // Give command to set channel of RFBee module to C002
      delay(200);
      filter_feedback();          // to filter the feedback of the command that given(example, OK+C001)
      digitalWrite(PIN,HIGH );  // turn the PIN on (HIGH is the voltage level)
      delay(200);
      get_temp();                 // Read and write temperature value on LCD shield
      digitalWrite(PIN, LOW);    // turn the PIN off by making the voltage LOW
      delay(200);
      Serial.println("AT+C009");       // Give command to set channel of RFBee module to C001
      delay(200);
      filter_feedback();
      digitalWrite(PIN,HIGH );   // turn the PIN on (HIGH is the voltage level)
      delay(200);
      get_temp_B();                 // Read and write temperature value on LCD shield
      delay(200);
    }
    
    void filter_feedback()        //  // to filter the feedback of the command that given(example, OK+C001)
    {
    if (Serial.available()) 
      {  
        lcd.setCursor(20,0);
        while (Serial.available() > 0)
         {
           lcd.write(Serial.read());
         }
      }
    delay(10);
    }
    
    void get_temp()
    {
    Serial.print("T");
    delay(200);
      {
      // when characters arrive over the serial port...
      if (Serial.available())               // wait a bit for the entire message to arrive
        {
        delay(200);
        lcd.setCursor(0,0);
        lcd.print("TEMP A: ");                   // send out a string
        while (Serial.available() > 0)
          {
           lcd.write(Serial.read());
          }
        lcd.write(223); // degree sign
        lcd.print("C                    ");
        }
      else 
        {
          lcd.setCursor(0,0);
          lcd.print("TEMP A: ");                   // send out a string
          lcd.setCursor(8,0);
          lcd.print("NO REPLY        ");
          delay(200);
        }
      }
    }
    
     void get_temp_B()
      {
      Serial.print("T");
      delay(200);
        {
        if (Serial.available())     // wait a bit for the entire message to arrive
          { 
          delay(200);
          lcd.setCursor(0,1);
          lcd.print("TEMP B: ");                   // send out a string
          while (Serial.available() > 0) 
            {
              lcd.write(Serial.read());
            }
          lcd.write(223); // degree sign
          lcd.print("C           ");
          }
        else 
          {
            lcd.setCursor(0,1);
            lcd.print("TEMP B: ");                   // send out a string
            lcd.setCursor(8,1);
            lcd.print("NO REPLY           ");
            delay(200);
          }
        }
      }     
    
    
    

