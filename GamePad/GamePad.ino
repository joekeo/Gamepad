/*
 Fadingwwwwsssasdasdasdasdqeqeqeqeqeqeqeqeasdasdasdwasdw1111
 */
 #include "Keyboard.h"
 
//Defining the column pins
byte cPins[] = {4,5,6,7,8};
byte cols = sizeof(cPins);

//Defining the Rows pins
byte rPins[] = {10,16,14,15};
byte rows = sizeof(rPins);

//store if the switch is presses
bool pressed = false;

//key definitions 5 Columns 4 Rows
//comparing the hex code in the HID usb tables, it seams that arduino has a 0x88 offset in the values
byte Key0[sizeof(rPins)][sizeof(cPins)] = 
                {{KEY_ESC,        0x5f + 0x88,                KEY_UP_ARROW,      0x61 + 0x88,                'r'},
                 {KEY_TAB,        KEY_LEFT_ARROW,            KEY_DOWN_ARROW, KEY_RIGHT_ARROW,                 'f'},
                 {KEY_LEFT_SHIFT, 0x59 + 0x88,             'z',            0x5b + 0x88,                       'c'},
                 {KEY_LEFT_CTRL,  '1',              '2',            '3',                              0x4e + 0x88}};


byte Key1[sizeof(rPins)][sizeof(cPins)] = 
                {{KEY_ESC,        'q',              'w',            'e',                 'r'},
                 {KEY_TAB,        'a',              's',            'd',                 'f'},
                 {KEY_LEFT_SHIFT, 0x64 + 0x88,      'z',            'x',                 'c'},
                 {KEY_LEFT_CTRL,  '1',              '2',            '3',                '4'}};



 

bool oldKey [sizeof(rPins)][sizeof(cPins)] = 
                {{false,false,false,false,false},
                 {false,false,false,false,false},
                 {false,false,false,false,false},
                 {false,false,false,false,false}};


//byte *Key;
int mode = 0;
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
 if (mode == 0)
  mode = mode0();
 if (mode == 1)
  mode = mode1();
  
}

int mode0(){
  if (digitalRead(A2) == 0){
    for (byte i = 0; i < rows; i++){
      digitalWrite(rPins[i],HIGH);
      for (byte j = 0; j < cols; j++){
        pressed = digitalRead(cPins[j]);
        if (pressed != oldKey[i][j]){
          if (pressed == 1){
            Keyboard.press(Key0[i][j]);
            oldKey[i][j] = 1;
          }
          else{
            Keyboard.release(Key0[i][j]);
            oldKey[i][j] = 0;
          }
        
        }
        
          //Serial.print(char(Key[i][j]));
        }
      digitalWrite(rPins[i],LOW);
      }

   delay(loopDelay);
  }
  //check if esc + 1 or 2 or 3 or 4 are pressed and change mode if so
  if (oldKey[0][0] == 1){
    if (oldKey[3][1] == 1)
      return 0;
    if (oldKey[3][2] == 1)
      return 1;
  }
  return 0;
}

int mode1(){
  if (digitalRead(A2) == 0){
    for (byte i = 0; i < rows; i++){
      digitalWrite(rPins[i],HIGH);
      for (byte j = 0; j < cols; j++){
        pressed = digitalRead(cPins[j]);
        if (pressed != oldKey[i][j]){
          if (pressed == 1){
            Keyboard.press(Key1[i][j]);
            oldKey[i][j] = 1;
          }
          else{
            Keyboard.release(Key1[i][j]);
            oldKey[i][j] = 0;
          }
        
        }
        
          //Serial.print(char(Key[i][j]));
        }
      digitalWrite(rPins[i],LOW);
      }

   delay(loopDelay);
  }
  
  //check if esc + 1 or 2 or 3 or 4 are pressed and change mode if so
  if (oldKey[0][0] == 1){
    if (oldKey[3][1] == 1)
      return 0;
    if (oldKey[3][2] == 1)
      return 1;
  }
  return 1;
}
