/* 
 * File:   serial.h
 * Author: yaya
 *
 * Created on 20 décembre 2009, 18:20
 */

#ifndef _SERIAL_H
#define	_SERIAL_H

#ifdef	__cplusplus
extern "C" {
#endif
void LinkToCar(void *data);
int openSerial();
void closeSerial();



#ifdef	__cplusplus
}
#endif

#endif	/* _SERIAL_H */

