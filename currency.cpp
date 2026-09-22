#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


// ============================================================
// CLASS 1: CURRENCY
// This class stores information about one currency.
// ============================================================

class Currency
{
private:
    int id;
    string name;
    string code;
    string symbol;
    double rateToINR;

public:

    // Default constructor
    Currency()
    {
        id = 0;
        name = "";
        code = "";
        symbol = "";
        rateToINR = 0;
    }

    // Parameterized constructor
    Currency(int i, string n, string c, string s, double rate)
    {
        id = i;
        name = n;
        code = c;
        symbol = s;
        rateToINR = rate;
    }

    // Getter functions

    int getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    string getCode()
    {
        return code;
    }

    string getSymbol()
    {
        return symbol;
    }

    double getRate()
    {
        return rateToINR;
    }

    // Display currency information

    void display()
    {
        cout << left
             << setw(5) << id
             << setw(25) << name
             << setw(10) << code
             << setw(10) << symbol
             << setw(15) << rateToINR
             << endl;
    }
};


// ============================================================
// CLASS 2: CURRENCY MANAGER
// This class stores and manages all currencies.
// ============================================================

class CurrencyManager
{
private:

    Currency currencies[8];

    int totalCurrencies;

public:

    CurrencyManager()
    {
        totalCurrencies = 8;

        // Currency rates are fixed for this educational project.
        // INR is used as the base currency.

        currencies[0] =
            Currency(1, "Indian Rupee", "INR", "Rs", 1.00);

        currencies[1] =
            Currency(2, "US Dollar", "USD", "$", 0.012);

        currencies[2] =
            Currency(3, "Euro", "EUR", "€", 0.011);

        currencies[3] =
            Currency(4, "British Pound", "GBP", "£", 0.0094);

        currencies[4] =
            Currency(5, "Japanese Yen", "JPY", "¥", 1.76);

        currencies[5] =
            Currency(6, "Australian Dollar", "AUD", "A$", 0.018);

        currencies[6] =
            Currency(7, "Canadian Dollar", "CAD", "C$", 0.016);

        currencies[7] =
            Currency(8, "Swiss Franc", "CHF", "Fr", 0.010);
    }


    // Display all available currencies

    void displayCurrencies()
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                  AVAILABLE CURRENCIES\n";
        cout << "============================================================\n";

        cout << left
             << setw(5) << "ID"
             << setw(25) << "Currency"
             << setw(10) << "Code"
             << setw(10) << "Symbol"
             << setw(15) << "Rate/INR"
             << endl;

        cout << "------------------------------------------------------------\n";

        for (int i = 0; i < totalCurrencies; i++)
        {
            currencies[i].display();
        }

        cout << "============================================================\n";
    }


    // Return a currency using its ID

    Currency getCurrency(int id)
    {
        for (int i = 0; i < totalCurrencies; i++)
        {
            if (currencies[i].getId() == id)
            {
                return currencies[i];
            }
        }

        // Return an empty currency if ID is invalid
        return Currency();
    }


    // Check whether currency ID is valid

    bool isValidCurrency(int id)
    {
        if (id >= 1 && id <= totalCurrencies)
        {
            return true;
        }

        return false;
    }


    // Display one currency

    void displayCurrencyDetails(int id)
    {
        if (!isValidCurrency(id))
        {
            cout << "\nInvalid currency ID.\n";
            return;
        }

        Currency c = getCurrency(id);

        cout << "\nCurrency Details\n";
        cout << "-------------------------\n";
        cout << "Name       : " << c.getName() << endl;
        cout << "Code       : " << c.getCode() << endl;
        cout << "Symbol     : " << c.getSymbol() << endl;
        cout << "Rate / INR : " << c.getRate() << endl;
    }
};


// ============================================================
// CLASS 3: CONVERTER
// This class performs currency conversion.
// ============================================================

class Converter
{
public:

    // Convert currency using INR as the base currency

    double convert(Currency from,
                   Currency to,
                   double amount)
    {
        // Step 1:
        // Convert source currency into INR

        double amountInINR;

        amountInINR = amount / from.getRate();


        // Step 2:
        // Convert INR into target currency

        double convertedAmount;

        convertedAmount = amountInINR * to.getRate();


        return convertedAmount;
    }


    // Display conversion calculation

    void showCalculation(Currency from,
                          Currency to,
                          double amount,
                          double result)
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                    CONVERSION RESULT\n";
        cout << "============================================================\n";

        cout << fixed << setprecision(2);

        cout << "From Currency : "
             << from.getName()
             << " (" << from.getCode() << ")" << endl;

        cout << "To Currency   : "
             << to.getName()
             << " (" << to.getCode() << ")" << endl;

        cout << "Amount        : "
             << amount << " "
             << from.getCode() << endl;

        cout << "Converted     : "
             << result << " "
             << to.getCode() << endl;

        cout << "============================================================\n";
    }
};


// ============================================================
// CLASS 4: HISTORY MANAGER
// This class handles file operations.
// ============================================================

class HistoryManager
{
private:

    string fileName;

public:

    HistoryManager()
    {
        fileName = "conversion_history.txt";
    }


    // Save conversion history into a file

