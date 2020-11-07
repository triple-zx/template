@echo off
for /l %%i in (1,1,10) do (
	gen_random.exe
	std.exe
	ping 0.0.0.0  -n 2 > null
	set name=random%i%.in
	ren rand.txt %name%
	move %name% D:/vscode/codearea/PA/pa1/
	
)
