REM Automatically generated from Makefile
..\bin\lcc -debug -Wm-yC -Wf-bo0 -c -o functions_bank_0.o functions_bank_0.c
..\bin\lcc -debug -Wm-yC -Wf-bo1 -c -o functions_bank_1.o functions_bank_1.c
..\bin\lcc -debug -I../music_includes -Wm-yC -Wf-bo2 -c -o assets_bank_2.o assets_bank_2.c
..\bin\lcc -debug -Wm-yC -Wf-bo3 -c -o assets_bank_3.o assets_bank_3.c
..\bin\lcc -debug -Wm-yC -Wl-ya4 -Wm-yt0x19 -Wl-yo4 -Wl-llib/hUGEDriver.lib -o tactics.gb src\asmfunctions.s functions_bank_0.o functions_bank_1.o assets_bank_2.o assets_bank_3.o
.\romusage.exe tactics.noi