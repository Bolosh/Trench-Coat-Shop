#pragma once
#include <fstream>
#include <vector>
#include "TrenchCoat.h"
#include "CustomException.h"
#include <iostream>

using namespace std;

class Repository {
protected:
	std::vector<TrenchCoat> v;

public:
	Repository(){
	};

	virtual ~Repository() {
		v.clear();
	}

	// returns the vector with all the trench coats
	std::vector<TrenchCoat> getVector() {
		return v;
	}

	// adds a new coat, throws exception if coat already exist
	void addCoat(TrenchCoat coat) {
		if (this->searchCoat(coat) != -1) {
			throw ExceptionClass("Coat already exists.");
		}
		v.push_back(coat);
	}

	// removes a coat, throws exception if coat dosen`t exist
	void removeCoat(TrenchCoat coat) {
		int pos = this->searchCoat(coat);
		if (pos == -1) {
			throw ExceptionClass("Coat dosen`t exist");
		}
		v.erase(v.begin() + pos);
	}

	// Returns the position of the coat if found, -1 otherwise
	int searchCoat(TrenchCoat coat) {
		/*auto it = std::find_if(v.begin(), v.end(), [coat](TrenchCoat c) {
			return c.getLink() == coat.getLink();
		});

		if (it != v.end()) return int(std::distance(v.begin(), it));
		return -1;
		*/
		int pos = 0;
		for (auto c : v) {
			if (c.getLink() == coat.getLink()) break;
			++pos;
		}
		if (pos == v.size()) return -1;
		return pos;
	}

	// returns the coat found at position
	TrenchCoat* getCoat(int pos) {
		return &v[pos];
	}

	// returns all the info of a coat given only the link
	TrenchCoat* findExactCoat(std::string link) {
		auto it = std::find_if(v.begin(), v.end(), [link](TrenchCoat c) {
			return c.getLink() == link;
		});

		if (it != v.end()) return &(*it);
		return NULL;
	}

	// returns the number of coats from the repo 
	int length() {
		return int(v.size());
	}

	// updates the coat`s info
	void updateCoat(TrenchCoat* coat, int size, int quantity, float price, std::string colour, std::string link) {
		coat->setSize(size);
		coat->setQuantity(quantity);
		coat->setPrice(price);
		coat->setColour(colour);
		coat->setLink(link);
	}

	virtual void save_file() {}
	virtual void load_file() {}
	virtual void save_CSV(string filename, vector<TrenchCoat> vect) {}
	virtual void save_HTML(string filename, vector<TrenchCoat> vect) {}

};
