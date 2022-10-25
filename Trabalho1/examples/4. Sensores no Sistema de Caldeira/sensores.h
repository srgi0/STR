#ifndef SENSORES_H
#define SENSORES_H

extern void sensor_put(double temp, double nivel);
extern double sensor_get(char s[5]);
extern void sensor_alarmeT(double limite);

#endif



