/*   TCP_Server.c: TCP Server  */
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <icpdas.h>                   
#include "Tcpip32.h"
#include "Var.h"              
#define MaxClentSocket 32
#define NUM_OF_SERVICE_PORT 3
fd_set rfds,s_fds;    // server socket set of socket file descriptors for reading
unsigned       ActiveSkt[2]={0, 0};
struct         timeval seltime={0,20};
unsigned short service_port[NUM_OF_SERVICE_PORT]={20001, 502, 10000};
int            socketPort[MaxClentSocket];
unsigned int  count_cikl=0;
int answer_to_modbus_tcp(char *bufer, int lenbuf);
void Port20001(int current_socket)
{
    int iRet,i;
    char buf[1024];
    unsigned int  pc,kt  ;
    unsigned long pop=0      ;
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
      ClearCom(2);
      for (i=0;i<8;i++)    ToCom(2,buf[i])     ;
      pc=0;pop=0;kt=0; /* 5 + 2*2 */
      while ((pc!=1)&&(pop<20000L)&&(kt<1024))
       {
        if (IsCom(2))
        if (IsTxBufEmpty(2))
         {
          buf[kt]=ReadCom(2);
          kt++;
         }
        pop++;
       }
       WaitTransmitOver2();
	   Print("\r\nMODBUS RTU");
       for (i=0;i<kt;i++) Print("%d;",buf[i]);
	   send(current_socket, buf, kt, 0);
	}
} 
void Port10000(int current_socket)
{
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
		send(current_socket, buf, strlen(buf), 0);
	}
} 
void Port10001(int current_socket)
{
    // current_socket: Socket number  
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
        if ((iRet=answer_to_modbus_tcp(buf,iRet))>0)
         {
		  send(current_socket, buf, iRet, 0);    
		 }
        else 
         {
           buf[0]=0x0;
 		   send(current_socket, buf, strlen(buf), 0);    
         } 
	}
}

