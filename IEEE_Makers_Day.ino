#include <Servo.h>

const int inX = A0; // analog input for x-axis
const int inY = A1; // analog input for y-axis
const int inPressed = 2; // input for detecting whether the joystick/button is pressed

int xValue = 0; // variable to store x value
int yValue = 0; // variable to store y value
int notPressed = 0; // variable to store the button's state => 1 if not pressed

int Laser = 6;
byte oldbutton = 0;
byte state = 0;

int xAng = 90;
int yAng = 90;

Servo servoXDIR;
Servo servoYDIR;

void setup() 
{
  Serial.begin(9600);
  pinMode(inX, INPUT); // setup x input
  pinMode(inY, INPUT); // setup y input
  pinMode(inPressed, INPUT_PULLUP); // we use a pullup-resistor for the button functionality
  pinMode(Laser, OUTPUT); //Laser

  servoXDIR.attach(8);
  servoYDIR.attach(9);

  servoXDIR.write(xAng);
  servoYDIR.write(yAng);

  digitalWrite(Laser,LOW);
}

void loop() 
{
  xValue = analogRead(inX); // reading x value [range 0 -> 1023]
  xValue = (xValue - 504)/-100;
  yValue = analogRead(inY); // reading y value [range 0 -> 1023]
  yValue =  (yValue - 512)/100;
  notPressed = digitalRead(inPressed); // reading button state: 1 = not pressed, 0 = pressed
  int Bright = analogRead(2);
 
  /*Button press turning light on or off*/
  if(notPressed && !oldbutton)
  {
    if(state == 0)
    {
      digitalWrite(Laser,LOW);
      state = 1;
    }
    else 
    {
      state = 0;
    }
    oldbutton = 1;
  }
  else if(!notPressed && oldbutton)
  {
    oldbutton = 0;
  }
  if (state == 0){
    analogWrite(Laser,Bright/4);
  }
  /*Motor Control*/
  if((abs(xValue)) > 0.25)
  {
    xAng = xAng + xValue;
    servoXDIR.write(xAng);
    delay(50);
    Serial.print(xAng);
  }
  if((abs(yValue)) > 0.25)
  {
    yAng = yAng + yValue;
    servoYDIR.write(yAng);
    delay(50);
    Serial.print(yAng);
  }

}
