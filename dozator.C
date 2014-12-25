//Инициализация библиотек и переменных

/*   TCP_Server.c: TCP Server  */
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <icpdas.h>                                
#include "Tcpip32.h"
#include "var.h"              
#define MaxClentSocket 32
#define NUM_OF_SERVICE_PORT 2
fd_set rfds,s_fds;    // server socket set of socket file descriptors for reading
unsigned       ActiveSkt[2]={0, 0};
struct         timeval seltime={0,20};
unsigned short service_port[NUM_OF_SERVICE_PORT]={10000, 502};
int            socketPort[MaxClentSocket];
unsigned int  count_cikl=0;
int answer_to_modbus_tcp(char *bufer, int lenbuf);
status[5]={0,0,0,0,0};//статус запросов 

//Инициализация функций 
/* ============== Расчёт контрольной суммы по алгоритму  CRC16 =====*/
unsigned int CRC16(unsigned char *Data, unsigned int size)
{
 union
  {
   unsigned char  b[2];
   unsigned short w   ;
  } Sum;
 unsigned char  shift_cnt;
 unsigned char  *ptrByte;
 unsigned long  byte_cnt = size;
 ptrByte = Data;
 Sum.w   = 0xffffU;
 for (;byte_cnt>0;byte_cnt--)
  {
   Sum.w=(unsigned short)((Sum.w/256U)*256U+((Sum.w%256U)^(*ptrByte++)));
   for (shift_cnt=0;shift_cnt<8;shift_cnt++)
    {
     if ((Sum.w&0x1)==1)
      Sum.w=(unsigned short)((Sum.w>>1)^0xa001U);
     else Sum.w>>=1;
    }
  }
 return Sum.w;
}
//--------Первый запуск-------
void  firstRunCheck(){//опрос дозаторов при первом запуске
  switch (stack)
   {
	 case 0: curentPerfIzvest = getDozator(adrDoz1, 1, &status[0]);if (status[0]==0) stack++;break;
	 case 1: setPerfIzvest   = getDozator(adrDoz1, 2, &status[1]);if (status[1]==0) stack++;break;
	 case 2: curentPerfSand   = getDozator(adrDoz2, 1, &status[2]);if (status[2]==0) stack++;break;
	 case 3: setPerfSand     = getDozator(adrDoz2, 2, &status[3]);if (status[3]==0) stack++;break;
	}
   if((status[0]==0)&&(status[1]==0)&&(status[2]==0)&&(status[3]==0))
    {
	 firststartdoz=0;stack=0;Print("\r\nNOT FIRSTDOZATOR");
	}
   else
    {
	firststartdoz = 1;
	}//firststartdoz=0;//delete me
}

