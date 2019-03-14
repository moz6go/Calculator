#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    DefaultInit();
    ui->setupUi(this);

    connect(ui->pushButton_0, &QPushButton::clicked, this, &MainWindow::DigitsNumbers);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &MainWindow::DigitsNumbers);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::DigitsNumbers);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::DigitsNumbers);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::DigitsNumbers);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::DigitsNumbers);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &MainWindow::DigitsNumbers);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &MainWindow::DigitsNumbers);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &MainWindow::DigitsNumbers);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &MainWindow::DigitsNumbers);

    connect(ui->pushButton_plus, &QPushButton::clicked, this, &MainWindow::MathOperations);
    connect(ui->pushButton_minus, &QPushButton::clicked, this, &MainWindow::MathOperations);
    connect(ui->pushButton_mult, &QPushButton::clicked, this, &MainWindow::MathOperations);
    connect(ui->pushButton_div, &QPushButton::clicked, this, &MainWindow::MathOperations);

    connect(ui->pushButton_reverse, &QPushButton::clicked, this, &MainWindow::Operations);
    connect (ui->pushButton_pow, &QPushButton::clicked, this,  &MainWindow::Operations);
    connect (ui->pushButton_1_div_x, &QPushButton::clicked, this,  &MainWindow::Operations);
    connect (ui->pushButton_sqrt, &QPushButton::clicked, this,  &MainWindow::Operations);
    connect (ui->pushButton_del, &QPushButton::clicked, this, &MainWindow::Operations);

    connect (ui->pushButton_equal, &QPushButton::clicked, this, &MainWindow::Equal);
    connect(ui->pushButton_dot, &QPushButton::clicked, this, &MainWindow::Dot);
    connect(ui->pushButton_ac, &QPushButton::clicked, this, &MainWindow::Ac);
    connect(ui->pushButton_ce, &QPushButton::clicked, this, &MainWindow::Ce);

    QObject::connect (this, &MainWindow::ButtonPressed, this, &MainWindow::CatchButtons);
}

void MainWindow::CatchButtons(QString text){
    if(text == "0") ui->pushButton_0->animateClick ();
    if(text == "1") ui->pushButton_1->animateClick ();
    if(text == "2") ui->pushButton_2->animateClick ();
    if(text == "3") ui->pushButton_3->animateClick ();
    if(text == "4") ui->pushButton_4->animateClick ();
    if(text == "5") ui->pushButton_5->animateClick ();
    if(text == "6") ui->pushButton_6->animateClick ();
    if(text == "7") ui->pushButton_7->animateClick ();
    if(text == "8") ui->pushButton_8->animateClick ();
    if(text == "9") ui->pushButton_9->animateClick ();
    if(text == "+") ui->pushButton_plus->animateClick ();
    if(text == "-") ui->pushButton_minus->animateClick ();
    if(text == "*") ui->pushButton_mult->animateClick ();
    if(text == "/") ui->pushButton_div->animateClick ();
    if(text == ".") ui->pushButton_dot->animateClick ();
    if(text == "\r") ui->pushButton_equal->animateClick ();
    if(text == "\b") ui->pushButton_del->animateClick ();
    if(text == "\u007F") ui->pushButton_ac->animateClick ();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    emit ButtonPressed (event->text ());
}

void MainWindow::DefaultInit() {
    isNewOper = false;
    firstNum = 0;
    secondNum = 0;
    strOperation = "+";
}

void MainWindow::DigitsNumbers() {
	QPushButton* button = static_cast<QPushButton*>(sender());
    if (isNewOper) {
        ui->showResult->setText(ui->pushButton_0->text());
    }
    if (afterEqual) {
        Ac();
    }
    if(ui->showResult->text().size () < 12) {
        long double dNumber = (ui->showResult->text() + button->text()).toDouble();
        ui->showResult->setText(QString::number(dNumber, 'g', 12));
    }
	isNewOper = false;
    afterEqual = false;
}

long double MainWindow::ResOperation(const long double& first, const long double& second, const QString& mathOper) {
    if (mathOper == "+") {
		return first + second;
	}
    else if (mathOper == "-") {
		return first - second;
	}
    else if (mathOper == "*") {
		return first * second;
	}
    else if (mathOper == "÷") {
        if (second != 0.0)	{
			return first / second;
		}
	}
	return first;
}

void MainWindow::Operations()
{
    QPushButton* button = static_cast<QPushButton*>(sender());
    if(button->text() == "±") {
        ui->showResult->setText(QString::number((ui->showResult->text()).toDouble()*(-1), 'g', 12));
        firstNum = ui->showResult->text ().toDouble ();
    }
    else if (button->text() == "⌫") {
        if(ui->showResult->text ().size () > 1){
            QString new_text = ui->showResult->text ();
            new_text.chop (1);
            ui->showResult->setText(new_text);
        }
        else {
            ui->showResult->setText("0");
        }
        firstNum = ui->showResult->text ().toDouble ();
    }
    else if (button->text() == "x²") {
        firstNum = (ui->showResult->text()).toDouble() * (ui->showResult->text()).toDouble();
        ui->showResult->setText(QString::number(firstNum, 'g', 12));
    }
    else if (button->text() == "√x") {
        firstNum = sqrt ((ui->showResult->text()).toDouble());
        ui->showResult->setText(QString::number(firstNum, 'g', 12));
    }
    else if (button->text() == "1/x") {
        firstNum = 1 / (ui->showResult->text()).toDouble();
        ui->showResult->setText(QString::number(firstNum, 'g', 12));
    }
    afterEqual = true;
    secondNum = 0;
}

void MainWindow::MathOperations() {
    if (!isNewOper) {
        afterEqual = false;
		QPushButton* button = static_cast<QPushButton*>(sender());
        secondNum = (ui->showResult->text()).toDouble();
		ui->showExpression->setText(ui->showExpression->text() + " " + ui->showResult->text() + " " + button->text());
        if((ui->showResult->text()).toDouble() == 0.0 && strOperation == "/") {
			ui->showResult->setText("Error: DIV/0");
			ui->showExpression->setText("");
		}
        else {
            ui->showResult->setText(QString::number(ResOperation(firstNum, (ui->showResult->text()).toDouble(), strOperation), 'g', 12));
			strOperation = button->text();
            isNewOper = true;
            firstNum = (ui->showResult->text()).toDouble();
		}
	}
}

void MainWindow::Equal() {
	MathOperations();
	ui->showExpression->setText("");
    isNewOper = false;
    afterEqual = true;
}

void MainWindow::Dot() {
    if(!(ui->showResult->text().contains('.')))     {
        ui->showResult->setText(ui->showResult->text() + '.');
    }
}

void MainWindow::Ac() {
    ui->showResult->setText(ui->pushButton_0->text());
    ui->showExpression->setText("");
    DefaultInit();
}

void MainWindow::Ce () {
    ui->showResult->setText(ui->pushButton_0->text());
}

MainWindow::~MainWindow() {
    delete ui;
}
