#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

void AnalyzeCommandFromPi (void);
void SelectActionFromPi (void);
void SendDone(void);
void SendStart(void);
void SendFailAX12(void);


void DetectSick(int channel);
void ReleaseSick (int channel);
void SendSick_Status(int val8);

void DetectUltrason(void);
void ReleaseUltrason(void);
void SendUltrason_Status(void);


#endif	/* COMMUNICATION_H */