//------------Анализ состояния системы--------------------
void checkSystem(){
float tmp;
int pc=0;
if (firststartdoz==0){
 //Print("\r\nOK=%d,%d",stack,pc);
 switch(stack){
 	    case 0:while (pc<5)
				{
                 tmp = getDozator(adrDoz1, 1, &status[0]);
			     if (status[0]==0) { 
				 	curentPerfIzvest = tmp;
					break; 
					}
				pc++;
				}
	   		   stack++;	 			   
	    	   break;
	    case 1:while (pc<5)
				{
				tmp = getDozator(adrDoz1, 2, &status[1]);
				if(status[1]==0) { 
					setPerfIzvest = tmp;
					break; 
					}
				pc++;
				}
	   		   stack++;
		  	   break;
	    case 2:while (pc<5)
				{
				tmp = getDozator(adrDoz2, 1, &status[2]);
				if(status[2]==0) { 
					curentPerfSand = tmp;
					break; 
					}
				pc++;
				}
	   		   stack++;
		  	   break;
	    case 3:while (pc<5)
				{
				tmp = getDozator(adrDoz2, 2, &status[3]);
				if(status[3]==0) { 
					setPerfSand = tmp;
					break; 
					}
				pc++;
				}
	   		   stack++;
		  	   break;
	   //---------------Status System------------------------------
	   case 4:while (pc<2)
				{
				tmp = getDozator(adrDoz2, 3, &status[4]);
                //Print("\r\n tmp= %d", tmp);//delete me
				if(status[4]==0) {
					if(tmp == 9)   statusDozator2 = 10;
					Print("\r\nSAND BLOCKED");
					break; 
					}
				pc++;
				}
	   		   stack=0;
		  	   break;
	}
  if((status[0]==1)||(status[1]==1))statusDozator1 = 2;
  else statusDozator1 = 0;
  if((status[2]==1)||(status[3]==1))statusDozator2 = 2;
  else statusDozator2 = 0;//__
  
  curentPerfomanceSummary = curentPerfSand + curentPerfIzvest;//++++++
  //-------------Проверка залипания
  if(statusDozator2==10){
  		Print("\r\nNEDOBOR");
		sandBlocked = 1;//Флаг блокировки песка	
  		}
	else{
		 sandBlocked = 0;
		}
 }	
}
//Управление вибратором-----------------------------------
void vibroToggle(int command){
	 SetPioDir(1,0);
	 switch (command){
	 		case 0:
                   vibro = 0;
		  		   Print("\r\nVibro stopped");
          		   outportb(0,0);
				   break;
			case 1:
				   vibro = 1;
	 	  		   Print("\r\nVibro started on 5 second");
		  		   outportb(0,1);
				   break;
			default:
					break;
	 }
}
//-------------Опрос дозатора---------------------
float getDozator(int NumDVL, int NumCom, int *status){
  
// чтение информации с ДВЛ - дозиметра
 unsigned char command[80];
 int           c1[80];
 unsigned char Answer[255];
 unsigned int  crc,pc,kt  ;
 unsigned long pop=0      ;
 unsigned int  lenans=0   ;
 unsigned int CountBytes  ; 

union
  {
   unsigned long val;
   float sf;
   unsigned char byte[4];
  } ddata; 

switch (NumCom)
  {
   case 1: command[0]=NumDVL;//текущая производительность
           command[1]=0x03;
           command[2]=0x00;
           command[3]=0x2E; //46;
           command[4]=0x00;
           command[5]=0x02; //47;
           CountBytes=6;
           break;
   case 2: command[0]=NumDVL;//плановая производительность
           command[1]=0x03;
           command[2]=0x00;
           command[3]=0x30; //48;
           command[4]=0x00;
           command[5]=0x02; //49;
           CountBytes=6;
   		   break;
   case 3: command[0]=NumDVL;//индикация состояния
           command[1]=0x03;
           command[2]=0x00;
           command[3]=0x23; //35;
           command[4]=0x00;
           command[5]=0x01; //один регистр;
           CountBytes=6;
   		   break;
  }

 crc=CRC16(command,CountBytes);
 command[CountBytes]  =(unsigned char)crc;
 command[CountBytes+1]=(unsigned char)(crc>>8);

ClearCom(2);
 //Print("\r\n");
 //for (pc=0;pc<8;pc++)   Print("%d;",command[pc]);
 for (pc=0;pc<8;pc++)    c1[pc] = command[pc];
 for (pc=0;pc<8;pc++)    ToCom(2,c1[pc])     ;
switch(NumCom){
			   case 1: case 2:
                      pc=0;pop=0;kt=0;lenans=5+4;
					  break;
			   case 3:
			   		  pc=0;pop=0;kt=0;lenans=5+2;
					  break;
} 
 while ((pc!=1)&&(pop<40000L))
  {
   if (IsCom(2))
    if (IsTxBufEmpty(2))
     {
      Answer[kt]=ReadCom(2);
      kt++;
	  if (kt>=lenans) break;
     }
   pop++;
  }
 WaitTransmitOver2();
if (lenans==kt) /* ответ пришёл правильный */
  {
   if (Answer[1]==0x03)
    {
      Print("\r\nReceive is correct from %d",NumDVL);
	  
	  switch (NumCom)
      {
       case 1: case 2: // ответ о производительности 
	   		ddata.byte[3]=Answer[3];
   			ddata.byte[2]=Answer[4];
   			ddata.byte[1]=Answer[5];
   			ddata.byte[0]=Answer[6];
			*status = 0;
			Print("NumCom=%d(%f)",NumCom,ddata.val * 0.01);
   			return ddata.val * 0.01;
			break;
	   case 3://ответ о состоянии системы  
	   		ddata.byte[1]=Answer[3];
            ddata.byte[0]=Answer[4];
			*status = 0;
			Print("Status System=%d",ddata.val);
   			return ddata.val;
			break;	   
      }
     *status = 1;
    }
   else
    {
     Print("\r\nError of receive! Num bytes = %d must been = %d",kt,lenans);
	 *status = 1;
    }
  }
 else /* ответ не пришел */
  {
   Print("\r\nError of receive! Num bytes = %d must been = %d",kt,lenans);
   *status = 1;
  } 
return -1;
}

