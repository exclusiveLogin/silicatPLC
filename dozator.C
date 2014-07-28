//������������� ��������� � ����������

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
status[4]={0,0,0,0};//������ �������� 

//������������� ������� 
/* ============== ������ ����������� ����� �� ���������  CRC16 =====*/
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
//--------������ ������-------
void  firstRunCheck(){//����� ��������� ��� ������ �������
  switch (stack)
   {
	 case 0: curentPerfIzvest = getDozator(adrDoz1, 1, &status[0]);if (status[0]==0) stack++;break;
	 case 1: oldPerfIzvest   = getDozator(adrDoz1, 2, &status[1]);if (status[1]==0) stack++;break;
	 case 2: curentPerfSand   = getDozator(adrDoz2, 1, &status[2]);if (status[2]==0) stack++;break;
	 case 3: oldPerfSand     = getDozator(adrDoz2, 2, &status[3]);if (status[3]==0) stack++;break;
	}
   if((status[0]==0)&&(status[1]==0)&&(status[2]==0)&&(status[3]==0))
    {
	 firststartdoz=0;stack=0;Print("\r\nNOT FIRSTDOZATOR");
	}
   else
    {
	// firststartdoz = 1;
	}
}

//------------����� ��������� �������--------------------
void checkSystem(){
float tmp;
int pc=0;
if (firststartdoz==0)
{
 Print("\r\nOK=%d,%d",stack,pc);
 switch(stack){
 	    case 0:while (pc<3)
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
	    case 1:while (pc<3)
				{
				tmp = getDozator(adrDoz1, 2, &status[1]);
				if(status[1]==0) { 
					oldPerfIzvest = tmp;
					break; 
					}
				pc++;
				}
	   		   stack++;
		  	   break;
	    case 2:while (pc<3)
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
	    case 3:while (pc<3)
				{
				tmp = getDozator(adrDoz2, 2, &status[3]);
				if(status[3]==0) { 
					oldPerfSand = tmp;
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
  else statusDozator2 = 0;
  curentPerfomanceSummary = curentPerfSand + curentPerfIzvest;//++++++

   if(statusDozator2==0){//���� ������ ��������� �����
		if(curentPerfSand<calcPerfSand*0.5){// � ��� �� ����� �� ������������ ������� ���� �� 50% 
			    if(Act(1)){//���� ��� ������� �� ������� ���� ��� �� ���������

		  				}
				else{
      				Run(1);//��������� �� 20 ������
					vibrotimer=1;//���� ��� ��������� ������ ��������
	 				} 										
		}
		else;
	}
 }	
}
//���������� ����������-----------------------------------
void vibroToggle(int command){
	 SetPioDir(1,0);
	 if(command==1){
          vibro = 1;
	 	  Print("\r\nVibro started on 5 second");
		  SetPio(1,1);
	 }
	 else{
          vibro = 0;
		  Print("\r\nVibro stopped");
          SetPio(1,0);
	 }
}
//-------------����� ��������---------------------
float getDozator(int NumDVL, int NumCom, int *status){
  
// ������ ���������� � ��� - ���������
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
   case 1: command[0]=NumDVL;//������� ������������������
           command[1]=0x03;
           command[2]=0x00;
           command[3]=0x2E; //46;
           command[4]=0x00;
           command[5]=0x02; //47;
           CountBytes=6;
           break;
   case 2: command[0]=NumDVL;//�������� ������������������
           command[1]=0x03;
           command[2]=0x00;
           command[3]=0x30; //48;
           command[4]=0x00;
           command[5]=0x02; //49;
           CountBytes=6;
   break;
  }

 crc=CRC16(command,CountBytes);
 command[CountBytes]  =(unsigned char)crc;
 command[CountBytes+1]=(unsigned char)(crc>>8);

ClearCom(2);
 Print("\r\n");
 for (pc=0;pc<8;pc++)   Print("%d;",command[pc]);
 for (pc=0;pc<8;pc++)    c1[pc] = command[pc];
 for (pc=0;pc<8;pc++)    ToCom(2,c1[pc])     ;
 pc=0;pop=0;kt=0;lenans=5+4;
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
if (lenans==kt) /* ����� ������ ���������� */
  {
   if (Answer[1]==0x03)
    {
      Print("\r\nReceive is correct from %d",NumDVL);
	  
	  switch (NumCom)
      {
       case 1: case 2: /* ����� � ������������������ */ 
	   		*status=0; 
	   		ddata.byte[3]=Answer[3];
   			ddata.byte[2]=Answer[4];
   			ddata.byte[1]=Answer[5];
   			ddata.byte[0]=Answer[6];
			*status = 0;
			Print("NumCom=%d(%f)",NumCom,ddata.val * 0.01);
   			return ddata.val * 0.01;	   
      }
     *status = 1;
    }
   else
    {
     Print("\r\nError of receive! Num bytes = %d must been = %d",kt,lenans);
	 *status = 1;
    }
  }
 else /* ����� �� ������ */
  {
   Print("\r\nError of receive! Num bytes = %d must been = %d",kt,lenans);
   *status = 1;
  } 
return -1;
}

//-------------�������� ������� ��������---------------------
int setDozator(int adrDevice, float newVal){
// ������ ���������� � ��� - ���������
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
command[1]=0x10;//������� ������     //
command[2]=0x00; // �����            //
command[3]=0x30; // 48;       //
command[4]=0x00; // 
command[5]=0x02; // ���������� ��������
command[6]=0x04; // ����
CountBytes=11;
//val.f     = newVal*100;   
val.value = (long)((float)newVal*100);
//val.f = newVal*100;
//Print("\r\nVal==%d",val.value);
command[7]  = val.byte[3]; 
command[8]  = val.byte[2]; 
command[9]  = val.byte[1]; 
command[10] = val.byte[0]; 

crc=CRC16(command,CountBytes);
command[CountBytes]  =(unsigned char)crc;
command[CountBytes+1]=(unsigned char)(crc>>8); 

//������� ������� �� ��������� ��������
ClearCom(2);
 for (pc=0;pc<13;pc++)    c1[pc] = command[pc];
 for (pc=0;pc<13;pc++)    ToCom(2,c1[pc])     ;
 pc=0;pop=0;kt=0;lenans=8;
 while ((pc!=1)&&(pop<20000L))//��������� ������
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

if (kt>=lenans) /* ����� ������ ���������� */
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
   else //�������� ����� ������
    {
     Print("\r\nError: some bytes is lost");
     return 0;
    }
  }
 else /* ����� �� ������ */
  {
   Print("\r\nError: some bytes is lost");
   return 0;
  }
}

//��������� ���������� �������----------------------------
void setIzvActivity(float val){
	 curentIzvestActivity=val;
}
//��������� ��������������--------------------------------
void setMV(float val){
     curentMV=val;
}
//��������� ������������������----------------------------
void setPerfomance(float val){
     neededPerfomanceSummary=val;
}
//-------------�������� ������ �� ���---------------------
void sendDataEth(int current_socket){
int i;
//�������� ��� �������
tmpbuf.tmpstruct.start[0]=1;
tmpbuf.tmpstruct.start[1]=1;
tmpbuf.tmpstruct.start[2]=1;
tmpbuf.tmpstruct.start[3]=1;
tmpbuf.tmpstruct.start[4]=1;
tmpbuf.tmpstruct.data[0]=workmode;//workmode
tmpbuf.tmpstruct.data[1]=curentPerfIzvest;//������� ������������������ �������
tmpbuf.tmpstruct.data[2]=oldPerfIzvest;//����������� ������������������ �������
tmpbuf.tmpstruct.data[3]=curentIzvestActivity;//���������� �������
tmpbuf.tmpstruct.data[4]=curentPerfSand;//������� ������������������ �����
tmpbuf.tmpstruct.data[5]=oldPerfSand;//����������� ������������������ �����
tmpbuf.tmpstruct.data[6]=curentMV;//������ �������
tmpbuf.tmpstruct.data[7]=statusDozator1;//������ �������� �������
tmpbuf.tmpstruct.data[8]=statusDozator2;//������ �������� �����
tmpbuf.tmpstruct.data[9]=curentPerfomanceSummary;//������� ������������������
tmpbuf.tmpstruct.data[10]=neededPerfomanceSummary;//������� ������������������
tmpbuf.tmpstruct.data[11]=vibro;//��������


for(i=0;i<53;i++){
    Print("%d.",tmpbuf.buf[i]);
	} 
send(current_socket, tmpbuf.buf, 53, 0);
}
//-------------������ ������ � ���---------------------
void analizDataEth(char *buf,int len_buf, int current_socket){
     int error=0;
	 int i,n;
//�������� ������
   Print("Len=%d",len_buf);
   for (i=0;i<10;i++) Print("=%d=",buf[i]);
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
	if (!error)		Print("not error\r\n");
	else            Print("error \r\n");
	if (error){		   
          	   return;
	   }
	Print("Simbol=%d\r\n",answertmpbuf.tmpstruct.i_command);
	switch (answertmpbuf.tmpstruct.i_command){
		case 'i':setIzvActivity(answertmpbuf.tmpstruct.value); 
			 break;
		case 'r':sendDataEth(current_socket); 
             break;
		case 'm':setMV(answertmpbuf.tmpstruct.value); 
             break;
 		case 'p':setPerfomance(answertmpbuf.tmpstruct.value); 
             break;
		case 99:calculateWork();            
             break;
        default  : error=1;break;
     } 
}
//-----------���������� ���� TCP-IP-----------------------
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
//-------------������������ ������� ��� ���������---------------------
//�����. �-�(%)/�����.�������(%)*������������������(�.�)=��������� �������(�.�)
//��������� ����� = ������������������ - ��������� ������� (�.�)
void calculateWork(){
	 int error1, error2;
//++? curentIzvestActivity==0
	 if(curentIzvestActivity==0)curentIzvestActivity=1;
	 calcPerfIzvest = (curentMV/curentIzvestActivity)*neededPerfomanceSummary;
	 calcPerfSand = neededPerfomanceSummary-calcPerfIzvest;
	 error1 = setDozator(adrDoz1, calcPerfIzvest);
	 error2 = setDozator(adrDoz2, calcPerfSand);
	 if(error1==0){
	 	  statusDozator1=0;
	 			   }
	 else{
     	  statusDozator1=2; 
	 }
	 if(error2==0){
	 	  statusDozator1=0;
	 			   }
	 else{
     	  statusDozator1=2; 
	 }
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
	adrDoz1=0x01;//��������	
	adrDoz2=0x02;//��������
	firststartdoz = 1;
	timers_duration[1]=20000; 
	timers_duration[2]=5000;  	 
	vibro = 0;
	vibrotimer=0;	

    	
	InitLib();
	TimerOpen();
    InstallCom(2,19200L,8,0,1)    ;
	Print("\r\n��� 1: ���樠������ TCP �ࢥ�!");                  /* ������������� */
	err=NetStart();
	if(err<0)
	{
		Print("\n\r�訡�� ���樠����樨 TCP �ࢥ�");
		return;
	}
	
	Print("\r\n��� 2: �������� ᮪�⮢ � ���� �痢� ��� ����訢����� ᮥ�������!");
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
  
	Print("\r\n��� 3.1. �������� ᮪�⮢ � ���!");
	Print("\r\n��� 3.2. �맮� �ࢨ� � �⢥�!")   ;
    //setDozator(1,3.42);
	//setDozator(2,2.2);
	//setDozator(1,3.5);
	for(;;)
	{
		
        if(firststartdoz==1){     //�������� ������� �������	
        		firstRunCheck();              	 	
		}
		else
         {
		  
		  if ((kcount%15)==0)
	 	   { Print("CheckSystem");checkSystem(); }//����� �������
		  kcount++;
		 }
		if(Act(1)){ //�������� ����������� �������
		     Print("\r\nwaiting...");//����
		}
		else{
			 if(vibrotimer==1){ //���� ������ ��� ������� � �������� ��..
			  				  vibroToggle(1);
			 				  Stop(1);
			 				  Run(2);
							  vibrotimer=0;
							  }			 
		}

		if(Act(2)){ //�������� ������� ��������
		     Print("\r\vibrating...");
		}
		else{
			 vibroToggle(0);
			 Stop(2);
			 }

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
        // ����� �� ��������� MODBUS RTU
  
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
