#include "Args.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <stdlib.h>

Args::Args(void){
	this->_one.reserve(100);
	this->_five.reserve(100);
	for (size_t i = 0; i < 1000000; i++) { this->_rand.push_back(i); }
	std::random_device rd;
    std::mt19937 g(rd());
	std::shuffle(this->_rand.begin(), this->_rand.end(), g);
}

Args::Args(Args const &obj){
	*this = obj;
}

Args &Args::operator=(Args const &obj){
	if (this != &obj) {
		this->_rand = obj.getRand();
		this->_one = obj.getOne();
		this->_five = obj.getFive();
	}
	return *this;
}

Args::~Args(void){
	for (int i = 0; i != 100; i++){
		if (this->_one[i]){
			if (this->_one[i][0])
				free(this->_one[i][0]);
			delete[] this->_one[i];
		}
		if (this->_five[i]){
			if (this->_five[i][0])
				free(this->_five[i][0]);
			delete[] this->_five[i];
		}
	}
}

std::vector<int> const &Args::getRand(void) const { return this->_rand; }
std::vector<char **> const &Args::getOne(void) const { return this->_one; }
std::vector<char **> const &Args::getFive(void) const { return this->_five; }

const char *Args::AllocException::what() const throw () { return "Allocation failed"; }

void Args::setArrays(void) {
	for (int i = 0; i != 100; i++){
		this->_one[i] = new char *[2];
		this->_five[i] = new char *[2];
	}
	int j = 0;
	int k = 0;
	std::string value_one;
	std::string value_five;
	for (size_t i = 0; i < 100000 - 1; i++){
		if (j < 100 && i % 100 == 0){
			this->_one[j][0] = strdup(value_one.c_str());
			if (!this->_one[j][0])
				throw AllocException();
			this->_one[j][1] = NULL;
			value_one.clear();
			j++;
		}
		if (k < 100 && i % 500 == 0){
			this->_five[k][0] = strdup(value_one.c_str());
			if (!this->_five[k][0])
				throw AllocException();
			this->_five[k][1] = NULL;
			value_five.clear();
			k++;
		}
		value_one.append(std::to_string(this->_rand[i]));
		value_one.push_back(' ');
		value_five.append(std::to_string(this->_rand[i]));
		value_five.push_back(' ');
		if (k >= 100)
			break ;
	}
}