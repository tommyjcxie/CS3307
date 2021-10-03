#pragma once

#ifndef STOCK_H
#define STOCK_H

class Stock {

//Private attributes for the Stock object
private:
	std::string companyName;
	double stockPrice;
	int stockQuantity;
	std::vector<double> stockHistory;

//Public methods for the Stock object
public:
	Stock();
	Stock(std::string name, double price, int quantity, std::vector<double> history);
	~Stock();
	std::string getCompanyName();
	double getCurrentStockPrice();
	std::vector<double> getStockHistory();
	void setCompanyName(std::string name);
	int getQuantity();
	void setQuantity(int quantity);
	void setCurrentStockPrice(double price);
	void setStockHistory(std::vector<double> history);
	void updatePrice();
};

#endif
