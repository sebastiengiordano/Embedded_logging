@echo off
cd %CD%
call cls
call .\build\tests\SuiteTestFramework\SuiteTest_ut.exe -v
cmd \k