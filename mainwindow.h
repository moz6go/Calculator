#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	QString strOperation;
	bool isNewOper;
	double firstNum;
	double secondNum;
	double ResOperation(const double& first, const double& second, const QString& mathOper);
private slots:
    void DigitsNumbers();
    void Operations();
    void MathOperations();
    void on_pushButton_dot_clicked();
    void on_pushButton_AC_clicked();
    void on_pushButton_equal_clicked();
};

#endif // MAINWINDOW_H
