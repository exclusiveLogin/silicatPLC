#define CountUstavok 12
extern union{	//����� �� ���
   		 unsigned char buf[66];
   		 struct{
		 		unsigned char start[6];//5
				float         data[15];//56+4 bytes
		 }tmpstruct;
   }tmpbuf;

extern union{	// ���� �������� ���������� 
		  unsigned char buf[11];
		  struct{
          		 unsigned char start[5];//5 bytes
				 unsigned char nb;//1 byte
		  		 unsigned char i_command;//1 byte                  
		  		 float value;//4 byte
		  }tmpstruct;
	}answertmpbuf; 

extern float workmode[2];

extern float curentPerfIzvest[2];//������� ����� ������� ������
extern float curentPerfSand[2];//������� ����� ����� ������
extern float curentPerfomanceSummary[2];//���� ������� ������������������ ������� + �����

extern float calcPerfIzvest[2];//������ ������� ������ ������� 
extern float calcPerfSand[2]  ;//������ ������� ������ �����

extern float curentMV[2]               ;//������������� �������� ������ ��������
extern float curentIzvestActivity[2]   ;//������������� �������� ���������� �������e
extern float neededPerfomanceSummary[2];//������������� �������� ������������������ 

extern float setPerfIzvest[2];//������������� �������� ������������������ �������
extern float setPerfSand[2]  ;//������������� �������� ������������������ �����

extern int stack;//��� ������������ ������ �������

extern int adrDoz[4];//����� 

extern int ffirststartdoz  ;//���� ������� �������
extern int statusDozator[4];//������ 1 ��������
//int statusDozator2;//������ 2 �������� 0-norm 1-stop 2-error 10-sand blocked
//int status[10];//4-doz zadanie 5-status sand
//int countFCD;

extern int vibro[4];
//int vibrotimer;//�������� ������� 
extern int vibroLock1;
extern int vibroLock2;
extern int vibroTmp;

extern int Block[4];
//int sandBlockedIz[2] ;//��������� ������� 0-��� 1- ����
//int sandBlockedPes[2];//��������� �����   0-��� 1- ����
/*
extern int vibrocounter1;//������� ������� ��������� �������
extern int vibrocounter2;//������� ������� ��������� ����� 
*/
extern int vibrocounter[4];
extern unsigned int CRC16(unsigned char *Data, unsigned int size);
extern void  firstRunCheck(void);
extern void checkSystem(void);
extern void vibroToggle(unsigned char command);
extern float getDozator(int NumDVL, int NumCom, int *status);
extern int setDozator(int adrDevice, float newVal);
extern int setIzvActivity(unsigned char *buf, int index,float val);
extern int setMV(unsigned char *buf,int index,float val);
extern int setPerfomance(unsigned char *buf,int index, float val);
extern int  sendDataEth(unsigned char *buf,int current_socket, int index); 
extern void analizDataEth(unsigned char *buf,int len_buf, int current_socket);
extern void netWork(int current_socket);
extern int calculateWork(unsigned char *buf,int index);
extern int setAutomaticMode(unsigned char *buf,int index);
extern int setManualMode(unsigned char *buf,int index);
extern int setPerfomanceIzvest(unsigned char *buf,int index, float val);
extern int setPerfomanceSand(unsigned char *buf,int index, float val);


//�������
// 0 - ������ �������: ����� ���������������� ������ ���������
// 1 - ������ �������: ������ ����������� ������ ���������
// 2 - ������ �����  : ����� ����������������� ������ ���������
// 3 - ������ �����  : ������ ����������� ������ ���������
extern unsigned char timers_action[8]; 
extern unsigned long timers_duration[8];
extern unsigned long timers_time_run[8];
union
 {
  unsigned char buffer[512];
  TVarEEPROM    r          ;
 } VarEEPROM,TmpEEPROM; /* ���������� ��� ���������� � EEPROMe */

