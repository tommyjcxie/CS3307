
#pragma once

#ifndef WATCHLIST_H
#define WATCHLIST_H
#include <map>

class Watchlist {

//Private attributes for the Watchlist object
private:
	std::map<std::string, Stock> stockList;
	
//Public methods for the Watchlist object
public: 
	Watchlist();
	~Watchlist();
	Stock getStock(std::string stock);
	bool containsStock(std::string stock);
	void changeStockQuantity(std::string stock, int quantity);
	void changeStockPrice(std::string stock, double price);
	void removeStock(std::string);
	std::map<std::string, Stock> getStockList();
	void insertToStockList(Stock newStock);
	void updateStockList(std::string stock, int shares);
};

#endif
