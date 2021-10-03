#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "stock.h"
#include "portfolio.h"
#include "watchlist.h"
#include <random>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json; 

//Initialize all attributes to empty values
Portfolio::Portfolio() {
    this->currentPortfolioValue = 0;
    this->buyingPower = 0;
}

//Empty destructor
Portfolio::~Portfolio() {
}

/*! \brief This algorithm for counting the total stock value
 *  
 *  This function takes all the stocks and the value of each,
 *  then it multiplies each and allows adds it to a total value
 * 
 *  @param superlist is an Watchlist argument of the watchlist class 
 *  containing the master list of all the stocks
 *  @return returns a double that represents the total value of stocks
 *  @author Daniel Cho
 */
double Portfolio::calculatePortfolioValue(Watchlist *superlist){
    //Update prices first
    map<std::string, Stock>::iterator it2;
    map<std::string, Stock> superListMap2 = this->portfolio.getStockList();
    for (it2 = superListMap2.begin(); it2 != superListMap2.end(); it2++){
        this->portfolio.changeStockPrice(it2->first, superlist->getStock(it2->first).getCurrentStockPrice());
    }
    //sum of all stocks (stockprice * stockquantity)
    double total; 
    int currentStockValue;
    map<std::string, Stock>::iterator it;
    map<std::string, Stock> superListMap = this->portfolio.getStockList();
    if(superListMap.begin() == superListMap.end()){
        this->currentPortfolioValue = 0;
    }
    for (it = superListMap.begin(); it != superListMap.end(); it++){
        total += (it->second.getCurrentStockPrice() * it->second.getQuantity());
        this->currentPortfolioValue = total;
    }
    return this->currentPortfolioValue + buyingPower;
}


/*! \brief This algorithm prints out the stocks and values of the portfolio
 *  
 *  This function iterates over the stocks in the portfolio and prints out 
 *  how many shares of each is owned.
 *  Then we show the portfolio values.
 *  
 *  @param superlist is an Watchlist argument of the watchlist class 
 *  containing the master list of all the stocks
 *  @return nothing
 *  @author Daniel Cho
 */
void Portfolio::printPortfolioStocks(Watchlist *superlist){
    map<std::string, Stock>::iterator it;
    map<std::string, Stock> superListMap = this->portfolio.getStockList();
    cout << endl; 
    cout << "Your current portfolio contains: " << endl;
    for (it = superListMap.begin(); it != superListMap.end(); it++){
        cout << it->first << " : " << it->second.getQuantity() << " shares" << endl;
    }
    double val = calculatePortfolioValue(superlist);
    cout << "Your portfolio stock balance is $" << this->currentPortfolioValue << endl;
    cout << "Your portfolio buying power is $" << this->buyingPower << endl;
    cout << "Your total portfolio is valued at $" << val << endl;
}

/*! \brief This algorithm prints out the stocks and values of the portfolio
 *  
 *  This function iterates over the stocks in the portfolio and prints out 
 *  how many shares of each is owned.
 *  Then we show the portfolio values.
 *  
 *  @param superlist is an Watchlist argument of the watchlist class 
 *  containing the master list of all the stocks
 *  @return nothing
 *  @author Daniel Cho
 */
void Portfolio::printPortfolioStocksRec(Watchlist *superlist){
     cout << "| PORTFOLIO |" << endl;
     cout << endl;
    // Random seed
    random_device rd;
 
    // Initialize Mersenne Twister pseudo-random number generator
    mt19937 gen(rd());
 
    // Generate pseudo-random numbers
    // uniformly distributed in range (1, 100)
    uniform_int_distribution<> dis(1, 100);
    map<std::string, Stock>::iterator it;
    map<std::string, Stock> superListMap = this->portfolio.getStockList();
    cout << endl; 
    cout << "Your current portfolio contains: " << endl;
    for (it = superListMap.begin(); it != superListMap.end(); it++){
        int randomX = dis(gen);
        cout << it->first << " : " << it->second.getQuantity() << " shares";
         if (randomX > 50){
            cout << "| Probability of gaining money: " << randomX << "%" " | You should hold onto this stock." << endl; 
         }
         else{
             cout << "| Probability of gaining money: " << randomX << "%" " | You should sell this stock." << endl;
        }

    }
    double val = calculatePortfolioValue(superlist);
    cout << "\nYour portfolio stock balance is $" << this->currentPortfolioValue << endl;
    cout << "Your balance (buying power) is $" << this->buyingPower << endl;
    cout << "Your total portfolio is valued at $" << val << endl;
 
}

/*! \brief This function retruns the portfolio value
 *  
 *  Call the calculate portfolio value and return it
 *  
 *  @param superlist is an Watchlist argument of the watchlist class 
 *  containing the master list of all the stocks
 *  @return none
 *  @author Daniel Cho
 */
