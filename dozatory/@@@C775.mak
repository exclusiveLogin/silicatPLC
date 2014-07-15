.AUTODEPEND

#=========================================================
#		*General Macro Define*
#=========================================================
TCROOT	= C:\PROGRA~1\BC31
CC 	= C:\PROGRA~1\BC31\BIN\BCC.EXE
TLINK 	= C:\PROGRA~1\BC31\BIN\TLINK.exe
ICPLIB	= C:\ICPDAS\MINIOS~1\lib

#=========================================================
#		*Implicit  Rules*
#=========================================================
.c.obj:
	$(CC) -c {$< }

.cpp.obj:
	$(CC) -c {$< }

#=========================================================
#		*Target Macro Define*
#=========================================================
TARGET=NONAME00
DEFINES=i7188EA
OBJS=NONAME00.OBJ
INCS=C:\ICPDAS\MINIOS~1\lib
ICPLIB=C:\ICPDAS\MINIOS~1\lib
LIBS=

CC=$(CC) +$(TARGET).CFG

#=========================================================
#		*Explicit Rules*
#=========================================================
$(TARGET).exe: $(TARGET).cfg $(OBJS) $(LIBS)
  $(TLINK) /x/c @&&|
$(TCROOT)\lib\c0l.obj+
$(OBJS)
$(TARGET),

C:\PROGRA~1\BC31\lib\emu.lib+
C:\PROGRA~1\BC31\lib\mathl.lib+
C:\PROGRA~1\BC31\lib\cl.lib+

|
  -@del $(TARGET).cfg

#=========================================================
#		*Compiler Configuration File*
#=========================================================
$(TARGET).cfg:
  copy &&|
-ml
-1
-V
-vi-
-D$(DEFINES)
-I$(TCROOT)\INCLUDE;$(INCS)
-L$(TCROOT)\LIB;$(ICPLIB)
| $(TARGET).cfg
