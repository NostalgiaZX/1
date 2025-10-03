
#include "motor.h"
float ratio = 19.2;
float linermap(float in, float inmin, float inmax, float outmin, float outmax) {
    float out;
    out = (in - inmin) * (outmax - outmin) / (inmax - inmin) + outmin;
    return out;
}
float trans360(float in) {
    while (in > 180.0) {
        in -= 360.0;
    }
    while (in < -180.0) {
        in += 360.0;
    }
    return in;
}
void Motor::canrxmsgcallback(const uint8_t rdata[8]) {
    temp = rdata[6];
    auto I = static_cast<int16_t>((rdata[4] << 8) | rdata[5]);
    current = linermap(I, -16384, 16384, -20, 20);
    auto temp = static_cast<int16_t>((rdata[2] << 8) | rdata[3]);
    rotate_speed = (float)temp / 19.2;
    last_ecd_angle = ecd_angle;
    ecd_angle = linermap((rdata[0] << 8) | rdata[1], 0, 8191, 0, 360);
    delta_ecd_angle = trans360(ecd_angle - last_ecd_angle);
    delta_angle = delta_ecd_angle / ratio;
    angle += delta_angle;
}
Motor motor1(ratio);