
#include <stdint.h>
#ifndef MOTOR_H
#define MOTOR_H
float linermap(float in,float inmin,float inmax,float outmin,float outmax);
float trans360(float in);
class Motor {
private:
    const float ratio;
    float angle=0.f;
    float delta_angle=0.f;
    float ecd_angle=0.f;
    float last_ecd_angle=0.f;
    float delta_ecd_angle=0.f;
    float rotate_speed=0.f;
    float current=0.f;
    float temp=0.f;
public:
    explicit Motor(const float ratio_):ratio(ratio_){}
    void canrxmsgcallback(const uint8_t rdata[8]);
    float getAngle()
    {
        return angle;
    }
};
#endif //MOTOR_H