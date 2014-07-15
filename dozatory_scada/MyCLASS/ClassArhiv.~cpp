#include "ClassArhiv.hpp"
//---------------------------------------------------------------------------
__fastcall MyArhiv::MyArhiv(TComponent *Comp, int CountTags, unsigned int period_write) : TObject()
{
 if (CountTags==0) throw Exception("Нет тэгов в архиве");
 if ((FValTags  = (double *)calloc(CountTags,sizeof(double)))==NULL) throw Exception("Ошибка выделения памяти для значений")           ;
 if ((FStatTags = (int *)   calloc(CountTags,sizeof(int)))   ==NULL) throw Exception("Ошибка выделения памяти для статусов значений")  ;
 if ((FIDTags   = (int *)   calloc(CountTags,sizeof(int)))   ==NULL) throw Exception("Ошибка выделения памяти для идентификации тэгов");
 if ((FArhivValTags  = (double *)calloc(CountTags,sizeof(double)))==NULL) throw Exception("Ошибка выделения памяти для архивных значений")           ;
 if ((FArhivStatTags = (int *)   calloc(CountTags,sizeof(int)))   ==NULL) throw Exception("Ошибка выделения памяти для архивных статусов значений")  ;
 if ((FArhivIDTags   = (int *)   calloc(CountTags,sizeof(int)))   ==NULL) throw Exception("Ошибка выделения памяти для идентификации архивных тэгов");
 FTimer = 0;
 if (period_write<1000) FTimerInterval = 1000;
 else                   FTimerInterval = period_write;
 FTimerEnabled    = false;
 FInitArhiv       = false;
 FCountTags       = CountTags;
 FActiveWrite     = false;
 ActiveArhiv      = this;
}
//---------------------------------------------------------------------------
__fastcall MyArhiv::~MyArhiv(void)
{
 if (FValTags != NULL) { free(FValTags) ;FValTags = NULL; }
 if (FStatTags!= NULL) { free(FStatTags);FStatTags= NULL; }
 if (FIDTags  != NULL) { free(FValTags) ;FIDTags  = NULL; }
 if (FArhivValTags != NULL) { free(FArhivValTags) ;FArhivValTags = NULL; }
 if (FArhivStatTags!= NULL) { free(FArhivStatTags);FArhivStatTags= NULL; }
 if (FArhivIDTags  != NULL) { free(FArhivValTags) ;FArhivIDTags  = NULL; }
 if (FTimer!=0) { timeKillEvent(FTimer); FTimer=0; }
}
//---------------------------------------------------------------------------
void __fastcall MyArhiv::FSetActiveWrite(bool value)
{
 if (value!=FActiveWrite)
  {
   if (value)
    {
     if (FInitArhiv)
      {
       FActiveWrite = true;
       FTimer = timeSetEvent(FTimerInterval, 0, Timer1Timer, TIME_PERIODIC, TIME_CALLBACK_FUNCTION | TIME_PERIODIC);
       FTimerEnabled = true;

      }
     else
      {
       if (OnActiveArhiv) { OnActiveArhiv(this, FInitArhiv, FIDTags, FValTags, FStatTags); }
       if (FInitArhiv)
        {
         FActiveWrite = true;
       FTimer = timeSetEvent(FTimerInterval, 0, Timer1Timer, TIME_PERIODIC, TIME_CALLBACK_FUNCTION | TIME_PERIODIC);
       FTimerEnabled = true;
        }
       else               { FActiveWrite = false; FTimerEnabled = false; }
      }
    }
   else                   { FActiveWrite = false; FTimerEnabled = false; }
  }
}
//---------------------------------------------------------------------------
void __fastcall MyArhiv::SetData(int IDTag, double Val, int Status)
{
 /*if ((IDTag==1)&&(Val<1))
  int k=0;*/
 for (int i=0;i<FCountTags;i++)
  {
   if (FIDTags[i]==IDTag)
    {
     FValTags[i]  = Val   ;
     FStatTags[i] = Status;
     return;
    }
  }
 return;
}
//---------------------------------------------------------------------------
void __fastcall MyArhiv::FSetCom(int CodeCom)
{
 switch (CodeCom)
  {
   case -10: FErrorDostup=true; break;
   case -11: FErrorDostup=false;break;
  }
}
//---------------------------------------------------------------------------
TData __fastcall MyArhiv::GetFDataTag(TDateTime DateArhiv, int IDTag)
{
 struct TData         Ret;
 static TDateTime     Old;
 static char          NameCurDir[255];
 static AnsiString    TekDir         ;
 static bool          first=true     ;
 int                  handle_file    ;
 static AnsiString    OldName=""     ;
 static unsigned long kb = 0L;
 static bool          Error = true;
 static double tim;
 if (first) // определить текущую директорию                           
  {
   GetCurrentDirectory(255,NameCurDir);
   TekDir    = NameCurDir;
   first     = false     ;
  }
 if (IDTag>=10000)
  {
   Ret.Status  = 1;
   Ret.Val     = 0;
   Ret.YesData = true;
   return Ret;
  }
 if (Old!=DateArhiv)
  {
   AnsiString ARHIV = "ARHIV";
   AnsiString YEAR  = DateArhiv.FormatString("yyyy");
   AnsiString MON   = DateArhiv.FormatString("mm")  ;
   AnsiString DAT   = DateArhiv.FormatString("dd")  ;
   AnsiString HOUR  = DateArhiv.FormatString("hh")  ;
   int min = StrToInt(DateArhiv.FormatString("nn"));
   int sec = StrToInt(DateArhiv.FormatString("ss"));
   Old = DateArhiv;
   AnsiString  NameFile   = TekDir+"\\"+ARHIV+"\\"+YEAR+"\\"+MON+"\\"+DAT+"\\" + HOUR +".dat";
   Error=true;
   if ((handle_file=_open(NameFile.c_str(),O_RDONLY|O_BINARY))>0) // чтение информации из файла
    {
/*     unsigned int  kb_zag  = sizeof(int)*ActiveArhiv->CountTags+sizeof(int);
     unsigned int  len_buf = ((sizeof(double)+sizeof(int))*ActiveArhiv->CountTags+sizeof(double))*3600; //  ((    значение и статус   ) *кол-во тэгов + дата и время) 60 сек * 60 мин
     unsigned char *buf; */
     if (OldName!=NameFile) // разбор заголовка
      {
       lseek(handle_file,0L,SEEK_SET)    ;
       Error = false;
       _read(handle_file,&kb,sizeof(int)); // размер заголовка
       if (kb == sizeof(int)*ActiveArhiv->CountTags+sizeof(int)) // размер заголовка должен соответствовать количеству архивных тэгов
        {
         if (_read(handle_file,FArhivIDTags,sizeof(int)*ActiveArhiv->CountTags)!=(signed int)(sizeof(int)*ActiveArhiv->CountTags)) Error=true;
        }
       else Error = true;
       OldName = NameFile;
      }
     else Error = false;
     if (!Error)
      {
       unsigned long sm = min * 60 + sec;
       sm = kb + sm * ((sizeof(double)+sizeof(int))*ActiveArhiv->CountTags+sizeof(double));
       sm = lseek(handle_file,sm,SEEK_SET);
       if (_read(handle_file,(unsigned char *)&tim,sizeof(double))!=sizeof(double)) Error=true;
       else if (_read(handle_file,(unsigned char *)FArhivValTags,(unsigned int)(sizeof(double)*ActiveArhiv->CountTags))!=(signed int)(sizeof(double)*ActiveArhiv->CountTags)) Error=true;
       else if (_read(handle_file,(unsigned char *)FArhivStatTags,sizeof(int)*ActiveArhiv->CountTags)!=(signed int)(sizeof(int)*ActiveArhiv->CountTags))      Error=true;
      }
     _close(handle_file);
     handle_file = -1;
    }
  }
 if ((tim==0)||(Error)) { FDataTag.YesData=false;FDataTag.Val=0;FDataTag.Status=1; }
 else
  {
   FDataTag.YesData=false;
   for (int pc=0;pc<FCountTags;pc++)
    {
     if (FArhivIDTags[pc]==IDTag)
      {
       FDataTag.Val     = FArhivValTags[pc];
       FDataTag.Status  = FArhivStatTags[pc];
       FDataTag.YesData = true;break;
      }
    }
   if (!FDataTag.YesData) { FDataTag.Val=0;FDataTag.Status=1; }
  }
 Ret = FDataTag;
 return Ret;
}
/*int old_sec=-1;
unsigned int old_kb=1000; */
void __stdcall Timer1Timer(UINT TimerID, UINT Message, DWORD dwUser, DWORD dw1, DWORD dw2)
{
 // раз в секунду запись в архив
 static char       NameCurDir[255];
 static AnsiString TekDir         ;
 static bool       first=true     ;
 int               handle_file    ;
 AnsiString ARHIV = "ARHIV";
 TDateTime TD = Now();
 AnsiString YEAR  = TD.FormatString("yyyy");
 AnsiString MON   = TD.FormatString("mm")  ;
 AnsiString DAT   = TD.FormatString("dd")  ;
 AnsiString HOUR  = TD.FormatString("hh")  ;
 int min = StrToInt(TD.FormatString("nn"));
 int sec = StrToInt(TD.FormatString("ss"));
 double tim = TD.Val;
 /*if ((old_sec!=-1)&&((sec-old_sec)>1)&&(old_sec!=59))
  int l=0;
 old_sec = sec;*/
 if (ActiveArhiv==NULL) return;
 if (first) // определить текущую директорию
  {
   GetCurrentDirectory(255,NameCurDir);
   TekDir    = NameCurDir;
   first     = false     ;
  }
 AnsiString  NameFile   = TekDir+"\\"+ARHIV+"\\"+YEAR+"\\"+MON+"\\"+DAT+"\\" + HOUR +".dat";
 if (!FileExists(TekDir+"\\"+ARHIV+"\\"+YEAR+"\\"+MON+"\\"+DAT+"\\" + HOUR +".dat")) // создать файл ARHIV\\XXXX\\MM\\DD\\hh - час
  {
   // Проверить наличие директории ARHIV
   if (!DirectoryExists(TekDir+"\\"+ARHIV))  if (!CreateDir(TekDir+"\\"+ARHIV)) { ActiveArhiv->Com=-10;/* FErrorDostup=true;*/return; }
   // Проверить наличие директории ARHIV\\XXXX - год
   if (!DirectoryExists(TekDir+"\\"+ARHIV+"\\"+YEAR))  if (!CreateDir(TekDir+"\\"+ARHIV+"\\"+YEAR)) { ActiveArhiv->Com=-10; /* FErrorDostup=true; */return; }
   // Проверить наличие директории ARHIV\\XXXX\\MM - месяц
   if (!DirectoryExists(TekDir+"\\"+ARHIV+"\\"+YEAR+"\\"+MON))  if (!CreateDir(TekDir+"\\"+ARHIV+"\\"+YEAR+"\\"+MON)) { ActiveArhiv->Com=-10; /*FErrorDostup=true; */return; }
   // Проверить наличие директории ARHIV\\XXXX\\MM\\DD - день
   if (!DirectoryExists(TekDir+"\\"+ARHIV+"\\"+YEAR+"\\"+MON+"\\"+DAT))  if (!CreateDir(TekDir+"\\"+ARHIV+"\\"+YEAR+"\\"+MON+"\\"+DAT)) { ActiveArhiv->Com=-10;/*FErrorDostup=true;*/return; }
   // создать файл      ARHIV\\XXXX\\MM\\DD\\hh - час

   if ((handle_file=_open(NameFile.c_str(),O_RDWR|O_BINARY|O_CREAT))>0) // создание нулевого файла
    {
     unsigned int  kb_zag = sizeof(int)*ActiveArhiv->CountTags+sizeof(int);
     unsigned char *buf;
     lseek(handle_file,0L,SEEK_SET);
     _write(handle_file,(unsigned char *)&kb_zag,sizeof(int))           ;
     _write(handle_file,(unsigned char *)ActiveArhiv->IDTags,sizeof(int)*ActiveArhiv->CountTags);
     unsigned int len_buf = ((sizeof(double)+sizeof(int))*ActiveArhiv->CountTags+sizeof(double))*3600; //  ((    значение и статус   ) *кол-во тэгов + дата и время) 60 сек * 60 мин
     buf = (unsigned char *)calloc(len_buf,sizeof(char));
     // заполнение нулями
     _write(handle_file,(unsigned char *)buf,len_buf);
     _close(handle_file);
     handle_file=-1;
     free(buf);
    }
   else { ActiveArhiv->Com = -10;/* FErrorDostup = true; */return; }
  }
 if ((handle_file=_open(NameFile.c_str(),O_RDWR|O_CREAT|O_BINARY))>0) // Запись информации в файл
  {
   // чтение размера заголовка
   unsigned int  kb = 0L;
   unsigned long sm = min * 60 + sec;
 /*  static int old_sm=0;
   if ((sm-old_sm)>1)
    {

     int k=0;
    }
   old_sm=sm;  */
   lseek(handle_file,0L,SEEK_SET);
   _read(handle_file,&kb,sizeof(int));
  /*  int k2=0;
   else
    if ((old_kb!=kb)&&(old_kb!=1000))
     int k3=0;
   old_kb=kb;*/
   sm = kb + sm * ((sizeof(double)+sizeof(int))*ActiveArhiv->CountTags+sizeof(double));
   lseek(handle_file,sm,SEEK_SET);
   _write(handle_file,&tim,sizeof(double));//!=sizeof(double))
   /* int k4=0;   */
   /*if (ActiveArhiv->ValTags[1]<1)
    int i=0;
   if (
   */
   _write(handle_file,(unsigned char *)ActiveArhiv->ValTags,sizeof(double)*ActiveArhiv->CountTags);
   /*!=sizeof(double)*ActiveArhiv->CountTags)
    int k=0;
   if (*/
   _write(handle_file,(unsigned char *)ActiveArhiv->StatTags,sizeof(int)*ActiveArhiv->CountTags);
   /*!=sizeof(int)*ActiveArhiv->CountTags)
    int k1=0;  */
   _close(handle_file);
   handle_file=-1;
   ActiveArhiv->Com = -11; /* FErrorDostup = false;*/
  }
 else { ActiveArhiv->Com=-10;/* FErrorDostup = true;*/return; }
}
//---------------------------------------------------------------------------


