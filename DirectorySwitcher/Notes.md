# Bugs

# ToDo
* continue in method MainWindow::on_pushButtonSwitch_clicked()

# Ideas

# Done

# General Description
often I have the problem that I am copying around directories
for example i have the three folders:
* build_32BitRunning
* build_64BitCopiedFrom32Bit
* build_64BitCopiedFromEmpty

and I have to copy the content to build several times to test.

Information
- baseName (build)
- configNames (32BitRunning, 64BitCopiedFrom32Bit, 64BitCopiedFromEmpty)
- configName is stored in a fileName like 64BitCopiedFrom32Bit.inf and stored in the folder

GUI
- comboBox with all configNames
- button 'switch directory'

change directory with
- rename current baseName folder (if existing) to baseName_oldConfigName
- rename current baseName_newConfigName folder to baseName
