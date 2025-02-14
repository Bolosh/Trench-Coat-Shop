#pragma once
#include "Repository.h"
#include "FileRepo.h"
#include "Command.h"

class Service {
private:
	Repository* r = new FileRepo;
	CommandManager manager;

public:
	Service() {
	}
	~Service() {
	}

	// save the repository data into the file
	void save_file() {
		r->save_file();
	}

	// load the saved data into the repository
	void load_file() {
		r->load_file();
	}

	// returns the vector with all the trench coats
	std::vector<TrenchCoat> getRepoData() {
		return r->getVector();
	}

	// adds a new coat, throws exception if coat already exist
	void addCoat(TrenchCoat coat) {
		try {
			//r->addCoat(coat);
			manager.executeCommand(new AddCommand(*this->r, coat));
		}
		catch (const ExceptionClass& e) {
			throw ExceptionClass(string(e.what()));
		}
	}

	// removes a coat, throws exception if coat dosen`t exist
	void removeCoat(TrenchCoat coat) {
		try {
			//r->removeCoat(coat);
			manager.executeCommand(new RemoveCommand(*this->r, coat));
		}
		catch (const ExceptionClass& e) {
			throw ExceptionClass(string(e.what()));
		}
	}

	// returns the coat found at position
	TrenchCoat* getCoat(int pos) {
		return r->getCoat(pos);
	}

	// returns all the info of a coat given only the link
	TrenchCoat* findExactCoat(std::string link) {
		return r->findExactCoat(link);
	}

	// returns the number of coats from the repo
	int repoLength() {
		return r->length();
	}

	// updates the coat`s info
	void updateCoat(TrenchCoat* coat, int size, int quantity, float price, std::string colour, std::string link) {
		//r->updateCoat(coat, size, quantity, price, colour, link);
		TrenchCoat c;
		c.makeCoat(size, quantity, price, colour, link);
		manager.executeCommand(new UpdateCommand(*this->r, *coat, c));
	}

	void undo() {
		manager.undo();
	}

	void redo() {
		manager.redo();
	}

	bool isEmpty(string s) {
		return manager.isEmpty(s);
	}

	// save to CSV format
	void save_CSV(string filename, std::vector<TrenchCoat> coats) {
		r->save_CSV(filename, coats);
	}

	// save to HTML format
	void save_HTML(string filename, std::vector<TrenchCoat> coats) {
		r->save_HTML(filename, coats);
	}
};

