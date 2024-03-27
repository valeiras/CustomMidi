//GND - GND
//VCC - VCC
//SDA - Pin A4
//SCL - Pin A5

#include "Wire.h"
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"

#define ATMEGA328
// #define DEBUG

#ifdef ATMEGA328
#include "midi_interface328.h"
#elif defined(ATMEGA32U4)
#include "midi_interface32U4.h"
#endif

#if defined(ATMEGA328) || defined(ATMEGA32U4)
MidiInterface *interface;
#endif

//instantiate a MPU6050 object, the object name is mpu
MPU6050 mpu(0x68);

const int MAX_ANGLE = 90;
const int MAX_W = 1000;
const byte NB_SENSORS = 6;
const byte MIDI_CH = 1;

//statement MPU6050 control and state variable
bool dmpReady = false;  //set true if DMP init was successful
uint8_t mpuIntStatus;   //This variable is used to save the state when MPU6050 stop working
uint8_t devStatus;      //Return to equipment status, 0 for success, others for error
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

//state direction and movement of variables:
Quaternion q;           //quaternion variable W,X,Y,Z
VectorFloat gravity;    //gravity vector X，Y, Z
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

const byte controlChanges[NB_SENSORS] = {20, 21, 22, 23, 24, 25};
uint8_t lastMidiValues[NB_SENSORS] = {255, 255, 255, 255, 255, 255};
uint8_t currMidiValues[NB_SENSORS] = {0, 0, 0, 0, 0, 0};


void setup()
{
  #ifdef ATMEGA328
  interface = new MidiInterface328();
#elif defined(ATMEGA32U4)
  Serial.begin(9600);
  interface = new MidiInterface32U4();
#elif defined(DEBUG)
  Serial.begin(9600);
  delay(1000);
#endif
  Wire.begin();
  mpu.initialize();
  delay(2); //delay 2ms

  //upload and configure DMP digital motion processing engine
  devStatus = mpu.dmpInitialize(); //Return to DMP status, 0 for success, others for error

  if (devStatus == 0)
  {
    mpu.setDMPEnabled(true);

    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;

    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  else {
    Serial.print(devStatus);
  }
}

void loop()
{
  float x, wx;
  float y, wy;
  float z, wz;

  if (!dmpReady)
    return;

  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();

  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
  }

  else if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);  //take three axis angle from the DMP. they are Yaw, Pitch and Roll. put them into the succession of the array.Units: radian
    x=ypr[2] * 180/M_PI;
    y=ypr[1] * 180/M_PI;
    z=ypr[0] * 180/M_PI;

    wx=mpu.getRotationX()/16.4; //configuration is 16. plus or minus2000°/s, 65536/4000
    wy=mpu.getRotationY()/16.4; //configuration is 16. plus or minus2000°/s, 65536/4000
    wz=mpu.getRotationZ()/16.4; //configuration is 16. plus or minus2000°/s, 65536/4000

    currMidiValues[0] = sensorToMidi(x, MAX_ANGLE);
    currMidiValues[1] = sensorToMidi(y, MAX_ANGLE);
    currMidiValues[2] = sensorToMidi(z, MAX_ANGLE);
    currMidiValues[3] = sensorToMidi(wx, MAX_W);
    currMidiValues[4] = sensorToMidi(wy, MAX_W);
    currMidiValues[5] = sensorToMidi(wz, MAX_W);
    
    for(int ii=0; ii<1; ii++){
      if(currMidiValues[ii] != lastMidiValues[ii]){
        #if defined(ATMEGA328) || defined(ATMEGA32U4)
        interface->sendCCMessage(MIDI_CH, controlChanges[ii], currMidiValues[ii]);
        #else
        Serial.print(ii);
        Serial.print(": ");
        Serial.print(currMidiValues[ii]);
        Serial.print(", ");
        Serial.println(lastMidiValues[ii]);
        delay(1000);
        #endif
        lastMidiValues[ii] = currMidiValues[ii];
      }
    }
  }
}

uint8_t sensorToMidi(int16_t sensorRead, int16_t maxSensorValue){
  int16_t lowerLimit = -maxSensorValue;
  int16_t output =constrain(sensorRead, lowerLimit, maxSensorValue);
  output = output < maxSensorValue ? output : maxSensorValue;
  output = map(output, lowerLimit, maxSensorValue, 0, 127);
  return output;
}
