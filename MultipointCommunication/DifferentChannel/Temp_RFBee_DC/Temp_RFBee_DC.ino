        
        /* 
        This sketch for temperature sensor node of wireless communication between 
        RFBee module using DIFFERENT channel to communicate each other
        */
               
        byte rx_data = 0;                          //variable to store receive data
        int temp_analogPin = A0;                  // LM35 connected to Analog port-1
        
        void setup()
        {
         Serial.begin(9600);                     // 9600 baud rate
        }
        
        void loop()
        {
        int temp_value;
        temp_value = analogRead(temp_analogPin);                
        temp_value = (float)temp_value*0.448;                             
        
        if(Serial.available())                 // check if UART receive data
          {
          rx_data = Serial.read();            //store data received
            if(rx_data == 'T')                //if the character received is 'T'
            {   
              Serial.print(temp_value);       // print temperature value in decimal
            }
          }
        }
