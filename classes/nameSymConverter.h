#pragma once
#ifndef NAMESYMCONV_H
#define NAMESYMCONV_H

#include <map>
#include <string>

class NameSymConverter{
	
	private:
	std::map<std::string, std::string> nameSymMap;
	static NameSymConverter* _instance;
	
	protected:
	NameSymConverter();
	
	public:
	~NameSymConverter();
	std::string getSymbol(std::string);
	static NameSymConverter instance();
};

#endif
