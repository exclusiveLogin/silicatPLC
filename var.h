#define Run(NumTimer)       timers_time_run[NumTimer]=TimerReadValue();timers_action[NumTimer]=1;                                        // запуск таймера
#define Act(NumTimer)       (((TimerReadValue()-timers_time_run[NumTimer])<timers_duration[NumTimer])&&(timers_action[NumTimer]==1))     // таймер активен
#define Stop(NumTimer)      timers_action[NumTimer]=0;                                                                                   // Останов таймера

union{	//ОТВЕТ НА АРМ
   		 unsigned char buf[53];
   		 struct{
		 		unsigned char start[5];//5
				float         data[12];//48 bytes
		 }tmpstruct;
   }tmpbuf;

union{	// СЮДА ЗАПИСАЛИ ИНФОРМАЦИЮ 
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
float oldPerfIzvest;
float oldPerfSand;
int stack;
int adrDoz1;
int adrDoz2;
int firststartdoz;
int statusDozator1;
int statusDozator2;
int status[4];
int countFCD;
int vibrotimer;

unsigned int CRC16(unsigned char *Data, unsigned int size);
void  firstRunCheck(void);
void checkSystem(void);
void vibroToggle(int command);
float getDozator(int NumDVL, int NumCom, int *status);
int setDozator(int adrDevice, float newVal);
void setIzvActivity(float val);
void setMV(float val);
void setPerfomance(float val);
void sendDataEth(int current_socket); 
void analizDataEth(char *buf,int len_buf, int current_socket);
void netWork(int current_socket);
void calculateWork(void);


//Таймеры
unsigned char timers_action[2]; 
unsigned long timers_duration[2];
unsigned long timers_time_run[2];
