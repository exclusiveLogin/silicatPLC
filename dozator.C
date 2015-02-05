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
extern void ReadFromEEPROM(void);
extern void WriteToEEPROM(void) ;

fd_set rfds,s_fds;    // server socket set of socket file descriptors for reading
unsigned char musor[1000];
unsigned       ActiveSkt[2]={0, 0};
struct         timeval seltime={0,20};
unsigned short service_port[NUM_OF_SERVICE_PORT]={10000, 502};
int            socketPort[MaxClentSocket];
unsigned int  count_cikl=0;

int answer_to_modbus_tcp(char *bufer, int lenbuf);
int status[10]={1,1,1,1,1,1,1,1,1,1};//статус запросов 
unsigned char musor1[1000];
float getDozator(int NumDVL, int NumCom, int *status);


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
	 case 0: curentPerfIzvest[0] = getDozator(adrDoz[0], 1, &status[0]); stack++;break;
	 case 1: setPerfIzvest[0]    = getDozator(adrDoz[0], 2, &status[1]); stack++;break;
	 case 2: curentPerfSand[1]   = getDozator(adrDoz[1], 1, &status[2]); stack++;break;
	 case 3: setPerfSand[1]      = getDozator(adrDoz[1], 2, &status[3]); stack++;break;
	 case 4: curentPerfIzvest[2] = getDozator(adrDoz[2], 1, &status[5]); stack++;break;
	 case 5: setPerfIzvest[2]    = getDozator(adrDoz[2], 2, &status[6]); stack++;break;
	 case 6: curentPerfSand[3]   = getDozator(adrDoz[3], 1, &status[7]); stack++;break;
	 case 7: setPerfSand[3]      = getDozator(adrDoz[3], 2, &status[8]); stack++;break;
	}
   if(stack==8) //++?
    {
	 ffirststartdoz=0;stack=0;Print("\r\nNOT FIRSTDOZATOR");
	}
   else
    {
 	  ffirststartdoz = 1;
	}//firststartdoz=0;//delete me
}