//-------------Отправка задания дозатору---------------------
int setDozator(int adrDevice, float newVal){
// запись информации в ДВЛ - дозиметра
 unsigned char command[80];
 int           c1[80];
 unsigned char Answer[255];
 unsigned int  crc,pc,kt,crcAnswer;
 unsigned long pop=0;
 unsigned int  lenans=0;
 unsigned int CountBytes; 

union{
	 long value;//4 byte //++? float
	 char byte[4];
	 float f;
}val;

command[0]=adrDevice;                //
command[1]=0x10;//команда записи     //
command[2]=0x00; // адрес            //
command[3]=0x30; // 48;       //
command[4]=0x00; // 
command[5]=0x02; // количество регстров
command[6]=0x04; // байт
CountBytes=11;
//val.f     = newVal*100;   
val.value = (long)((float)newVal*100);
//val.f = newVal*100;
Print("\r\nVal==%d",val.value);
command[7]  = val.byte[3]; 
command[8]  = val.byte[2]; 
command[9]  = val.byte[1]; 
command[10] = val.byte[0]; 

crc=CRC16(command,CountBytes);
command[CountBytes]  =(unsigned char)crc;
command[CountBytes+1]=(unsigned char)(crc>>8); 

//Отсылка запроса на установку значения
ClearCom(2);
 for (pc=0;pc<13;pc++)    c1[pc] = command[pc];
 for (pc=0;pc<13;pc++)    ToCom(2,c1[pc])     ;
 pc=0;pop=0;kt=0;lenans=8;
 while ((pc!=1)&&(pop<20000L))//Получение ответа
  {
   if (IsCom(2))
    if (IsTxBufEmpty(2))
     {
      Answer[kt]=ReadCom(2);
      kt++;if (kt>=lenans) break;
     }
   pop++;
  }
 WaitTransmitOver2();

if (kt>=lenans) /* ответ пришёл правильный */
  {
   Print("\r\n");
   for (pc=0;pc<kt;pc++) Print("%d;",Answer[pc]);
   if ((Answer[0]==command[0])&&(Answer[1]==command[1])&&(Answer[2]==command[2])&&(Answer[3]==command[3])&&(Answer[4]==command[4])&&(Answer[5]==command[5]))
    {
	  crcAnswer=CRC16(Answer,kt-2);
	  if((Answer[6]==(unsigned char)crcAnswer)&&(Answer[7]==(unsigned char)(crcAnswer>>8)))
	  {
	  			Print("\r\nFor Write Correct adr=%d",adrDevice);
     			return 1;
	 			}
	  else{
                Print("\r\nFor Write CRC not correct from adr=%d",adrDevice);
     			return 0;
	 			}
    }
   else //неверный фрейм пакета
    {
     Print("\r\nError: some bytes is lost");
     return 0;
    }
  }
 else /* ответ не пришел */
  {
   Print("\r\nError: some bytes is lost");
   return 0;
  }
}

