#define Run(NumTimer)       timers_time_run[NumTimer]=TimerReadValue();timers_action[NumTimer]=1;                                        // запуск таймера
#define Act(NumTimer)       (((TimerReadValue()-timers_time_run[NumTimer])<timers_duration[NumTimer])&&(timers_action[NumTimer]==1))     // таймер активен
#define Stop(NumTimer)      timers_action[NumTimer]=0;                                                                                   // Останов таймера

union{	//ОТВЕТ НА АРМ
   		 unsigned char buf[66];
   		 struct{
		 		unsigned char start[6];//5
				float         data[15];//56+4 bytes
		 }tmpstruct;
   }tmpbuf;

union{	// СЮДА ЗАПИСАЛИ ИНФОРМАЦИЮ 
		  unsigned char buf[11];
		  struct{
          		 unsigned char start[5];//5 bytes
				 unsigned char nb;//1 byte
		  		 unsigned char i_command;//1 byte                  
		  		 float value;//4 byte
		  }tmpstruct;
	}answertmpbuf; 

float workmode[2];

float curentPerfIzvest[2];//Сколько сыпет извести Сейчас
float curentPerfSand[2];//Сколько сыпет песка Сейчас
float curentPerfomanceSummary[2];//ФАКТ текущей производительности известь + песок

float calcPerfIzvest[2];//Расчет сколько СЫПАТЬ извести 
float calcPerfSand[2]  ;//Расчет сколько СЫПАТЬ песка

float curentMV[2]               ;//Установленное значение молото вяжущего
float curentIzvestActivity[2]   ;//Установленное значение активности извести
float neededPerfomanceSummary[2];//Установленное значение производительности 

float setPerfIzvest[2];//Установленное значение производительности извести
float setPerfSand[2]  ;//Установленное значение производительности песка

int stack;//для поочередного опроса системы

int adrDoz[4];//Адрес 

int ffirststartdoz  ;//Флаг первого запуска
int statusDozator[4];//Статус 1 дозатора
//int statusDozator2;//Статус 2 дозатора 0-norm 1-stop 2-error 10-sand blocked
//int status[10];//4-doz zadanie 5-status sand
//int countFCD;

int vibro[4];
//int vibrotimer;//вибратор взведен 
int vibroLock1;
int vibroLock2;
int vibroTmp;

int Block[4];
//int sandBlockedIz[2] ;//залипание известь 0-нет 1- есть
//int sandBlockedPes[2];//залипание песка   0-нет 1- есть
/*
int vibrocounter1;//счетчик попыток вибратора извести
int vibrocounter2;//счётчик попыток вибратора песка 
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


//Таймеры
// 0 - таймер извести: общая продолжтельность работы вибратора
// 1 - таймер извести: период непрерывной работы вибратора
// 2 - таймер песка  : общая продолжительность работы вибратора
// 3 - таймер песка  : период непрерывной работы вибратора
unsigned char timers_action[8]; 
unsigned long timers_duration[8];
unsigned long timers_time_run[8];
