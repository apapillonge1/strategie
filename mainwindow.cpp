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

    ui->stackedWidget->setCurrentIndex(0);                  //index stack widget : (0: menu 1: 2: 3: map)

    connect(ui->btn_start_map, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(2);});
    connect(ui->btn_strategie_map, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->btn_close_strategie, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(0);});

    connect(ui->btn_start_menu, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(2);});
    connect(ui->btn_strategie_menu, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->btn_tests_menu, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentIndex(0);});
}

MainWindow::~MainWindow()
{
    delete ui;
}