//Установка активности извести----------------------------
void setIzvActivity(float val){
	 curentIzvestActivity=val;
	 //Print("\r\n Set activity izvest: - %f",curentIzvestActivity);
}
//Установка молотовяжущего--------------------------------
void setMV(float val){
     curentMV=val;
	 //Print("\r\n Set MV:%f ",curentMV);
}
//Установка производительности----------------------------
void setPerfomance(float val){
     neededPerfomanceSummary=val;
     Print("\r\n Set Summary:%f ",neededPerfomanceSummary);
}
//Установка автоматичсеского режима----------------------------
void setAutomaticMode(){
     workmode = 0;
	 Print("\r\n Set AUTOMATIC MODE");
}
//Установка ручного режима----------------------------
void setManualMode(){
     workmode = 1;
	 Print("\r\n Set MANUAL MODE");
}
//Установка производительности извести----------------------------
void setPerfomanceIzvest(float val){
	 int error;
	 error = setDozator(adrDoz1, val);
     if(error==0)		statusDozator1=0;//записалось
	 else				statusDozator1=2;//не записалось
	 Print("\r\n Set perfomance IZVEST:%f ",val);
}
//Установка производительности песка----------------------------
void setPerfomanceSand(float val){
     int error;
	 error = setDozator(adrDoz2, val);
     if(error==0)		statusDozator2=0;//записалось
	 else				statusDozator2=2;//не записалось
	 Print("\r\n Set perfomance SAND:%f ",val);
}
//-------------Отправка данных на АРМ---------------------
void sendDataEth(int current_socket){
int i;
//Заглушка для отладки
tmpbuf.tmpstruct.start[0]=1;
tmpbuf.tmpstruct.start[1]=1;
tmpbuf.tmpstruct.start[2]=1;
tmpbuf.tmpstruct.start[3]=1;
tmpbuf.tmpstruct.start[4]=1;
tmpbuf.tmpstruct.data[0]=workmode;//workmode
tmpbuf.tmpstruct.data[1]=curentPerfIzvest;//текущая производительность извести
tmpbuf.tmpstruct.data[2]=calcPerfIzvest;//вычисленная производительность извести
tmpbuf.tmpstruct.data[3]=curentIzvestActivity;//активность извести
tmpbuf.tmpstruct.data[4]=curentPerfSand;//текущая производительность песка
tmpbuf.tmpstruct.data[5]=calcPerfSand;//вычисленная производительность песка
tmpbuf.tmpstruct.data[6]=curentMV;//Молото вяжущее
tmpbuf.tmpstruct.data[7]=statusDozator1;//Статус дозатора извести
tmpbuf.tmpstruct.data[8]=statusDozator2;//Статус дозатора песка
tmpbuf.tmpstruct.data[9]=curentPerfomanceSummary;//текущая производительность
tmpbuf.tmpstruct.data[10]=neededPerfomanceSummary;//уставка производительности
tmpbuf.tmpstruct.data[11]=vibro;//Вибратор
tmpbuf.tmpstruct.data[12]=setPerfIzvest;//Установленная производительность извести
tmpbuf.tmpstruct.data[13]=setPerfSand;//Установленная производительность песка


//for(i=0;i<61;i++){
//    Print("%d.",tmpbuf.buf[i]);
//	} 
send(current_socket, tmpbuf.buf, 61, 0);
}
//-------------Анализ данных с АРМ---------------------
void analizDataEth(char *buf,int len_buf, int current_socket){
     int error=0;
	 int i,n;
//Реальный буффер
   //Print("Len=%d",len_buf);
   //for (i=0;i<10;i++) Print("=%d=",buf[i]);
   if (len_buf<6) return;
	 for(i=0;i<len_buf-6;i++)
      {
   	   if ((buf[i]==1)&&(buf[i+1]==1)&&(buf[i+2]==1)&&(buf[i+3]==1)&&(buf[i+4]==1))
        {
		if ((i+9)<len_buf){
		   for(n=0;n<10;n++){
		   		answertmpbuf.buf[n]=buf[i+n];
		   		}
           i=i+10;
		   }
         else error=1;
		}
		
		if(error==1) break;
	}	
	//if (!error)		Print("not error\r\n");
	//else            Print("error \r\n");
	if (error){		   
          	   return;
	   }
	//Print("Simbol=%d\r\n",answertmpbuf.tmpstruct.i_command);
	switch (answertmpbuf.tmpstruct.i_command){
		case 105:setIzvActivity(answertmpbuf.tmpstruct.value);//i
			 //Print("\r\n activity recvd: %f",answertmpbuf.tmpstruct.value); 
			 break;
		case 114:sendDataEth(current_socket);//r 
             break;
		case 109:setMV(answertmpbuf.tmpstruct.value);//m 
             break;
 		case 112:setPerfomance(answertmpbuf.tmpstruct.value);//p 
             break;
		case 99:calculateWork();//c            
             break;
		case 97:setAutomaticMode();//a
			 break;
		case 98:setManualMode();//b
			 break;
		case 101:setPerfomanceIzvest(answertmpbuf.tmpstruct.value);//e
			 break;
		case 115:setPerfomanceSand(answertmpbuf.tmpstruct.value);//s
			 break;
        default  : error=1;break;
     } 
}
//-----------Обработчик сети TCP-IP-----------------------
void netWork(int current_socket){
	int iRet;
    char buf[1024];
	iRet=recv(current_socket, buf, 1024, 0);
    if(iRet<=0)
    {
        shutdown(current_socket,2);
		closesocket(current_socket);                    
		FD_CLR(current_socket,&s_fds);
		socketPort[current_socket]=-1;
		if(current_socket>=16)
			ActiveSkt[1]&=~(1<<(current_socket-16));
		else
			ActiveSkt[0]&=~(1<<current_socket);
    }
    else
	{
		buf[iRet]=0x0;
		analizDataEth(buf,iRet,current_socket);	
	}
}
//-------------Формирование задания для дозаторов---------------------
//Актив. М-В(%)/Актив.Извести(%)*Производительность(т.ч)=Дозировка извести(т.ч)
//Дозировка песка = Производительность - Дозировка извести (т.ч)
void calculateWork(){
	 int error1, error2;
	 if(curentIzvestActivity==0)curentIzvestActivity=1;
	 calcPerfIzvest = (curentMV/curentIzvestActivity)*neededPerfomanceSummary;
	 calcPerfSand = neededPerfomanceSummary-calcPerfIzvest;
	 //Print("\r\n Calc is accepted izvest:%f :: Sand:%f",calcPerfIzvest,calcPerfSand);
	 //release
	 error1 = setDozator(adrDoz1, calcPerfIzvest);
	 error2 = setDozator(adrDoz2, calcPerfSand);
	 if(error1==0){
	 	  statusDozator1=0;
	 			   }
	 else{
     	  statusDozator1=2; 
	 }
	 if(error2==0){
	 	  statusDozator2=0;
	 			   }
	 else{
     	  statusDozator2=2; 
	 }//__
}

