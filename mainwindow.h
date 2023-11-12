#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>
#include <QDir>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void add_to_test_list(void);

    void connectButtons(void);


private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    QTimer *timer;
    QDir test_strat;
    int nbrItemsListWidget;

    void lecture_fichiers();
    void afficher_fichiers();

};
#endif // MAINWINDOW_H
