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
    long double firstNum;
    long double secondNum;
    long double ResOperation(const long double& first, const long double& second, const QString& mathOper);
    void DefaultInit();
    void keyPressEvent(QKeyEvent *event);
private slots:
    void CatchButtons(QString text);
    void DigitsNumbers ();
    void Operations ();
    void MathOperations ();
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
