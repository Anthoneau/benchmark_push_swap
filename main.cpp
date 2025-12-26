#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include "Args.hpp"

int main(int ac, char **av, char **env) {
	if (ac != 2){
		std::cerr << "\e[0;31mUsage:\e[0m\e[0;33m\t" << av[0]  << " \"program_path\"\e[0m" << std::endl;
		std::exit(1);
	}
	(void)env;
	Args args;
	try
	{
		args.setArrays();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	//const int bytes = 10;
	//char **ptr = new char*[2];
	//ptr[0] = strdup("1 0 1");
	//ptr[1] = NULL;
	//int pipe_fd[2];
	//pipe(pipe_fd);
	//pid_t pid = fork();
	//int state;
	//if (!pid){
	//	close(pipe_fd[0]);
	//	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
	//		close(pipe_fd[1]);
	//		std::exit(2);
	//	}
	//	execve(av[1], ptr, env);
	//	close(pipe_fd[1]);
	//	std::exit(1);
	//}
	//close(pipe_fd[1]);
	//char *filebuf;
	//filebuf = static_cast<char*>(calloc(bytes, sizeof(char)));
	//if (!filebuf){
	//	std::cerr << "Alloc error" << std::endl;
	//	std::exit(1);
	//}
	//std::string str;
	//while (read(pipe_fd[0], filebuf, bytes)) {
	//	str.append(filebuf);
	//	bzero(filebuf, 10);
	//}
	//close(pipe_fd[0]);
	//waitpid(pid, &state, 0);
	//WEXITSTATUS(state);
	//if (state == 512){
	//	std::cerr << "dup2 failed" << std::endl;
	//	std::exit(1);
	//}
	//if (state == 256){
	//	std::cerr << "Error with program" << std::endl;
	//	std::exit(1);
	//}
	//if (state == 0){
	//	std::cerr << "Error with args" << std::endl;
	//	std::exit(1);
	//}
	//std::cout << "state" << state << std::endl;
	//std::cout << "test réussi" << std::endl;
	//std::cout << "filebuf: " << str << std::endl;
	//free(ptr[0]);
	//delete[] ptr;
	return 0;
}