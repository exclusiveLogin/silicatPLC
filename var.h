#define Run(NumTimer)       timers_time_run[NumTimer]=TimerReadValue();timers_action[NumTimer]=1;                                        // запуск таймера
#define Act(NumTimer)       (((TimerReadValue()-timers_time_run[NumTimer])<timers_duration[NumTimer])&&(timers_action[NumTimer]==1))     // таймер активен
#define Stop(NumTimer)      timers_action[NumTimer]=0;                                                                                   // Останов таймера

union{	//ОТВЕТ НА АРМ
   		 unsigned char buf[61];
   		 struct{
		 		unsigned char start[5];//5
				float         data[14];//56 bytes
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

float curentPerfIzvest;//Сколько сыпет извести Сейчас
float curentPerfSand;//Сколько сыпет песка Сейчас
float curentPerfomanceSummary;//ФАКТ текущей производительности известь + песок

float calcPerfIzvest;//Расчет сколько СЫПАТЬ извести 
float calcPerfSand;//Расчет сколько СЫПАТЬ песка

float curentMV;//Установленное значение молото вяжущего
float curentIzvestActivity;//Установленное значение активности извести
float neededPerfomanceSummary;//Установленное значение производительности 

float setPerfIzvest;//Установленное значение производительности извести
float setPerfSand;//Установленное значение производительности песка

int stack;//для поочередного опроса системы

int adrDoz1;//Адрес 1 дозатора
int adrDoz2;//Адрес 2 дозатора
int ffirststartdoz;//Флаг первого запуска
int statusDozator1;//Статус 1 дозатора
int statusDozator2;//Статус 2 дозатора 0-norm 1-stop 2-error 10-sand blocked
int status[5];//4-doz zadanie 5-status sand
//int countFCD;

int vibro;
<<<<<<< HEAD
//int vibrotimer;//вибратор взведен 
=======
int vibrotimer;//вибратор взведен 
>>>>>>> origin/master

int sandBlocked1;//залипание известь 0-нет 1- есть
int sandBlocked2;//залипание песка   0-нет 1- есть
int vibrocounter1;//счетчик попыток вибратора извести
int vibrocounter2;//счётчик попыток вибратора песка 

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


//Таймеры
// 0 - таймер извести: общая продолжтельность работы вибратора
// 1 - таймер извести: период непрерывной работы вибратора
// 2 - таймер песка  : общая продолжительность работы вибратора
// 3 - таймер песка  : период непрерывной работы вибратора
unsigned char timers_action[4]; 
unsigned long timers_duration[4];
unsigned long timers_time_run[4];
