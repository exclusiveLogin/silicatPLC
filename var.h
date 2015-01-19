#define Run(NumTimer)       timers_time_run[NumTimer]=TimerReadValue();timers_action[NumTimer]=1;                                        // ������ �������
#define Act(NumTimer)       (((TimerReadValue()-timers_time_run[NumTimer])<timers_duration[NumTimer])&&(timers_action[NumTimer]==1))     // ������ �������
#define Stop(NumTimer)      timers_action[NumTimer]=0;                                                                                   // ������� �������

union{	//����� �� ���
   		 unsigned char buf[66];
   		 struct{
		 		unsigned char start[6];//5
				float         data[15];//56+4 bytes
		 }tmpstruct;
   }tmpbuf;

union{	// ���� �������� ���������� 
		  unsigned char buf[11];
		  struct{
          		 unsigned char start[5];//5 bytes
				 unsigned char nb;//1 byte
		  		 unsigned char i_command;//1 byte                  
		  		 float value;//4 byte
		  }tmpstruct;
	}answertmpbuf; 

float workmode[2];

float curentPerfIzvest[2];//������� ����� ������� ������
float curentPerfSand[2];//������� ����� ����� ������
float curentPerfomanceSummary[2];//���� ������� ������������������ ������� + �����

float calcPerfIzvest[2];//������ ������� ������ ������� 
float calcPerfSand[2]  ;//������ ������� ������ �����

float curentMV[2]               ;//������������� �������� ������ ��������
float curentIzvestActivity[2]   ;//������������� �������� ���������� �������
float neededPerfomanceSummary[2];//������������� �������� ������������������ 

float setPerfIzvest[2];//������������� �������� ������������������ �������
float setPerfSand[2]  ;//������������� �������� ������������������ �����

int stack;//��� ������������ ������ �������

int adrDoz[4];//����� 

int ffirststartdoz  ;//���� ������� �������
int statusDozator[4];//������ 1 ��������
//int statusDozator2;//������ 2 �������� 0-norm 1-stop 2-error 10-sand blocked
//int status[10];//4-doz zadanie 5-status sand
//int countFCD;

int vibro[4];
//int vibrotimer;//�������� ������� 
int vibroLock1;
int vibroLock2;
int vibroTmp;

int Block[4];
//int sandBlockedIz[2] ;//��������� ������� 0-��� 1- ����
//int sandBlockedPes[2];//��������� �����   0-��� 1- ����
/*
int vibrocounter1;//������� ������� ��������� �������
int vibrocounter2;//������� ������� ��������� ����� 
*/
int vibrocounter[4];
unsigned int CRC16(unsigned char *Data, unsigned int size);
void  firstRunCheck(void);
void checkSystem(void);
void vibroToggle(unsigned char command);
float getDozator(int NumDVL, int NumCom, int *status);
int setDozator(int adrDevice, float newVal);
void setIzvActivity(int index,float val);
void setMV(int index,float val);
void setPerfomance(int index, float val);
void sendDataEth(int current_socket, int index); 
void analizDataEth(char *buf,int len_buf, int current_socket);
void netWork(int current_socket);
void calculateWork(int index);
void setAutomaticMode(int index);
void setManualMode(int index);
void setPerfomanceIzvest(int index, float val);
void setPerfomanceSand(int index, float val);


//�������
// 0 - ������ �������: ����� ���������������� ������ ���������
// 1 - ������ �������: ������ ����������� ������ ���������
// 2 - ������ �����  : ����� ����������������� ������ ���������
// 3 - ������ �����  : ������ ����������� ������ ���������
unsigned char timers_action[8]; 
unsigned long timers_duration[8];
unsigned long timers_time_run[8];
