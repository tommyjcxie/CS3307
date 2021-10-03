#include <iostream>
#include <fstream>
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
#include "menuOptions.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

/*! \brief The mainline logic of our 
 *         program, displays menu.
 *  
 *  The main function of our program is responsible
 *  for displaying the menu as well as updating our
 *  database with new users. It contains algorithms
 *  for authentication, parsing data, and calls the
 *  various methods prompted by the user in the menu.
 *  This function ties our whole program together.
 * 
 *  @param list is an Watchlist argument of the watchlist class 
 *  containing the master list of all the stocks
 *  @param userList is a Watchlist argument of the watchlist class
 *  containing the user's watchlist
 *  @return none
 *  @author Jian Xie
 */
int main(int argc, char **argv)
{

    cout << "Welcome To The Stock Market Simulator! \n";
    ifstream inputFile("usersDatabase.txt");

    //Create Watchlist objects for all the stocks and for a user to keep track of specific stocks
    Watchlist superList;
    Watchlist userList;
    Portfolio userPortfolio;
    string name;

    cout << "What currency would you like to work in?" << endl;
    cout << "1. CAD \n";
    cout << "2. USD \n";
    cout << "3. Euro \n";
    int currency;
    cin >> currency;

    // Conversion rate used in this program
    double convRate = 1.0; // Default USD

    if (currency == 1)
    {
        cout << "You have selected CAD." << endl;
        convRate = 1.29;
    }
    else if (currency == 2)
    {
        cout << "You have selected USD." << endl;
        convRate = 1.0;
    }
    else if (currency == 3)
    {
        cout << "You have selected EURO." << endl;
        convRate = 0.834748;
    }

    //Insert stocks to the superList watch list
    vector<string> stonks = {};
    string line1;
    ifstream symbols("symbolsAndNames.txt");
    while (getline(symbols, line1))
    {
        stringstream s(line1);
        string sym;
        s >> sym;
        stonks.push_back(sym);
    }
    symbols.close();
    for (auto it = stonks.begin(); it != stonks.end(); it++)
    {
        vector<double> stockHistoryPrices = StockData::getCandle(*it);
        for (int i = 0; i < stockHistoryPrices.size(); i++)
        {
            stockHistoryPrices[i] = stockHistoryPrices[i] * convRate;
        }
        superList.insertToStockList(Stock(*it, StockData::getQuote(*it) * convRate, 0, stockHistoryPrices));
    }

    //START OF MENU
    //if file is empty, so no users then create a new user
    if (inputFile.peek() == std::ifstream::traits_type::eof())
    {
        int initialMoney;
        string password;
        cout << "This is your first time running the program so you must register a new user. \n";
        cout << "------------------------------------ \n"
             << "\n";

        cout << "Enter a username: \n";
        cin.ignore();
        name;
        getline(cin, name);

        cout << "Welcome " + name + ". You are a new user, enter a password: \n";
        password;
        getline(cin, password);

        cout << "Your password is now set as: " << password << "\n";
        cout << "\n";
        cout << "------------------------------------ \n";
        cout << "\nWelcome to the main menu! \n";
        cout << "This is your first time entering the menu as this user, so please set your initial buying power. \n";
        cout << "Note: Make sure you enter an integer as you will not be able to proceed until you do so. \n";
        while (true)
        {
            cin >> initialMoney;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
            }
            else
                break;
        }
        cout << "Success! You have set " << initialMoney << " as your initial buying power. \n"
             << "\n";

        //writing to flat-file DB, ie) the txt file.
        ofstream toFile;
        toFile.open("usersDatabase.txt", fstream::in | fstream::app);
        toFile << name << " " << password << " " << initialMoney << endl;

        userPortfolio.setBuyingPower(initialMoney);

        printMenu(&superList, &userList, &userPortfolio, name);
    }

    //there are already users created. ie) users.txt is NOT empty.
    else
    {
        bool flag = true;
        cout << "We see that you have registered a user before. \n";
        while (flag)
        {
            //Menu to allow user to log-in, create a new account, or clear all users.
            cout << "Press 1 to log in as an existing user, 2 to create a new user, or 3 to clear all users, 4 to quit:  \n";

            int newOrExisting;
            cin >> newOrExisting;
            cin.ignore();

            if (newOrExisting == 1)
            {
                //TODO: Allow user to log in as existing user with the password.
                //WE NEED API SET UP TO DO THIS.

                //Processing txt-file database
                vector<string> txtLine;
                vector<string> userVector;
                vector<string> passVector;
                vector<string> moneyVector;
                string line;
                ifstream myfile("usersDatabase.txt");

                //storing each line of txt file in a vector
                //Delimitter and text file processing
                while (getline(myfile, line))
                {
                    txtLine.push_back(line);
                }

                //going through each line and seperating username, password and balance into different vectors.
                //Delimitter and text file processing
                for (int i = 0; i < txtLine.size(); i++)
                {
                    stringstream s(txtLine[i]);
                    string word;
                    s >> word;
                    userVector.push_back(word);
                    s >> word;
                    passVector.push_back(word);
                    s >> word;
                    moneyVector.push_back(word);
                }

                //Authentication for log-in
                //Contains main algorithm for checking password
                cout << "Enter username:  \n";
                int index;
                getline(cin, name);
                if (std::find(userVector.begin(), userVector.end(), name) != userVector.end())
                {

                    auto it = find(userVector.begin(), userVector.end(), name);
                    if (it != userVector.end())
                    {
                        index = it - userVector.begin();
                    }

                    cout << "Enter password: \n";
                    string password;
                    getline(cin, password);

                    //Verification succeeded
                    if (passVector[index] == password)
                    {
                        stringstream buffer;
                        string line;
                        ifstream file;

                        file.open("usersStocks.txt");
                        while (getline(file, line))
                        {
                            buffer << line << endl;
                        }
                        file.close();
                        json j = json::parse(buffer);

                        userPortfolio.setBuyingPower(stoi(moneyVector[index]));
                        json stocks = j[name]["stocks"];
                        for (json::iterator it = stocks.begin(); it != stocks.end(); ++it) {
                            superList.changeStockQuantity(it.key(), (int)(it.value()["shares"]));
                            cout.setstate(ios_base::failbit);
                            userPortfolio.buyStock(it.key(), (int)it.value()["shares"], &superList);
                            cout.clear();
                            //std::cout << it.key() << " : " << it.value()["shares"] << "\n";
                        }
                        printMenu(&superList, &userList, &userPortfolio, name);
                        return 0;
                    }

                    //Verification failed
                    else
                    {
                        cout << "Incorrect password try again. \n";
                        exit(1);
                    }
                }

                //Invalid Input
                else
                {
                    cout << "Username does not exist try again.  \n";
                }
            }

            //If user wants to create a new account
            else if (newOrExisting == 2)
            {

                int initialMoney;
                string password;
                cout << "What is your name: \n";
                name;
                getline(cin, name);

                cout << "Welcome " + name + ". You are a new user, enter a password: \n";
                password;
                getline(cin, password);

                cout << "Your password is now set as: " << password << "\n";
                cout << "\n";
                cout << "------------------------------------ \n";
                cout << "\nWelcome to the main menu! \n";
                cout << "This is your first time entering the menu as this user, so please set your initial buying power. \n";
                cout << "Note: Make sure you enter an integer as you will not be able to proceed until you do so. \n";
                while (true)
                {
                    cin >> initialMoney;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                    }
                    else
                        break;
                }
                cout << "Success! You have set " << initialMoney << " as your initial buying power. \n"
                     << "\n";

                //writing to the file/database
                ofstream toFile;
                toFile.open("usersDatabase.txt", fstream::in | fstream::app);
                toFile << name << " " << password << " " << initialMoney << endl;

                userPortfolio.setBuyingPower(initialMoney);
                bool earlyReturn = false;
                printMenu(&superList, &userList, &userPortfolio, name);
            }

            //clearing all the users.
            else if (newOrExisting == 3)
            {
                ofstream toFile;
                toFile.open("usersDatabase.txt", ofstream::out | ofstream::trunc);
                toFile.close();
                cout << "Cleared!" << endl;
                flag = false;
            }

            else if (newOrExisting == 4)
            {
                flag = false;
            }
        }
    }
}
