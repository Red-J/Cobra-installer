@echo off
set PS3SDK=/c/PSDK3v2
set WIN_PS3SDK=C:/PSDK3v2
set PATH=%WIN_PS3SDK%/mingw/msys/1.0/bin;%WIN_PS3SDK%/mingw/bin;%WIN_PS3SDK%/ps3dev/bin;%WIN_PS3SDK%/ps3dev/ppu/bin;%WIN_PS3SDK%/ps3dev/spu/bin;%WIN_PS3SDK%/mingw/Python27;%PATH%;
set PSL1GHT=%PS3SDK%/psl1ght
set PS3DEV=%PS3SDK%/ps3dev


if exist cobra755.pkg del cobra755.pkg>nul

if exist Cobra_755.elf del  Cobra_755.elf>nul
if exist Cobra_755.self del Cobra_755.self>nul
if exist build del /s/q build\*.*>nul

make pkg

ren build\pkg EP0001-COBJ75511_00-0000000000000000
param_sfo_editor.exe build\EP0001-COBJ75511_00-0000000000000000\PARAM.SFO "ATTRIBUTE" 133

if exist Cobra_755.elf del Cobra_755.elf>nul
if exist Cobra_755.self del Cobra_755.self>nul
if exist Cobra_755.pkg del Cobra_755.pkg>nul
if exist build del /q build\*.*>nul
if not exist build goto end

echo ContentID = EP0001-COBJ75511_00-0000000000000000>package.conf
echo Klicensee = 000000000000000000000000000000000000>>package.conf
echo PackageVersion = 01.00>>package.conf
echo DRMType = Free>>package.conf
echo ContentType = GameExec>>package.conf

psn_package_npdrm.exe -n package.conf build\EP0001-COBJ75511_00-0000000000000000

del package.conf

if exist  cobra755 del  cobra755.pkg>nul
move /y EP0001-COBJ75511_00-0000000000000000.pkg  cobra755.pkg
pause

del /s/q build>nul
rd /q/s build

:end
