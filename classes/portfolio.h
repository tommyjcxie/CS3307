#pragma once

#include <map>
#include "stock.h"
#include "watchlist.h"
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

class Portfolio {

//Private attributes for the Portfolio object
private:
	Watchlist portfolio;
	double currentPortfolioValue;
	double buyingPower;
	double calculatePortfolioValue(Watchlist *superlist);

//Public methods for the Portfolio object
public:
	Portfolio();
	~Portfolio();
	int getAmountOfShares(std::string company);
	void printPortfolioStocks(Watchlist *superlist); 
	double getPortfolioValue(Watchlist *superlist);
	double getBuyingPower();
	void setBuyingPower(double currentBuyingPower);
	void buyStock(std::string company, int shares, Watchlist *list);
	void sellStock(std::string company, int shares, Watchlist *list); 
	void printPortfolioStocksRec(Watchlist *superlist);
	void saveListToJson(std::string userName);
};

#endif
