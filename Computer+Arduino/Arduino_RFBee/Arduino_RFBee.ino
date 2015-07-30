    // Example sketch for tutorial of CT-UNO using with RFBee 433MHz
    // Please visit: http://tutorial.cytron.com.my/2015/01/29/wireless-communication-between-arduino-and-computer-with-rfbee/
        
    #include <LiquidCrystal.h>  //include the library of LCD 
    
    //initialize LCD
    LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  //4-bit interface
    int lcd_key     = 0;  //variable to record the keypress on LCD keypad shield
    int adc_key_in  = 0;  //analog value of keypress on Keypad shield
    int same_key = 0;    //variable to record whether the key press is the same
    char inKey;  // Character received from Serial input
    int Cursor = 0;  // Position of cursor, 0 is top left, (rows*columns)-1 is bottom right
    int rows = 2;  // Number rows, will be either 2 or 4
    int columns = 16; // Number of columns, will be 16 or 20
    int characters; // rows * columns
    //constant for button on keypad shield.
    
    #define btnRIGHT  0
    #define btnUP     1
    #define btnDOWN   2
    #define btnLEFT   3
    #define btnSELECT 4
    #define btnNONE   5
    
    //function to read keypress on LCD keypad shield
    int read_LCD_buttons(){      
       adc_key_in = analogRead(0);      
       if (adc_key_in < 50)   return btnRIGHT;   //if Right button is press, analog = 30 
       else if (adc_key_in < 250)  return btnUP; //if Up button is press, analog =  150
       else if (adc_key_in < 450)  return btnDOWN;  //if Down button is press, analog = 360 
       else if (adc_key_in < 650)  return btnLEFT;  //if Left button is press, analog = 535
       else if (adc_key_in < 850)  return btnSELECT;  //if Select button is press, analog = 760
       else return btnNONE;     //if no button is press, analog = 1023
    }    
    
    void setup(){
       lcd.begin(16, 2);  // initialize LCD 
       Serial.begin(4800); // initialize UART with 4800 baud
       lcd.setCursor(2,0);   //move LCD cursor           
       lcd.print("RFBEE CYTRON");  //print message on LCD
       Serial.println("TYPE ANYTHING !!");   //send string to UART, via RFBee if it is connected.
    }
  
     void loop(){
       lcd_key = read_LCD_buttons();  // read the buttons
       if(lcd_key==btnUP){
         if(same_key == 0){
           same_key = 1;  //change the value in same
           lcd.clear();  //clear LCD
           lcd.setCursor(0,1);  //move cursor to 2nd line
           lcd.print("UP");
           Serial.println("UP button is pressed!");  
         }
       }
     
       else if(lcd_key==btnDOWN){
         if(same_key == 0){
           same_key = 1;  //change the value in same
           lcd.clear();  //clear LCD
           lcd.setCursor(0,1);  //move cursor to 2nd line
           lcd.print("DOWN");
           Serial.println("DOWN button is pressed!");  
         }
       }
       
       else if(lcd_key==btnLEFT){
         if(same_key == 0){
           same_key = 1;  //change the value in same
           lcd.clear();  //clear LCD
           lcd.setCursor(0,1);  //move cursor to 2nd line
           lcd.print("LEFT");
           Serial.println("LEFT button is pressed!");  
         }
       }
    
        else if(lcd_key==btnRIGHT){
         if(same_key == 0){
           same_key = 1;  //change the value in same
           lcd.clear();  //clear LCD
           lcd.setCursor(0,1);  //move cursor to 2nd line
           lcd.print("RIGHT");
           Serial.println("RIGHT button is pressed!");  
         }
       }
       else if(lcd_key==btnSELECT){
         if(same_key == 0){
           same_key = 1;  //change the value in same
           lcd.clear();  //clear LCD
           lcd.setCursor(0,1);  //move cursor to 2nd line
           lcd.print("SELECT");
           Serial.println("SELECT button is pressed!");  
         }
       }
       else if(lcd_key==btnNONE){
         same_key = 0;  //reset the same key variable to indicate no button is press     
       }
     
          // when characters arrive over the serial port...
        if (Serial.available()) {
              // wait a bit for the entire message to arrive
              delay(100);
              // clear the screen
              lcd.clear();
              Cursor = 0;
              // read all the available characters
              while (Serial.available() > 0) {
                // display each character to the LCD
                inKey = Serial.read();
                LCDDisplay(inKey);
              }
            }
         }
 
      
    void LCDDisplay(char character)
      {
          int currentRow = 0;
          characters = rows * columns;
          // If Cursor is beyond screen size, get it right
          while (Cursor >= characters)
            Cursor -= characters;
          while (Cursor < 0)
            Cursor += characters;
          if (Cursor >= columns)
            currentRow = Cursor/columns;
          lcd.setCursor(Cursor%columns, currentRow);
          lcd.write(character);
          Cursor++;
      }

  
