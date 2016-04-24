#include <Servo.h>

#define trigPin 13
#define echoPin 12

#define trigPin1 8
#define echoPin1 7

#define trigPin2 14
#define echoPin2 15

#define trigPin3 16
#define echoPin3 17

#define GPS_TX 18
#define GPS_RX 19


#include <Wire.h>

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

int L3G4200D_Address = 105; //I2C address of the L3G4200D

int x;
int y;
int z;


int moteur5 = 10;
int moteur4 = 20;
int moteur3 = 6;
int moteur2 = 5;
int moteur1 = 3;

int t1,t2,t3,t4;

Servo monServo; 

int gps() {
  // gps modu
//  retourn 1 ou 0 
}

void inclinaison  () {
  // capteur d'inclinaison 

}
void setup() {
  
 Serial.begin(9600);
 pinMode(3, OUTPUT);  
 pinMode(moteur1, OUTPUT); 
 monServo.attach(9);
 monServo.write( 0 );
 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  analogWrite(moteur1, 150); 
  setupL3G4200D(2000);
  
}

void loop() {
  getGyroValues();
  Serial.print("moteur");
  int v = Serial.read();
  analogWrite(moteur1, v);

   // 9odem
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 20) {  // This is where the LED On/Off happens
    
    Serial.print(distance);
    Serial.println(" cm0");
    t1 = 1 ; }
    else 
    {
      t1 = 0 ;   
}
 
  // lteli 

  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 20) {  // This is where the LED On/Off happens
    
    Serial.print(distance);
    Serial.println(" cm wraha ");
    t2 =1 ;
}
else 
{t2=0; }
  

  // droit 
    
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 20) {  // This is where the LED On/Off happens
    
    Serial.print(distance);
    Serial.println(" cm a droit");
    t3= 1 ;

}else 
{t3=0; }
  


  // gouche 
  
    
  digitalWrite(trigPin3, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin3, LOW);
  duration = pulseIn(echoPin3, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 20) {  // This is where the LED On/Off happens
    
    Serial.print(distance);
    Serial.println(" cm a gouche");
  t4= 1 ;
}else 
{t4=0; }



if ( t1 == 1 ) 
{
  analogWrite(moteur2, 250); 
  }

if (t2 == 1)
{analogWrite(moteur3, 250); 
  }

if (t3==1)
{
analogWrite(moteur4, 250);   
}


if (t4==1) 
{ 
  
  analogWrite(moteur5, 250);  
}
}


  void getGyroValues(){

  byte xMSB = readRegister(L3G4200D_Address, 0x29);
  byte xLSB = readRegister(L3G4200D_Address, 0x28);
  x = ((xMSB << 8) | xLSB);

  byte yMSB = readRegister(L3G4200D_Address, 0x2B);
  byte yLSB = readRegister(L3G4200D_Address, 0x2A);
  y = ((yMSB << 8) | yLSB);

  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  z = ((zMSB << 8) | zLSB);
}

int setupL3G4200D(int scale){
  //From  Jim Lindblom of Sparkfun's code

  // Enable x, y, z and turn off power down:
  writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:

  if(scale == 250){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
  }else if(scale == 500){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
  }else{
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
  }

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}

void writeRegister(int deviceAddress, byte address, byte val) {
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

int readRegister(int deviceAddress, byte address){

    int v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();

    Wire.requestFrom(deviceAddress, 1); // read a byte

    while(!Wire.available()) {
        // waiting
    }

    v = Wire.read();
    return v;



}
