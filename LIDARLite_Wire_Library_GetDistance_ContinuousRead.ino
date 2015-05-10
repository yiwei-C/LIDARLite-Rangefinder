
/* 

http://pulsedlight3d.com

This sketch demonstrates getting distance with the LIDAR-Lite Sensor

It utilizes the 'Arduino Wire Library'

*/

#include <Wire.h>
#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite. slave address Ox62
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x04          // Value to initiate ranging.
#define    RegisterHighLowB    0x8f          // Register to get both High and Low bytes in 1 call.

int reading = 0;
int count=0;
int arr[10];

void setup()
{
  Wire.begin(); // join i2c bus
  Serial.begin(9600); // start serial communication at 9600bps
}

void loop()
{
  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterMeasure); // sets register pointer to  (0x00)  
  Wire.write((int)MeasureValue); // sets register pointer to  (0x04)  
  Wire.endTransmission(); // stop transmitting

  delay(20); // Wait 20ms for transmit

  Wire.beginTransmission((int)LIDARLite_ADDRESS); // transmit to LIDAR-Lite
  Wire.write((int)RegisterHighLowB); // sets register pointer to (0x8f)
  Wire.endTransmission(); // stop transmitting

  delay(20); // Wait 20ms for transmit

  Wire.requestFrom((int)LIDARLite_ADDRESS, 2); // request 2 bytes from LIDAR-Lite

  if(2 <= Wire.available()) // if two bytes were received
  {
    reading = Wire.read(); // receive high byte (overwrites previous reading)
    reading = reading << 8; // shift high byte to be high 8 bits
    reading |= Wire.read(); // receive low byte as lower 8 bits
    //if(reading<1500&&reading>-1){
      if(reading>-1){
      arr[count]=reading;
      count++;
      if(count==10){
        int total=0;
        count=0;
        int biggest=arr[0];
        int smallest=arr[0];
        for(int i=0;i<10;i++){
          total+=arr[i];
          if(arr[i]>biggest){
            biggest=arr[i];
          }
          if(arr[i]<smallest){
            smallest=arr[i];
          }
        }
        total=total-biggest-smallest;
        Serial.println(total/8);
      }
    }
    //Serial.print("the original reading is: ");
    //Serial.println(reading); // print the reading
  }
}

