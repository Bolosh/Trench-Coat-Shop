#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_a8.h"

class a8 : public QMainWindow
{
    Q_OBJECT

public:
    a8(QWidget *parent = nullptr);
    ~a8();

private:
    Ui::a8Class ui;
};
