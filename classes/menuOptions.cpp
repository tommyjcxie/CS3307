#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <iostream>
#include "stock.h"
#include "watchlist.h"
#include "displaycompany.h"
#include "stockData.h"
#include "portfolio.h"


using namespace std;
/*! \brief The algorithm for taking care
 *         of buying a stock.
 *
 *  This function prompts the user to allow them to search
 *  for a specific stock. After searchign for it, they are
 *  given the option to either buy,sell the stock and/or add it
 *  to their wishlist. This function will loop until the
 *  user chooses to quit so they can buy and add as many
 *  stocks as they want until they choose to quit.
 * 
 *  @param list is an Watchlist argument of the watchlist class
 *  @return none
 *  @author Daniel Cho
 */

void searchAndBuy(Watchlist *list, Portfolio *userPortfolio){
  //Set a flag to allow the user to keep viewing stocks
  bool flag = true;

  while(flag){
    //Show the user all the stocks using an iterator
    cout << "| SEARCH AND BUY |" << endl;
    cout << endl;
    cout << "These are the avaliable stocks. \n";
    map<std::string, Stock>::iterator it;
    map<std::string, Stock> superListMap = (*list).getStockList();
    for (it = superListMap.begin(); it != superListMap.end(); it++){
        cout << it->first << endl;
    }

    //Get the stock form the user
    cout << "\nPlease enter the stock symbol as it is displayed or the company name: " << endl;
    string choosenStock;
    cin >> choosenStock; 
    //Call the display company function to show information about the stocks
    cout << endl;
    displayCompany(choosenStock, (*list));

    //Get the Stock object for the choosen stock
    Stock selectedStock = (*list).getStock(choosenStock);
    int buyChosenStock;
    //Check if the user would like to purchase this stock
    cout << "\nSelect 1 to buy the stock or 2 to exit" << endl;
    cin >> buyChosenStock;
    //Call buyStock method to make the transaction
    if (buyChosenStock == 1){
        int stockAmount;
        cout << "\nHow many stocks would you like (please enter an integer)? " << endl;
        cin >>stockAmount;
        if(userPortfolio->getBuyingPower() >= stockAmount*(*list).getStock(choosenStock).getCurrentStockPrice()){
            (*list).changeStockQuantity(choosenStock, (*list).getStock(choosenStock).getQuantity() + stockAmount);
            (*userPortfolio).buyStock(choosenStock, stockAmount, list);
        }
        else{
          cout << "You have insufficient funds!" << endl;
        }
    }
    else if(buyChosenStock ==2){
        flag = false;
        break;
    }

    //Check if the user would like to add more stocks to the watch list
    cout << "\nPress 1 to view more stocks or 2 to exit." << endl;
    int choice;
    cin >> choice;
    if(choice ==2){
        flag = false;
    }
  
  }
}

/*! \brief The algorithm for taking care
 *         of selling a stock.
 *
 *  From the user's portfolio, the user can choose which
 *  stock to sell. The user is promted to give the name
 *  of the stock and how many shares to sell. This function 
 *  will loop until the user chooses to quit so they can 
 *  sell as many stocks as they want (as long as they have them).
 * 
 *  @param list is an Watchlist argument of the watchlist class
 *  @return none
 *  @author Jia Yu Man
 */
void sell(Watchlist *list, Portfolio *userPortfolio){
    //Set a flag to allow the user to keep selling stocks
  bool flag = true;

  while(flag){
    //Prompt the user for the option to sell any owned stocks or not
    cout << "\nWould you like to sell any of your stocks? 1 for Yes, 2 for No" << endl;
    int sellOption;
    cin >> sellOption;
    if (sellOption == 1){
      string whichStock;
      int shares;
      //Prompt the user for which stock to sell
      cout << "\nWhich stock would you like to sell: " << endl;
      cin >> whichStock;
      //Prompt the user for how many shares of the selected stock to sell
      cout << "How many shares would you like to sell: " <<endl;
      cin >> shares;
      //Call the sellStock function to complete the transaction
      if(userPortfolio->getAmountOfShares(whichStock) >= shares){
        (*userPortfolio).sellStock(whichStock, shares, list);
        (*list).changeStockQuantity(whichStock, (*list).getStock(whichStock).getQuantity() - shares);
      }
      else{
        cout << "You dont have enough shares to sell!" << endl;
      }
    }
    else{
      flag = false;
      break;
    }
  }
}

/*! \brief This algorithm for taking
 *         care of adding to watchlist.
 *  
 *  This function allows you to add a stock to a watchlist.
 *  After the stock is added to your watchlist, it will 
 *  display all the stocks that are on your watchlist.
 *  You can keep adding stocks until you choose to exit
 *  and the list will keep getting updated
 * 
 *  @param list is an Watchlist argument of the watchlist class 
 *  containing the master list of all the stocks
 *  @param userList is a Watchlist argument of the watchlist class
 *  containing the user's watchlist
 *  @return none
 *  @author Daniel Cho
 */
