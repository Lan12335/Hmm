//Transmitter, arduino UNO with debugging Serial.print

#include <nRF24L01.h>
#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

//All for nRF24L01
RF24 radio(8,7);
byte Address[] [6] = {"1Node","2Node}";

//All for force sensors
int F1; int F2; int F3;
const byte Ff1 = A0; const byte Ff2 = A1; const byte Ff3 = A2;

//All for Pseudo randomness
int RandomNn1; int RandomNn2; int RandomNn3;

//For Servo and RTC transmitting 
byte pos1=90; byte pos2=90; byte pos3=90;
int 3POS[6];  //we used an array to send the data
unsigned char data;

/* scl A4
sda A3 */

//ValN[] = {Else if, if, Ran1,Ran2,...}
int ValX[6] = {99-15+40,59-19+7,36-87+80,80-69+3,93-15+13};
int ValY[6] = {52-38+18,38-29+2,97-3+72,39-21+30,33-68+28};
int ValZ[6] = {78-84+81,49-38+62,80-17+47,26-60+26,25-60+76};  

//For LED
const byte Sensing= 2; 
const byte Switch on = 4;
const byte Open = 
const byte Closed = 

//open close
byte key1;
byte key2;
byte key3;
void setup() {
  Serial.begin(9600);

  //LED
  pinMode(Sensing, OUTPUT);  //When UNO r3 is sensing from the force sensors
  pinMode(Switch on, OUTPUT);  //For outside switch
  pinMode(Open, OUTPUT);  //The lock is open
  pinMode(Closed, OUTPUT);  //The lock is closed
  digitalWrite(Green on, HIGH);  //The green LED for power will open via switch outside the transmitter

  //nRF24L01
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radio.setChannel(124);
  radio.openWritingPipe(Address[1])
  radio.openReadingPipe(1, Address[0])  
}

//method for irrelevant LED "loop"
void start() {
   if(F1>=100||F2>=100||F3>=100) {
    digitalWrite(Sensing, HIGH);
    Serial.println("Green on" +"\n");  //The green on LED means that the UNO r3 is sensing something from the force sensors
    delay(100);    
  }
 
   else{
    digitalWrite(Sensing, LOW);
    Serial.println("No reads"+"\n");
    delay(100);
 }     
}

/*CASES when F123>=100,>=700,>=500
when F123>=100,map3=0-3
when F123>=500,map3=4-6
when F123>=700,map3=7-9
*/

void look() {
  radio.startListening()
  if(radio.availble() && (F1<100) && (F2<100) && (F3<100)) {
    while(radio.available()) {
      digital.Write(Open, LOW);
      digital.Write(Close, HIGH); 
    }
  }

    else if(radio.available() &&  (F1>=100) || (F2>=100) || (F3>=100)){
      byte q=30*5;
      byte w=60*5;
      byte e=90*5;   
       
  }
}
//method for pseudo random "loop"
void normal100() {
   if(F1>100) {
    RandomNn1 = random(99)-random(15)+random(40);
    RandomNn2 = random(52)-random(38)+random(18);
    RandomNn3 = random(78)-random(84)+random(81);
    Serial.println("Sensing..."+"Triggered Normal 1"+"\n");

    pos1=map((map(abs(RandomNn1),0,abs(ValX[0]),1,3)*10),0,30,0,90);
    pos2=map((map(abs(RandomNn2),0,abs(ValY[0]),1,3)*10),0,30,0,90);
    pos3=map((map(abs(RandomNn3),0,abs(ValZ[0]),1,3)*10),0,30,0,90);
  }

  if(F2>100) {
    RandomNn1 = random(99)-random(15)+random(40);
    RandomNn2 = random(52)-random(38)+random(18);
    RandomNn3 = random(78)-random(84)+random(81);
    Serial.println("Sensing..."+"Triggered Normal 1"+"\n");

    pos1=map((map(abs(RandomNn1),0,abs(ValX[0]),1,3)*10),0,30,0,90);
    pos2=map((map(abs(RandomNn2),0,abs(ValY[0]),1,3)*10),0,30,0,90);
    pos3=map((map(abs(RandomNn3),0,abs(ValZ[0]),1,3)*10),0,30,0,90);
  }

  if(F3>100) {
    RandomNn1 = random(99)-random(15)+random(40);
    RandomNn2 = random(52)-random(38)+random(18);
    RandomNn3 = random(78)-random(84)+random(81);
    Serial.println("Sensing..."+"Triggered Normal 1"+"\n");

    pos1=map((map(abs(RandomNn1),0,abs(ValX[0]),1,3)*10),0,30,0,90);
    pos2=map((map(abs(RandomNn2),0,abs(ValY[0]),1,3)*10),0,30,0,90);
    pos3=map((map(abs(RandomNn3),0,abs(ValZ[0]),1,3)*10),0,30,0,90);
  }
}

void normal700() {
  if(F1>=700) {
    RandomNn1 = random(59)-random(19)+random(7);
    RandomNn2 = random(38)-random(29)+random(2);
    RandomNn3 = random(49)-random(38)+random(62);
    Serial.println("Sensing..."+"Triggered Normal 2"+"\n");
    
    pos1=map((map(abs(RandomNn1),0,abs(ValX[1]),1,3)*10),0,30,0,90;
    pos2=map((map(abs(RandomNn2),0,abs(ValY[1]),1,3)*10),0,30,0,90;
    pos3=map((map(abs(RandomNn3),0,abs(ValZ[1]),1,3)*10),0,30,0,90;   
  }

  if(F2>=700) {
    RandomNn1 = random(59)-random(19)+random(7);
    RandomNn2 = random(38)-random(29)+random(2);
    RandomNn3 = random(49)-random(38)+random(62);
    Serial.println("Sensing..."+"Triggered Normal 2"+"\n");
    
    pos1=map((map(abs(RandomNn1),0,abs(ValX[1]),1,3)*10),0,30,0,90;
    pos2=map((map(abs(RandomNn2),0,abs(ValY[1]),1,3)*10),0,30,0,90;
    pos3=map((map(abs(RandomNn3),0,abs(ValZ[1]),1,3)*10),0,30,0,90;   
  }

  if(F3>=700) {
    RandomNn1 = random(59)-random(19)+random(7);
    RandomNn2 = random(38)-random(29)+random(2);
    RandomNn3 = random(49)-random(38)+random(62);
    Serial.println("Sensing..."+"Triggered Normal 2"+"\n");
    
    pos1=map((map(abs(RandomNn1),0,abs(ValX[1]),1,3)*10),0,30,0,90;
    pos2=map((map(abs(RandomNn2),0,abs(ValY[1]),1,3)*10),0,30,0,90;
    pos3=map((map(abs(RandomNn3),0,abs(ValZ[1]),1,3)*10),0,30,0,90;   
  }
}

void normal500() {
  if(F1>=500) {
    RandomNn1 = random(36)-random(87)+random(80);
    RandomNn2 = random(97)-random(3)+random(72);
    RandomNn3 = random(80)-random(17)+random(47);
    Serial.println("Sensing..."+"Triggered Nnormal 1"+"\n");
  
    pos1=map((map(abs(RandomNn1),0,abs(ValX[2]),1,3)*10),0,30,0,90);
    pos2=map((map(abs(RandomNn2),0,abs(ValY[2]),1,3)*10),0,30,0,90);
    pos3=map((map(abs(RandomNn3),0,abs(ValZ[2]),1,3)*10),0,30,0,90);
  }
  
  if(F2>=500) {
    RandomNn1 = random(80)-random(69)+random(3);
    RandomNn2 = random(39)-random(21)+random(30);
    RandomNn3 = random(26)-random(60)+random(26);  
    Serial.println("Sensing..."+"Triggered Nnormal 2"+"\n");
 
    pos1=map((map(abs(RandomNn1),0,abs(ValX[3]),1,3)*10),0,30,0,90);
    pos2=map((map(abs(RandomNn2),0,abs(ValY[3]),1,3)*10),0,30,0,90);
    pos3=map((map(abs(RandomNn3),0,abs(ValZ[3]),1,3)*10),0,30,0,90);
  }
  
  if(F3>=500) {
    RandomNn1 = random(93)-random(15)+random(13);
    RandomNn2 = random(33)-random(68)+random(28);
    RandomNn3 = random(25)-random(60)+random(76);
    Serial.println("Sensing..."+"Triggered Nnormal 3"+"\n");

    pos1=map((map(abs(RandomNn1),0,abs(ValX[4]),1,3)*10),0,30,0,90);
    pos2=map((map(abs(RandomNn2),0,abs(ValY[4]),1,3)*10),0,30,0,90);
    pos3=map((map(abs(RandomNn3),0,abs(ValZ[4]),1,3)*10),0,30,0,90);
  }
}

//Serials
void DebuggingF123() {
  if(F1>100) {
    Serial.println("F1 movement")
  }

  else{
    Serial.print("no movement")
  }

  if(F2>100) {
    Serial.println("F2 movement")    
  }

  else{
    Serial.print("no movement")
  }

 if(F3>100) {
    Serial.println("F3 movement")    
  }

  else{
    Serial.print("no movement")
  } 
} 

//method for RTC "setup"
void REALTIME() {
  tmElements_t tm;
  if (RTC.read(tm)) {
    Serial.println("Time: ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(",Date: ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println("\n");
    3POS[0]={print2digits(tm.Hour) + ":" + print2digits(tm.Minute) + ":" + print2digits(tm.Second)};
    3POS[1]={print2digits(tm.Day) + "/" + print2digits(tm.Month) + "/" + print2digits(tm.Year)};

  }
  
  else {
    if (RTC.chipPresent()) {
      Serial.println("run SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

//method for RTC "loop"
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

void loop() { 
  REALTIME();

  F1=analogRead(Ff1); F2=analogRead(Ff2); F3=analogRead(Ff3);
  
  if((F1>100)||(F2>100)||(F3>100)) {
  DebuggingF123();  //debugs

  start();  //just LED 
  
  normal100();  //Pseudo randomness 
  
  normal500();

  normal700();
  }

  look();

  while(!radio.available()) {
    Serial.println("nothing received"+"\n");
    return;
  }
  
  if(radio.available()) {
    while(radio.available()) {
      radio.read(&data, sizeof(char)); 
    }
  }

  if(data==1) {
    radio.stopListening();
    radio.write(3POS, sizeof(3POS));
    3POS[0];
    3POS[1];
    3POS[2]=pos1; 
    3POS[3]=pos2;
    3POS[4]=pos3;
    Serial.print("sent");
  }

 Serial.println("\n");
 Serial.print("pos1: "); Serial.print(pos1); 
 Serial.println("\n");
 Serial.print("pos2: "); Serial.print(pos2);
 Serial.println("\n");
 Serial.print("pos3: "); Serial.print(pos3);
 Serial.println("\n");
 delay(50);
}