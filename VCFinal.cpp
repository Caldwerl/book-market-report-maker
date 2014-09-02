/*
 * VCFinal
 * Brian Caldwell
 * 12/02/2013
 *
 */
 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

#define MAX_BOOKS 100
#define MAX_MARKETS 6

using namespace std;

//Struct used to hold all 
//book data from input file
struct bookData{
	
	string name;
	string listingID;
	string sellerSKU;
	
	double price;
	int quantity;
	
	string openDate;
	string itemNote;
	string itemCondition;
	
	string productID;
	string market;
	
};

//Struct used to hold market data 
//from input file and calculations
struct marketData{
	
	string market;
	string name;
	
	string streetAddress;
	string city;
	string state;
	string country;
	
	int inventoryRecords;
	int quantityBooks;
	double avgBookPrice;
	double avgBookPriceTotal;
	double totalMarketValue;
	
};

//Function to print out a dividing line for the output
void printDivider(ofstream& outputFile);

//Function to read in and store the header line
void readInHeader(ifstream& inputFile, string& header);

//Function to read in and store book data
void readBooks(ifstream& inputFile, bookData books[]);

//Function to read in and store market data
void readMarkets(ifstream& inputFile, marketData markets[]);

//Function to list any unmatched markets as the UNKNOWN market
void sortUnknown(marketData markets[], bookData books[]);

//Function to output the report data
void outputReport(ofstream& outputFile, marketData markets[], bookData books[], marketData& total);






int main(){
	
	//Declares the file input variable
	ifstream inputFileBook;
	inputFileBook.open("books.txt");
	
	ifstream inputFileMarket;
	inputFileMarket.open("markets.txt");
	
	ofstream outputFile;
	outputFile.open("report.txt");
	
	//Declares the struct arrays to hold book and market data
	bookData books[MAX_BOOKS];
	marketData markets[MAX_MARKETS];
	marketData marketTotals;
	
	//Sets the last market in the array to be Total
	marketTotals.market = "Total";
	marketTotals.name = "Total";
	marketTotals.streetAddress.clear();
	marketTotals.city.clear();
	marketTotals.state.clear();
	marketTotals.country.clear();
	
	//Initializes market numerical data to 0
	marketTotals.inventoryRecords = 0;
	marketTotals.quantityBooks = 0;
	marketTotals.avgBookPrice = 0;
	marketTotals.avgBookPriceTotal = 0;
	marketTotals.totalMarketValue = 0;
	
	//Declares the strings to hold header line
	string bookHeader;
	string marketHeader;
	
	readInHeader(inputFileBook, bookHeader);
	readBooks(inputFileBook, books);
	
	readInHeader(inputFileMarket, marketHeader);
	readMarkets(inputFileMarket, markets);
	
	sortUnknown(markets, books);
	
	outputReport(outputFile, markets, books, marketTotals);
	
	system("PAUSE");
	
	//Closes the input and output file streams
	inputFileBook.close();
	inputFileMarket.close();
	outputFile.close();
	
    return 0;
}






//Function to print out a dividing line for the output
void printDivider(ofstream& outputFile){
	
	for(int i=0; i < 31; i++)
		outputFile << '=';
}

//Function to read in and store the header line
void readInHeader(ifstream& inputFile, string& header){
	
	getline(inputFile, header, '\n');
	
}

//Function to read in and store book data
void readBooks(ifstream& inputFile, bookData books[]){
	
	int i = 0;
	string blanks;
	
	
	//While loop to retrieve data from market file
	while(!inputFile.eof() && i < MAX_BOOKS){
		
		getline(inputFile, books[i].name, '\t');
		getline(inputFile, books[i].listingID, '\t');
		getline(inputFile, books[i].sellerSKU, '\t');
		
		inputFile >> books[i].price;
		getline(inputFile, blanks, '\t');
		inputFile >> books[i].quantity;
		getline(inputFile, blanks, '\t');
	
		getline(inputFile, books[i].openDate, '\t');
		getline(inputFile, books[i].itemNote, '\t');
		getline(inputFile, books[i].itemCondition, '\t');
	
		getline(inputFile, books[i].productID, '\t');
		getline(inputFile, books[i].market, '\n');
		
		i++;
	}
}


