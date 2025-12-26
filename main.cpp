#include <iostream>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <string>
#include <sys/wait.h>

int main(int ac, char **av, char **env) {
	const int bytes = 10;
	char **ptr = new char*[2];
	ptr[0] = strdup("1 0 1");
	ptr[1] = NULL;
	int pipe_fd[2];
	pipe(pipe_fd);
	pid_t pid = fork();
	int state;
	if (!pid){
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			std::exit(2);
		close(pipe_fd[0]);
		execve("./push_swap", ptr, env);
		std::exit(1);
	}
	close(pipe_fd[1]);
	char *filebuf;
	filebuf = static_cast<char*>(calloc(bytes, sizeof(char)));
	if (!filebuf){
		std::cerr << "Alloc error" << std::endl;
		std::exit(1);
	}
	std::string str;
	while (read(pipe_fd[0], filebuf, bytes)) {
		str.append(filebuf);
		bzero(filebuf, 10);
	}
	close(pipe_fd[0]);
	waitpid(pid, &state, 0);
	WEXITSTATUS(state);
	if (state == 512){
		std::cerr << "dup2 failed" << std::endl;
		std::exit(1);
	}
	if (state == 256){
		std::cerr << "Error with program" << std::endl;
		std::exit(1);
	}
	std::cout << "state" << state << std::endl;
	std::cout << "test réussi" << std::endl;
	std::cout << "filebuf: " << str << std::endl;
	return 0;
}