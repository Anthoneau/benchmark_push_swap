#include <vector>
#include <exception>

class Args
{
	private:
		std::vector<int> _rand;
		std::vector<char **> _one;
		std::vector<char **> _five;
	public:
		Args(void);
		Args(Args const &obj);
		Args &operator=(Args const &obj);
		~Args(void);

		std::vector<int> const &getRand(void) const;
		std::vector<char **> const &getOne(void) const;
		std::vector<char **> const &getFive(void) const;

		void setArrays(void);

		class AllocException: public std::exception {
			public:
				const char* what() const throw ();
		};
};

