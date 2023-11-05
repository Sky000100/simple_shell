#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * execute_command - Execute a command with arguments.
 * @argv: An array of strings containing the command and its arguments.
 *
 * Return: (int) The exit status of the executed command.
 */

int execute_command(char **argv)
{
	pid_t child_pid;
	int status = 0;

	if (argv == NULL || *argv == NULL)
	{
		return (status);
	}

	if (check_for_builtin(argv))
	{
		return (status);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (child_pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(child_pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (status);
}

/**
 * main - Entry point of the program.
 *
 * This function is the entry point of the program.
 *			It demonstrates the usage of
 * the execute_command function by executing a sample
 *			command. The exit status of
 * the executed command is printed.
 *
 * Return: (int) Returns 0 to indicate successful program execution.
 */

int main(void)
{
	char *argv[] = {"ls", "-l", NULL};
	int exit_status = execute_command(argv);

	printf("Exit status: %d\n", exit_status);

	return (0);
}

