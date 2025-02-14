#pragma once
#include "Admin.h"
#include "User.h"
#include <qcheckbox.h>
#include <qbuttongroup.h>

class Starter : public QWidget {
private:
	Admin* a;
	User* u;

	QLabel* empty;
	QCheckBox* csvMode;
	QCheckBox* htmlMode;

	QPushButton* adminButton;
	QPushButton* userButton;

public:
	Starter() {
		setWindowTitle(QString::fromStdString("Pick the way the application is started"));
		setMinimumWidth(400);
		setMinimumHeight(150);

		QGridLayout* mainLayout = new QGridLayout{ this };
	
		this->empty = new QLabel{};

		this->csvMode = new QCheckBox{ "CSV" };
		this->htmlMode = new QCheckBox{ "HTML" };

		this->csvMode->setChecked(true);

		QButtonGroup* group = new QButtonGroup(this);
		group->setExclusive(true);
		group->addButton(csvMode);
		group->addButton(htmlMode);

		this->adminButton = new QPushButton{ "Admin Mode" };
		this->userButton = new QPushButton{ "User Mode" };

		mainLayout->addWidget(this->csvMode, 1, 1);
		mainLayout->addWidget(this->htmlMode, 2, 1);
		mainLayout->addWidget(this->userButton, 1, 0);
		mainLayout->addWidget(this->adminButton, 2, 0);
		mainLayout->addWidget(this->empty, 3, 0);

		QObject::connect(this->adminButton, &QPushButton::clicked, this, &Starter::adminButtonHandler);
		QObject::connect(this->userButton, &QPushButton::clicked, this, &Starter::userButtonHandler);
	}

	void adminButtonHandler(){
		if (this->csvMode->isChecked()) a = new Admin("csv");
		else if (this->htmlMode->isChecked()) a = new Admin("html");
		a->show();
		this->close();
	}
	
	void userButtonHandler() {
		if (this->csvMode->isChecked()) u = new User("csv");
		else if (this->htmlMode->isChecked()) u = new User("html");
		u->show();
		this->close();
	}

};


