#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamestate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), stackedWidget(new QStackedWidget), test_strat("./../test_strat")
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
    connect(ui->btn_start_menu, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->strategie);});
    connect(ui->btn_tests_menu, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->Tests);});

    //test connect
    connect(ui->btn_close_tests, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->menu);});
    connect(ui->btn_close_map_test, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->Tests);});
    connect(ui->btn_start_tests, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->map_test_2);});

    //stratégie connect
    connect(ui->btn_close_strategie, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->menu);});
     connect(ui->btn_start_strategie, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->menu_start);});

    //start connect
    connect(ui->btn_close_menu_start, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->strategie);});
    connect(ui->btn_go_menu_start, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->map_start);});
    connect(ui->btn_close_map_start, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->menu_start);});
    connect(ui->btn_start_map_start, &QPushButton::clicked, this, [this](){ui->stackedWidget->setCurrentWidget(ui->menu);});


    // lecture du fichier et création de bouton avec leurs noms
    test_strat.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    test_strat.setSorting(QDir::Size | QDir::Reversed);

    QWidget *client = new QWidget(this);
    QGridLayout *grid_test = new QGridLayout(client);
    client->setLayout(grid_test);

    ui->scrollArea->setWidget(client);

        QFileInfoList list = test_strat.entryInfoList();
        std::cout << "fichier present : " << std::endl;


        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));
            std::cout << std::endl;
            if(fileInfo.completeSuffix()=="json")
            {
                QPushButton *btn_test = new QPushButton(fileInfo.fileName());
                grid_test->addWidget(btn_test);
                connect(btn_test, &QPushButton::clicked,this, &MainWindow::add_to_test_list);
            }
            QPushButton *btn_test_dnq = new QPushButton (fileInfo.fileName());
            grid_test->addWidget(btn_test_dnq);
        }
}

void MainWindow::add_to_test_list()
{
        QPushButton *btn = static_cast<QPushButton*>(sender());
        std::cout<< btn->text().toStdString() << std::endl;
}

MainWindow::~MainWindow()
{
        delete ui;
}
