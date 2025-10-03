
#include "motor.h"
float ratio=19.2;
float linermap(float in,float inmin,float inmax,float outmin,float outmax){
   float out;
   out=(in-inmin)*(outmax-outmin)/(inmax-inmin)+outmin;
return out;
}
float trans360(float in)
{
    while (in>360.0)
   {in-=360.0;}
    while (in<0.0)
   {in+=360.0;}
    return in;
}
void Motor::canrxmsgcallback(const uint8_t rdata[8]){
   temp=rdata[6];
   int I=(rdata[4]<<8)|rdata[5];
   current=linermap(I,-16384,16384,-20,20);
   rotate_speed=(rdata[2]<<8)|rdata[3];
   last_ecd_angle=ecd_angle;
   ecd_angle=(rdata[0]<<8)|rdata[1];
   delta_ecd_angle=ecd_angle-last_ecd_angle;
   delta_angle=linermap(delta_ecd_angle,0,8191,0.0,360.0)/ratio;
   delta_angle=trans360(delta_angle);
   angle+=delta_angle;

}
Motor motor1(ratio);