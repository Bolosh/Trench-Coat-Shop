#pragma once
#include "Repository.h"
#include <stack>


class Command {
public:
	Command* cmd;
	virtual void execute() = 0;
	virtual void unexecute() = 0;
};

class AddCommand : public Command {
private:
	Repository& r;
	TrenchCoat coat;

public:
	AddCommand(Repository& repo, TrenchCoat c) : r(repo) {
		//this->r = repo;
		this->coat = c;
	}

	void execute() override {
		try {
			this->r.addCoat(this->coat);
		}
		catch (exception()){}
	}

	void unexecute() override {
		try {
			this->r.removeCoat(this->coat);
		}
		catch (exception()) {}
	}
};

class RemoveCommand : public Command {
private:
	Repository& r;
	TrenchCoat coat;

public:
	RemoveCommand(Repository& repo, TrenchCoat c) : r(repo) {
		//this->r = repo;
		this->coat = c;
	}

	void execute() override {
		try {
			this->r.removeCoat(this->coat);
		}
		catch (exception()) {}
	}

	void unexecute() override {
		try {
			this->r.addCoat(this->coat);
		}
		catch (exception()) {}
	}
};

class UpdateCommand : public Command {
private:
	Repository& r;
	TrenchCoat preUpdate;
	TrenchCoat postUpdate;

public:
	UpdateCommand(Repository& repo, TrenchCoat preUpdate, TrenchCoat postUpdate) : r(repo) {
		//this->r = repo;
		this->preUpdate = preUpdate;
		this->postUpdate = postUpdate;
	}

	void execute() override {
		try {
			this->r.removeCoat(this->preUpdate);
			this->r.addCoat(this->postUpdate);
		}
		catch (exception()) {}
	}

	void unexecute() override {
		try {
			this->r.removeCoat(this->postUpdate);
			this->r.addCoat(this->preUpdate);
		}
		catch (exception()) {}
	}
};

class CommandManager {
private:
	stack<Command*> undoStack;
	stack<Command*> redoStack;

public:
	void executeCommand(Command* cmd) {
		cmd->execute();
		this->undoStack.push(cmd);
	}

	void undo() {
		if (!this->undoStack.empty()) {
			Command* cmd = this->undoStack.top();
			this->undoStack.pop();
			cmd->unexecute();
			redoStack.push(cmd);
		}	
	}

	void redo() {
		if (!this->redoStack.empty()) {
			Command* cmd = this->redoStack.top();
			this->redoStack.pop();
			cmd->execute();
			this->undoStack.push(cmd);
		}
	}

	bool isEmpty(string s) {
		if (s == "undo") return this->undoStack.empty();
		else if (s == "redo") return this->redoStack.empty();
		else return false;
	}

};