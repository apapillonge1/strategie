#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamestate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainWindow), stackedWidget(new QStackedWidget), test_strat_dir("./../test_strat"),strat_dir("./../strats"),
    mapHeight(2000), mapLength(3000), btnHeight(75), mapScale(0.2)
{

    nbrItemsListWidget = 0;
    strategyNbrs = 0;
    ui->setupUi(this);
    QRectF scene_rect(0, 0, mapLength, mapHeight);
    GameState::get()->playground().setSceneRect(scene_rect);
    QImage image = QIcon(":/ressources/images/vinyles_table_2024_BETA.svg").pixmap(scene_rect.width(), scene_rect.height()).toImage();
    GameState::get()->playground().setBackgroundBrush(image);
    button_group.setExclusive(true);

    ui->playground->scale(mapScale, mapScale);
    ui->playground->setScene(&GameState::get()->playground());

    ui->playground_test->scale(mapScale, mapScale);
    ui->playground_test->setScene(&GameState::get()->playground());

    ui->btn_blue_menu_start->setCheckable(true);
    ui->btn_yellow_menu_start->setCheckable(true);
    ui->btn_blue_menu_start->setStyleSheet("QPushButton::checked{background-color: rgb(0,0,255);}");
    ui->btn_yellow_menu_start->setStyleSheet("QPushButton::checked{background-color: rgb(255,255,0);}");
    teamChoice.addButton(ui->btn_blue_menu_start);
    teamChoice.addButton(ui->btn_yellow_menu_start);
    teamChoice.setExclusive(true);

    ui->stackedWidget->setCurrentWidget(ui->menu);
    connectButtons();
    readTestFiles();
}

MainWindow::~MainWindow()
{
    ui->list_tests->clear();
    memory_vector.clear();
    delete ui;
}

void MainWindow::connectButtons()
{
    // menu connect

    connect(ui->btn_start_menu, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->strategy); });
    connect(ui->btn_tests_menu, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->Tests); });

    // test connect
    connect(ui->btn_close_tests, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu); });
    connect(ui->btn_close_map_test, &QPushButton::clicked, this, &MainWindow::btn_close_map_test);
    connect(ui->btn_start_tests, &QPushButton::clicked, this, &MainWindow::showTestFiles);
    connect(ui->btn_suppr_tests, &QPushButton::clicked, this, &MainWindow::on_btn_suppr_test_clicked);


    // strategy connect
    connect(ui->btn_strategy_close, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu); });
    connect(ui->btn_strategy_start, &QPushButton::clicked, this, &MainWindow::readStrategyFiles);

    // start connect

    connect(ui->btn_close_menu_start, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->strategy); });
    connect(ui->btn_go_menu_start, &QPushButton::clicked, this, &MainWindow::enable_go_button);
    connect(ui->btn_close_map_start, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu_start); });
    connect(ui->btn_start_map_start, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu); });

    // read files and create buttons with their name
    test_strat_dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    test_strat_dir.setSorting(QDir::Size | QDir::Reversed);

    QWidget *client = new QWidget(this);                //memory leak
    memory_vector.push_back(client);
    QGridLayout *grid_test = new QGridLayout(client);
    memory_vector.push_back(grid_test);
    client->setLayout(grid_test);

    ui->scrollArea->setWidget(client);

    QFileInfoList list = test_strat_dir.entryInfoList();
    std::cout << "Existing files : " << std::endl;

    for (const auto & fileInfo : list)
    {
        std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));
        std::cout << std::endl;
        if (fileInfo.completeSuffix() == "json")
        {
            QPushButton *btn_test = new QPushButton(fileInfo.fileName());
            memory_vector.push_back(btn_test);
            btn_test->setFixedHeight(btnHeight);
            grid_test->addWidget(btn_test);
            connect(btn_test, &QPushButton::clicked, this, &MainWindow::add_to_test_list);
        }
    }
}

void MainWindow::add_to_test_list()
{
    QPushButton *btn = static_cast<QPushButton *>(sender());
    ui->list_tests->setDragEnabled(true);
    ui->list_tests->setDragDropMode(QAbstractItemView::InternalMove);
    ui->list_tests->setMinimumHeight(btnHeight);
    QListWidgetItem *item = new QListWidgetItem(btn->text());                   //memory leak
    memory_vector.push_back((QObject*)item);
    ui->list_tests->addItem(item);
    std::cout << btn->text().toStdString() << std::endl;
    nbrItemsListWidget++;
}