//-----------------------------------------------------------------------------

void main(void)
{
	struct sockaddr_in serverAdd[2];
	struct sockaddr_in clientAdd;	
	int clientAddLen;
	int new_con,i,c,err;
	int s[2];
	unsigned int kcount=0;
    status[0]=1;status[1]=1;status[2]=1;status[3]=1;
	stack = 0;
	adrDoz1=0x02;//ИЗВЕСТЬ	
	adrDoz2=0x01;//ПЕСОК
	firststartdoz = 1;
	timers_duration[1]=5000;   	 
	vibro = 0;
	vibrotimer=0;
	vibrocounter = 0;
    	
	InitLib();
	TimerOpen();
    InstallCom(2,19200L,8,0,1)    ;
	Print("\r\n Ј 1: €­ЁжЁ «Ё§ жЁп TCP бҐаўҐа !");                  /* инициализация */
	err=NetStart();
	if(err<0)
	{
		Print("\n\rЋиЁЎЄ  Ё­ЁжЁ «Ё§ жЁЁ TCP бҐаўҐа ");
		return;
	}
	
	Print("\r\n Ј 2: ‘®§¤ ­ЁҐ б®ЄҐв®ў Ё Ё¬Ґ­ бўп§Ґ© ¤«п Їа®б«гиЁў Ґ¬ле б®Ґ¤Ё­Ґ­Ё©!");
	for(i=0; i<2; i++)
	{
		s[i]=socket(PF_INET, SOCK_STREAM, 0);
		memset(&serverAdd[i], 0, sizeof(serverAdd[i]));
		serverAdd[i].sin_family= AF_INET;
		serverAdd[i].sin_addr.s_addr= 0;
		serverAdd[i].sin_port= htons(service_port[i]);
		bind(s[i], (struct sockaddr *)&serverAdd[i], sizeof(serverAdd[i]));
		listen(s[i], MaxClentSocket-1);
	}
  
	Print("\r\n Ј 3.1. ®¦Ё¤ ­ЁҐ б®ЄҐв®ў Ё ЇаЁс¬!");
	Print("\r\n Ј 3.2. ўл§®ў бҐаўЁб  Ё ®вўҐв!")   ;
    //setDozator(1,3.42);
	//setDozator(2,2.2);
	//setDozator(1,3.5);
	for(;;)
	{
		
        if(firststartdoz==1){     //проверка первого запуска	
        		firstRunCheck();              	 	
		}
		else
         {
		  
		  if ((kcount%15)==0){ 
		  	 Print("\r\n CheckSystem");checkSystem(); 
			 }//Опрос системы
		  kcount++;
		 }

         if(sandBlocked==1){//Если есть залипание
		 					if((Act(1)==0)&&(vibrotimer==0)){//Если таймер остановлен и не взведен
            							  Print("\r\n Vibro Start-------------------...ACT=%d counter=%d",Act(1),vibrocounter);
										  Run(1);
										  vibrotimer=1;
										  if(vibrocounter<5)	vibroToggle(1);
										  vibrocounter++;
										  //if(vibrocounter == 3) sandBlocked = 0;//Delete this
										  if(vibrocounter>5){
                                                vibrocounter=5; 
                                                sandBlocked=0;
										  }	  
		 					}
							else;
		 }
		 else{
			 //восстанавливаем счетчики и останавливаем вибратор принудительно 
			 Stop(1);
			 vibrotimer = 0;
			 vibrocounter = 0;
			 if(vibro)	vibroToggle(0);
		 }


		 if((Act(1)==0)&&(vibrotimer==1)){//Если таймер остановлен и взведен
         	Print("\r\n Vibro STOP  ---------------------ACT=%d",Act(1));
			vibrotimer = 0;
			Stop(1);
			Run(1);
			vibroToggle(0);							  
		 }
		 else;
		 



		YIELD();
		//Step 3-1: Wait for activity on sockets and accept a connection
		for(i=0; i<2; i++)
		{
			FD_ZERO(&rfds);
			FD_SET(s[i],&rfds);
			
			new_con=selectsocket(MaxClentSocket, &rfds, NULL, NULL, &seltime);	//wait for activity on a set of sockets
			if(new_con>0)
			{
				memset( &clientAdd, 0, sizeof(clientAdd));
				clientAddLen = sizeof(clientAdd);
				c = accept(s[i],(struct sockaddr *)&clientAdd, &clientAddLen);
				Print("create socket %d \n\r",c);
				if(c<0)
				{
					shutdown(c,2);
					closesocket(c);
				}
				else if(c>0 && c<MaxClentSocket)
				{
					FD_SET(c,&s_fds);
					socketPort[c]=service_port[i];
					if(c>=16)
						ActiveSkt[1]|=1<<(c-16);
					else
						ActiveSkt[0]|=1<<c;
					
					SOCKET_SET_TCP_KEEP_ALIVE_ON(c);
				}
			}
		}
		//Step 3-2 perform service, receive and send
		for(i=1; i<MaxClentSocket; i++)
		{
			if(FD_ISSET(i,&s_fds))
			{
				if(!ioctlsocket(i,FIONREAD,&err) && (err>0))
				{
					if(socketPort[i]==10000)
					{
						netWork(i);
					}
                   else Print("\r\nSendPort=%d",socketPort[i]); 
				}
			}
		}
        // опрос по протоколу MODBUS RTU
  
		//Press ESC to terminate the program.
		if(Kbhit() && Getch()=='q')
		{
			Nterm();
            RestoreCom(2);
			TimerClose(); 
			return;
		}
       count_cikl++;
	}
 
}

