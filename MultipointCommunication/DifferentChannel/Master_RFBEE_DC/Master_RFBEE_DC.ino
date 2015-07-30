        /* 
        This sketch for Master node that hacked of wireless communication between 
        RFBee module using Different channel to communicate each other 
        */
        
        #include <LiquidCrystal.h> // include the library code:
        #include <EEPROM.h>
        LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // initialize the library with the numbers of the interface pins
        int PIN = 12;      
        int i ; // address of EEPROM
        int count_address = 0; // count how many address of EEPROM used
        int NONE = 0 ;// NO BYTE RECEIVE

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
        
        Serial.println("AT+C002");       // Give command to set channel of RFBee module to C002
        delay(200);
        
        filter_feedback();          // to filter the feedback of the command that given(example, OK+C001)
        
        digitalWrite(PIN,HIGH );  // turn the PIN on (HIGH is the voltage level)
        delay(200);
        
        clear_EEPROM_memory();          // to clear stored memory inside EEPROM
        i = 0; // start reading from the first byte (address 0) of the EEPROM
        get_temp();                 // Read and write temperature value on LCD shield
        temp();                  //  Analysize temperature value
        count_address = i ;  // to count until when the address of EEPROM is used

        digitalWrite(PIN, LOW);    // turn the PIN off by making the voltage LOW
        delay(1000);
        
        Serial.println("AT+C003");       // Give command to set channel of RFBee module to C001
        delay(500);
        
        filter_feedback();
        
        digitalWrite(PIN,HIGH );   // turn the PIN on (HIGH is the voltage level)
        delay(200);
        
        data_comp();       // Read data from computer 
        comp();           // Pass high temparature value or NO reply value from temperature sensor node to computer
        }

      void filter_feedback()        //  // to filter the feedback of the command that given(example, OK+C001)
        {
          if (Serial.available()) {  

            while (Serial.available() > 0) {
            lcd.write(Serial.read());
            }
          }
        lcd.clear();
        }
        
        void clear_EEPROM_memory()
          {
          EEPROM.write(1, 0);  // to clear stored memory inside EEPROM
          EEPROM.write(2, 0);   // to clear stored memory inside EEPROM
          EEPROM.write(3, 0);   // to clear stored memory inside EEPROM
          }
        
        void temp()
        {
          // if temperature below 9C , lcd shield will display " cold"
          if(EEPROM.read(1) >='0'&&EEPROM.read(2) ==0&&EEPROM.read(3) == NONE) //   < 9°C
          {
          lcd.setCursor(0,1);
          lcd.print("TOO COLD");
          delay(200);
          }
           
        // if temperature below 19C , lcd shield will display " cold"
         if( EEPROM.read(1) <='1'&&EEPROM.read(2) >='0'&&EEPROM.read(3) ==NONE) //  Between 10°C < 19°C
          {
          lcd.setCursor(0,1);
          lcd.print("COLD");
          delay(200);
          } 
        // if temperature above 40C , lcd shield will display "too hot"
        if( EEPROM.read(1) >='4' && EEPROM.read(2) >= '0'&&EEPROM.read(3) ==NONE) // +40C
          {
          lcd.setCursor(0,1);
          lcd.print("TOO HOT ");
          delay(200);
          } 
        
        if( EEPROM.read(1) <= '1'  && EEPROM.read(2) <= '2' &&EEPROM.read(3) >= '0' ) // <120C
          {
          lcd.setCursor(0,1);
          lcd.print("EXTREME HOT !!");
          delay(200);
          }
          
         // if temperature above 300C , lcd shield will display "something wrong" to mention there is problem with temparature node
        if( EEPROM.read(1) >= '3'  && EEPROM.read(2) >= '0' &&EEPROM.read(3) >= '0' ) // +300C
          {
          lcd.setCursor(0,1);
          lcd.print("SMTG WRONG ");
          delay(200);
          }
        }
        
        void comp()
        {
          // if temperature above 100C , lcd shield will display "too hot"
          if( EEPROM.read(1) <= '1'  && EEPROM.read(2) <= '2' &&EEPROM.read(3) >= '0' ) // <120C
          {              
            Serial.print("Temp A: ");
           for ( i= 1; i <= count_address ; i++){
              Serial.write(EEPROM.read(i));        // read a byte from the current address of the EEPROM
              } 
          Serial.write('°'); // degree sign
          Serial.println('C'); // degree sign
          Serial.println("Extreme HOT !! ");
          delay(200);
          }
         
        // if temperature above 300C , lcd shield will display "something wrong" to mention there is problem with temparature node
        if( EEPROM.read(1) >= '3'  && EEPROM.read(2) >= '0' &&EEPROM.read(3) >= '0' ) // +300C
          {              
            Serial.print("Temp A: ");
           for ( i= 1; i <= count_address ; i++){
              Serial.write(EEPROM.read(i));        // read a byte from the current address of the EEPROM
              } 
          Serial.write('°'); // degree sign
          Serial.println('C'); // degree sign
          Serial.println("Something wrong with temperature node !! ");
          delay(200);
          }
        // if temperature above 40C , lcd shield will display "too hot"
        if( EEPROM.read(1) >='4' && EEPROM.read(2) >= '0'&&EEPROM.read(3) ==NONE) // +40
          {            
            Serial.print("Temp A: ");
           for ( i= 1; i <= count_address ; i++){
              Serial.write(EEPROM.read(i));        // read a byte from the current address of the EEPROM
              } 
                     
          Serial.write('°'); // degree sign
          Serial.println('C'); // degree sign
          Serial.println("Too hot !!");
          delay(200);
          }
          
              if(EEPROM.read(1) >='0'&&EEPROM.read(2) ==0&&EEPROM.read(3) ==NONE) //  <9°C
          {            
            Serial.print("Temp A: ");
           for ( i= 1; i <= count_address ; i++){
              Serial.write(EEPROM.read(i));        // read a byte from the current address of the EEPROM
              } 
          Serial.write('°'); // degree sign
          Serial.println('C'); // degree sign
          Serial.println("Too cold !!");
          delay(200);
          }
          
         if( EEPROM.read(1) <='1'&&EEPROM.read(2) >='0'&&EEPROM.read(3) ==NONE) //  Between 10°C < 19°C
          {            
            Serial.print("Temp A: ");
           for ( i= 1; i <= count_address ; i++){
              Serial.write(EEPROM.read(i));        // read a byte from the current address of the EEPROM
              } 
          Serial.write('°'); // degree sign
          Serial.println('C'); // degree sign
          Serial.println("Cold !!");
          delay(200);
          }
          
        if( EEPROM.read(1) ==NONE && EEPROM.read(2) == NONE &&EEPROM.read(3) ==NONE)  // No data receive form Temperature node
          {
          Serial.println("Temp A : NO REPLY !!");
          delay(200);
          }
        }
        
        void get_temp()
        {
        Serial.print("T");
        delay(200);
        lcd.print("Temp A: ");
          {
            if (Serial.available()) {
              while (Serial.available() > 0) {
              i=i+1;                              // to store memory in EEPROM address for another available byte
              EEPROM.write(i, Serial.read());    // each address store only one byte
              lcd.write(EEPROM.read(i));        // read a byte from the current address of the EEPROM
              }
            lcd.write(223); // degree sign
            lcd.print("C");
            }
          
            else {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Temp A: ");
            lcd.setCursor(0,1);
            lcd.print("NO REPLY");
            delay(200);
            }
          }
        }
        
        void data_comp()                // Read data from computer 
        {
          // when characters arrive over the serial port...
          if (Serial.available()) {
            // wait a bit for the entire message to arrive
            delay(10);
            lcd.clear();
            while (Serial.available() > 0) {
              // display each character to the LCD
              lcd.write(Serial.read());
            }
          }
        }
