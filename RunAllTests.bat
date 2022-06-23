@echo off
cd %CD%
call cls
Rem call .\build\tests\SuiteTestFramework\SuiteTest_ut.exe -v
call .\build\tests\libs\assertion\LibsTest-Assertion_ut.exe -v
call .\build\tests\libs\assertion-disabled\LibsTest-Assertion-Disabled_ut.exe -v
cmd \k