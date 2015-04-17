#include "asserv.h"
#include "motion.h"
#include "odo.h"
#include "pid.h"
#include "debug.h"

// asserv
extern volatile int asserv_mode;
extern volatile PositionAsserv pos_asserv;
extern volatile SpeedAsserv speed_asserv;
extern volatile AngleAsserv angle_asserv;

// motion
extern volatile float motion_initialized;
extern volatile MotionState motionState;
extern volatile MotionConstraint motionConstraint;
extern volatile int blocked;
extern volatile MotionSequence motionSequence;

// odo
extern volatile Odo odo;

// debug
extern volatile int debug_mode;
extern volatile int debug_count;
//extern volatile SpeedDebug speedDebug;
//extern volatile PosDebug posDebug;