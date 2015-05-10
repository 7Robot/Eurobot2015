#ifndef _LIB_ASSERV_DEFAULT_H_
#define _LIB_ASSERV_DEFAULT_H_

#include "../communication.h"

#ifndef NULL
#define NULL 0
#endif


/*############################################################################*/
/*                                  Motion                                    */
/*############################################################################*/

#ifndef DEFAULT_CONSTRAINT_V_MAX
#define DEFAULT_CONSTRAINT_V_MAX {0.5, 6} // 1.2 normal, 0.5 homologation
#endif

#ifndef DEFAULT_CONSTRAINT_A_MAX
#define DEFAULT_CONSTRAINT_A_MAX {0.50, 0.50, 0.30}
#endif

#ifndef BLOCK_LIMIT
#define BLOCK_LIMIT 500000
#endif

/*############################################################################*/
/*                                    Odo                                     */
/*############################################################################*/

#ifndef DEFAULT_ODO_COEFS
#define DEFAULT_ODO_COEFS {54327, 0.000018407, 0.287}
#endif

#ifndef DEFAULT_PERIOD
#define DEFAULT_PERIOD 0.008
#endif

/*############################################################################*/
/*                                  Asserv                                    */
/*############################################################################*/

#ifndef DEFAULT_ASSERV_MODE
#define DEFAULT_ASSERV_MODE ASSERV_MODE_OFF
#endif
#ifndef DEFAULT_STOP_DISTANCE
#define DEFAULT_STOP_DISTANCE 0.008
#endif

/*############################################################################*/
/*                                   PID                                      */
/*############################################################################*/

// 4 asserv différentes (position et vitese pour chaque roue) donc 4 PID
#ifndef DEFAULT_PID_COEFS_DELTA
#define DEFAULT_PID_COEFS_DELTA {100,20,0,0,0} //{200,70,900,0.3,0.8}{130,90,3000,0.5,0.9}{200,30,30,0,0}{200,20,0,0,0}
#endif
#ifndef DEFAULT_PID_COEFS_ALPHA
#define DEFAULT_PID_COEFS_ALPHA {20,8,0,0,0} //{10,5,30,0,0.7}{20,10,0,0,0}
#endif

// valeurs max de l'intégrale en position et en vitesse
#ifndef DEFAULT_PID_MAX_INT_DELTA
#define DEFAULT_PID_MAX_INT_DELTA 0.7 // 0.7
#endif
#ifndef DEFAULT_PID_MAX_INT_ALPHA
#define DEFAULT_PID_MAX_INT_ALPHA 0.8
#endif
/*
#ifndef DEFAULT_PID_COEFS_VG
#define DEFAULT_PID_COEFS_VG {400,4,50,0.7,0.7}
#endif
#ifndef DEFAULT_PID_COEFS_VD
#define DEFAULT_PID_COEFS_VD {400,4,50,0.7,0.7}
#endif
 */

// valeurs max de l'intégrale en position et en vitesse
#ifndef DEFAULT_PID_MAX_INT_DELTA
#define DEFAULT_PID_MAX_INT_DELTA 0.5 // 0.7
#endif
#ifndef DEFAULT_PID_MAX_INT_ALPHA
#define DEFAULT_PID_MAX_INT_ALPHA 5
#endif

// ainsi que les conditions d'arrêt des PID en position et vitesse
#ifndef DEFAULT_PID_EPS_DELTA
#define DEFAULT_PID_EPS_DELTA {0.02,0.02}//0.02
#endif
#ifndef DEFAULT_PID_EPS_ALPHA
#define DEFAULT_PID_EPS_ALPHA {0.02,0.02}
#endif

/*############################################################################*/
/*                                  DEBUG                                     */
/*############################################################################*/

#ifndef DEFAULT_DEBUG_MODE
#define DEFAULT_DEBUG_MODE 0
#endif

#endif // _LIB_ASSERV_DEFAULT_H_