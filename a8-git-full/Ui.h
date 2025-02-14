#pragma once
#include "Service.h"
#include <iostream>
#include <limits>
#include <windows.h>
using namespace std;

class Ui {
private:
    Service s;
    vector<TrenchCoat> cart;
    string mode;
    string csv_file = "csv_file.csv";
    string html_file = "html_file.html";
    string csv_basket = "basket.csv";
    string html_basket = "basket.html";

public:
    void save_CSV(string filename, vector<TrenchCoat> coats) {
        s.save_CSV(filename, coats);
    }

    void save_HTML(string filename, vector<TrenchCoat> coats) {
        s.save_HTML(filename, coats);
    }

    void save_file() {
        s.save_file();
    }

    void load_file() {
        s.load_file();
    }

    int readIntegerNumber(const char* message) {
        int input = -1;
        bool valid = false;
        do {
            cout << message << flush;
            cin >> input;
            if (cin.good()) {
                //everything went well, we'll get out of the loop and return the value
                valid = true;
            }
            else {
                //something went wrong, we reset the buffer's state to good
                cin.clear();
                //and empty it
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input; please re-enter." << endl;
            }
        } while (!valid);
        return (input);
    }

    float readFloatNumber(const char* message) {
        float input = -1;
        bool valid = false;
        do {
            cout << message << flush;

            cin >> input;
            if (cin.good()) {
                //everything went well, we'll get out of the loop and return the value
                valid = true;
            }
            else {
                //something went wrong, we reset the buffer's state to good
                cin.clear();
                //and empty it
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input; please re-enter." << endl;
            }
        } while (!valid);

        return (input);
    }

    void readStringWithSpaces(const char* message, string &str) {
        cout << message;
        //getline(cin, str);
        cin >> str;
    }

    void addCoat() {
        string colour, link;
        int size = readIntegerNumber("Input the size > ");
        int quantity = readIntegerNumber("Input the quanitity > ");
        float price = readFloatNumber("Input the price > ");

        fgetc(stdin);
        readStringWithSpaces("Input the colour > ", colour);
        readStringWithSpaces("Input the link > ", link);

        TrenchCoat coat;
        coat.makeCoat(size, quantity, price, colour, link);
        try {
            s.addCoat(coat);
            tc(11), cout << "\n>> Coat added succesfully! <<\n\n";
        }
        catch (const ExceptionClass& e) {
            tc(14), cout << '\n' << e.what() << "\n\n";
        }
    }

    void addExactCoat(TrenchCoat coat) {
        s.addCoat(coat);
    }

    TrenchCoat* findExactCoat() {
        string link;
        fgetc(stdin);
        readStringWithSpaces("Input the link > ", link);
        return s.findExactCoat(link);
    }

    void removeCoat() {
        TrenchCoat* coat = findExactCoat();
        if (coat == NULL) return;
        try {
            s.removeCoat(*coat);
            tc(11), cout << "\n>> Coat removed succesfully! <<\n\n";
        }
        catch (const ExceptionClass& e) {
            tc(14), cout << '\n' << e.what() << '\n';
        }
    }

    void tc(int c) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    void printCoatDetails(TrenchCoat* coat) {
        cout << "Coat with size ", tc(10);
        cout << coat->getSize(), tc(15);
        cout << ", colour ", tc(10);
        cout << coat->getColour(), tc(15);
        cout << ", has a price of ", tc(10);
        cout << coat->getPrice(), tc(15);
        cout << ", in quantity of ", tc(10);
        cout << coat->getQuantity(), tc(15);
        cout << " and found at ", tc(10);
        cout << coat->getLink(), tc(15);
        cout << ".\n";
    }

    bool updateCoat() {
        TrenchCoat* coat = findExactCoat();
        if (coat == NULL) return false;

        printCoatDetails(coat);

        string colour, link;
        int size = readIntegerNumber("Input the new size > ");
        fgetc(stdin);
        readStringWithSpaces("Input the new colour > ", colour);
        float price = readFloatNumber("Input the new price > ");
        int quantity = readIntegerNumber("Input the new quanitity > ");
        fgetc(stdin);
        readStringWithSpaces("Input the new link > ", link);

        if (quantity == 0) s.removeCoat(*coat);

        coat->setSize(size);
        coat->setQuantity(quantity);
        coat->setPrice(price);
        coat->setColour(colour);
        coat->setLink(link);
        return true;
    }

    bool updateQuantity() {
        TrenchCoat* coat = findExactCoat();
        if (coat == NULL) return false;
        printCoatDetails(coat);
        int quantity = readIntegerNumber("Input the new quanitity > ");
        if (quantity == 0) s.removeCoat(*coat);
        else coat->setQuantity(quantity);
        return true;
    }

    void displayAll(){
        std::vector<TrenchCoat> v = s.getRepoData();
        for (TrenchCoat c : v) {
            printCoatDetails(&c);
        }
    }

    void openLink() {
        string link;
        fgetc(stdin);
        readStringWithSpaces("Input the link > ", link);
        string url = string("start ").append(link);
        //cout << url << endl << endl;
        system(url.c_str());
    }

    void open_file() {
        if (this->mode == "csv") {
            save_CSV(this->csv_basket, cart);
            string url = string("start ").append("basket.csv");
            system(url.c_str());
        }
        else if (this->mode == "html") {
            save_HTML(this->html_basket, cart);
            string url = string("start ").append("basket.html");
            system(url.c_str());
        }
    }

