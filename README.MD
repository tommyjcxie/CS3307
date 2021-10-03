How to build:
 
g++ main.cpp stock.cpp watchlist.cpp displaycompany.cpp stockData.cpp portfolio.cpp nameSymConverter.cpp menuOptions.cpp -o main
 
How to run:
 
./main
 
IMPORTANT NOTE: Input validation has not yet been perfected, so make sure you enter in the input accurately (as specified in the instructions).
 
Initially the program will ask you to set a currency that you would like (EURO, CAD, USD).
After setting the currency, if this is your first time running the program, you will be prompted to create a user. There you will be able to set your username, password and initial buying power. This info will be stored in a flat-file database.
 
After creating a user, the next time you log in you will have options to 1. either log-in as an existing user, 2. create a new user, or 3. clear all the users in the database (as stated in the user story). This program also has authentication working, so if you log-in as an existing user and enter an incorrect username or password you will be denied entry to the menu (as stated in our user story).
 
 
After creating a user and/or logging in, you will be presented with our menu with various options you can select to interact with our program.
 
Option 1: Search and buy stock --> In option 1, you will be presented with a list of stocks. You can then enter the symbol or company name of the stock you want to buy. Next, you will be presented with the pricing history and current price of the stock as well as other relevant information such as percentage gain/loss. A graph is also displayed to visualize this. From there, you can choose to either buy the stock or exit. 
 
Option 2: View your watchlist --> In option 2, you are able to search for stocks and add them to your watchlist. After adding the stock to your watchlist, it will display your watchlist. You also have the option of removing the stock from your wishlist.
 
Option 3: View your portfolio and/or sell a stock --> In option 3, you are able to see what stocks you own in your portfolio, your buying power, and your total portfolio balance. You are also given the option to sell a stock if you wish to do so.
 
Option 4: Update the stock price -> In option 4, selecting this emulates updating the stock price. This updated price will be reflected in your portfolio so you can see your portfolio change everytime you update the stock price.
 
Option 5: Quit --> Quit the program.

