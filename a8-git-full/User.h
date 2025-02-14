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

#include "TabeleView.h"

#include <iomanip>
#include <sstream>

class User : public QWidget {
private:
	//TableView table;

	Service s;
	string mode;
	vector<TrenchCoat> cart;
	string csv_file = "csv_file.csv";
	string html_file = "html_file.html";
	string csv_basket = "basket.csv";
	string html_basket = "basket.html";
	int sizeFilter = 0;
	float total = 0.0;
	int currentItem = 0;

	QListWidget* coatsListWidget;

	QLabel* message;
	QLabel* empty;

	QLabel* sizeLabel;
	QLabel* quantityLabel;
	QLabel* priceLabel;
	QLabel* colourLabel;
	QLabel* linkLabel;
	QLabel* totalLabel;

	QLabel* sizeText;
	QLabel* quantityText;
	QLabel* priceText;
	QLabel* colourText;
	QLabel* linkText;
	QLabel* totalText;

	QLineEdit* sizeEdit;

	QPushButton* addButton;
	QPushButton* filerButton;
	QPushButton* nextButton;
	QPushButton* checkoutButton;
	QPushButton* closeButton;
	QPushButton* linkButton;

	QPushButton* tableButton;
public:
	User(string mode) {
		this->mode = mode;

		setWindowTitle(QString::fromStdString("Trench coats! (User)"));
		setMinimumWidth(800);
		setMinimumHeight(500);

		s.load_file();
		this->buildGui();
		this->populateList();

		QObject::connect(this->addButton, &QPushButton::clicked, this, &User::addButtonHandler);
		QObject::connect(this->filerButton, &QPushButton::clicked, this, &User::filterButtonHandler);
		QObject::connect(this->nextButton, &QPushButton::clicked, this, &User::nextButtonHandler);
		QObject::connect(this->checkoutButton, &QPushButton::clicked, this, &User::checkoutButtonHandler);
		QObject::connect(this->closeButton, &QPushButton::clicked, this, &User::closeButtonHandler);
		QObject::connect(this->linkButton, &QPushButton::clicked, this, &User::linkButtonHandler);

		QObject::connect(this->tableButton, &QPushButton::clicked, this, &User::tableButtonHandler);

		this->coatsListWidget->setCurrentRow(this->currentItem);
		this->showCurrentItem();
	}

	void buildGui() {
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
		this->message->setFont(*new QFont{ "AnyStyle" });

		this->addButton = new QPushButton{ "Add" };
		this->filerButton = new QPushButton{ "Filter" };
		this->nextButton = new QPushButton{ "Next" };
		this->checkoutButton = new QPushButton{ "Checkout" };
		this->closeButton = new QPushButton{ "Save and Close" };
		this->linkButton = new QPushButton{ "Open Link" };
		
		this->tableButton = new QPushButton{ "Table View" };
		
		QLabel* sizeFilterLabel = new QLabel{ "Size Filter" };
		this->sizeEdit = new QLineEdit{ "0" };

		this->sizeLabel = new QLabel{ "Size" };
		this->quantityLabel = new QLabel{ "Quantity" };
		this->priceLabel = new QLabel{ "Price" };
		this->colourLabel = new QLabel{ "Colour" };
		this->linkLabel = new QLabel{ "Link" };
		this->totalLabel = new QLabel{ "Total" };

		this->sizeText = new QLabel{};
		this->quantityText = new QLabel{};
		this->priceText = new QLabel{};
		this->colourText = new QLabel{};
		this->linkText = new QLabel{};
		this->totalText = new QLabel{ "0" };

		this->sizeText->setFrameStyle(QFrame::Panel | QFrame::Sunken);
		this->sizeText->setMargin(10);
		this->quantityText->setFrameStyle(QFrame::Panel | QFrame::Sunken);
		this->quantityText->setMargin(10);
		this->priceText->setFrameStyle(QFrame::Panel | QFrame::Sunken);
		this->priceText->setMargin(10);
		this->colourText->setFrameStyle(QFrame::Panel | QFrame::Sunken);
		this->colourText->setMargin(10);
		this->linkText->setFrameStyle(QFrame::Panel | QFrame::Sunken);
		this->linkText->setMargin(10);
		this->totalText->setFrameStyle(QFrame::Panel | QFrame::Sunken);
		this->totalText->setMargin(10);

		rightLayout->addWidget(sizeFilterLabel, 0, 0);
		rightLayout->addWidget(this->sizeEdit, 0, 1);
		rightLayout->addWidget(this->addButton, 1, 0);
		rightLayout->addWidget(this->filerButton, 0, 2);
		rightLayout->addWidget(this->nextButton, 2, 0);
		rightLayout->addWidget(this->checkoutButton, 1, 2);
		rightLayout->addWidget(this->closeButton, 3, 2);
		rightLayout->addWidget(this->linkButton, 2, 2);

		rightLayout->addWidget(this->tableButton, 3, 2);

		rightLayout->addWidget(this->message, 1, 1, 2, 1);
		
		rightLayout->addWidget(this->sizeLabel, 3, 0);
		rightLayout->addWidget(this->sizeText, 3, 1);
		rightLayout->addWidget(this->quantityLabel, 4, 0);
		rightLayout->addWidget(this->quantityText, 4, 1);
		rightLayout->addWidget(this->priceLabel, 5, 0);
		rightLayout->addWidget(this->priceText, 5, 1);
		rightLayout->addWidget(this->colourLabel, 6, 0);
		rightLayout->addWidget(this->colourText, 6, 1);
		rightLayout->addWidget(this->linkLabel, 7, 0);
		rightLayout->addWidget(this->linkText, 7, 1);
		rightLayout->addWidget(this->totalLabel, 8, 0);
		rightLayout->addWidget(this->totalText, 8, 1);

		rightLayout->addWidget(this->empty, 9, 0, 8, 2);

		mainLayout->addLayout(rightLayout);
	}