void addToWatchlist(Watchlist *mainList, Watchlist *userList){
    //Set a flag to allow the user to keep adding stocks 
    cout << "| WATCHLIST |" << endl;
    bool flag = true;
    while(flag){
        //Print out the stock list to show what they are tracking
        cout << "\nHere is a list of your watch list stocks" << endl;
        map<std::string, Stock>::iterator it3;
        map<std::string, Stock> userListMap = (*userList).getStockList();
        for (it3 = userListMap.begin(); it3 != userListMap.end(); it3++){
            cout << it3->first << " | Price: " << to_string(mainList->getStock(it3->first).getCurrentStockPrice()) << endl;   
        }

        //Check if the user would like to add more stocks to the watch list
        cout << "\nPress 1 to add more stocks to your watch list, 2 to remove a stock or 3 to exit: " << endl;
        int choice;
        cin >> choice;
        if (cin.fail()){
                cout << "Please enter an integer an integer. \n";
                // clear error state
                cin.clear();
                // discard 'bad' character(s)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

        if(choice == 1){
            //Show the user stock information using an iterator
            map<std::string, Stock>::iterator it2;
            map<std::string, Stock> superListMap2 = mainList->getStockList();
            for (it2 = superListMap2.begin(); it2 != superListMap2.end(); it2++){
                cout << it2->first << endl;
            }
            //Get the stock from the user
            cout << "\nPlease enter the stock name exactly as it is displayed to add to your watch list: " << endl;
            string wishStock;
            cin >> wishStock;
        
            //Add the stock to their watch list 
            Stock thisStock = mainList->getStock(wishStock);
	        (*userList).insertToStockList(thisStock);
        }
        else if(choice == 2){
            cout << "\nPlease enter the stock that you would like to remove: " << endl;
            string stockToRemove;
            cin >> stockToRemove;
            (*userList).removeStock(stockToRemove);
        }
        else if(choice == 3){
            flag = false;
        }
    }
}

/*! \brief This algorithm for updating the price of stocks
 * 
 *  This function updates the costs of each stock and makes sure to update the actual value 
 *  through the use of pointers
 * 
 *  @param superlist is an Watchlist argument of the watchlist class 
 *  containing the master list of all the stocks
 *  @return none
 *  @author Daniel Cho
 */
void updateStockPrice(Watchlist *superList){
    cout << "| UPDATE STOCKS |" << endl;
    cout << endl;
    //updatingg the price
    map<std::string, Stock>::iterator it;
    map<std::string, Stock> superListMap = superList->getStockList();
    for (it = superListMap.begin(); it != superListMap.end(); it++){
        //superList->getStock(it->second.getCompanyName()).updatePrice();
        it->second.updatePrice();
    }
    cout << "Prices have been updated! These are the new prices \n";
    for (it = superListMap.begin(); it != superListMap.end(); it++){
        superList->changeStockPrice(it->first, it->second.getCurrentStockPrice());
        cout << it->first << ": "<< to_string(it->second.getCurrentStockPrice()) << endl;
    }
}

/*! \brief The function that displays the menu
 *
 *  This function displays a menu that gives the user many 
 *  different options that could be done in the program.
 * 
 *  @param list is an Watchlist argument of the watchlist class
 *  @param userlist is an Watchlist argument of the watchlist class
 *  @param userPortfolio is an Watchlist argument of the watchlist class
 *  @param name the user's declared name
 *  @return none
 *  @author Daniel Cho
 */
void printMenu(Watchlist *superList, Watchlist *userList, Portfolio *userPortfolio, string name){
    bool flag = true;
        while(flag){
             cout << "\n";
             cout << "------------------------------------ \n";
             cout << "What do you want to do? \n";
             cout << "1. Search and buy a stock.  \n";
             cout << "2. View your watchlist and add/remove stocks.  \n";
             cout << "3. View your portfolio and/or sell a stock. \n";
             cout << "4. Update stock prices. \n";
            // cout << "5. Change currency. \n";
             cout << "5. Quit \n";
             int option;
             cin >> option;
             cout << endl;
             if (cin.fail()){
                cout << "Please enter an integer an integer. \n";
                // clear error state
                cin.clear();
                // discard 'bad' character(s)
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            //START OF MENU OPTIONS

            if (option == 1){
                //Call the function to search and buy
                searchAndBuy(superList, userPortfolio);
                userPortfolio->printPortfolioStocks(superList);
            }
            else if(option == 2){
                //Call the function to add stocks to the users watchlist
                addToWatchlist(superList,userList);
            }
            else if(option == 3){
                userPortfolio->printPortfolioStocksRec(superList);
                sell(superList, userPortfolio);
            }
            else if(option == 4){
                updateStockPrice(superList);
            }   
            
            else if (option == 5){
                cout << "Thanks for playing the stock simulator game. \n";
                userPortfolio->saveListToJson(name);
                flag = false;
                break;
            }
    }
}