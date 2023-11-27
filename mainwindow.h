#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>
#include <QDir>
#include <QButtonGroup>
#include <QVector>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class mainWindow;
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


private slots:

    void on_btn_suppr_test_clicked(void);

    void btn_close_map_test(void);

    void readTestFiles(void);

    void showTestFiles(void);

    void readStrategyFiles(void);

    void enable_go_button(void);

private:
    Ui::mainWindow *ui;
    QStackedWidget *stackedWidget;
    QTimer *timer;
    QDir test_strat_dir;
    QDir strat_dir;
    QButtonGroup button_group;
    QButtonGroup teamChoice;
    int nbrItemsListWidget;
    int strategyNbrs;
    int btnHeight;
    int mapHeight;
    int mapLength;
    int mapScale;
    QVector <QObject*> memory_vector;

};
#endif // MAINWINDOW_H
