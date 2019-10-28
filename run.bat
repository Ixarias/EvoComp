@ECHO OFF
mode con: cols=120 lines=40
:: ft20
xcopy /Y C:\Users\Victor\Documents\GitHub\EvoComp2\ft20ms.txt C:\Users\Victor\Documents\GitHub\EvoComp2\MachineSequences.txt
xcopy /Y C:\Users\Victor\Documents\GitHub\EvoComp2\ft20pt.txt C:\Users\Victor\Documents\GitHub\EvoComp2\ProcessingTime.txt
ECHO ft20
start /W /B /HIGH "run" C:\Users\Victor\Documents\GitHub\EvoComp2\a.exe
start /W /B /HIGH "run2" C:\Users\Victor\Documents\GitHub\EvoComp2\a.exe
start /W /B /HIGH "run3" C:\Users\Victor\Documents\GitHub\EvoComp2\a.exe
start /W /B /HIGH "run4" C:\Users\Victor\Documents\GitHub\EvoComp2\a.exe
start /W /B /HIGH "run5" C:\Users\Victor\Documents\GitHub\EvoComp2\a.exe
start /W /B /HIGH "run6" C:\Users\Victor\Documents\GitHub\EvoComp2\a.exe
start /W /B /HIGH "run7" C:\Users\Victor\Documents\GitHub\EvoComp2\a.exe
start /W /B /HIGH "run8" C:\Users\Victor\Documents\GitHub\EvoComp2\a.exe
start /W /B /HIGH "run9" C:\Users\Victor\Documents\GitHub\EvoComp2\a.exe
start /W /B /HIGH "run10" C:\Users\Victor\Documents\GitHub\EvoComp2\a.exe