double Portfolio::getPortfolioValue(Watchlist *superlist){
    return calculatePortfolioValue(superlist);
}

/*! \brief This function returns the buying power
 *  
 *  @param none
 *  @return none
 *  @author Daniel Cho
 */
double Portfolio::getBuyingPower(){
    return this->buyingPower;
}


/*! \brief This function sets the buying power
 *  
 *  @param none
 *  @return none
 *  @author Daniel Cho
 */
void Portfolio::setBuyingPower(double currentBuyingPower){
    this->buyingPower = currentBuyingPower;
}

/*! \brief This function gets the amount of shares from a stock
 *  
 *  @param string for the company
 *  @return int to show how many shares there are
 *  @author Daniel Cho
 */
int Portfolio::getAmountOfShares(std::string company){
    return portfolio.getStock(company).getQuantity();
    //return portfolio.getStockList().find(company)->second.getQuantity();
}


/*! \brief This function buys the stock
 *  
 *  @param company is an string argument representing the company
 *  containing master list of all the stocks
 *  @param list is an Watchlist argument of the watchlist class 
 *  containing the master list of all the stocks
 *  @return none
 *  @author Daniel Cho
 */
void Portfolio::buyStock(string company, int shares, Watchlist *list){
    Stock stock = list->getStock(company);
    //include number of stock to buy using stock.setQuantity
    double currentStockPrice = (list)->getStock(company).getCurrentStockPrice();
    int currentStockQuantity = (list)->getStock(company).getQuantity();
    cout << "the current stock quantity is " << currentStockQuantity << endl;

    this->buyingPower -= currentStockPrice*shares;
    if(this->portfolio.containsStock(company)){
        this->portfolio.changeStockQuantity(company, currentStockQuantity);
    }
    else{
        this->portfolio.insertToStockList(stock);
    }
    cout << "Thank you for buying the stock." << endl;
    cout << "Your new updated balance (buying power) is $" << this->buyingPower << endl;
}

/*! \brief This function sells the stock
 *  
 *  @param company is an string argument representing the company
 *  containing master list of all the stocks
 *  @param list is an Watchlist argument of the watchlist class 
 *  containing the master list of all the stocks
 *  @return none
 *  @author Jia Yu Man
 */
void Portfolio::sellStock(string company, int shares, Watchlist *list){
    if (this->portfolio.containsStock(company)){
        Stock stock = list->getStock(company);
        double currentStockPrice = (list)->getStock(company).getCurrentStockPrice();
        int currentStockQuantity = (list)->getStock(company).getQuantity();
        int newStockQuantity = currentStockQuantity - shares;
        this->buyingPower += currentStockPrice * shares;
        double val = calculatePortfolioValue(list) - (currentStockPrice * shares);
        double newBuyingPower = this->currentPortfolioValue - (currentStockPrice*shares);

        cout << "You have sold " << shares << " shares of " << company << endl; 
        cout << "You have " << newStockQuantity << " share(s) left from " << stock.getCompanyName() << endl;
        cout << "Your new portfolio stock balance is $" << newBuyingPower << endl;
        cout << "Your new updated balance (buying power) is $" << this->buyingPower << endl;
        cout << "Your total portfolio is valued at $" << val << endl;
        
        //Update prices first
        map<std::string, Stock>::iterator it2;
        map<std::string, Stock> superListMap2 = this->portfolio.getStockList();
        for (it2 = superListMap2.begin(); it2 != superListMap2.end(); it2++){
            this->portfolio.changeStockQuantity(it2->first, list->getStock(it2->first).getQuantity());
        }
        this->portfolio.updateStockList(company, shares);
    }
    else {
        cout << "You do not own any shares of this stock." << endl;
    }
    
}


/*! \brief The function saves the current user's portfolio to a json file
 *
 *  The function saves the current user's portfolio to a json file
 * 
 *  @param userName the user's declared name
 *  @return none
 *  @author Yan Feng Lin
 */
void Portfolio::saveListToJson(std::string userName)
{
    ifstream myFile;
    string line;
    stringstream buffer;
    json j;
    myFile.open("usersStocks.txt");
    if (myFile.is_open()){
        while (getline (myFile,line) ){
            buffer << line << endl;
        }
        json j = json::parse(buffer);
    }
    myFile.close();

    j[userName]["buyingPower"] = this->getBuyingPower();

	map<string, Stock>::iterator it;
    map<std::string, Stock> listMap = this->portfolio.getStockList();
    for (it = listMap.begin(); it != listMap.end(); it++){
		j[userName]["stocks"][it->second.getCompanyName()]["shares"] = it->second.getQuantity();
	}
    ofstream toFile;
    toFile.open("usersStocks.txt");
	toFile << j.dump();
    toFile.close();
}