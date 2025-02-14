#pragma once
#include <string>

class TrenchCoat {
private:
	int size = 0;
	int quantity = 0;
	float price = 0;
	std::string colour = "";
	std::string link = "";

public:
	// sets all the atributes of a coat
	void makeCoat(int size, int quantity, float price, std::string colour, std::string link) {
		this->size = size;
		this->quantity = quantity;
		this->price = price;
		this->colour = colour;
		this->link = link;
	}
	
	// returns the size of the coat
	int getSize() const { return this->size; }
	// returns the quantity of the coat
	int getQuantity() const { return this->quantity; }
	// returns the price of the coat
	float getPrice() const { return this->price; }
	// returns the colour of the coat
	std::string getColour() const { return this->colour; }
	// returns the link of the coat
	std::string getLink() const { return this->link; }

	// sets the size of the coat
	void setSize(int size) { this->size = size; }
	// sets the quantity of the coat
	void setQuantity(int quantity) { this->quantity = quantity; }
	// sets the price of the coat
	void setPrice(float price) { this->price = price; }
	// sets the colour of the coat
	void setColour(std::string colour) { this->colour = colour; }
	// sets the link of the coat
	void setLink(std::string link) { this->link = link; }

};