int answer_to_modbus_tcp(char *bufer, int lenbuf)
{
 char           tmp[256];
 int            nfun=  0;
 int            adr =  0;
 unsigned int   kreg=  0;
 //int            pc  =  0;
 int            kw  =  0;
 unsigned int   pcreg   ;
 float          fval    ;
 unsigned int   sm      ;
// int           onlyread=1;
 union
  {
   float         f   ;
   unsigned char c[4];
  } f;
 union
  {
   unsigned char c[2];
   unsigned int i;
  } vi;
 int adr_ustr,i;
 Print("\r\n BYL1 lenbuf= %d",lenbuf);
 
 if ((lenbuf<8)||(lenbuf>500)) return 0;
 Print("\r\nPriem:");
 for (i=0;i<lenbuf;i++) Print("%d;",bufer[i]);
 tmp[0]=bufer[0]; tmp[1]=bufer[1]; tmp[2]=0; tmp[3]=0;
 tmp[6]=bufer[6];
 adr_ustr=tmp[6];
 nfun=bufer[7];
 if ((nfun!=0x03)&&(nfun!=0x04)&&(nfun!=0x10))  {  return 0;  }
 if (lenbuf<12) return 0;
 /* адрес регистра       */
 adr = bufer[8] *256+bufer[9] ;
 kreg= bufer[10]*256+bufer[11];
 if (kreg>255) return 0;
 //onlyread=1;
 if ((adr<1)&&(adr>15)) return 0; 
 if (nfun==0x10) /* запись регистров */
  {
   sm=0;
   vi.i=6; //kreg*2+3;
   tmp[4] =vi.c[1]  ;
   tmp[5] =vi.c[0]  ;
   tmp[6] =adr_ustr ;
   tmp[7] =nfun     ;
   tmp[8] =bufer[8] ;// количество слов в ответе
   tmp[9] =bufer[9] ;
  // vi.i   =kreg*2;
   tmp[10]=bufer[10];
   tmp[11]=bufer[11];
/*    УСТАНОВКА ЗНАЧЕНИЙ 
   for (pcreg=adr;pcreg<adr+kreg;pcreg=pcreg+2)
    {
     if (!check_registr(pcreg,&fval,&onlyread)) onlyread=1;
     if (onlyread)
      {

       tmp[7]=0x80+nfun;
       tmp[8]=0x02;
       tmp[4]=0x00;
       tmp[5]=0x09;
       for (pc=0;pc<9;pc++) bufer[pc]=tmp[pc];
       return 9;
      }
	 else
      {
       f.c[3]=bufer[13 +sm];
       f.c[2]=bufer[14 +sm];
       f.c[1]=bufer[15 +sm];
       f.c[0]=bufer[16 +sm];
       sm=sm+4;
      }
     set_register(pcreg,f.f);
    }
   for (pcreg=0;pcreg<12;pcreg++)  {  bufer[pcreg]=tmp[pcreg];}
   return 12; */
   return 0;
  } 
 /* чтение регистров */
 if ((nfun==0x03)||(nfun==0x04))
  {
   vi.i=kreg*2+3;
   tmp[4]=vi.c[1];
   tmp[5]=vi.c[0];
   tmp[6]=adr_ustr;
   tmp[7]=nfun    ;
   tmp[8]=kreg * 2; // количество байт в ответе
   if (kreg>255) return 0;
//   if (write_to_memo1) Memo1->Lines->Add("Кол-во регистров = "+IntToStr(kreg));
   sm=0;
   kw=0;
   for (pcreg=adr;pcreg<adr+kreg;pcreg=pcreg+2)
    {
       /*if (!check_registr(pcreg,&fval,&onlyread)) */
       if ((pcreg>0)&&(pcreg<=29)) fval=ValIO[(pcreg-1)/2];
       else         fval=0;
       f.f=fval;
       tmp[9 +sm] =f.c[3];
       tmp[10 +sm]=f.c[2];
       tmp[11+sm] =f.c[1];
       tmp[12+sm] =f.c[0];
       sm=sm+4;kw=kw+2;
    }
   tmp[8]=kw;
   for (pcreg=0;pcreg<sm+9;pcreg++)   bufer[pcreg]=tmp[pcreg];
   Print("\r\nSend:");
   for (i=0;i<sm+9;i++) Print("%d;",bufer[i]);

   return sm+9;
  }
 return 0;
}
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
/* ============== Чтение информации от БС-М2 с адресом AdrUstr =====*/
int Read_Modul(int AdrUstr, int NumZap)
{
 unsigned char command[80];
 int           c1[80];
 unsigned char Answer[255];
 unsigned int  crc,pc,kt  ;
 unsigned long pop=0      ;
 unsigned int  lenans=0   ;
 unsigned int  kr=0       ;
 union
  {
   unsigned char c[2];
   int           val ;
  } tmpint;
 union
  {
   unsigned char c[4];
   unsigned long val ;
  } tmplong;
 command[0]= AdrUstr         ; /* адрес устройства   */
 command[1]= 0x03            ; /* функция чтения     */
 switch (NumZap)
  {
   case 1: /* чтение порога срабатывания №1 и №2 */
	   command[2]= 0x10            ;
	   command[3]= 0x00            ; /* адрес переменных   */
	   command[4]= 0x00            ;
	   command[5]= 0x03            ; /* 6 байт  3 регистра */
	   kr=3;
	   break;
   case 2: /* чтение состояния ГСМ-05 и текущей концентрации */
	   command[2]= 0x11            ;
	   command[3]= 0xA7            ;
	   command[4]= 0x00            ;
	   command[5]= 0x0C            ;
	   kr=12;
	   break;
   default: return 0;
  }
 crc       = CRC16(command,6);
 command[6]=(unsigned char)        crc;
 command[7]=(unsigned char)   (crc>>8);
 ClearCom(2);
 for (pc=0;pc<8;pc++)    c1[pc] = command[pc];
 for (pc=0;pc<8;pc++)    ToCom(2,c1[pc])     ;
 pc=0;pop=0;kt=0;lenans=5+2*kr; /* 5 + 2*2 */
 while ((pc!=1)&&(pop<20000L))
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
 if (lenans==kt) /* ответ пришёл правильный */
  {
   if (Answer[1]==0x03)
    {
     /* Print("\r\nОтвет правильный от %d",AdrUstr); */
     switch (NumZap)
      {
       case 1: for (kt=0;kt<3;kt++)
                {
                 tmpint.c[1]=Answer[3+kt*2];
	             tmpint.c[0]=Answer[4+kt*2];
	             ValIO[kt]=tmpint.val;
				}
   	           break;
       case 2: /* чтение текущей концентрации */
               for (kt=0;kt<12;kt++)
                {
                 tmpint.c[1]=Answer[3+kt*2];
	             tmpint.c[0]=Answer[4+kt*2];
	             ValIO[kt+3]=tmpint.val;
				}
   	           break;	   
      }
     return 1;
    }
   else
    {
     Print("\r\nОшибка приёма! количество принятых байт = %d должно быть %d",kt,lenans);
     return 0;
    }
  }
 else /* ответ не пришел */
  {
   Print("\r\nОшибка приёма! количество принятых байт = %d должно быть %d",kt,lenans);
   return 0;
  }

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
		//Step 3-2: perform service, receive and send
		for(i=1; i<MaxClentSocket; i++)
		{
			if(FD_ISSET(i,&s_fds))
			{
				if(!ioctlsocket(i,FIONREAD,&err) && (err>0))
				{
					if(socketPort[i]==10000)
					{
						Port10000(i);
					}
					else if(socketPort[i]==502)
					{
						Print("byl=Port=502\r\n");
						Port10001(i);
					}
                    else if (socketPort[i]==20001)
                    {
                        Port20001(i);
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
       if (count_cikl==10)  { if (Read_Modul(2, 1)==0)  { ValIO[0]=-2;ValIO[1]=-2;ValIO[2]=-2; } }
       else if (count_cikl==20) { if (Read_Modul(2, 2)==0)  { for (i=3;i<15;i++) ValIO[i]=-2;  } }
       else if (count_cikl>20) count_cikl=0;
	}
 
}

