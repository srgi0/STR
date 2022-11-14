#ifndef SENSORES_H
#define SENSORES_H

void sensor_put(double temp, double nivel);
void sensor_put2(double Ta, double Ti, double No);
double sensor_get(char s[2]);
void sensor_alarmeT(double limite);

#endif



