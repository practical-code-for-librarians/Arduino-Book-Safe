#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>



//#include <LiquidCrystal.h>
/* Arduino Unlocking code to use with you're own mechanism, here it's used to show a welcome or not <br> *  message on a lcd i2c screen
 *  The wiring is (keypad from 8to1) to arduino digital pins(9to2)
 *  lcd i2c on (5v,GND, SDA on A4 SCL on A)
 *  By SurtrTech
 */
#include <Keypad.h> 
//Libraries you can download them via Arduino IDE
#include <Wire.h>

#define I2C_ADDR 0x3F // LCD i2c Adress and pins or 0x3F or 0x27
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
//LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
const byte numRows= 4; //number of rows on the keypad
const byte numCols= 3; //number of columns on the keypad
int code = 129;  //The code I used, you can change it
int tot,i1,i2,i3,i4;
char c1,c2,c3,c4,c5;
//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3'}, 
{'4', '5', '6'}, 
{'7', '8', '9'},
{'*', '0', '#'}
};
//Code that shows the the keypad connections to the arduino terminals
//byte rowPins[numRows] = {8,7,6,5}; //Rows 0 to 3
//byte colPins[numCols]= {4,3,2}; //Columns 0 to 3

byte rowPins[numRows] = {5,6,7,8}; //connect to the row pinouts of the keypad
byte colPins[numCols] = {2,3,4}; //connect to the column pinouts of the keypad


int relay_pin = 10;
//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
void setup()
           {
            Serial.begin(9600);
            pinMode(relay_pin, OUTPUT);
            
           }
void loop()
{
      
      digitalWrite(relay_pin, LOW);
      
      char keypressed = myKeypad.getKey();  //The getKey fucntion keeps the program runing, as long you didn't press "*" the whole thing bellow wouldn't be triggered
         //Serial.println("..." + keypressed);
         if (keypressed == '#')             // and you can use the rest of you're code simply
             {      //when the "*" key is pressed you can enter the passcode
                    keypressed = myKeypad.waitForKey();  // here all programs are stopped until you enter the four digits then it gets compared to the code above
                    if (keypressed != NO_KEY)
                      {
                       c1 = keypressed;
                        Serial.println(keypressed);
                       }
                    keypressed = myKeypad.waitForKey();
                    if (keypressed != NO_KEY)
                      {
                       c2 = keypressed;
                        Serial.println(keypressed);
                       }
                     keypressed = myKeypad.waitForKey();
                   if (keypressed != NO_KEY)
                      {
                       c3 = keypressed;
                        Serial.println(keypressed);
                       }
                      
                      
                     //the keys pressed are stored into chars I convert them to int then i did some multiplication to get the code as an int of xxxx
                     i1=(c1-48)*100;
                     i2=(c2-48)*10;
                     i3=c3-48;
                     tot=i1+i2+i3;
         Serial.println(tot);
         Serial.println(code);
        
         if (tot == code) //if the code is correct you trigger whatever you want here it just print a message on the screen
         {
          Serial.println("open");

          Serial.println(digitalRead(relay_pin));
          digitalWrite(relay_pin, HIGH);
          Serial.println(digitalRead(relay_pin));
          delay(2000);
          digitalWrite(relay_pin, LOW);
         }
         else //if the code is wrong you get another thing
         {
          Serial.print("Wrong code");
          
         }
               
              }
}
