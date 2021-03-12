@echo off
git add .
set /p msg=Enter commit message, empty for current time: 
if "x%msg%"=="x^%msg^%" (
  set msg=Sync: %date% %time%
)
git commit -S -am "%msg%"

git push