//------------Анализ состояния системы--------------------
void checkSystemNum(int index)
{
float tmp;
int pc=0;
static int stack=0;
/*if (ffirststartdoz==0)*/{
 //Print("\r\nOK=%d,%d",stack,pc);
 Print("\r\n CheckSystem=%d;", stack);
 for (pc=0;pc<4;pc++)  Print("(%d=%d)",pc,statusDozator[pc]);
 pc=0;
 switch(stack){
        case 5:
 	    case 0:while (pc<1)
				{
                 tmp = getDozator(adrDoz[index*2], 1, &status[index*5]);
			     if (status[index*5]==0) { 
				 	curentPerfIzvest[index] = tmp;
                    statusDozator[index*2]=statusDozator[index*2]&~1;
					break; 
					}
					else{
					statusDozator[index*2]=statusDozator[index*2]|1;
					}
				pc++;
				}
	   		   stack++;	 			   
	    	   break;
        case 6:
	    case 1:while (pc<5)
				{
				tmp = getDozator(adrDoz[index*2], 2, &status[index*5+1]);
				if(status[index*5+1]==0) { 
					setPerfIzvest[index] = tmp;
                    statusDozator[index*2]=statusDozator[index*2]&~1;
					break; 
					}
				else{
					statusDozator[index*2]=statusDozator[index*2]|1;
					}
				pc++;
				}
			   pc=0;
			   if ((fabs(setPerfIzvest[index]-calcPerfIzvest[index])>0.01)&&(workmode[index]==0)) // установить новое задание 
			    {
				  //if (adrDoz[index*2]==3)
				  // {
 			 	   Print("\r\nSet New Izvest FOR ERROR %f (%f)",setPerfIzvest[index],calcPerfIzvest[index]);
				  /*while (pc<5)

                   {*/ 
                      setDozator(adrDoz[index*2],setPerfIzvest[index])                    ;
                      setDozator(adrDoz[index*2],calcPerfIzvest[index]);/*pc++; }   */ 
                  // }
                  //Print("\r\nEnd New Izvest FOR ERROR");
			    }
	   		   stack++;
		  	   break;
        case 7:
	    case 2:while (pc<5)
				{
				tmp = getDozator(adrDoz[index*2+1], 1, &status[index*5+2]);
				if(status[index*5+2]==0) { 
					statusDozator[index*2+1]=statusDozator[index*2+1]&~1;
                    curentPerfSand[index] = tmp;
					break; 
					}
				else{
					 statusDozator[index*2+1]=statusDozator[index*2+1]|1;
					}
				pc++;
				}
	   		   stack++;
		  	   break;
        case 8:
	    case 3:while (pc<5)
				{
				tmp = getDozator(adrDoz[index*2+1], 2, &status[index*5+3]);
				if(status[index*5+3]==0) { 
                    statusDozator[index*2+1]=statusDozator[index*2+1]&~1;
					setPerfSand[index] = tmp;
					break; 
					}
				else{
					statusDozator[index*2+1]=statusDozator[index*2+1]|1;
					}
				pc++;
				}
			   pc=0;
			   if ((fabs(setPerfSand[index]-calcPerfSand[index])>0.01)&&(workmode[index]==0)) // установить новое задание 
				{
                 //Print("\r\nSet New Sand FOR ERROR %f(%f)",setPerfSand[index],calcPerfSand[index]);
			    /* while (pc<5)
				  { */
				   setDozator(adrDoz[index*2+1],setPerfSand[index]);
                   setDozator(adrDoz[index*2+1],calcPerfSand[index]);
				 /*  pc++;
				  } */
                 //Print("\r\nSet End Sand FOR ERROR");
				}
	   		   stack++;
		  	   break;
	   //---------------Status System------------------------------
       case 9:
	   case 4:
			   if ((status[index*5+0]==0)&&(status[index*5+1]==0))
				{
			     if (setPerfIzvest[index]>0)
			  	  {
                   if (fabs(curentPerfIzvest[index])/setPerfIzvest[index]<0.90) statusDozator[index*2] = statusDozator[index*2] | 4;
				   else statusDozator[index*2] = statusDozator[index*2] & (~4);
				  }
			     else  statusDozator[index*2] = statusDozator[index*2] & (~4);
				}

			   if ((status[index*5+2]==0)&&(status[index*5+3]==0))
				{
			     if (setPerfSand[index]>0)
                  {
				    if (fabs(curentPerfSand[index])/setPerfSand[index]<0.90) statusDozator[index*2+1] =statusDozator[index*2+1] | 4;
				    else statusDozator[index*2+1] = statusDozator[index*2+1] & ~4;
				  }
			     else statusDozator[index*2+1] = statusDozator[index*2+1] & ~4;
				}
	   		   if (index!=0) stack=0; else stack++;
		  	   break;
	}
/*  if((status[0]==1)||(status[1]==1))statusDozator1 = 2;
  else statusDozator1 = 0;
  if((status[2]==1)||(status[3]==1))statusDozator2 = 2;
  else statusDozator2 = 0;//__*/
  
  curentPerfomanceSummary[index] = curentPerfSand[index] + curentPerfIzvest[index];//++++++
  //-------------Проверка залипания
   if ((stack==0)||(stack==5))
   {
  if ((statusDozator[index*2]&4)==4){
  		Print("\r\nNEDOBOR1 %d",index);
		Block[index*2] = 1;//Флаг блокировки песка	
  		}
	else{
		 Block[index*2] = 0;
		}
  if((statusDozator[index*2+1]&4)==4){
  		Print("\r\nNEDOBOR2 %d",index);
		 Block[index*2+1] = 1;//Флаг блокировки песка	
  		}
	else{
		 Block[index*2+1] = 0;
		}
 }	}
}
void checkSystem(){
 static int index=0;
 checkSystemNum(index);
 index=1-index;
// checkSystemNum(1);
}
//Управление вибратором-----------------------------------
void vibroToggle(unsigned char command){
	 outportb(076,command);
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
  //8 float sf;
   unsigned char byte[4];
  } ddata; 
