#include <iostream>
#include <sstream>
#include <fstream>
#include "nlohmann/json.hpp"

#include "stockData.h"

using namespace std;
using json = nlohmann::json;

/*! \brief Helper function for converting to json
 *         
 *  
 * 	This method reads a text file then converts it to a json object and returns it
 *  @param string
 *  @return json
 *  @author Yan Feng Lin
 */
json fileToJson(string fileName){
    stringstream buffer;
    string line;
    ifstream file;
    
    file.open("data/" + fileName);
    while (getline(file, line)) {
        buffer << line << endl;
    }
    file.close();

    json j = json::parse(buffer);

    return j;
}

/*! \brief Static method that returns the most recent price of a stock
 *         
 *  
 * 	This static method takes a stock symbol and returns the most recent price of that stock
 *  @param string
 *  @return double
 *  @author Yan Feng Lin
 */
double StockData::getQuote(string stockSymbol){    
    json j = fileToJson(stockSymbol + "quote.json");

    return j["c"];
}

/*! \brief Static method that returns price history of a stock
 *         
 *  
 * 	This static method takes a stock symbol and returns the price history of that stock (closing price for each month of past year)
 *  @param string
 *  @return vector<double>
 *  @author Yan Feng Lin
 */
vector<double> StockData::getCandle(string stockSymbol){
    json j = fileToJson(stockSymbol + "candle.json");

    return j["c"];
}