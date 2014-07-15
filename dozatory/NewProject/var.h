#define Run()       timers_time_run=TimerReadValue();timers_action=1;                                             
#define Act()       (((TimerReadValue()-timers_time_run)<timers_duration)&&(timers_action==1))  
#define Stop()      timers_action=0;    

union{	//ÎÒÂÅÒ ÍÀ ÀÐÌ
   		 unsigned char buf[53];
   		 struct{
		 		unsigned char start[5];//5
				float         data[12];//48 bytes
		 }tmpstruct;
   }tmpbuf;

union{	// ÑÞÄÀ ÇÀÏÈÑÀËÈ ÈÍÔÎÐÌÀÖÈÞ 
		  unsigned char buf[10];
		  struct{
          		 unsigned char start[5];//5 bytes
		  		 unsigned char i_command;//1 byte
		  		 float value;//4 byte
		  }tmpstruct;
	}answertmpbuf; 

float workmode;
float curentPerfIzvest;
float calcPerfIzvest;
float curentPerfSand;
float calcPerfSand;
float curentMV;
float curentIzvestActivity;
float curentPerfomanceSummary;
float neededPerfomanceSummary;
float vibro;
int stack;
int adrDoz1;
int adrDoz2;
int firststartdoz;
int statusDozator1;
int statusDozator2;
int status[4];
int countFCD;

unsigned int CRC16(unsigned char *Data, unsigned int size);
void  firstRunCheck();
void checkSystem();
void vibroToggle(int command);
int getDozator(int NumDVL, int NumCom, int *status);
int setDozator(int adrDevice, float newVal);
void setIzvActivity(float val);
void setMV(float val);
void setPerfomance(float val);
void sendDataEth(int current_socket); 
void analizDataEth(char *buf,int len_buf, int current_socket);
void netWork(int current_socket);
void calcWork();


//Òàéìåðû
unsigned char timers_action; 
unsigned long timers_duration;
unsigned long timers_time_run;
