#pragma once
#include <qwidget.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qurl.h>
#include <qdesktopservices.h>
#include <qtableview.h>
#include <qstandarditemmodel.h>

#include <vector>
#include "TrenchCoat.h"
#include <string>

#include <iostream>

class TableView : public QAbstractTableModel {
private:
    std::vector<TrenchCoat> cart;
    float total = 0.0;

public:
    TableView(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return int(cart.size()) + 1;
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 6;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid())
            return QVariant();

        if (index.row() == cart.size())
            if (index.column() == 5) return QVariant(total);
            else return QVariant();

        if (role == Qt::DisplayRole) {
            const TrenchCoat& coat = cart[index.row()];
            switch (index.column()) {
            case 0: return QVariant(coat.getSize());
            case 1: return QVariant(coat.getQuantity());
            case 2: return QVariant(coat.getPrice());
            case 3: return QVariant(QString::fromStdString(coat.getColour()));
            case 4: return QVariant(QString::fromStdString(coat.getLink()));
            case 5: return QVariant(coat.getPrice() * coat.getQuantity());
            default: return QVariant();
            }
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return tr("Size"); // Column 0 header
            case 1: return tr("Quantity"); // Column 1 header
            case 2: return tr("Price"); // Column 2 header
            case 3: return tr("Colour"); // Column 3 header
            case 4: return tr("Link"); // Column 4 header
            case 5: return tr("Total"); // Column 5 header
            default: return QVariant();
            }
        }

        return QAbstractTableModel::headerData(section, orientation, role);
    }

    // Custom function to set the cart data
    void setCart(std::vector<TrenchCoat> newCart, float total) {
        beginResetModel();
        this->cart = newCart;
        this->total = total;
        endResetModel();
    }
};