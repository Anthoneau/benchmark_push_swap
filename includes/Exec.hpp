#pragma once
#include <exception>
#include "Args.hpp"

class Exec
{
	private:
		std::vector<int> count_one;
		std::vector<int> count_five;
	public:
		Exec(void);
		Exec(Exec const &obj);
		Exec &operator=(Exec const &obj);
		~Exec(void);

		void run(const Args &args, char *program, char **env);

		class FdException: public std::exception {
			public:
				const char* what() const throw ();
		};
		class ProgramException: public std::exception {
			public:
				const char* what() const throw ();
		};
		class ArgException: public std::exception {
			public:
				const char* what() const throw ();
		};
		class PipeException: public std::exception {
			public:
				const char* what() const throw ();
		};
		class AllocException: public std::exception {
			public:
				const char* what() const throw ();
		};
		class ExitProgram: public std::exception {
			public:
				const char* what() const throw ();
		};
};
