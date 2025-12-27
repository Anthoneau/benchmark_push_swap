#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <string.h>
#include "Exec.hpp"

const int FDERROR = 512;
const int PROGRAMERROR = 768;
const int ARGSERROR = 1024;
const int READ = 10;

Exec::Exec(void){
	this->count_one.reserve(100);
	this->count_five.reserve(100);
}

Exec::Exec(Exec const &obj){
	*this = obj;
}

Exec &Exec::operator=(Exec const &obj){
	if (this != &obj){
		this->count_one = obj.count_one;
		this->count_five = obj.count_five;
	}
	return *this;
}

Exec::~Exec(void) {}

const char *Exec::FdException::what() const throw () { return "Dup failed"; }
const char *Exec::ProgramException::what() const throw () { return "Program failed"; }
const char *Exec::ArgException::what() const throw () { return "Arguments error"; }
const char *Exec::PipeException::what() const throw () { return "Pipe failed"; }
const char *Exec::AllocException::what() const throw () { return "Allocation failed"; }
const char *Exec::ExitProgram::what() const throw () { return ""; }

int countMovements(char **args, char *program, char **env){
	int pipe_fd[2];
	if (pipe(pipe_fd) == -1)
		throw Exec::PipeException();
	pid_t pid = fork();
	if (!pid){
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
			close(pipe_fd[1]);
			throw Exec::FdException();
		}
		execve(program, args, env);
		close(pipe_fd[1]);
		throw Exec::ProgramException();
	}
	close(pipe_fd[1]);
	int status = 0;
	waitpid(pid, &status, 0);
	int real_status = WEXITSTATUS(status);
	if (real_status == FDERROR || real_status == PROGRAMERROR || real_status == ARGSERROR)
		throw Exec::ExitProgram();

	char *filebuf;
	filebuf = static_cast<char*>(calloc(READ, sizeof(char)));
	if (!filebuf)
		throw Exec::AllocException();
	int bytes;
	int count = 0;
	while ((bytes = read(pipe_fd[0], filebuf, READ))) {
		for (int i = 0; i < READ; i++){
			if (filebuf[i] == '\n')
				count++;
		}
		bzero(filebuf, READ);
	}
	free(filebuf);
	close(pipe_fd[0]);
	return count;
}

void Exec::run(const Args &args, char *program, char **env) {
	for (int i = 0; i < 100; i++){
		int count = countMovements((args.getOne())[i], program, env);
		this->count_one.push_back(count);
	}
	for (int i = 0; i < 100; i++){
		int count = countMovements((args.getFive())[i], program, env);
		this->count_five.push_back(count);
	}
	size_t total_one = 0;
	size_t total_five = 0;
	for (std::vector<int>::iterator it = this->count_one.begin(); it != this->count_one.end(); it++){
		total_one += *it;
	}
	total_one /= this->count_one.size();
	std::cout << "The average number of moves for 100 digits is: ~" << total_one << std::endl;
	for (std::vector<int>::iterator it = this->count_five.begin(); it != this->count_five.end(); it++){
		total_five += *it;
	}
	total_five /= this->count_one.size();
	std::cout << "The average number of moves for 500 digits is: ~" << total_five << std::endl;
}
