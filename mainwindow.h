#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDebug>
#include <QKeyEvent>
#include <cmath>

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
    void DefaultInit();
    void setFirst(double first);
    void setSecond (double second);
    void keyPressEvent(QKeyEvent *event);
    double BinaryCalculate(const double& first, const double& second, const QString& mathOper);
private slots:
    void ButtonsHandler(QString text);
    void DigitsNumbers ();
    void UnaryOperations ();
    void BinaryOperations ();
    void Dot ();
    void Ac ();
    void Ce ();
    void Equal ();
signals:
    void ButtonPressed (QString text);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
