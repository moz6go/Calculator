#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    Ui::MainWindow *ui;
	QString strOperation;
	bool isNewOper;
    bool afterEqual;
	double firstNum;
	double secondNum;
	double ResOperation(const double& first, const double& second, const QString& mathOper);
    void DefaultInit();
private slots:
    void DigitsNumbers();
    void Operations();
    void MathOperations();
    void on_pushButton_dot_clicked();
    void on_pushButton_AC_clicked();
    void on_pushButton_equal_clicked();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
