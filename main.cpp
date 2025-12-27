#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/wait.h>
#include "Args.hpp"
#include "Exec.hpp"

int main(int ac, char **av, char **env) {
	if (ac != 2){
		std::cerr << "\e[0;31mUsage:\e[0m\e[0;33m\t" << av[0]  << " \"program_path\"\e[0m" << std::endl;
		std::exit(1);
	}
	try
	{
		Args args;
		Exec exec;
		args.setArrays(av[1]);
		exec.run(args, av[1], env);
	}
	catch(const Exec::FdException& e)
	{
		std::cerr << e.what() << std::endl;
		return 2;
	}
	catch(const Exec::ProgramException& e)
	{
		std::cerr << e.what() << std::endl;
		return 3;
	}
	catch(const Exec::ArgException& e)
	{
		std::cerr << e.what() << std::endl;
		return 4;
	}
	catch(const Exec::ExitProgram& e)
	{
		return 1;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}