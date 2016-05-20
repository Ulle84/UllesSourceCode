@echo off

echo processing file %1
echo --------------------------------------------------------------------------------

echo starting astyle
D:\ube\Tools\AStyle\astyle.exe --options=D:\ube\Tools\AStyle\AStyleOptions.txt %1
echo --------------------------------------------------------------------------------

echo starting code cleaner (1st run)
D:\ube\Misc\UllesSourceCode\build\CodeCleanerConsole-Desktop-Release\release\CodeCleaner.exe %1
echo --------------------------------------------------------------------------------

echo starting code cleaner (2nd run)
D:\ube\Misc\UllesSourceCode\build\CodeCleanerConsole-Desktop-Release\release\CodeCleaner.exe %1