//Function to read in and store market data
void readMarkets(ifstream& inputFile, marketData markets[]){
	
	int i = 0;
	
	//While loop to retrieve data from market file
	while(!inputFile.eof() && i < (MAX_MARKETS - 2)){
	
		getline(inputFile, markets[i].market, '\t');
		getline(inputFile, markets[i].name, '\t');
		getline(inputFile, markets[i].streetAddress, '\t');
		getline(inputFile, markets[i].city, '\t');
		getline(inputFile, markets[i].state, '\t');
		getline(inputFile, markets[i].country, '\n');

		//Initializes market numerical data to 0
		markets[i].inventoryRecords = 0;
		markets[i].quantityBooks = 0;
		markets[i].avgBookPrice = 0;
		markets[i].avgBookPriceTotal = 0;
		markets[i].totalMarketValue = 0;
		
		i++;
	}
	
	//Sets the last market in the array to be UNKNOWN
	markets[i].market = "UNKNOWN";
	markets[i].name = "UNKNOWN";
	markets[i].streetAddress.clear();
	markets[i].city.clear();
	markets[i].state.clear();
	markets[i].country.clear();
	
	//Initializes market numerical data to 0
	markets[i].inventoryRecords = 0;
	markets[i].quantityBooks = 0;
	markets[i].avgBookPrice = 0;
	markets[i].avgBookPriceTotal = 0;
	markets[i].totalMarketValue = 0;
}

//Function to list any unmatched markets as the UNKNOWN market
void sortUnknown(marketData markets[], bookData books[]){
	
	bool marketMatch = 0;
	
	for(int n = 0; n < MAX_BOOKS; n++){
		
		marketMatch = 0;
		
		for(int i = 0; i < MAX_MARKETS; i++){
			
			if(markets[i].market.compare(books[n].market) == 0){
				marketMatch = 1;
				break;
			}
			
		}
		
		if(!marketMatch){
			//If no matches with the market list are found, the market is listed as UNKNOWN
			books[n].market = "UNKNOWN";
		}
	}
}

//Function to output the report data
void outputReport(ofstream& outputFile, marketData markets[], bookData books[], marketData& total){
	
	//Outer for loop that handles the markets
	for(int i = 0; i < MAX_MARKETS-1; i++){
		
		if(markets[i].name.compare("UNKNOWN") == 0){
			outputFile << endl << markets[i].name << endl;
		}
		
		else{
			outputFile << markets[i].name << endl << markets[i].streetAddress << endl 
			<< markets[i].city << ", " << markets[i].state << ", " << markets[i].country << endl;
		}
		
		printDivider(outputFile);
		
		//Inner for loop that handles the books
		for(int n = 0; n < MAX_BOOKS; n++){
			
			//If the markets are identical, print the book data
			if(markets[i].market.compare(books[n].market) == 0){
				
				outputFile << fixed << setprecision(2);
				
				outputFile << endl << books[n].name << endl;
				outputFile << "ISBN:  " << books[n].productID << endl;
				outputFile << "Price:  $" << books[n].price << endl << "Quantity:  " << books[n].quantity << endl;
				outputFile << "Inventory Value:  $" << (books[n].price * books[n].quantity) << endl;
				
				//Updates the totals for this market with this books data
				markets[i].inventoryRecords++;
				markets[i].quantityBooks += books[n].quantity;
				markets[i].totalMarketValue += (books[n].price * books[n].quantity);
				markets[i].avgBookPriceTotal += books[n].price;
				
			}
		}
		
		outputFile << endl;
		
		printDivider(outputFile);
		
		if(markets[i].name.compare("UNKNOWN") == 0){
			outputFile << endl << markets[i].name << endl;
		}
		
		else{
			outputFile << endl << markets[i].market << endl;
		}
		
		markets[i].avgBookPrice = markets[i].avgBookPriceTotal / markets[i].inventoryRecords;
		
		outputFile << "Total Inventory Records:  " << markets[i].inventoryRecords << endl;
		outputFile << "Average Book Price:  $" << markets[i].avgBookPrice << endl;
		outputFile << "Total Quantity of Books:  " << markets[i].quantityBooks << endl;
		outputFile << "Total Market Value:  $" << markets[i].totalMarketValue << endl << endl;
		
		total.totalMarketValue += markets[i].totalMarketValue;
		total.quantityBooks += markets[i].quantityBooks;
		total.inventoryRecords += markets[i].inventoryRecords;
		total.avgBookPriceTotal += markets[i].avgBookPriceTotal;
		
	}
	
	printDivider(outputFile);
	outputFile << endl;
	printDivider(outputFile);
	
	total.avgBookPrice = total.avgBookPriceTotal / total.inventoryRecords;
	
	outputFile << endl;
	outputFile << "Total Inventory Records:  " << total.inventoryRecords << endl;
	outputFile << "Average Book Price:  $" << total.avgBookPrice << endl;
	outputFile << "Total Quantity of Books:  " << total.quantityBooks << endl;
	outputFile << "Total Market Value:  $" << total.totalMarketValue << endl << endl;
}
