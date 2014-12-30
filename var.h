#define Run(NumTimer)       timers_time_run[NumTimer]=TimerReadValue();timers_action[NumTimer]=1;                                        // ������ �������
#define Act(NumTimer)       (((TimerReadValue()-timers_time_run[NumTimer])<timers_duration[NumTimer])&&(timers_action[NumTimer]==1))     // ������ �������
#define Stop(NumTimer)      timers_action[NumTimer]=0;                                                                                   // ������� �������

union{	//����� �� ���
   		 unsigned char buf[61];
   		 struct{
		 		unsigned char start[5];//5
				float         data[14];//56 bytes
		 }tmpstruct;
   }tmpbuf;

union{	// ���� �������� ���������� 
		  unsigned char buf[10];
		  struct{
          		 unsigned char start[5];//5 bytes
		  		 unsigned char i_command;//1 byte
		  		 float value;//4 byte
		  }tmpstruct;
	}answertmpbuf; 

float workmode;

float curentPerfIzvest;//������� ����� ������� ������
float curentPerfSand;//������� ����� ����� ������
float curentPerfomanceSummary;//���� ������� ������������������ ������� + �����

float calcPerfIzvest;//������ ������� ������ ������� 
float calcPerfSand;//������ ������� ������ �����

float curentMV;//������������� �������� ������ ��������
float curentIzvestActivity;//������������� �������� ���������� �������
float neededPerfomanceSummary;//������������� �������� ������������������ 

float setPerfIzvest;//������������� �������� ������������������ �������
float setPerfSand;//������������� �������� ������������������ �����

int stack;//��� ������������ ������ �������

int adrDoz1;//����� 1 ��������
int adrDoz2;//����� 2 ��������
int ffirststartdoz;//���� ������� �������
int statusDozator1;//������ 1 ��������
int statusDozator2;//������ 2 �������� 0-norm 1-stop 2-error 10-sand blocked
int status[5];//4-doz zadanie 5-status sand
//int countFCD;

int vibro;
<<<<<<< HEAD
//int vibrotimer;//�������� ������� 
=======
int vibrotimer;//�������� ������� 
>>>>>>> origin/master

int sandBlocked1;//��������� ������� 0-��� 1- ����
int sandBlocked2;//��������� �����   0-��� 1- ����
int vibrocounter1;//������� ������� ��������� �������
int vibrocounter2;//������� ������� ��������� ����� 

unsigned int CRC16(unsigned char *Data, unsigned int size);
void  firstRunCheck(void);
void checkSystem(void);
void vibroToggle(unsigned char command);
float getDozator(int NumDVL, int NumCom, int *status);
int setDozator(int adrDevice, float newVal);
void setIzvActivity(float val);
void setMV(float val);
void setPerfomance(float val);
void sendDataEth(int current_socket); 
void analizDataEth(char *buf,int len_buf, int current_socket);
void netWork(int current_socket);
void calculateWork(void);
void setAutomaticMode(void);
void setManualMode(void);
void setPerfomanceIzvest(float val);
void setPerfomanceSand(float val);


//�������
// 0 - ������ �������: ����� ���������������� ������ ���������
// 1 - ������ �������: ������ ����������� ������ ���������
// 2 - ������ �����  : ����� ����������������� ������ ���������
// 3 - ������ �����  : ������ ����������� ������ ���������
unsigned char timers_action[4]; 
unsigned long timers_duration[4];
unsigned long timers_time_run[4];
