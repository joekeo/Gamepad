/*
 Fading
 */
 #include "Keyboard.h"
 
//Defining the column pins
byte cPins[] = {6,5,4,8,7};
byte cols = sizeof(cPins);

//Defining the Rows pins
byte rPins[] = {15,14,16,10};
byte rows = sizeof(rPins);

//store if the switch is presses
bool pressed = false;

//key definitions 5 Columns 4 Rows
byte Key[sizeof(rPins)][sizeof(cPins)] = 
                {{KEY_ESC,        'q',              KEY_UP_ARROW,   'e',                'r'},
                 {KEY_TAB,        KEY_LEFT_ARROW,   KEY_DOWN_ARROW, KEY_RIGHT_ARROW,    'f'},
                 {KEY_LEFT_SHIFT, 0x31,              'z',            'x',                'c'},
                 {KEY_LEFT_CTRL,  '1',              '2',            '3',                0x2C}};

bool oldKey [sizeof(rPins)][sizeof(cPins)] = 
                {{false,false,false,false,false},
                 {false,false,false,false,false},
                 {false,false,false,false,false},
                 {false,false,false,false,false}};



int ledPin = 9;    // LED connected to digital pin 9
int maxV = 255;
void setup() {
  //delacre a safe fuse if the keyboard goes rough
  //this is the fuse 
  pinMode(A0, INPUT);
  //Serial.begin(9600);
  //declar the I/O pins for the keys
  for (byte i = 0; i < cols; i++)
    pinMode(cPins[i],INPUT);
  
  for (byte i = 0; i < cols; i++)
    pinMode(rPins[i],OUTPUT);

  //turn the leds on
  analogWrite(ledPin,255);

  Keyboard.begin();
 
  
  
}

int loopDelay = 10; //in ms

void loop() {
  if (digitalRead(A2) == 0){
    for (byte i = 0; i < rows; i++){
      digitalWrite(rPins[i],HIGH);
      for (byte j = 0; j < cols; j++){
        pressed = digitalRead(cPins[j]);
        if (pressed != oldKey[i][j]){
          if (pressed == 1){
            Keyboard.press(Key[i][j]);
            oldKey[i][j] = 1;
          }
          else{
            Keyboard.release(Key[i][j]);
            oldKey[i][j] = 0;
          }
        
        }
        
          //Serial.print(char(Key[i][j]));
        }
      digitalWrite(rPins[i],LOW);
      }
   //Serial.println(' ');
   //Keyboard.releaseAll();
   delay(loopDelay);
  }
}


