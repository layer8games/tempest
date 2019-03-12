del ..\..\Lib\* /S /Q
del ..\..\Headers\Engine\ /S /Q
xcopy ..\..\..\Killer_Engine\Bin\Win32_Debug\Killer_Engine_Win32_Debug.lib ..\..\Lib\ /s /i /y
xcopy ..\..\..\Killer_Engine\Lib\* ..\..\Lib\ /s /i /y
xcopy ..\..\..\Killer_Engine\Headers\* ..\..\Headers\ /s /i /y
PAUSE