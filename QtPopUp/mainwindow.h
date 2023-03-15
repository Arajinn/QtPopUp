#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class PopUpWidgetsContainer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PopUpWidgetsContainer* mPopUpWidgetsContainer;
private slots:
    void onPopUpButtonClicked();
};

#endif // MAINWINDOW_H