/*if (NumDVL==1||NumDVL==2)
 {
  float ret=0.0;
  ret=NumDVL*10+NumCom;
  *status=0;
  return ret;
 } */
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
 while ((pc!=1)&&(pop<5000L))
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
	//		break;
	   case 3://ответ о состоянии системы  
	   		ddata.byte[1]=Answer[3];
            ddata.byte[0]=Answer[4];
			*status = 0;
			Print("Status System=%d",ddata.val);
   			return ddata.val;
//			break;	   
      }
     *status = 1;
    }
   else
    {
     Print("\r\nError of receive! Num bytes = %d must been = %d NumDVL(1)=%d",kt,lenans,NumDVL);
	 *status = 1;
    }
  }
 else /* ответ не пришел */
  {
   Print("\r\nError of receive! Num bytes = %d must been = %d NumDVL(1)=%d",kt,lenans,NumDVL);
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
//	 float f;
}val;
//if (adrDevice!=3) return 1;
command[0]=adrDevice;                //
command[1]=0x10;//10;//команда записи     //
command[2]=0x00; // адрес            //
command[3]=0x30; // 48;       //
command[4]=0x00; // 
command[5]=0x02; //0x02 количество регстров
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
 for (pc=0;pc<13;pc++)    { c1[pc] = command[pc];Print(">%d",c1[pc]); }
 for (pc=0;pc<13;pc++)    ToCom(2,c1[pc])     ;
 pc=0;pop=0;kt=0;lenans=8;
 while ((pc!=1)&&(pop<5000L))//Получение ответа
  {
   if (IsCom(2))
    if (IsTxBufEmpty(2))
     {
      Answer[kt]=ReadCom(2);
      kt++;//if (kt>=lenans) break;
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
int setIzvActivity(unsigned char *buf,int index, float val){
	 Print("\r\n Set activity izvest: - %f",curentIzvestActivity);
	 curentIzvestActivity[index]=val;
	 buf[0]='o';buf[1]='k';
	 return 2;
}
//Установка молотовяжущего--------------------------------
int setMV(unsigned char *buf,int index, float val){
	 Print("\r\n Set MV:%f ",curentMV);
     curentMV[index]=val;
	 buf[0]='o';buf[1]='k';
	 return 2;
}
//Установка производительности----------------------------
int setPerfomance(unsigned char *buf,int index, float val){
     neededPerfomanceSummary[index]=val;
     Print("\r\n Set Summary:%f ",neededPerfomanceSummary);
	 buf[0]='o';buf[1]='k';
	 return 2;

}
//Установка автоматичсеского режима----------------------------
int setAutomaticMode(unsigned char *buf,int index){
     workmode[index] = 0;
	 Print("\r\n Set AUTOMATIC MODE");
	 buf[0]='o';buf[1]='k';
	 return 2;
}
//Установка ручного режима----------------------------
int setManualMode(unsigned char *buf,int index){
     workmode[index] = 1;
	 Print("\r\n Set MANUAL MODE");
	 buf[0]='o';buf[1]='k';
	 return 2;
}
//Установка производительности извести----------------------------
int setPerfomanceIzvest(unsigned char *buf,int index, float val){
	 int error;
	 error = setDozator(adrDoz[index*2],  0 );
	 error = setDozator(adrDoz[index*2], val);
     if(error==0)		statusDozator[index*2]=statusDozator[index*2]&~1;//записалось
	 else				statusDozator[index*2]=statusDozator[index*2]| 1;//не записалось
	 Print("\r\n Set perfomance IZVEST:%f ",val);
	 buf[0]='o';buf[1]='k';
	 return 2;
}
//Установка производительности песка----------------------------
int setPerfomanceSand(unsigned char *buf,int index, float val){
     int error;
	 error = setDozator(adrDoz[index*2+1], 0  );
	 error = setDozator(adrDoz[index*2+1], val);
     if(error==0)		statusDozator[index*2+1]=statusDozator[index*2+1]&~1;//записалось
	 else				statusDozator[index*2+1]=statusDozator[index*2+1]| 1;//не записалось
	 Print("\r\n Set perfomance SAND:%f ",val);
	 buf[0]='o';buf[1]='k';
	 return 2;
}
//-------------Отправка данных на АРМ---------------------
int sendDataEth(unsigned char *buf,int current_socket, int index){
int i;
//Заглушка для отладки
tmpbuf.tmpstruct.start[0]=1;
tmpbuf.tmpstruct.start[1]=1;
tmpbuf.tmpstruct.start[2]=1;
tmpbuf.tmpstruct.start[3]=1;
tmpbuf.tmpstruct.start[4]=1;
tmpbuf.tmpstruct.start[5]=index;
tmpbuf.tmpstruct.data[0]=workmode[index];//workmode
tmpbuf.tmpstruct.data[1]=curentPerfIzvest[index];//текущая производительность извести
tmpbuf.tmpstruct.data[2]=calcPerfIzvest[index];//вычисленная производительность извести
tmpbuf.tmpstruct.data[3]=curentIzvestActivity[index];//активность извести
tmpbuf.tmpstruct.data[4]=curentPerfSand[index];//текущая производительность песка
tmpbuf.tmpstruct.data[5]=calcPerfSand[index];//вычисленная производительность песка
tmpbuf.tmpstruct.data[6]=curentMV[index];//Молото вяжущее
tmpbuf.tmpstruct.data[7]=statusDozator[index*2]  ;//Статус дозатора извести
tmpbuf.tmpstruct.data[8]=statusDozator[index*2+1];//Статус дозатора песка
tmpbuf.tmpstruct.data[9]=curentPerfomanceSummary[index];//текущая производительность
tmpbuf.tmpstruct.data[10]=neededPerfomanceSummary[index];//уставка производительности
tmpbuf.tmpstruct.data[11]=vibro[index*2];//++?Вибратор
tmpbuf.tmpstruct.data[12]=vibro[index*2+1];//++?Вибратор
tmpbuf.tmpstruct.data[13]=setPerfIzvest[index];//Установленная производительность извести
tmpbuf.tmpstruct.data[14]=setPerfSand[index];//Установленная производительность песка



for(i=0;i<66;i++){  buf[i]=tmpbuf.buf[i]; 
 //   Print("==%d.",tmpbuf.buf[i]);
	} 
 send(current_socket, buf, 66, 0);
 return 66;
}
//-------------Анализ данных с АРМ---------------------
void analizDataEth(unsigned char *buf,int len_buf, int current_socket){
     int error=0;
	 int i,n;
     int index=0;
	 int len_answ=0;
	 char buffer_send[1024];
//Реальный буффер
   Print("Len=%d\r\n",len_buf);
   for (i=0;i<11;i++) Print("=%d=",buf[i]);
   if (len_buf<6) return;
	 for(i=0;i<len_buf-6;i++) //++?
      {
   	   if ((buf[i]==1)&&(buf[i+1]==1)&&(buf[i+2]==1)&&(buf[i+3]==1)&&(buf[i+4]==1)&&((buf[i+5]==0)||(buf[i+5]==1)))
        {
        index=buf[i+5];   
		if (11<=len_buf){
		   for(n=0;n<11;n++){
		   		answertmpbuf.buf[n]=buf[i+n];
		   		}
			break;
		   }
         else error=1;
		}
		
		if(error==1) break;
	}	
	//if (!error)		Print("not error\r\n");
	//else            Print("error \r\n");
	if (error){	
	           len_answ=3;buffer_send[0]='e';buffer_send[2]='r';buffer_send[3]='r';
               send(current_socket,buffer_send,len_answ,0);
          	   return;
	   }
	//Print("Simbol=%d\r\n",answertmpbuf.tmpstruct.i_command);
	switch (answertmpbuf.tmpstruct.i_command){
		case 105:len_answ=setIzvActivity(buffer_send,index,answertmpbuf.tmpstruct.value);//i
			 //Print("\r\n activity recvd: %f",answertmpbuf.tmpstruct.value); 
			 break;
		case 114:len_answ=sendDataEth(buffer_send,current_socket,index);
                 Print("\r\nREAD");//r 
             break;
		case 109:len_answ=setMV(buffer_send,index,answertmpbuf.tmpstruct.value);//m 
             break;
 		case 112:len_answ=setPerfomance(buffer_send,index,answertmpbuf.tmpstruct.value);//p 
             break;
		case 99:len_answ=calculateWork(buffer_send,index);//c            
             break;
		case 97:len_answ=setAutomaticMode(buffer_send,index);//a
			 break;
		case 98:len_answ=setManualMode(buffer_send,index);//b
			 break;
		case 101:len_answ=setPerfomanceIzvest(buffer_send,index,answertmpbuf.tmpstruct.value);//e
			 break;
		case 115:len_answ=setPerfomanceSand(buffer_send,index,answertmpbuf.tmpstruct.value);//s
			 break;
        default  : error=1;break;
     } 
    if (len_answ==0) { len_answ=3;buffer_send[0]='e';buffer_send[2]='r';buffer_send[3]='r'; }
	send(current_socket,buffer_send,len_answ,0);
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
	//	buf[iRet]=0x0;
		analizDataEth(buf,iRet,current_socket);	
        WriteToEEPROM();
	}
}
//-------------Формирование задания для дозаторов---------------------
//Актив. М-В(%)/Актив.Извести(%)*Производительность(т.ч)=Дозировка извести(т.ч)
//Дозировка песка = Производительность - Дозировка извести (т.ч)
int calculateWork(unsigned char *buf,int index){
	 int error1, error2;
	 if(curentIzvestActivity[index]==0) curentIzvestActivity[index]=1;
	 calcPerfIzvest[index] = (curentMV[index]/curentIzvestActivity[index])*neededPerfomanceSummary[index];
	 calcPerfSand[index]   = neededPerfomanceSummary[index]-calcPerfIzvest[index];
	 //Print("\r\n Calc is accepted izvest:%f :: Sand:%f",calcPerfIzvest,calcPerfSand);
	 //release
	 error1 = setDozator(adrDoz[index*2]  , 0);
	 error1 = setDozator(adrDoz[index*2]  , calcPerfIzvest[index]);
	 error2 = setDozator(adrDoz[index*2+1], 0);
	 error2 = setDozator(adrDoz[index*2+1], calcPerfSand[index]);
	 if(error1==0){
	 	  statusDozator[index*2]=statusDozator[index*2]&~1;
	 			   }
	 else{
     	  statusDozator[index*2]=statusDozator[index*2]|1; 
	 }
	 if(error2==0){
	 	  statusDozator[index*2+1]=statusDozator[index*2+1]&~1;
	 			   }
	 else{
     	  statusDozator[index*2+1]=statusDozator[index*2+1]|1; 
	 }//__
 buf[0]='o';buf[1]='k';return 2;
}

//-----------------------------------------------------------------------------
void timers_vibrat(int NumVib)
{
 if (((Block[NumVib]==1)&&(vibrocounter[NumVib]==0))||(Act(NumVib*2))) // залипание извести или не обработан таймер общего вибрирования
  {
	if (vibrocounter[NumVib]==0) // первое залипание
     {
	  vibrocounter[NumVib]=1;
	  Run(NumVib*2);  Run(NumVib*2+1);  // запуск таймеров
 	 }
    else
	 {
      if (Act(NumVib*2)) // не истёк общий таймер вибрирования
       {
		 if (Act(NumVib*2+1)) // не истек таймер непрерыного вибрирования
				 ;
		 else // истёк таймер непрерывного вибрирования
		  {
			vibrocounter[NumVib]++;
		    Stop(NumVib*2+1)      ;// Повторный запуск если не исчезло залипание
            if (Block[NumVib]==1) Run(NumVib*2+1);
		  }
	   }
	  else // истёк общий тамер вибрирования
	   {
	    Stop(NumVib*2); // остановить таймер вибрированя
        Stop(NumVib*2+1); // остановить тамер непрерывного вибрирования
	   }
	}
  }
 else if (Block[NumVib]==0) // нет залипания вибрирование помогло
  {
   vibrocounter[NumVib]=0;
   statusDozator[NumVib]=statusDozator[NumVib]&~8;
  }
 else // залипание вибрирование не помогло
  {
   statusDozator[NumVib]=statusDozator[NumVib]|8; //++? Вибрирование не помогло
  }
}
void main(void)
{
	struct sockaddr_in serverAdd[2];
	struct sockaddr_in clientAdd;	
	int clientAddLen;
	int new_con,i,c,err;
	int s[2];
	int upr_code=0;
    int pc;
    int deb=0;
	unsigned int kcount=0;
	for (pc=0;pc<10;pc++) status[pc]=1;
	for (pc=0;pc<4;pc++)  vibrocounter[pc]=0;
	stack = 0;
	adrDoz[0]=0x02;//ИЗВЕСТЬ	
	adrDoz[1]=0x01;//ПЕСОК
	adrDoz[2]=0x03;//ИЗВЕСТЬ	
	adrDoz[3]=0x04;//ПЕСОК
	ffirststartdoz = 1;  // устанавливаем флаг первого запуска
	timers_duration[0]=30000;  // вибрировать 30 секунд.
	timers_duration[1]= 5000;  // по 5 секунд. 	 
	timers_duration[2]=30000;  // вибрировать 30 секунд.
	timers_duration[3]= 5000;  // по 5 секунд. 	 
	timers_duration[4]=30000;  // вибрировать 30 секунд.
	timers_duration[5]= 5000;  // по 5 секунд. 	 
	timers_duration[6]=30000;  // вибрировать 30 секунд.
	timers_duration[7]= 5000;  // по 5 секунд. 	 
	vibro[0] = 0;
	vibro[1] = 0;
	vibro[2] = 0;
	vibro[3] = 0;
//	vibrotimer=0;
//	vibrocounter1 = 0;
//	vibrocounter2 = 0;
/*	sandBlocked1=1; //del
	sandBlocked2=1; //del */
	vibroLock1 = 0;
	vibroLock2 = 0;
	
    	
	InitLib();
	TimerOpen();
    InstallCom(2,19200L,8,0,1)    ;
	if (deb==1)
     {
       workmode[0]               =0;//workmode
       calcPerfIzvest[0]         =3.24;//вычисленная производительность извести
       curentIzvestActivity[0]   =76.7;//активность извести
       calcPerfSand[0]           =3.76;//вычисленная производительность песка
       curentMV[0]               =35.5;//Молото вяжущее
       neededPerfomanceSummary[0]=7.0 ;//уставка производительности
       workmode[1]               =0;//workmode
       calcPerfIzvest[1]         =3.29;//вычисленная производительность извести
       curentIzvestActivity[1]   =76.2;//активность извести
       calcPerfSand[1]           =3.71;//вычисленная производительность песка
       curentMV[1]               =35.8;//Молото вяжущее
       neededPerfomanceSummary[1]=7.0 ;//уставка производительности
       WriteToEEPROM();
	 }
	else ReadFromEEPROM();
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
		if(Kbhit() && Getch()=='q')//Выход по Esc
		{
			Nterm();
            RestoreCom(2);
			TimerClose(); 
			return;
		} 

        if(ffirststartdoz==1){     //проверка первого запуска	
        	firstRunCheck(); 
        //   ffirststartdoz==0;             	 	
		}
		else
         {
		  
		  if ((kcount%50)==0){ 
		  	  checkSystem(); 
			 }//Опрос системы
		  kcount++;
		 }       
		// БЛОК ВИБРИРОВАНИЯ ПО ИЗВЕСТИ
		vibroTmp = inportb(0);
		//Print("\r\nvibroTmp %d",vibroTmp);
		
		for (pc=0;pc<4;pc++) { timers_vibrat(pc);vibro[pc]=0; }
/*		if (((sandBlocked1==1)&&(vibrocounter1==0))||(Act(0))) // залипание извести или не обработан таймер общего вибрирования
		 {
		   if (vibrocounter1==0) // первое залипание
            {
			 vibrocounter1=1;
			 Run(0);  Run(1);  // запуск таймеров
			}
		   else          
			{
              if (Act(0)) // не истёк общий таймер вибрирования
               {
				if (Act(1)) // не истек таймер непрерыного вибрирования
				 ;
				else // истёк таймер непрерывного вибрирования)
				 {
				  vibrocounter1++;
				  Stop(1);// Повторный запуск если не исчезло залипание
                  if (sandBlocked1==1) Run(1);
				 }
			   }
			  else // истёк общий тамер вибрирования
			   {
				 Stop(0); // остановить таймер вибрированя
				 Stop(1); // остановить тамер непрерывного вибрирования
			   }
			}
		 }
		else if (sandBlocked1==0) // нет залипания вибрирование помогло
		 {
		  vibrocounter1=0;
	 	 }
		 // БЛОК ВИБРИРОВАНИЯ ПО ПЕСКУ
		if (((sandBlocked2==1)&&(vibrocounter2==0))||(Act(2))) // залипание песка или не обработан таймер общего вибрирования
		 {
		   if (vibrocounter2==0) // первое залипание
            {
			 vibrocounter2=1;
			 Run(2);  Run(3);  // запуск таймеров
			}
		   else
			{
              if (Act(2)) // не истёк общий таймер вибрирования
               {
				if (Act(3)) // не истек таймер непрерыного вибрирования
				 ;
				else // истёк таймер непрерывного вибрирования)
				 {
				  vibrocounter2++;
				  Stop(3);// Повторный запуск если не исчезло залипание
                  if (sandBlocked2==1) Run(3);
				 }
			   }
			  else // истёк общий тамер вибрирования
			   {
				 Stop(2); // остановить таймер вибрированя
				 Stop(3); // остановить тамер непрерывного вибрирования
			   }
			}
		 }
		else if (sandBlocked2==0) // нет залипания вибрирование помогло
		 {
		  vibrocounter2=0;
	 	 }*/
		upr_code=0;   //++?
//		if (~vibroTmp&1==1) { Stop(0);Stop(1);vibrocounter1=0;} // блокировка по извести
//		if (~vibroTmp&2==2) { Stop(2);Stop(3);vibrocounter2=0;} // блокировка по песку
          
		if ((Act(1))&&(vibrocounter[0]%2==1)) { upr_code=upr_code+1;vibro[0]=1; }
		if ((Act(3))&&(vibrocounter[1]%2==1)) { upr_code=upr_code+2;vibro[1]=1; }
		if ((Act(5))&&(vibrocounter[2]%2==1)) { upr_code=upr_code+4;vibro[2]=1; }
		if ((Act(7))&&(vibrocounter[3]%2==1)) { upr_code=upr_code+8;vibro[3]=1; }
	//	if (vibro==1) Print("\r\nWKL %d",upr_code); 
        vibroToggle(upr_code);


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
						Print("\r\n1");netWork(i);Print("\r\n2");
					}
                   else Print("\r\nSendPort=%d",socketPort[i]); 
				}
			}
		}
        // опрос по протоколу MODBUS RTU
        
	}
 
}

