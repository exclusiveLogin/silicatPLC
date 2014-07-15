//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormDiag.h"
#include "FormBlok.h"
#include "FormPassword.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFDiag *FDiag;
//---------------------------------------------------------------------------
__fastcall TFDiag::TFDiag(TComponent* Owner)
        : TForm(Owner)
{
 union
  {
   unsigned char s[4];
   long l;
   float v;
  } tekzn;
 float d;
 tekzn.s[0]=  0;
 tekzn.s[1]=128;
 tekzn.s[2]=  0;
 tekzn.s[3]=  0;
 d=tekzn.l;
 short unsigned int m=d;
 int k=0;
}
//---------------------------------------------------------------------------
void __fastcall TFDiag::BitBtn1Click(TObject *Sender)
{
 // ���� ������ ��� �������� ���� ����������
 FPassword->Edit1->Text="";
 FPassword->Caption = "������� ������ �������:";
 FPassword->Edit1->PasswordChar = '*';
 if (FPassword->ShowModal()==mrOk)
  {
   if (FPassword->Edit1->Text == Password)
    {
     for (int pc=0;pc<36;pc++)
      {
       FBlok->ID_Time_Blok[pc]=IDTag_Time_Blok[pc];
       FBlok->ID_On_Blok[pc]  =IDTag_On_Blok[pc]  ;
      }
     FBlok->OnGetParam = OnGetParam; 
     FBlok->ShowModal();
     FBlok->Timer1->Enabled=false;
    }
   else
    {
     Application->MessageBoxA("��� ����� �� ��������� ����������!","��������!",MB_OK+MB_ICONSTOP);
    }
  }

}
//---------------------------------------------------------------------------
void __fastcall TFDiag::FormHide(TObject *Sender)
{
 Timer1->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TFDiag::FormShow(TObject *Sender)
{
  Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFDiag::Timer1Timer(TObject *Sender)
{
 // ����� � ����������� ����������
 double Val   ;
 int    Status;
 bool   Error=false;
 if (OnGetParam!=NULL)
  {
   OnGetParam(this,IDOsn,Val,Status)   ;
   if (Status!=0) Error=true;
   if ((Val==1)&&(Status==0)) Label2->Visible=true; else Label2->Visible=false;
   OnGetParam(this,IDDop[0],Val,Status);
   if (Status!=0) Error=true;
   if ((Val==1)&&(Status==0)) Label3->Visible=true; else Label3->Visible=false;
   unsigned int ddd = Val;
   if ((ddd&    1)==    1) StaticText2->Color  = clRed;  else StaticText2->Color = clGreen;
   if ((ddd&    2)==    2) StaticText3->Color  = clRed;  else StaticText3->Color = clGreen;
   if ((ddd&    4)==    4) StaticText4->Color  = clRed;  else StaticText4->Color = clGreen;
   if ((ddd&    8)==    8) StaticText5->Color  = clRed;  else StaticText5->Color = clGreen;
   if ((ddd&   16)==   16) StaticText6->Color  = clRed;  else StaticText6->Color = clGreen;
   if ((ddd&   32)==   32) StaticText7->Color  = clRed;  else StaticText7->Color = clGreen;
   if ((ddd&  256)==  256) StaticText16->Color = clRed; else StaticText16->Color = clGreen;
   if ((ddd&  512)==  512) StaticText17->Color = clRed; else StaticText17->Color = clGreen;
   if ((ddd& 1024)== 1024) StaticText18->Color = clRed; else StaticText18->Color = clGreen;
   if ((ddd& 2048)== 2048) StaticText19->Color = clRed; else StaticText19->Color = clGreen;
   if ((ddd& 4096)== 4096) StaticText23->Color = clRed; else StaticText23->Color = clGreen;
   if ((ddd& 8192)== 8192) StaticText24->Color = clRed; else StaticText24->Color = clGreen;
   if ((ddd&16384)==16384) StaticText25->Color = clRed; else StaticText25->Color = clGreen;
   OnGetParam(this,IDDop[0],Val,Status);
   if (Status!=0) Error=true;
   ddd = Val;
   StaticText8->Visible =(ddd& 1)==  1;
   StaticText15->Visible=(ddd& 2)==  2;
   StaticText22->Visible=(ddd& 4)==  4;
   StaticText29->Visible=(ddd& 8)==  8;
   StaticText36->Visible=(ddd&16)== 16;
   StaticText43->Visible=(ddd&32)== 32;
   StaticText50->Visible=(ddd&64)== 64;
   for (int pc1=0;pc1<2;pc1++)
    for (int pc=0;pc<6;pc++)
     {
      OnGetParam(this,IDTag_CRP[pc1][pc],Val,Status);
      if (Status!=0) Error=true;
      TLabel *tmp;
      tmp=(TLabel *)FindComponent("L_CRP"+IntToStr(pc1)+"_"+IntToStr(pc));
      if (tmp!=NULL)
       if (Status==0) // ���� ������
        {
         if (pc<3)
          {
           tmp->Caption     = FormatFloat("##0.0",Val);
           tmp->Font->Color = clWhite;
          }
         else if (pc==3) // ���������
          {
           unsigned int tt = (unsigned int)Val;
           if (pc1==0)
            {
             L_CRP0_3_0->Visible = ((tt&1)==1);
             L_CRP0_3_1->Visible = ((tt&2)==2);
             L_CRP0_3_2->Visible = ((tt&8)==8);
            }
           else
            {
             L_CRP1_3_0->Visible = ((tt&1)==1);
             L_CRP1_3_1->Visible = ((tt&2)==2);
             L_CRP1_3_2->Visible = ((tt&8)==8);
            }
          }
         else if (pc==4) // �������������
          {
           unsigned int tt = (unsigned int)Val;
           if (pc1==0)
            {
             L_CRP0_4_0->Visible  = ((tt&    1)==    1);
             L_CRP0_4_1->Visible  = ((tt&    2)==    2);
             L_CRP0_4_2->Visible  = ((tt&    4)==    4);
             L_CRP0_4_3->Visible  = ((tt&    8)==    8);
             L_CRP0_4_4->Visible  = ((tt&   32)==   32);
             L_CRP0_4_5->Visible  = ((tt&  128)==  128);
             L_CRP0_4_6->Visible  = ((tt&  256)==  256);
             L_CRP0_4_7->Visible  = ((tt&  512)==  512);
             L_CRP0_4_8->Visible  = ((tt& 2048)== 2048);
             L_CRP0_4_9->Visible  = ((tt& 4096)== 4096);
             L_CRP0_4_10->Visible = ((tt& 8192)== 8192);
             L_CRP0_4_11->Visible = ((tt&16384)==16384);
            }
           else
            {
             L_CRP1_4_0->Visible  = ((tt&    1)==    1);
             L_CRP1_4_1->Visible  = ((tt&    2)==    2);
             L_CRP1_4_2->Visible  = ((tt&    4)==    4);
             L_CRP1_4_3->Visible  = ((tt&    8)==    8);
             L_CRP1_4_4->Visible  = ((tt&   32)==   32);
             L_CRP1_4_5->Visible  = ((tt&  128)==  128);
             L_CRP1_4_6->Visible  = ((tt&  256)==  256);
             L_CRP1_4_7->Visible  = ((tt&  512)==  512);
             L_CRP1_4_8->Visible  = ((tt& 2048)== 2048);
             L_CRP1_4_9->Visible  = ((tt& 4096)== 4096);
             L_CRP1_4_10->Visible = ((tt& 8192)== 8192);
             L_CRP1_4_11->Visible = ((tt&16384)==16384);
            }
          }
         else if (pc==5)
          {
           unsigned int tt=(unsigned int)Val;
           if (pc1==0)
            {
             L_CRP0_5_0->Visible  = ((tt&    1)==    1);
             L_CRP0_5_1->Visible  = ((tt&    8)==    8);
             L_CRP0_5_2->Visible  = ((tt&   16)==   16);
            }
           else
            {
             L_CRP1_5_0->Visible  = ((tt&    1)==    1);
             L_CRP1_5_1->Visible  = ((tt&    8)==    8);
             L_CRP1_5_2->Visible  = ((tt&   16)==   16);
            }
          }
        }
       else           // ��� ������
        {
         if (pc<3)
          {
           tmp->Caption     = "---";
           tmp->Font->Color = clRed;
          }
         else if (pc==3)
          {
           if (pc1==0)
            {
             L_CRP0_3_0->Visible = false;
             L_CRP0_3_1->Visible = false;
             L_CRP0_3_2->Visible = false;
            }
           else
            {
             L_CRP1_3_0->Visible = false;
             L_CRP1_3_1->Visible = false;
             L_CRP1_3_2->Visible = false;
            }
          }
         else if (pc==4)
          {
           if (pc1==0)
            {
             L_CRP0_4_0->Visible  = false;
             L_CRP0_4_1->Visible  = false;
             L_CRP0_4_2->Visible  = false;
             L_CRP0_4_3->Visible  = false;
             L_CRP0_4_4->Visible  = false;
             L_CRP0_4_5->Visible  = false;
             L_CRP0_4_6->Visible  = false;
             L_CRP0_4_7->Visible  = false;
             L_CRP0_4_8->Visible  = false;
             L_CRP0_4_9->Visible  = false;
             L_CRP0_4_10->Visible = false;
             L_CRP0_4_11->Visible = false;
            }
           else
            {
             L_CRP1_4_0->Visible  = false;
             L_CRP1_4_1->Visible  = false;
             L_CRP1_4_2->Visible  = false;
             L_CRP1_4_3->Visible  = false;
             L_CRP1_4_4->Visible  = false;
             L_CRP1_4_5->Visible  = false;
             L_CRP1_4_6->Visible  = false;
             L_CRP1_4_7->Visible  = false;
             L_CRP1_4_8->Visible  = false;
             L_CRP1_4_9->Visible  = false;
             L_CRP1_4_10->Visible = false;
             L_CRP1_4_11->Visible = false;
            }
          }
         else if (pc==5)
          {
           if (pc1==0)
            {
             L_CRP0_5_0->Visible  = false;
             L_CRP0_5_1->Visible  = false;
             L_CRP0_5_2->Visible  = false;
            }
           else
            {
             L_CRP1_5_0->Visible  = false;
             L_CRP1_5_1->Visible  = false;
             L_CRP1_5_2->Visible  = false;
            }
          }
        }
     }

   for (int pc=0;pc<8;pc++)
    {
     OnGetParam(this,IDTag_UPS[pc],Val,Status);
     if (Status!=0) Error=true;
     if (pc!=7)
      {
       TLabel *tmp;
       tmp=(TLabel *)FindComponent("L_UPS_"+IntToStr(pc));
       if (tmp!=NULL)
        if (Status==0) // ���� ������
         {
          tmp->Caption=FormatFloat("##0.0",Val);
          tmp->Font->Color = clWhite;
         }
        else
         {
          tmp->Caption = "---";
          tmp->Font->Color = clRed;
         }
      }
     else // ����������� ����
      {
       if (Status==0)
        {
          unsigned int tt=(unsigned int)Val;
          Label93->Visible =(tt &128)==128;
          Label94->Visible =(tt & 64)== 64;
          Label95->Visible =(tt & 32)== 32;
          Label96->Visible =(tt & 16)== 16;
          Label97->Visible =(tt &  8)==  8;
          Label98->Visible =(tt &  4)==  4;
          Label99->Visible =(tt &  2)==  2;
          Label100->Visible=(tt &  1)==  1;
        }
       else
        {
          Label93->Visible =false;
          Label94->Visible =false;
          Label95->Visible =false;
          Label96->Visible =false;
          Label97->Visible =false;
          Label98->Visible =false;
          Label99->Visible =false;
          Label100->Visible=false;
        }
      }
    }
   if (Error) StaticText1->Visible=true; else StaticText1->Visible=false; 
  }
}
//---------------------------------------------------------------------------
