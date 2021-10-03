#include <iostream>
#include <sstream>
#include <fstream>

#include "nameSymConverter.h"

using namespace std;

NameSymConverter* NameSymConverter::_instance = NULL;

/*! \brief Static method that returns an instance of NameSymConverter
 *         
 *  
 * 	Singleton design implementation; static method returns the instance
 *  of NameSymConverter, or creates one if it doesn't exist yet then returns it
 *  @return NameSymConverter
 *  @author Yan Feng Lin
 */
NameSymConverter NameSymConverter::instance()
{
  if (_instance == NULL)
    _instance = new NameSymConverter();

  return *_instance;
}

/*! \brief Default private constructor, maps company names to stock symbols
 *         
 *  
 * 	Default constructor reads company names and their stock symbols from symbolsAndNames.txt then maps them
 *  @return none
 *  @author Yan Feng Lin
 */
NameSymConverter::NameSymConverter(){
	string line;
	ifstream myfile("symbolsAndNames.txt");
	this->nameSymMap = {};
	while (getline(myfile, line)){
		stringstream s(line);
		string sym;
		string name;
		s >> sym;
		s >> name;
		this->nameSymMap.insert(pair<string, string>(name, sym));
	}
	myfile.close();
}

/*! \brief This method is the destructor
 *         
 *  
 * 	This method is simply the destructor for the client class.
 *  @return none
 *  @author Yan Feng Lin
 */
NameSymConverter::~NameSymConverter(){
	
}

/*! \brief This method takes the company name as a parameter and returns its respective stock symbol
 *         
 *  
 * 	This method takes the company name as a parameter and returns its respective stock symbol
 *  @param string
 *  @return string
 *  @author Yan Feng Lin
 */
string NameSymConverter::getSymbol(std::string name){
	return nameSymMap.find(name)->second;
}
