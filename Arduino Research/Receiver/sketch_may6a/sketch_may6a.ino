//Receiver, arduino RF-Nano

#include <Adafruit_Fingerprint.h>
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SD.h>

//naming servo
Servo SR1;
Servo SR2;
Servo SR3;
int 3POS[6];

//All for micro SD card function
File myFile;
String positions = "test.txt";

//All for fingerprint function
#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
const int chipSelect = 5;
SoftwareSerial mySerial(7,6);
#else
#define mySerial Serial1
#endif
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//All for nRF24L01 function
RF24 radio(10,9);
const byte Address[] {6} = {"1Node", "2Node"};

unsigned char data=1;

void setup() {
  Serial.begin(9600);
  
  FINGER();
  //servo
  SR1.attach(2, 500, 2500); 
  SR2.attach(3, 500, 2500);
  SR3.attach(4, 500, 2500);
  
  delay(100);
  SR1.write(90);
  SR2.write(90);
  SR3.write(90);
  delay(100);  

  //nRF24L01
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radiosetChannel(124);
  radio.openWritingPipe(Address[0]);
  radio.openReadingPipe(1, Address[1]);

  //SD
  while(!Serial){}; 

  initializeCard();

  if(SD.exists(positions)) {
    SD.remove(positions);
    Serial.print("\nfile has been overwritten\n");
  }

  writeHeader();

  Serial.print("sumakses") //SD
}

//method for SD "in setup"
void initializeCard() {
  Serial.print("initializing: ");
  if(!SD.begin(5)) {
    Serial.print("nuh uh");
    while(1);
  }
  Serial.print("oks");
}

//method for SD "in setup"
void writeHeader() {
  myFile = SD.open(positions, FILE_WRITE); 

  if(myFile) {
    Serial.print("writing to" + positions +":");

    myFile.println("Pos1,Pos2,Pos3");

    myFile.close();
  }

  else {
    Serial.print("error in header");
  }
}

//method for Fingerprint "in setup"
void FINGER() {
  finger.begin(57600);
  delay(5);

 /*
  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

 */
  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data.");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
  
}

void loop() {
  radio.stopListening(); 
  radio.write(&data,sizeof(char));
  delay(50);

  radio.startListening();
  if(radio.available()) {
    Serial.println("may signal");
  }
  getFingerprintID(); //tells that a fingerprint is needed for the device to work
  if((radio.available()) && (finger.fingerID == 1)||(finger.fingerID == 2)||(finger.fingerID == 3)) {  

  bool done=false;

    while(!done){


      done = radio.read(3POS, sizeof(3POS));  //reads the data received
      Serial.print("Time: "); Serial.print(3POS[0]); Serial.print("\n");  //time
      Serial.print("Day(DMY): "); Serial.print(3POS[1]); Serial.print("\n");   //day
      
      Serial.print("POS1: "); Serial.print(3POS[2]); Serial.print("\n");  //for servo1
      Serial.print("POS2: "); Serial.print(3POS[3]); Serial.print("\n");  //for servo2
      Serial.print("POS3: "); Serial.print(3POS[4]); Serial.print("\n");  //for servo3

      SR1.write(pos1);  //S1
      SR2.write(pos2);  //S2
      SR3.write(pos3);  //S3
      delay(50);
      
      writeData();  //method on SD
    }
}
else {
    Serial.println("naur");
}
}

//fingerprint
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}

//method for SD card "in loop"
void writeData() {
  myFile = SD.open(positions, FILE_WRITE);

  if(myFile) {
    myFile.print("Time: ");
    myFile.print(3POS[0]);
    myFile.print("Day(DMY): ");
    myFile.print(3POS[1]);
    
    myFile.print("Positions(123): ");    
    myFile.print(3POS[2]);
    myFile.print(",");
    myFile.print(3POS[3]);
    myFile.print(",");
    myFile.print(3POS[4]);

    myFile.close();
  }
  else {
    Serial.print("error in write");
  }
}