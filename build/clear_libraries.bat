@echo off
RD /S /Q Libraries\include
RD /S /Q Libraries\lib
del .\tmplib\*
RD /S /Q .\tmplib
RD /S /Q .\src