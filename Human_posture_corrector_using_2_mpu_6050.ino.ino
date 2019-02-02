#include<Wire.h>
const int MPU2=0x69,MPU1=0x68;
int16_t AcX1,AcY1,AcZ1,Tmp1,GyX1,GyY1,GyZ1;
int16_t AcX2,AcY2,AcZ2,Tmp2,GyX2,GyY2,GyZ2;
bool post;
int count;
//-------------------------------------------------\setup loop\------------------------------------------------------------ 
 void setup(){ 
      pinMode(3,OUTPUT);
      //pinMode(5,OUTPUT);
      count=0;
      post=true;
      Wire.begin(); 
      Wire.beginTransmission(MPU1);
      Wire.write(0x6B);// PWR_MGMT_1 register 
      Wire.write(0); // set to zero (wakes up the MPU-6050)
      Wire.endTransmission(true);Wire.begin(); 
      Wire.beginTransmission(MPU2);
      Wire.write(0x6B);// PWR_MGMT_1 register 
      Wire.write(0); // set to zero (wakes up the MPU-6050)
      Wire.endTransmission(true);
      Serial.begin(9600); 
     } 
     
//---------------------------------------------------\void loop\------------------------------------------------------------
 void loop(){
   
      //get values for first mpu having address of 0x68   
      GetMpuValue1(MPU1);
      GetMpuValue2(MPU2);
      if((GyZ1-GyZ2)>400 || (GyZ1-GyZ2)<-400 )// ||((GyY1-GyY2)100 || (GyY1-GyY2)>-100 ) || ((GyZ1-GyZ2)>100 || (GyZ1-GyZ2)>-100 ))
      { post=false;
        delay(5000);
        GetMpuValue1(MPU1);
        GetMpuValue2(MPU2);
        if((GyZ1-GyZ2)>400 || (GyZ1-GyZ2)<-400 )//||((GyY1-GyY2)>100 || (GyY1-GyY2)>-100 ) || ((GyZ1-GyZ2)>100 || (GyZ1-GyZ2)>-100 ))
        {
          while(post==false)
          {
            vibrate();
           GetMpuValue1(MPU1);
           GetMpuValue2(MPU2);
           if((GyZ1-GyZ2)>400 || (GyZ1-GyZ2)<-400)//||((GyY1-GyY2)>100 || (GyY1-GyY2)>-100 ) || ((GyZ1-GyZ2)>100 || (GyZ1-GyZ2)>-100 ))
           {
            post=false;
            }
           else
           {
            post=true;
            break;
            }
          }
          }            
      }
    }
 
//----------------------------------------------\user defined functions\-------------------------------------------------- 
      
 
 void GetMpuValue1(const int MPU){ 
   
      Wire.beginTransmission(MPU); 
      Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
      Wire.endTransmission(false);
      Wire.requestFrom(MPU, 14, true); // request a total of 14 registers 
      AcX1=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
      AcY1=Wire.read()<<8|  Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
      AcZ1=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 
      Tmp1=Wire.read()<<8| Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L) 
      GyX1=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
      GyY1=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
      GyZ1=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 
      /*Serial.print("AcX = ");
      Serial.print(AcX1);
      Serial.print(" | AcY = "); 
      Serial.print(AcY1);
      Serial.print(" | AcZ = ");
      Serial.print(AcZ1); */
      Serial.print(" | GyX1 = ");
      Serial.print(GyX1); 
      Serial.print(" | GyY1 = "); 
      Serial.print(GyY1);
      Serial.print(" | GyZ1 = ");
      Serial.println(GyZ1); 
      Serial.print("\n*****************************************\n");
     }
     
     
 void GetMpuValue2(const int MPU){ 
   
      Wire.beginTransmission(MPU); 
      Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
      Wire.endTransmission(false);
      Wire.requestFrom(MPU, 14, true); // request a total of 14 registers 
      AcX2=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
      AcY2=Wire.read()<<8|  Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
      AcZ2=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 
      Tmp2=Wire.read()<<8| Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L) 
      GyX2=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
      GyY2=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
      GyZ2=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 
     /* Serial.print("AcX = ");
      Serial.print(AcX2);
      Serial.print(" | AcY = "); 
      Serial.print(AcY2);
      Serial.print(" | AcZ = ");
      Serial.print(AcZ2);  */
      Serial.print(" | GyX2 = ");
      Serial.print(GyX2); 
      Serial.print(" | GyY2 = "); 
      Serial.print(GyY2);
      Serial.print(" | GyZ2 = ");
      Serial.println(GyZ2); 
      Serial.print("\n*****************************************\n");
     
     }
 void vibrate()
 {
  Serial.print("\n OH NO!!! Wrong Posture");
 analogWrite(3,155);
  //analogWrite(5,155);
  delay(2000);
  analogWrite(3,0);      
  //analogWrite(5,0);      
  delay(2000);
 }
  
