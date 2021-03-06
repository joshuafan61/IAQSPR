#include <SoftwareSerial.h>
#define START_1 0x42
#define START_2 0x4d
 
#define DATA_LENGTH_H        0
#define DATA_LENGTH_L        1
#define PM1_0_CF1_H          2
#define PM1_0_CF1_L          3
#define PM2_5_CF1_H          4
#define PM2_5_CF1_L          5
#define PM10_CF1_H           6
#define PM10_CF1_L           7
#define PM1_0_ATMOSPHERE_H   8
#define PM1_0_ATMOSPHERE_L   9
#define PM2_5_ATMOSPHERE_H   10
#define PM2_5_ATMOSPHERE_L   11
#define PM10_ATMOSPHERE_H    12
#define PM10_ATMOSPHERE_L    13
#define UM0_3_H              14
#define UM0_3_L              15
#define UM0_5_H              16
#define UM0_5_L              17
#define UM1_0_H              18
#define UM1_0_L              19
#define UM2_5_H              20
#define UM2_5_L              21
#define UM5_0_H              22
#define UM5_0_L              23
#define UM10_H               24
#define UM10_L               25
#define VERSION              26
#define ERROR_CODE           27
#define CHECKSUM             29

int sensorValue2;
int sensorValue7;
int sensorValue131;
int sensorValue135;
int sensorValue136;
unsigned char chrRecv;
byte bytCount = 0;
int PIN_GREEN_Rx = 9; //10
int PIN_PURPLE_Tx = 10; //9
SoftwareSerial myPMS7003(PIN_GREEN_Rx, PIN_PURPLE_Tx);



void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
  myPMS7003.begin(9600);
}

void loop()
{
  unsigned char chrData[30];
  if (myPMS7003.available())
  {
     chrRecv = myPMS7003.read();
     if (chrRecv == START_1 && bytCount == 0)  bytCount = 1;
     if (chrRecv == START_2 && bytCount == 1)  bytCount = 2;
     if (bytCount == 2)
     {
        bytCount = 0;
        for(int i = 0; i < 30; i++)
        {chrData[i] = myPMS7003.read();}
     }}
  sensorValue2 = analogRead(5);       // read analog input pin 5
  Serial.println(sensorValue2, DEC);  // prints the value read
  sensorValue7 = analogRead(0);
  Serial.println(sensorValue7, DEC);
  sensorValue131 = analogRead(1);
  Serial.println(sensorValue131, DEC);
  sensorValue135 = analogRead(2);
  Serial.println(sensorValue135, DEC);
  sensorValue136 = analogRead(3);
  Serial.println(sensorValue136, DEC);                      // wait 100ms for next reading
  int dust = ShowPM_ATMO(chrData);
  delay(1000);  
}

unsigned int GetPM_Data(unsigned char chrSrc[], byte bytHigh, byte bytLow)
{
   return (chrSrc[bytHigh] << 8) + chrSrc[bytLow];
}

int ShowPM_ATMO(unsigned char chrData[])
{

   //Serial.print("PM 1.0: ");
   Serial.println(GetPM_Data(chrData, PM1_0_ATMOSPHERE_H, PM1_0_ATMOSPHERE_L));
   //Serial.print("PM 2.5: ");
   Serial.println(GetPM_Data(chrData, PM2_5_ATMOSPHERE_H, PM2_5_ATMOSPHERE_L));
   //Serial.print("PM 10: ");
   Serial.println(GetPM_Data(chrData, PM10_ATMOSPHERE_H, PM10_ATMOSPHERE_L));
   delay(1000); 
}