    void saveHistory(Currency from,
                     Currency to,
                     double amount,
                     double result)
    {
        ofstream file;

        file.open(fileName, ios::app);

        if (file.is_open())
        {
            file << fixed << setprecision(2);

            file << amount << " "
                 << from.getCode()
                 << " = "
                 << result << " "
                 << to.getCode()
                 << endl;

            file.close();

            cout << "\nConversion saved successfully.\n";
        }
        else
        {
            cout << "\nError: Could not open history file.\n";
        }
    }


    // Display saved history

    void showHistory()
    {
        ifstream file;

        file.open(fileName);

        if (!file.is_open())
        {
            cout << "\nNo conversion history found.\n";
            return;
        }

        string line;

        cout << "\n";
        cout << "============================================================\n";
        cout << "                  CONVERSION HISTORY\n";
        cout << "============================================================\n";

        bool found = false;

        while (getline(file, line))
        {
            cout << line << endl;
            found = true;
        }

        if (!found)
        {
            cout << "No records available.\n";
        }

        cout << "============================================================\n";

        file.close();
    }


    // Clear history file

    void clearHistory()
    {
        ofstream file;

        file.open(fileName, ios::trunc);

        if (file.is_open())
        {
            file.close();

            cout << "\nConversion history cleared successfully.\n";
        }
        else
        {
            cout << "\nUnable to clear history.\n";
        }
    }
};


// ============================================================
// CLASS 5: USER INPUT
// This class handles input validation.
// ============================================================

class UserInput
{
public:

    // Get a currency ID

    int getCurrencyChoice(string message)
    {
        int choice;

        cout << message;
        cin >> choice;

        return choice;
    }


    // Get amount from user

    double getAmount()
    {
        double amount;

        cout << "Enter amount: ";
        cin >> amount;

        return amount;
    }


    // Check whether amount is valid

    bool isValidAmount(double amount)
    {
        if (amount > 0)
        {
            return true;
        }

        return false;
    }
};


// ============================================================
// CLASS 6: CURRENCY CONVERTER SYSTEM
// This is the main controller class.
// ============================================================

class CurrencyConverterSystem
{
private:

    CurrencyManager currencyManager;

    Converter converter;

    HistoryManager historyManager;

    UserInput input;


public:

    // Display main menu

    void displayMenu()
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                CURRENCY CONVERTER SYSTEM\n";
        cout << "============================================================\n";

        cout << "1. Convert Currency\n";
        cout << "2. View Available Currencies\n";
        cout << "3. View Currency Details\n";
        cout << "4. View Conversion History\n";
        cout << "5. Clear Conversion History\n";
        cout << "6. Exit\n";

        cout << "============================================================\n";
    }


    // Perform currency conversion

    void performConversion()
    {
        int fromID;
        int toID;
        double amount;
        double result;


        // Show currencies

        currencyManager.displayCurrencies();


        // Select source currency

        fromID =
            input.getCurrencyChoice(
                "\nEnter source currency ID: "
            );


        // Validate source currency

        if (!currencyManager.isValidCurrency(fromID))
        {
            cout << "\nInvalid source currency.\n";
            return;
        }


        // Select target currency

        toID =
            input.getCurrencyChoice(
                "Enter target currency ID: "
            );


        // Validate target currency

        if (!currencyManager.isValidCurrency(toID))
        {
            cout << "\nInvalid target currency.\n";
            return;
        }


        // Enter amount

        amount = input.getAmount();


        // Validate amount

        if (!input.isValidAmount(amount))
        {
            cout << "\nAmount must be greater than zero.\n";
            return;
        }


        // Get currency objects

        Currency fromCurrency =
            currencyManager.getCurrency(fromID);

        Currency toCurrency =
            currencyManager.getCurrency(toID);


        // Perform conversion

        result =
            converter.convert(
                fromCurrency,
                toCurrency,
                amount
            );


        // Display result

        converter.showCalculation(
            fromCurrency,
            toCurrency,
            amount,
            result
        );


        // Save conversion

        historyManager.saveHistory(
            fromCurrency,
            toCurrency,
            amount,
            result
        );
    }


    // Show currency details

    void showCurrencyDetails()
    {
        int id;

        currencyManager.displayCurrencies();

        cout << "\nEnter currency ID: ";
        cin >> id;

        currencyManager.displayCurrencyDetails(id);
    }


    // Start the application

    void start()
    {
        int choice;

        do
        {
            displayMenu();

            cout << "\nEnter your choice: ";
            cin >> choice;


            switch (choice)
            {
                case 1:

                    performConversion();

                    break;


                case 2:

                    currencyManager.displayCurrencies();

                    break;


                case 3:

                    showCurrencyDetails();

                    break;


                case 4:

                    historyManager.showHistory();

                    break;


                case 5:

                    historyManager.clearHistory();

                    break;


                case 6:

                    cout << "\n";
                    cout << "Thank you for using ";
                    cout << "Currency Converter System!\n";

                    break;


                default:

                    cout << "\nInvalid choice!";
                    cout << " Please enter a number from 1 to 6.\n";
            }

        }
        while (choice != 6);
    }
};


// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    // Create object of the main system class

    CurrencyConverterSystem system;


    // Start the program

    system.start();


    return 0;
}