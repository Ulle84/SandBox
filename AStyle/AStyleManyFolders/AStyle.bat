@echo off

rem set options
set folders=TemplateQtExecutable\code TemplateViAcquiDevice\code
set suffix=cpp h hpp

FOR %%f IN (%folders%) DO (
  FOR %%s IN (%suffix%) DO (
    astyle.exe --options=AStyleOptions.txt %%f\*.%%s
  )
)