void MainWindow::btn_close_map_test()
{
    ui->stackedWidget->setCurrentWidget(ui->Tests);
    ui->list_map_test_2->clear();
}

void MainWindow::on_btn_suppr_test_clicked()
{
    foreach (QListWidgetItem *ligne, ui->list_tests->selectedItems())
    {
        delete ui->list_tests->takeItem(ui->list_tests->row(ligne));
        nbrItemsListWidget --;
    }
}

void MainWindow::showTestFiles()
{
    std::cout << "----------------------------------" << std::endl;
    if (nbrItemsListWidget <= 0)
    {
        std::cout << "No item in the list" << std::endl;
        return;
    }
    ui->stackedWidget->setCurrentWidget(ui->map_test_2);
    for (int i = 0; i <ui->list_tests->count(); i++)
    {
        std::cout << "Hello" << std::endl;
        std::cout << "----------------------------------" << std::endl;
        QString fileName = "../test_strat/" + ui->list_tests->item(i)->text();
        std::cout << fileName.toStdString() << std::endl;
        ui->list_map_test_2->addItem(ui->list_tests->item(i)->text());
    }
}

void MainWindow::readStrategyFiles()
{
    if(button_group.checkedId()!= -1)
    {
        ui->stackedWidget->setCurrentWidget(ui->menu_start);
        return;
    }
    std::cout << "No checked strategy "<< std::endl;
}
void MainWindow::readTestFiles()
{
    // lecture du fichier et création de bouton avec leurs noms
    test_strat_dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    test_strat_dir.setSorting(QDir::Size | QDir::Reversed);

    QWidget *client = new QWidget(this);
    memory_vector.push_back(client);

    QGridLayout *grid_test = new QGridLayout(client);
    memory_vector.push_back(grid_test);
    client->setLayout(grid_test);
    ui->scrollArea->setWidget(client);
    QFileInfoList list = test_strat_dir.entryInfoList();
    std::cout << "Existing files : " << std::endl;
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));
        std::cout << std::endl;
        if (fileInfo.completeSuffix() == "json")
        {
            QPushButton *btn_test = new QPushButton(fileInfo.fileName());              //memory
            memory_vector.push_back(btn_test);
            btn_test->setMinimumHeight(btnHeight);
            grid_test->addWidget(btn_test);
            connect(btn_test, &QPushButton::clicked, this, &MainWindow::add_to_test_list);
        }
    }

    strat_dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    strat_dir.setSorting(QDir::Size | QDir::Reversed);
    QWidget *client2 = new QWidget(this);                       //memory leak
    memory_vector.push_back(client2);
    QGridLayout *grid_strat = new QGridLayout(client2);
    memory_vector.push_back(grid_strat);
    client2->setLayout(grid_strat);
    ui->scrollArea_2->setWidget(client2);
    QFileInfoList list2 = strat_dir.entryInfoList();
    for (const auto &fileInfo2 : list2)
    {
        std::cout << qPrintable(QString("%1 %2").arg(fileInfo2.size(), 10).arg(fileInfo2.fileName()));
        std::cout << std::endl;
        if (fileInfo2.completeSuffix() == "json")
        {
            QPushButton *btn_test = new QPushButton(fileInfo2.fileName());                      //memory leak
            memory_vector.push_back(btn_test);
            btn_test->setMinimumHeight(btnHeight);
            btn_test->setStyleSheet("QPushButton::checked{background-color: rgb(0,255,0);}");
            btn_test->setCheckable(true);
            grid_strat->addWidget(btn_test);
            button_group.addButton(btn_test);
            std::cout <<button_group.id(btn_test) << std::endl;

            strategyNbrs++;
        }
    }
}

void MainWindow::enable_go_button(void)
{
    if(teamChoice.checkedId() == -1)
    {
        ui->btn_go_menu_start->setStyleSheet("QPushButton::checked{background-color: rgb(192,192,192);}");
        return;
    }
    ui->stackedWidget->setCurrentWidget(ui->map_start);
}
