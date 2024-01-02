#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>
#include <QDir>
#include <QButtonGroup>
#include <QVector>
#include <iostream>
#include <QPushButton>
#include <QListWidgetItem>
#include <QGridLayout>
#include "ui_mainwindow.h"

#include "constants.h"
#include "strategies.h"
#include "ui/gameElements/plants.h"
#include "qt_graphics_models/playground.h"
#include "qt_graphics_models/robot.h"
#include "qt_graphics_models/game_element.h"

//#include "path_finding/path_finder.h"
//#include "path_finding/path_checker.h"

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

    void readTestFiles(void);

    void readStratFiles(void);

    void showTestFiles(void);

    void launchSelectedStrategy(void);

    void enable_go_button(void);

    void go_to_strategy(void);

    void go_to_test(void);

private:
    Ui::mainWindow *ui;

    playground_scene playground;
    robot_graphic_item robot;
    game_element fragile_plant_pot;
    game_element fragile_plant;
    game_element regular_plant_pot;
    game_element regular_plant;

    QStackedWidget *stackedWidget;
    QTimer *timer;
    QDir test_strat_dir;
    QDir strat_dir;
    QButtonGroup button_group;
    QButtonGroup teamChoice;
    int nbrItemsListWidget;
    QVector <QPushButton*> push_button_vector;
    QVector <QWidget*> widget_vector;
    QVector <QGridLayout*> grid_layout_vector;
    QVector <QListWidgetItem*> list_widget_item_vector;
    //path_finder<holonome> pf; // or path_finder<differential> path_finder;

    QVector <Plants*> plants;

    VRAC_context ctx{.colorside = true};

};
#endif // MAINWINDOW_H
