
#include <iostream>
#include <vector>
#include <map>
#include "stock.h"
#include "watchlist.h"
#include "nameSymConverter.h"

using namespace std;

/*! \brief This method is the default constructor
 *         
 *  
 * 	This method is the default constructor
 *  @return none
 *  @author Tommy Xie
 */
Watchlist::Watchlist() {
}

/*! \brief This method is the destructor
 *         
 *  
 * 	This method is simply the destructor for the client class.
 *  @return none
 *  @author Jian Xie
 */
Watchlist::~Watchlist() {
}

/*! \brief This method fetches the specified stock.
 *         
 *  
 * 	This method takes in a stock name as an argument,
 * 	ie) AAPL. It then loops through the HashMap to find
 * 	if the stock exists.
 *  @param stock The symbol of the company/stock you wish to get
 *  @return The price of the stock
 *  @author Jian Xie
 */
Stock Watchlist::getStock(std::string stock) {
	std::map<std::string, Stock>::iterator it;
	it = stockList.find(NameSymConverter::instance().getSymbol(stock));
	return it->second;
}

/*! \brief This method changes the stock price
 *	 
 *  @param stock The symbol of the company/stock you wish to change
 * 	@param price The new price of the stock
 *  @return none
 *  @author Daniel Cho
 */
void Watchlist::changeStockPrice(std::string stock, double price){
	std::map<std::string, Stock>::iterator it;
	it = this->stockList.find(NameSymConverter::instance().getSymbol(stock));
	it->second.setCurrentStockPrice(price);
}

/*! \brief This method removes the stock from the watchlist
 *	 
 *  @param stock The symbol of the company/stock you wish to remove
 *  @return none
 *  @author Daniel Cho
 */
void Watchlist::removeStock(std::string stock){
	std::map<std::string, Stock>::iterator it;
	it = this->stockList.find(NameSymConverter::instance().getSymbol(stock));
	if(it != this->stockList.end()){
		this->stockList.erase(NameSymConverter::instance().getSymbol(stock));
	}
}

/*! \brief This method checks if the stock exists when buying
 *	 
 *  @param stock The symbol of the company/stock you wish to buy
 *  @return none
 *  @author Yan Feng Lin
 */
bool Watchlist::containsStock(std::string stock){
	std::map<std::string, Stock>::iterator it;
	it = stockList.find(NameSymConverter::instance().getSymbol(stock));
	if(it != this->stockList.end()){
		return true;
	}
	return false;
}

/*! \brief This method changes the stock quantity
 *	 
 *  @param stock The symbol of the company/stock you wish to change
 * 	@param quantity The quantity you want to set it as an int
 *  @return none
 *  @author Daniel Cho
 */
void Watchlist::changeStockQuantity(std::string stock, int quantity){
	std::map<std::string, Stock>::iterator it;
	it = this->stockList.find(NameSymConverter::instance().getSymbol(stock));
	it->second.setQuantity(quantity);
}

/*! \brief This method returns the Watchlist.
 *         
 *  
 * 	This method returns the entire Watchlist as a HashMap.
 *  @return The Watchlist as a HashMap
 *  @author Jian Xie
 */
map<std::string, Stock> Watchlist::getStockList() {
	return this->stockList;
}

/*! \brief This method inserts a new stock to the watch list
 *	 
 *  @param newStock The stock that you want to add into the watchlist
 *  @return none
 *  @author Daniel Cho
 */
void Watchlist::insertToStockList(Stock newStock) {
	this->stockList.insert(std::pair<std::string, Stock>(newStock.getCompanyName(), newStock));
}

/*! \brief This method changes the stock quantity
 *	 
 *  @param stock The symbol of the company/stock you wish to change
 * 	@param quantity The quantity you want to set it as an int
 *  @return none
 *  @author Jia Yu Man
 */
void Watchlist::updateStockList(std::string stock, int shares){
	std::map<std::string, Stock>::iterator it;
	it = this->stockList.find(NameSymConverter::instance().getSymbol(stock));
	if (it != this->stockList.end()){
		int quantity = it->second.getQuantity();
		quantity = quantity - shares;
		it->second.setQuantity(quantity);         
		if (quantity == 0){
			this->stockList.erase(it->first);
		} 
	}
}
