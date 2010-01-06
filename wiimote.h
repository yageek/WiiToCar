/* 
 * File:   wiimote.h
 * Author: yaya
 *
 * Created on 20 décembre 2009, 17:59
 */

#ifndef _WIIMOTE_H
#define	_WIIMOTE_H

#ifdef	__cplusplus
extern "C" {
#endif

void cwiid_callback(cwiid_wiimote_t *wiimote, int mesg_count,
                    union cwiid_mesg mesg[], struct timespec *timestamp);



#ifdef	__cplusplus
}
#endif

#endif	/* _WIIMOTE_H */

