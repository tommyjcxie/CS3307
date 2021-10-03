#include <iostream>
#include <string>
#include <vector>
#include "stock.h"
#include "watchlist.h"
#include "displaycompany.h"
#include "portfolio.h"

#ifndef MENUOPTIONS_H
#define MENUOPTIONS_H

void searchAndBuy(Watchlist *list, Portfolio *userPortfolio);
void sell(Watchlist *list, Portfolio *userPortfolio);
void addToWatchlist(Watchlist *mainList, Watchlist *userList);
void updateStockPrice(Watchlist *superList);
void printMenu(Watchlist *superList, Watchlist *userList, Portfolio *userPortfolio, std::string name);

#endif