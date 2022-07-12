#include <stdio.h>
#include <stdlib.h>

#define _SVID_SOURCE 1
#include <termios.h>
#include <unistd.h>
#include <signal.h>

struct termios termios_save;

void reset_the_terminal(void)
{
	tcsetattr(0, 0, &termios_save );
}

sig_atomic_t the_flag = 0;

void handle_the_stuff(int num)
{
	char buff[4];
	buff[0] = '[';
	buff[2] = '0' + num%10;
	num /= 10;
	buff[1] = '0' + num%10;
	buff[3] = ']';
	write(0, buff, sizeof buff);
	the_flag = 1;
}

int main (void)
{
	int rc;
	int ch;
	struct termios termios_new;

	rc = tcgetattr(0, &termios_save );
	if (rc) {perror("tcgetattr"); exit(1); }

	rc = atexit(reset_the_terminal);
	if (rc) {perror("atexit"); exit(1); }

	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &termios_new );
	if (rc) {perror("tcsetattr"); exit(1); }

	signal(SIGINT, handle_the_stuff);

	printf("(pseudoshell)Start typing:\n" );
	while(1) {
		ch = getc(stdin);
		if (the_flag) {
			printf("Saw the signal, last character was %02x\n", (unsigned) ch);
			break;
		}
	}

	exit (0);
}