	void populateList() {
		this->message->setText(QString::fromStdString("Output messages"));
		this->coatsListWidget->clear();
		int index = 1;
		for (auto coat : s.getRepoData()) {
			if (this->sizeFilter == 0 || this->sizeFilter == coat.getSize()) {
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
		}
		if (index == 1) this->message->setText(QString::fromStdString("No more coats to show."));
	}

	void addButtonHandler() {
		auto link = this->linkText->text().toStdString();
		TrenchCoat* c = s.findExactCoat(link);
		if (c == NULL) this->message->setText(QString::fromStdString("Coat does not exist."));
		else {
			int j = 0;
			for (TrenchCoat coat : cart) {
				if (coat.getLink() == c->getLink()) break;
				++j;
			}
			if (j == cart.size()) {
				cart.push_back(*c);
				cart[j].setQuantity(1);
			}
			else cart[j].setQuantity(cart[j].getQuantity() + 1);
			this->total += c->getPrice();

			std::ostringstream os;
			os << std::fixed << std::setprecision(2) << this->total;
			string string = os.str();

			this->totalText->setText(QString::fromStdString(string));
			if (c->getQuantity() == 1) s.removeCoat(*c);
			else c->setQuantity(c->getQuantity() - 1);
			this->populateList();
			if (this->coatsListWidget->count() == 0) {
				this->message->setText(QString::fromStdString("No more coats to show."));
				this->sizeText->setText(QString::fromStdString(""));
				this->quantityText->setText(QString::fromStdString(""));
				this->priceText->setText(QString::fromStdString(""));
				this->colourText->setText(QString::fromStdString(""));
				this->linkText->setText(QString::fromStdString(""));
			}
			else {
				this->coatsListWidget->setCurrentRow(this->currentItem);
				this->showCurrentItem();
			}
		}
	}

	void filterButtonHandler() {
		auto filter = this->sizeEdit->text();
		this->sizeFilter = filter.toInt();
		this->populateList();
		this->currentItem = 0;
		this->coatsListWidget->setCurrentRow(this->currentItem);
		this->showCurrentItem();
	}

	void showCurrentItem() {
		string str = this->coatsListWidget->currentItem()->text().toStdString();
		size_t index = str.find("Link:");
		string link = str.substr(index);
		link.erase(0, 6);
		TrenchCoat* coat = s.findExactCoat(link);
		this->sizeText->setText(QString::fromStdString(to_string(coat->getSize())));
		this->quantityText->setText(QString::fromStdString(to_string(coat->getQuantity())));
		std::ostringstream os;
		os << std::fixed << std::setprecision(2) << coat->getPrice();
		string string = os.str();
		this->priceText->setText(QString::fromStdString(string));
		this->colourText->setText(QString::fromStdString(coat->getColour()));
		this->linkText->setText(QString::fromStdString(coat->getLink()));
	}

	void nextButtonHandler() {
		this->currentItem++;
		if (this->currentItem == this->coatsListWidget->count()) this->currentItem = 0;
		if (this->coatsListWidget->count() == 0) {
			this->message->setText(QString::fromStdString("No more coats to show."));
			this->sizeText->setText(QString::fromStdString(""));
			this->quantityText->setText(QString::fromStdString(""));
			this->priceText->setText(QString::fromStdString(""));
			this->colourText->setText(QString::fromStdString(""));
			this->linkText->setText(QString::fromStdString(""));
		}
		else {
			this->coatsListWidget->setCurrentRow(this->currentItem);
			this->showCurrentItem();
		}
	}

	void linkButtonHandler() {
		auto link = this->linkText->text();
		QDesktopServices::openUrl(QUrl(link));
	}

	void checkoutButtonHandler() {
		if (this->mode == "csv") {
			s.save_CSV(this->csv_basket, cart);
			QDesktopServices::openUrl(QUrl(QString::fromStdString(this->csv_basket)));
		}
		else if (this->mode == "html") {
			s.save_HTML(this->html_basket, cart);
			QDesktopServices::openUrl(QUrl(QString::fromStdString(this->html_basket)));
		}
	}

	void closeButtonHandler() {
		s.save_file();
		if (this->mode == "csv") {
			s.save_CSV(this->csv_file, s.getRepoData());
			s.save_CSV(this->csv_basket, this->cart);
		}
		else if (this->mode == "html") {
			s.save_HTML(this->html_file, s.getRepoData());
			s.save_HTML(this->html_basket, s.getRepoData());
		}
		close();
	}

	void tableButtonHandler() {
		TableView* table = new TableView;
		table->setCart(this->cart, this->total);
		QTableView* view = new QTableView;
		view->setModel(table);
		view->resize(650, 400);
		view->show();

		// Connect a slot to delete the table object when the view is closed
		QObject::connect(view, &QWidget::destroyed, [=]() {
			delete table;
			delete view;
		});
	}

};
