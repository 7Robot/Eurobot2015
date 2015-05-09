
#ifndef __ULTRASON
#define __ULTRASON


void Init_Ultrasons (void);

#define ULTRASON_THRESOLD  300      // seuil d'alarme en mm
#define ULTRASON_THRESOLD_TRIGGER   50      // zone du triger de schmitt


#define PIN_ULTRASON        _RC5            // RC5 = connecteur 5V n2?
#define TRIS_ULTRASON       _TRISC5
#define PIN_CN_ULTRASON_IE  _CN26IE

#define U_ETAT_OFF              0x00
#define U_ETAT_FOR_SEND1        0x01
#define U_ETAT_SEND1            0x02
#define U_ETAT_WAIT1            0x04
#define U_ETAT_WAIT0            0x08
#define U_ETAT_WAIT0_OVERSHOOT  0x10
#define U_ETAT_WAIT_FOR_RESTART 0x20


extern volatile uint8_t Etat_Ultrason;
extern volatile uint16_t Mesure_Timer_Ultrason;     // mesure brutale du timer
extern volatile uint16_t Mesure_Distance_Ultrason;  // distance en mm
extern uint8_t Sector_Ultrason;

extern volatile uint8_t Debug_Ultrason;
extern volatile uint16_t count_Debug_Ultrason;

void Init_Ultrasons(void);

void Start_Stop_Debug_Ultrason(void);



#endif

