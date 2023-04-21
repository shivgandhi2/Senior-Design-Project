void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
//Physical Reed Array
int reed_status [8][8]; //Holds logic value for each reed switch (row,column)
int mux_values[4][16];
//Arduino Pins
const byte MUX_ADDR [4] = {A3, A2, A1, A0}; // I/O pins (represent binary)
const byte MUX_SELECT [4] = {7, 8, 9, 13}; //Enable Pins (digital pins on arduino)


const int MUX_OUTPUT = 12; //Sig Pin (reed output)
const byte MUX_CHANNEL[16][4] = {
  {0, 0, 0, 0},
  {0, 0, 0, 1},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 1, 0, 0},
  {0, 1, 0, 1},
  {0, 1, 1, 0},
  {0, 1, 1, 1},
  {1, 0, 0, 0},
  {1, 0, 0, 1},
  {1, 0, 1, 0},
  {1, 0, 1, 1},
  {1, 1, 0, 0},
  {1, 1, 0, 1},
  {1, 1, 1, 0},
  {1, 1, 1, 1}
};




void setup() {
  Serial.begin(9600);

  //Initializing Mux board to be off
  initMux();

  pinMode(MUX_OUTPUT, INPUT_PULLUP); //No signal-> default 5v value

  //Initalizing Reed Logic Array 
  for (byte i = 0; i < 7; i++) {
    for (byte j = 0; j < 7; j++) {
      reed_status[i][j] = 1; //setting a default value to 5v (Magnet to reedswtich closes circuit to GND)
    }
  }

}

void loop() {
  reedPrint(); 
}



void reedPrint(){
  for (byte i = 0; i < 4; i++) {
    digitalWrite(MUX_SELECT[i], LOW); //Selecting mux board to enable (Enable = 0 ->Enable mux board)
    for (int j = 0; j < 16; j++) {  //Channels to read or write to on currently enabled mux board  
      for (byte k = 0; k < 4; k++) {
        digitalWrite(MUX_ADDR [k], MUX_CHANNEL [j][k]); //Configuing binary address for current j channel
      }

      int test = digitalRead(MUX_OUTPUT);
     
      mux_values[i][j] = test;
      

    }
   
    initMux();
    delay(1000);
    
  }
  
  for (int a = 0; a < 16; a++) {  //Channels to read or write to on currently enabled mux board  
       Serial.print("Channel: ");
        Serial.print(a);
        Serial.print("-> ");
      for (byte b = 0; b < 4; b++) {
       
        Serial.print(mux_values[b][a]);
        Serial.print(" ");

      }
      Serial.println("");
       
  }
    Serial.println("-----------------");
      delay(1000);



}

void initMux(){

for (byte i = 0; i < 4; i++) {
    pinMode (MUX_ADDR [i], OUTPUT);
    digitalWrite(MUX_ADDR [i], LOW); //Set all I/O pins to 0 logic
    pinMode (MUX_SELECT [i], OUTPUT);
    digitalWrite(MUX_SELECT [i], HIGH); //Disabling each mux board (E = 1 ->Mux board is off)
  }

}














}
