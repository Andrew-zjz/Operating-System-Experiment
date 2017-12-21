myshell: my_shell.h my_shell.c prompt.c read_command.c cmd1.c cmd2.c cmd3.c
	gcc my_shell.c prompt.c read_command.c -o my_shell 
	gcc cmd1.c -o cmd1
	gcc cmd2.c -o cmd2
	gcc cmd3.c -o cmd3

test: test.c
	gcc test.c -o test

clean:
	rm -f my_shell
	rm -f cmd1
	rm -f cmd2
	rm -f cmd3
