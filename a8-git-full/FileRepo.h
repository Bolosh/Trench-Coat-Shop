#pragma once
#include "Repository.h"
#include "TrenchCoat.h"
#include <fstream>
using namespace std;

class FileRepo : public Repository {
private:
	string file = "memory.txt";

public:
	FileRepo() {}
	~FileRepo() {}

	// save the repository data into the file
	void save_file() override {
		ofstream f(file);
		for (TrenchCoat c : v) {
			// size | quantity | price | colour | link
			f << c.getSize() << ' ' << c.getQuantity() << ' ' << c.getPrice() << ' ' << c.getColour() << ' ' << c.getLink() << '\n';
		}
		f.close();
	}

	// load the saved data into the repository
	void load_file() override {
		ifstream f(file);
		int size;
		int quantity;
		float price;
		string colour;
		string link;

		while (!f.eof()) {
			f >> size >> quantity >> price >> colour >> link;
			TrenchCoat c;
			c.makeCoat(size, quantity, price, colour, link);
			try {
				this->addCoat(c);
			}
			catch (const ExceptionClass) {
				continue;
			}
		}
		f.close();
	}

	// save to CSV format
	void save_CSV(string filename, vector<TrenchCoat> vect) override {
		ofstream f(filename);
		for (TrenchCoat c : vect) {
			// size | quantity | price | colour | link
			f << c.getSize() << ',' << c.getQuantity() << ',' << c.getPrice() << ',' << c.getColour() << ',' << c.getLink() << '\n';
		}
		f.close();

	}

	// save to HTML format
	void save_HTML(string filename, vector<TrenchCoat> vect) override {
		ofstream f(filename);
		f << "<!DOCTYPE html>" << '\n';
		f << "<html>" << '\n';
		f << "<head>" << '\n';
		f << "<title> Coats </title>" << '\n';
		f << "</head>" << '\n';
		f << "<body>" << '\n';
		f << "<table border = " << char(34) << 1 << char(34) << ">" << '\n';
		f << "<tr>" << '\n';
		f << "<td>Size</td>" << '\n';
		f << "<td>Quantity</td>" << '\n';
		f << "<td>Price</td>" << '\n';
		f << "<td>Colour</td>" << '\n';
		f << "<td>Link</td>" << '\n';
		f << "</tr>" << '\n';
		for (auto c : vect) {
			f << "<tr>" << '\n';
			f << "<td>" << c.getSize() << "</td>" << '\n';
			f << "<td>" << c.getQuantity() << "</td>" << '\n';
			f << "<td>" << c.getPrice() << "</td>" << '\n';
			f << "<td>" << c.getColour() << "</td>" << '\n';
			f << "<td><a href=" << char(34) << c.getLink() << char(34) << ">Link</a></td>" << '\n';
			f << "</tr>" << '\n';
		}
		f << "</table>" << '\n';
		f << "</body>" << '\n';
		f << "</html>" << '\n';
		f.close();
	}

};