    void printADMINMenu() {
        tc(12), cout << "##---------->  Logged in as admin.  <----------##" << '\n', tc(15);
        cout << "1. Add coat." << '\n';
        cout << "2. Delete coat." << '\n';
        cout << "3. Update coat." << '\n';
        cout << "4. Update stock." << '\n';
        cout << "5. Display all coats." << '\n';
        cout << "6. Open link." << '\n';
        cout << "0. Exit." << '\n';
        tc(12), cout << "##---------->  ###################  <----------##" << '\n', tc(15);
    }

    void adminUi() {
        while (true) {
            printADMINMenu();
            int option = readIntegerNumber("Your choice > ");
            if (option == 0) break;
            else if (option == 1) {
                addCoat();
            }
            else if (option == 2) {
                removeCoat();
            }
            else if (option == 3) {
                bool res = updateCoat();
                if (res == false) tc(14), cout << "\n>> Coat couldn`t be updated. <<\n\n";
                else tc(11), cout << "\n>> Coat updated succesfully! <<\n\n";
            }
            else if (option == 4) {
                bool res = updateQuantity();
                if (res == false) tc(14), cout << "\n>> Coat dosen`t exists. <<\n\n";
                else tc(11), cout << "\n>> Coat updated succesfully. <<\n\n";
            }
            else if (option == 5) displayAll();
            else if (option == 6) openLink();
            else tc(14), cout << ">> Not a valid option.\n";
            tc(15);
        }
    }

    void userShopping() {
        int size = readIntegerNumber("Input the qunatity filter> ");
        int i = 0, loop_cout = 0;
        float total = 0.00;
        while (true) {
            TrenchCoat* coat = s.getCoat(i);
            if (size == 0 || coat->getSize() == size) {
                loop_cout = 0;
                cout << endl;
                printCoatDetails(coat);
                cout << "1. Keep | 2. Next | 3. Open link | 0. End shopping session\n";
                int user_input = readIntegerNumber("Your choice> ");
                if (user_input == 1) {
                    int j = 0;
                    for (TrenchCoat c : cart) {
                        if (c.getLink() == coat->getLink()) break;
                        ++j;
                    }
                    if (j == cart.size()) {
                        cart.push_back(*coat);
                        cart[j].setQuantity(1);
                    }
                    else cart[j].setQuantity(cart[j].getQuantity() + 1);
                    total += coat->getPrice();
                    coat->setQuantity(coat->getQuantity() - 1);
                    if (coat->getQuantity() == 0) {
                        s.removeCoat(*coat);
                        --i;
                    }
                }
                else if (user_input == 3) {
                    string url = string("start ").append(coat->getLink());
                    //cout << url << endl << endl;
                    system(url.c_str());
                }
                else if (user_input == 0) break;
                else if (user_input != 2) {
                    cout << "Not a valid option.\n";
                    --i;
                }
                tc(11), cout << "Current total: ", tc(12), cout << total << '\n', tc(15);
            }
            ++loop_cout;
            if (loop_cout == s.repoLength() + 2) {
                tc(14), cout << "\nNo more coats to show.\n\n", tc(15);
                break;
            }
            if (++i == s.repoLength()) i = 0;
        }
    }

    void checkout() {
        float total = 0.00;
        for (TrenchCoat c : cart) {
            tc(14), cout << c.getPrice() * c.getQuantity() << " from: ", tc(15);
            printCoatDetails(&c);
            total += (c.getPrice() * c.getQuantity());
        }
        tc(11), cout << "Current total: ", tc(12), cout << total << '\n', tc(15);
    }


    void printUSERMenu() {
        tc(10), cout << "##---------->  Logged in as user.  <----------##" << '\n', tc(15);
        cout << "1. Start shopping." << '\n';
        cout << "2. Checkout." << '\n';
        cout << "3. Show basket." << '\n';
        cout << "0. Exit." << '\n';
        tc(10), cout << "##---------->  ###################  <----------##" << '\n', tc(15);
    }

    void userUi() {
        while (true) {
            printUSERMenu();
            int option = readIntegerNumber("Your choice > ");
            if (option == 0) break;
            else if (option == 1) {
                userShopping();
            }
            else if (option == 2) {
                checkout();
            }
            else if (option == 3) {
                open_file();
            }
            else tc(14), cout << "Not a valid option.\n";
            tc(15);
        }
    }

    void startUi() {
        while (true) {
            string mode;
            readStringWithSpaces("Input the mode (csv/html): ", mode);
            if (mode == "csv") {
                this->mode = "csv";
                break;
            }
            else if (mode == "html") {
                this->mode = "html";
                break;
            }
            else if (mode == "exit" || mode == "0") {
                cout << ">>   Bye <o/   <<" << '\n';
                return;
            }
            else cout << "Not a valid option. Try again." << '\n';
        }
        while (true) {
            string mode;
            readStringWithSpaces("Input the mode (admin/user): ", mode);
            if (mode == "admin") {
                adminUi();
                break;
            }
            else if (mode == "user") {
                userUi();
                break;
            }
            else if (mode == "exit" || mode ==  "0")
                break;
            else cout << "Not a valid option. Try again." << '\n';
        }
        if (this->mode == "csv") save_CSV(this->csv_file, s.getRepoData());
        else if (this->mode == "html") save_HTML(this->html_file, s.getRepoData());
        cout << ">>   Bye <o/   <<" << '\n';
    }
    
};
