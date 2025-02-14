#pragma once
#include "Service.h"
#include <qwidget.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qurl.h>
#include <qdesktopservices.h>
#include <qmenubar.h>
#include <qmenu.h>
#include <qaction.h>

#include <iomanip>
#include <sstream>

class Admin : public QWidget {
private:
	Service s;
	string mode;
	string csv_file = "csv_file.csv";
	string html_file = "html_file.html";

	QListWidget* coatsListWidget;

	QLineEdit* sizeEdit;
	QLineEdit* quantityEdit;
	QLineEdit* priceEdit;
	QLineEdit* colourEdit;
	QLineEdit* linkEdit;

	QLabel* message;
	QLabel* empty;

	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* updateButton;
	QPushButton* getDataButton;
	QPushButton* linkButton;
	QPushButton* closeButton;

	QPushButton* undoButton;
	QPushButton* redoButton;

	QAction* undoAction;
	QAction* redoAction;

public:
	Admin(string mode) {
		this->mode = mode;

		setWindowTitle(QString::fromStdString("Trench coats! (Admin)"));
		setMinimumWidth(800);
		setMinimumHeight(500);

		s.load_file();
		this->buildGui();
		this->populateList();

		QObject::connect(this->addButton, &QPushButton::clicked, this, &Admin::addButtonHandler);
		QObject::connect(this->removeButton, &QPushButton::clicked, this, &Admin::removeButtonHandler);
		QObject::connect(this->updateButton, &QPushButton::clicked, this, &Admin::updateButtonHandler);
		QObject::connect(this->getDataButton, &QPushButton::clicked, this, &Admin::dataButtonHandler);
		QObject::connect(this->linkButton, &QPushButton::clicked, this, &Admin::linkButtonHandler);
		QObject::connect(this->closeButton, &QPushButton::clicked, this, &Admin::closeButtonHandler);
		
		QObject::connect(this->undoButton, &QPushButton::clicked, this, &Admin::undoButtonHandler);
		QObject::connect(this->redoButton, &QPushButton::clicked, this, &Admin::redoButtonHandler);

		connect(this->undoAction, &QAction::triggered, this, &Admin::undoButtonHandler);
		connect(this->redoAction, &QAction::triggered, this, &Admin::redoButtonHandler);

	}

	void buildGui(){
		QHBoxLayout* mainLayout = new QHBoxLayout{ this };
		this->coatsListWidget = new QListWidget{};
		mainLayout->addWidget(this->coatsListWidget);

		QGridLayout* rightLayout = new QGridLayout{};

		this->empty = new QLabel{};

		this->message = new QLabel{ "Output messages" };
		this->message->setFrameStyle(QFrame::Panel | QFrame::Sunken);
		this->message->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
		this->message->setMargin(10);
		this->message->setMaximumHeight(40);
		this->message->setFont(*new QFont{"AnyStyle"});

		// define the labels
		QLabel* sizeLabel = new QLabel{ "Size" };
		this->sizeEdit = new QLineEdit{};
		QLabel* quantityLabel = new QLabel{ "Quantity" };
		this->quantityEdit = new QLineEdit{};
		QLabel* priceLabel = new QLabel{ "Price" };
		this->priceEdit = new QLineEdit{};
		QLabel* colourLabel = new QLabel{ "Colour" };
		this->colourEdit = new QLineEdit{};
		QLabel* linkLabel = new QLabel{ "Link" };
		this->linkEdit = new QLineEdit{};

		this->undoAction = new QAction(tr("&Undo"), this);
		this->redoAction = new QAction(tr("&Redo"), this);

		undoAction->setShortcut(QKeySequence::Undo);
		redoAction->setShortcut(QKeySequence::Redo);

		addAction(undoAction);
		addAction(redoAction);

		// add the labes and the line edit
		rightLayout->addWidget(sizeLabel, 0, 0);
		rightLayout->addWidget(this->sizeEdit, 0, 1);
		rightLayout->addWidget(quantityLabel, 1, 0);
		rightLayout->addWidget(this->quantityEdit, 1, 1);
		rightLayout->addWidget(priceLabel, 2, 0);
		rightLayout->addWidget(this->priceEdit, 2, 1);
		rightLayout->addWidget(colourLabel, 3, 0);
		rightLayout->addWidget(this->colourEdit, 3, 1);
		rightLayout->addWidget(linkLabel, 4, 0);
		rightLayout->addWidget(this->linkEdit, 4, 1);

		this->addButton = new QPushButton{ "Add" };
		this->removeButton = new QPushButton{ "Remove" };
		this->updateButton = new QPushButton{ "Update" };
		this->getDataButton = new QPushButton{ "Get Data" };
		this->linkButton = new QPushButton{ "Open Link" };
		this->closeButton = new QPushButton{ "Save and Close" };
		
		this->undoButton = new QPushButton{ "Undo" };
		this->redoButton = new QPushButton{ "Redo" };

		rightLayout->addWidget(this->addButton, 5, 0);
		rightLayout->addWidget(this->removeButton, 6, 0);
		rightLayout->addWidget(this->updateButton, 5, 2);
		rightLayout->addWidget(this->getDataButton, 6, 2);
		rightLayout->addWidget(this->linkButton,7, 0);
		rightLayout->addWidget(this->closeButton, 7, 2);
		
		rightLayout->addWidget(this->undoButton, 8, 0);
		rightLayout->addWidget(this->redoButton, 8, 2);

		rightLayout->addWidget(this->message, 6, 1);
		rightLayout->addWidget(this->empty, 9, 1);

		mainLayout->addLayout(rightLayout);
	}

