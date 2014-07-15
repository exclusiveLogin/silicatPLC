//Инициализация библиотек и переменных

/*   TCP_Server.c: TCP Server  */
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <icpdas.h>                   
#include "Tcpip32.h"              
#define MaxClentSocket 32
#define NUM_OF_SERVICE_PORT 3
fd_set rfds,s_fds;    // server socket set of socket file descriptors for reading
unsigned       ActiveSkt[2]={0, 0};
struct         timeval seltime={0,20};
unsigned short service_port[NUM_OF_SERVICE_PORT]={20001, 502, 10000};
int            socketPort[MaxClentSocket];
unsigned int  count_cikl=0;
int answer_to_modbus_tcp(char *bufer, int lenbuf);

union{
   		 unsigned char buf[49];
   		 struct{
		 		unsigned char start[5];//5
				float         data[11];//44 bytes
		 }tmpstruct;
   }tmpbuf;



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


//-------------Получение данных от дозатора 1---------------------
void getDozator1(){

}

//-------------Получение данных от дозатора 2---------------------
void getDozator2(){

}
//-------------Отправка задания дозатору 1---------------------
void setDozator1(float zadanieDoz1){

}

//-------------Отправка задания дозатору 2---------------------
void setDozator2(float zadanieDoz2){

}
//-------------Отправка данных на АРМ---------------------
void sendDataEth(int current_socket){
//Заглушка для отладки
tmpbuf.tmpstruct.start[0]='s';
tmpbuf.tmpstruct.start[1]='t';
tmpbuf.tmpstruct.start[2]='a';
tmpbuf.tmpstruct.start[3]='r';
tmpbuf.tmpstruct.start[4]='t';
tmpbuf.tmpstruct.data[0]=0;
tmpbuf.tmpstruct.data[1]=3.45;
tmpbuf.tmpstruct.data[2]=3.4;
tmpbuf.tmpstruct.data[3]=35;
tmpbuf.tmpstruct.data[4]=2.5;
tmpbuf.tmpstruct.data[5]=2.6;
tmpbuf.tmpstruct.data[6]=26;
tmpbuf.tmpstruct.data[7]=0;
tmpbuf.tmpstruct.data[8]=1;
tmpbuf.tmpstruct.data[9]=5.6;
tmpbuf.tmpstruct.data[10]=5.7;
send(current_socket, tmpbuf.buf, strlen(tmpbuf.buf), 0);
}
//-------------Анализ данных с АРМ---------------------
void analizDataEth(char *buf,int current_socket){
     int error=0;
	 int i,n;
//Реальный буффер
	 union{
		  unsigned char buf[10];
		  struct{
          		 unsigned char start[5];//5 bytes
		  		 unsigned char i_command;//1 byte
		  		 float value;//4 byte
		  }tmpstruct;
	}answertmpbuf;


	 for(i=0;i<strlen(buf)-6;i++)
      {
   	   if ((buf[i]=='s')&&(buf[i+1]=='t')&&(buf[i+2]=='a')&&(buf[i+3]=='r')&&(buf[i+4]=='t'))
        {
		if ((i+9)>=strlen(buf)){
		   for(n=0;n>9;n++){
		   		answertmpbuf.buf[n]=buf[i+n];
		   		}
		   }
		}
		else error=1;
		if(error==1) break;
	}	

/*	switch (answertmpbuf.tmpstruct.i_command){
		case 'i': 
			 break;
		case 'r':sendDataEth(current_socket); 
             break;
		case 'm': 
             break;
 		case 'p': 
             break;
        default  : error=1;break;
     } */
}
//-----------Обработчик сети TCP-IP-----------------------
void netWork(int current_socket){
	int iRet;
    char buf[129];
	


	iRet=recv(current_socket, buf, 128, 0);
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
		/*send(current_socket, buf, strlen(buf), 0);*/
		analizDataEth(buf,current_socket);	
	}
}
//-------------Формирование задания для дозаторов---------------------
//Актив. М-В(%)/Актив.Извести(%)*Производительность(т.ч)=Дозировка извести(т.ч)
//Дозировка песка = Производительность - Дозировка извести (т.ч)
void calcWork(float molotoVyazhAct, float izvestAct, float Summary){
	 float izvestSumm;
	 float sandSumm; 
	 izvestSumm = (molotoVyazhAct/izvestAct)*Summary;
	 sandSumm = Summary-izvestSumm;
	 
	 setDozator1(izvestSumm);
     setDozator2(sandSumm);
}



void main(void)
{
	struct sockaddr_in serverAdd[2];
	struct sockaddr_in clientAdd;	
	int clientAddLen;
	int new_con,i,c,err;
	int s[2];
	
	InitLib();
    InstallCom(2,9600L,8,0,1)    ;
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
	for(;;)
	{
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
			return;
		}
       count_cikl++;
	}
 
}

