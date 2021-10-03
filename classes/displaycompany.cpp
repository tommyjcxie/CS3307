
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "stock.h"
#include "watchlist.h"

/*! \brief This prints out the spcific stock and its history
 *         
 *  
 * 	This method takes in the company name and Watchlist list and
 * 	displays the companys stock information. (i.e: the price, price
 * 	history, etc).
 *  @param company A string of the company's name, ex: AAPL for Apple
 *  @param list Watchlist object containing information on all the stocks
 *  @return none
 *  @author Yan Feng Lin
 */
void displayCompany(std::string company, Watchlist list) {

	//Get the stock object from the main list using the company name
	Stock thisStock = list.getStock(company);
		
	std::vector<double> history = thisStock.getStockHistory();
	int size = history.size();
	
	//Print out information
	std::cout << "The company is named " << thisStock.getCompanyName() << std::endl;
	std::cout << "History of the stock price: "<< std::endl;
	for (int i = 0; i < size-1; i++) {
		std::cout << (size-1 - i) << " month(s) ago: " << thisStock.getStockHistory()[i] << std::endl;
	}
    std::cout << "The current price is $" << thisStock.getCurrentStockPrice() << std::endl;
	
	//Initializing variables for the graph
    double maxPrice = 0;
    double minPrice = 9999;
    for(int i = 0; i < size-1; i++){
        if (maxPrice < thisStock.getStockHistory()[i]){
            maxPrice = thisStock.getStockHistory()[i];
        }
        if (minPrice > thisStock.getStockHistory()[i]){
            minPrice = thisStock.getStockHistory()[i];
        }
    }
    const int intervalCount = 9;
    double interval = (maxPrice - minPrice)/(intervalCount-1);
    double priceInterval[intervalCount];
    for (int i = 0; i < intervalCount; i++){
        priceInterval[intervalCount-1-i] = minPrice + interval*i;
    }

    std::cout << std::endl;
    //Prints a graph with the stock's price history
    for(int i = 0; i < intervalCount; i++){
        std::cout << std::setw(15) << "$" + std::to_string(int((priceInterval[i] + interval))) + " - $" + std::to_string(int(priceInterval[i])) + "|";
        for(int j = 0; j < size - 1; j++){
            if (thisStock.getStockHistory()[j] >= priceInterval[i] && thisStock.getStockHistory()[j] < priceInterval[i] + (interval - 0.01)){
                std::cout << std::setw(3) << "X" << "  ";
            }
            else{
                std::cout << "     ";
            }
        }
        std::cout << "\n";
    }
    std::cout << std::setw(13) << " ";
    for (int i = 0; i < size - 1; i++){
        std::cout << std::setw(5) << (size - 1 - i);
    }
    std::cout << std::endl;
    std::cout << std::setw(30) << " " << "month(s) ago" << std::endl;

    std::cout << "Gain over past year: " << 100 * ((thisStock.getCurrentStockPrice() - thisStock.getStockHistory()[0])/thisStock.getStockHistory()[0]) << "% ($"<< thisStock.getCurrentStockPrice() - thisStock.getStockHistory()[0] << ")" << std::endl;
	std::cout << "Gain over past month: " << 100 * ((thisStock.getCurrentStockPrice() - thisStock.getStockHistory()[size - 2])/thisStock.getStockHistory()[size - 2]) << "% ($"<< thisStock.getCurrentStockPrice() - thisStock.getStockHistory()[size - 2] << ")" << std::endl;

}