	void populateList() {
		this->coatsListWidget->clear();
		int index = 1;
		for (auto coat : s.getRepoData()) {
			string s = "";
			
			std::ostringstream os;
			os << std::fixed << std::setprecision(2) << coat.getPrice();
			string string = os.str();
			
			s.append(to_string(index));
			s.append(". Size: ");
			s.append(to_string(coat.getSize()));
			s.append(", Price: ");
			s.append(string);
			s.append(", Color: ");
			s.append(coat.getColour());
			s.append(", Link: ");
			s.append(coat.getLink());
			this->coatsListWidget->addItem(QString::fromStdString(s));
			++index;
		}

		if (s.isEmpty("undo")) this->undoButton->setEnabled(false);
		else this->undoButton->setEnabled(true);
		if (s.isEmpty("redo")) this->redoButton->setEnabled(false);
		else this->redoButton->setEnabled(true);
	}

	void addButtonHandler() {
		auto size = this->sizeEdit->text();
		auto quantity = this->quantityEdit->text();
		auto price = this->priceEdit->text();
		auto colour = this->colourEdit->text();
		auto link = this->linkEdit->text();

		TrenchCoat coat;
		coat.makeCoat(size.toInt(), quantity.toInt(), price.toFloat(), colour.toStdString(), link.toStdString());
		try {
			s.addCoat(coat);
			this->message->setText(QString::fromStdString("Coat added!"));
		}
		catch (const ExceptionClass& e) {
			this->message->setText(QString::fromStdString(e.what()));
		}
		this->populateList();
	}

	void removeButtonHandler() {
		auto size = this->sizeEdit->text();
		auto quantity = this->quantityEdit->text();
		auto price = this->priceEdit->text();
		auto colour = this->colourEdit->text();
		auto link = this->linkEdit->text();

		TrenchCoat coat;
		coat.makeCoat(size.toInt(), quantity.toInt(), price.toFloat(), colour.toStdString(), link.toStdString());
		try {
			s.removeCoat(coat);
			this->message->setText(QString::fromStdString("Coat removed!"));
		}
		catch (const ExceptionClass& e) {
			this->message->setText(QString::fromStdString(e.what()));
		}
		this->populateList();
	}

	void updateButtonHandler() {
		auto size = this->sizeEdit->text();
		auto quantity = this->quantityEdit->text();
		auto price = this->priceEdit->text();
		auto colour = this->colourEdit->text();
		auto link = this->linkEdit->text();

		TrenchCoat* c = s.findExactCoat(link.toStdString());
		if(c == NULL) this->message->setText(QString::fromStdString("Coat does not exist!"));
		else {
			s.updateCoat(c, size.toInt(), quantity.toInt(), price.toFloat(), colour.toStdString(), link.toStdString());
			this->message->setText(QString::fromStdString("Coat updated!"));
		}
		this->populateList();
	}

	void dataButtonHandler() {
		string str = this->coatsListWidget->currentItem()->text().toStdString();
		int i;
		for (i = 0; str[i] != '.'; ++i);
		string index = "";
		for (int j = 0; j < i; ++j) index += str[j];
		int pos = stoi(index);
		TrenchCoat* coat = s.getCoat(pos - 1);
		this->sizeEdit->setText(QString::fromStdString(to_string(coat->getSize())));
		this->quantityEdit->setText(QString::fromStdString(to_string(coat->getQuantity())));
		this->priceEdit->setText(QString::fromStdString(to_string(coat->getPrice())));
		this->colourEdit->setText(QString::fromStdString(coat->getColour()));
		this->linkEdit->setText(QString::fromStdString(coat->getLink()));
	}

	void linkButtonHandler() {
		auto link = this->linkEdit->text();
		QDesktopServices::openUrl(QUrl(link));
	}

	void closeButtonHandler() {
		s.save_file();
		if (this->mode == "csv") s.save_CSV(this->csv_file, s.getRepoData());
		else if (this->mode == "html") s.save_CSV(this->html_file, s.getRepoData());
		close();
	}

	void undoButtonHandler() {
		if(!s.isEmpty("undo")) {
			s.undo();
			this->populateList();
			this->message->setText(QString::fromStdString("Operation undoed!"));
		}
		else {
			this->message->setText(QString::fromStdString("No more undos!"));
		}
	}

	void redoButtonHandler() {
		if (!s.isEmpty("redo")) {
			s.redo();
			this->populateList();
			this->message->setText(QString::fromStdString("Operation redoed!"));
		}
		else {
			this->message->setText(QString::fromStdString("No more redos!"));
		}
	}
};
