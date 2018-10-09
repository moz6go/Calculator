#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	isNewOper = false;
	firstNum = 0;
	strOperation = "+";
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
	connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
	connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
	connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
	connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
	connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
	connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
	connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
	connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
	connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(DigitsNumbers()));
	connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(MathOperations()));
	connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(MathOperations()));
	connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(MathOperations()));
	connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(MathOperations()));
	connect(ui->pushButton_reverse, SIGNAL(clicked()), this, SLOT(Operations()));
	connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(Operations()));
}
void MainWindow::DigitsNumbers()
{
	QPushButton* button = static_cast<QPushButton*>(sender());
	if (isNewOper)
	{
		ui->showResult->setText("");
	}
	double dNumber = (ui->showResult->text() + button->text()).toDouble();
	ui->showResult->setText(QString::number(dNumber, 'g', 12));
	isNewOper = false;
}
double MainWindow::ResOperation(const double& first, const double& second, const QString& mathOper)
{
	if (mathOper == "+")
	{
		return first + second;
	}
	else if (mathOper == "-")
	{
		return first - second;
	}
	else if (mathOper == "*")
	{
		return first * second;
	}
	else if (mathOper == "/")
	{
		if (second)
		{
			return first / second;
		}
	}
	return first;
}
void MainWindow::Operations()
{
    QPushButton* button = static_cast<QPushButton*>(sender());
    if(button->text() == "+/-")
    {
		firstNum = (ui->showResult->text()).toDouble()*(-1);
		ui->showResult->setText(QString::number(firstNum, 'g', 12));
    }
    else if(button->text() == "%")
    {
		firstNum = (ui->showResult->text()).toDouble()*0.01;
		ui->showResult->setText(QString::number(firstNum, 'g', 12));
    }
}
void MainWindow::MathOperations()
{
	if (!isNewOper) 
	{
		QPushButton* button = static_cast<QPushButton*>(sender());
		ui->showExpression->setText(ui->showExpression->text() + " " + ui->showResult->text() + " " + button->text());
		secondNum = (ui->showResult->text()).toDouble();
		if(!secondNum && strOperation == "/")
		{
			ui->showResult->setText("Error: DIV/0");
			ui->showExpression->setText("");
		}
		else
		{
			ui->showResult->setText(QString::number(ResOperation(firstNum, secondNum, strOperation), 'g', 12));
			strOperation = button->text();
			firstNum = (ui->showResult->text()).toDouble();
			isNewOper = true;
		}
	}
}
void MainWindow::on_pushButton_equal_clicked()
{
	MathOperations();
	ui->showExpression->setText("");
	isNewOper = false;
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->showResult->text().contains('.')))
    {
        ui->showResult->setText(ui->showResult->text()+'.');
    }
}

void MainWindow::on_pushButton_AC_clicked()
{
    ui->showResult->setText(ui->pushButton_0->text());
	ui->showExpression->setText("");
	isNewOper = false;
	firstNum = 0;
	strOperation = "+";
}

MainWindow::~MainWindow()
{
    delete ui;
}
