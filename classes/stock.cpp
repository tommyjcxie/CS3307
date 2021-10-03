#include <iostream>
#include <vector>
#include "stock.h"
#include <ctime>
#include <random>
using namespace std;

/*! \brief The default constructor for Stock.
 *         
 *	This method initializes default stock values.
 * 
 *  @return none
 *  @author Jian Xie
 */
Stock::Stock() {
	this->companyName = "";
	this->stockPrice = 0;
  	this->stockQuantity = 0;        //stockQuantity is the quantity of stocks owned by the user
	this->stockHistory = {};
}

/*! \brief The is the constructor for the class.
 *         
 *	This method initializes the stock object with the values passed
 * 	from the parameter. i.e: name, price, quantitiy, price history.
 * 	
 * 	@param name The name of the stock
 *  @param price The price of the stock
 * 	@param quantity The quantity of the stock
 * 	@param history The price history of the stock
 *  @return none
 *  @author Jian Xie
 */
Stock::Stock(string name, double price, int quantity, vector<double> history) {
	this->companyName = name;
	this->stockPrice = price;
	this->stockQuantity = quantity;
	this->stockHistory = history;																						
}

/*! \brief The destructor for the class
 *         
 *	This method is the destructor for the stock class
 * 
 *  @return none
 *  @author Jian Xie
 */
Stock::~Stock() {
}

/*! \brief Method to return stock company name.
 *         
 *	This method returns the company name of the stock.
 * 
 *  @return The company name of the specified stock object.
 *  @author Jian Xie
 */
string Stock::getCompanyName() {
	return this->companyName;
}

/*! \brief Method to return current stock price.
 *         
 *	This method returns the current stock price of the stock.
 * 
 *  @return The stock price of the specified stock object.
 *  @author Jian Xie
 */
double Stock::getCurrentStockPrice() {
	return this->stockPrice;
}

/*! \brief Method to return stock price history.
 *         
 *	This method returns the stock price history.
 * 
 *  @return The stock price history of the specified stock object.
 *  @author Jian Xie
 */
vector<double> Stock::getStockHistory() {
	return this->stockHistory;
}

/*! \brief Method to return quantity of stock.
 *         
 *	This method returns the quantity of the stock bought.
 * 
 *  @return The quantity of the specified stock object.
 *  @author Jian Xie
 */
int Stock::getQuantity(){
    return this->stockQuantity;
}

/*! \brief Method to set the stock name.
 *         
 *	This method sets the stock name to the argument passed in.
 *
 * 	@param name The name you want to set the stock as.
 *  @return none
 *  @author Jian Xie
 */
void Stock::setCompanyName(string name) {
	this->companyName = name;
}

/*! \brief Method to set stock price.
 *         
 *	This method sets the stock price to the argument passed in.
 *
 * 	@param name The price you want to set the stock as.
 *  @return none
 *  @author Jian Xie
 */
void Stock::setCurrentStockPrice(double price) {
	this->stockPrice = price;
}

/*! \brief Method to set stock price history.
 *         
 *	This method sets the stock price history to the argument passed in.
 *
 * 	@param name The price history as a vector you want to set the stock as.
 *  @return none
 *  @author Jian Xie
 */
void Stock::setStockHistory(vector<double> history) {
	this->stockHistory = history;
}

/*! \brief Method to set stock quantity
 *         
 *	This method sets the stock quantity to the argument passed in.
 *
 * 	@param name The quantity you want to set the stock as.
 *  @return none
 *  @author Jian Xie
 */
void Stock::setQuantity(int quantity){
    this->stockQuantity = quantity;
}

/*! \brief Method to update stock price.
 *         
 *	This method simulates updating the stock price whenever it is called
 *  by using <time> and rand().
 *
 *  @return none
 *  @author Jian Xie
 */
void Stock::updatePrice(){
	int ran = rand()%2; // random number between 0 and 1
	std::srand((unsigned int)time(NULL));
	std::random_device rd;
	std::default_random_engine generator(rd()); // rd() provides a random seed
	std::uniform_real_distribution<double> distribution(0.1,10);
	double number = rand() % 10 + 0.1;

	if (ran == 0){
		this->stockPrice = this->stockPrice + number;
	}
	else{
		this->stockPrice = this->stockPrice - number;
	}
}