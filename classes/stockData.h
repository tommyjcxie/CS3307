#pragma once

#ifndef STOCKAPI_H
#define STOCKAPI_H

#include <string>
#include <vector>

class StockData {
public: 
    static double getQuote(std::string);
    static std::vector<double> getCandle(std::string);
};

#endif