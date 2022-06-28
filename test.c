#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int ac, char **av)
{
	int fd[2];
	if (pipe(fd) == -1)
	{
		return 1;
	}

	int	pid1 = fork();
	if (pid1 < 0)
	{
		return 2;
	}
	if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	// No need to check else because child process replace by ping because of exec
	int	pid2 = fork();
	if (pid2 < 0)
	{
		return 2;
	}
	if (pid2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	
	char *newargv[] = { "echo", "hello", "world", NULL };
    char *newenviron[] = { NULL };

    assert(argc == 2);  /* argv[1] identifie le
                           programme à exécuter */
    newargv[0] = argv[1];

    execve("/bin/echo", newargv, newenviron);
    perror("execve");   /* execve() ne retourne qu'en cas d'erreur */
    exit(EXIT_FAILURE);

	return (0);
}
