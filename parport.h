#ifndef PARPORT_H
#define PARPORT_H

#include "main.h"

BYTE receive_data(BYTE dest);
void send_data(BYTE dest, BYTE data);
void init_parport(void);
void cleanup_parport(void);

#endif // PARPORT_H
