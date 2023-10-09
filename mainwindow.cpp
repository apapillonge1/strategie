#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamestate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), stackedWidget(new QStackedWidget)
{
    ui->setupUi(this);
    QRectF scene_rect(0,0,3000,2000);
    GameState::get()->playground().setSceneRect(scene_rect);
    QImage image = QIcon(":/ressources/images/vinyles_table_2024_BETA.svg").pixmap(scene_rect.width(), scene_rect.height()).toImage();
    GameState::get()->playground().setBackgroundBrush(image);
    ui->playground->scale(0.2,0.2);
    ui->playground->setScene(&GameState::get()->playground());

    ui->playground_test->scale(0.2,0.2);
    ui->playground_test->setScene(&GameState::get()->playground());

    ui->stackedWidget->setCurrentIndex(0);                  //index stack widget : (0: menu 1: 2: 3: map)


    //menu connect
    connect(ui->btn_start_menu, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(4);});
    //connect(ui->btn_tests_menu, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->btn_tests_menu, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->btn_strategie_menu, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(3);});

    //test connect
    connect(ui->btn_close_tests, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->btn_close_map_test, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->btn_start_tests, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(2);});

    //stratégie connect
    connect(ui->btn_close_strategie, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(0);});

    //start connect
    connect(ui->btn_close_menu_start, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(0);});
    connect(ui->btn_go_menu_start, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(5);});
    connect(ui->btn_close_map_start, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(4);});
    connect(ui->btn_start_map_start, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(0);});


}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::my_timer()
{

}
