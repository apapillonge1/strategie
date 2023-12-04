#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamestate.h"
#include "utility.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainWindow), stackedWidget(new QStackedWidget), test_strat_dir("./../test_strat"),strat_dir("./../strats")
{

    nbrItemsListWidget = 0;
    strategyNbrs = 0;
    ui->setupUi(this);
    QRectF scene_rect(0, 0, MAPLENGTH, MAPHEIGHT);
    GameState::get()->playground().setSceneRect(scene_rect);
    QImage image = QIcon(":/ressources/images/vinyles_table_2024_BETA.svg").pixmap(scene_rect.width(), scene_rect.height()).toImage();
    GameState::get()->playground().setBackgroundBrush(image);
    button_group.setExclusive(true);

    ui->playground->scale(MAPSCALE, MAPSCALE);
    ui->playground->setScene(&GameState::get()->playground());

    ui->playground_test->scale(MAPSCALE, MAPSCALE);
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

    for (auto element : push_button_vector)
    {
        delete element;
    }
    push_button_vector.clear();

    for (auto element : widget_vector)
    {
        delete element;
    }
    widget_vector.clear();

    for (auto element : list_widget_item_vector)
    {
        delete element;
    }
    list_widget_item_vector.clear();

    for (auto element : grid_layout_vector)
    {
        delete element;
    }
    grid_layout_vector.clear();
    delete ui;
}

void MainWindow::connectButtons()
{
    // menu connect

    connect(ui->btn_start_menu, &QPushButton::clicked, this, &MainWindow::go_to_strategy);
    connect(ui->btn_tests_menu, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->Tests); });

    // test connect
    connect(ui->btn_close_tests, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu); });
    connect(ui->btn_close_map_test, &QPushButton::clicked, this, &MainWindow::go_to_test);
    connect(ui->btn_start_tests, &QPushButton::clicked, this, &MainWindow::showTestFiles);
    connect(ui->btn_suppr_tests, &QPushButton::clicked, this, &MainWindow::on_btn_suppr_test_clicked);


    // strategy connect
    connect(ui->btn_strategy_close, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu); });
    connect(ui->btn_strategy_start, &QPushButton::clicked, this, &MainWindow::launchSelectedStrategy);

    // start connect

    connect(ui->btn_close_menu_start, &QPushButton::clicked, this, &MainWindow::go_to_strategy);
    connect(ui->btn_go_menu_start, &QPushButton::clicked, this, &MainWindow::enable_go_button);
    connect(ui->btn_close_map_start, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu_start); });
    connect(ui->btn_start_map_start, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu); });
}

void MainWindow::add_to_test_list()
{
    QPushButton *btn = static_cast<QPushButton *>(sender());
    ui->list_tests->setDragEnabled(true);
    ui->list_tests->setDragDropMode(QAbstractItemView::InternalMove);
    ui->list_tests->setMinimumHeight(BTNHEIGHT);
    QListWidgetItem *item = new QListWidgetItem(btn->text());
    list_widget_item_vector.push_back(item);
    ui->list_tests->addItem(item);
    std::cout << btn->text().toStdString() << std::endl;
    nbrItemsListWidget++;
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

void MainWindow::launchSelectedStrategy()
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
    widget_vector.push_back(client);

    QGridLayout *grid_test = new QGridLayout(client);
    grid_layout_vector.push_back(grid_test);
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
            QPushButton *btn_test = new QPushButton(fileInfo.fileName());
            push_button_vector.push_back(btn_test);
            btn_test->setMinimumHeight(BTNHEIGHT);
            grid_test->addWidget(btn_test);
            connect(btn_test, &QPushButton::clicked, this, &MainWindow::add_to_test_list);
        }
    }
}

void MainWindow::readStratFiles(void)
{
    strat_dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    strat_dir.setSorting(QDir::Size | QDir::Reversed);
    QWidget *client2 = new QWidget(this);
    widget_vector.push_back(client2);
    QGridLayout *grid_strat = new QGridLayout(client2);
    grid_layout_vector.push_back(grid_strat);
    client2->setLayout(grid_strat);
    ui->scrollArea_2->setWidget(client2);
    QFileInfoList list2 = strat_dir.entryInfoList();
    for (const auto &fileInfo2 : list2)
    {
        std::cout << qPrintable(QString("%1 %2").arg(fileInfo2.size(), 10).arg(fileInfo2.fileName()));
        std::cout << std::endl;
        if (fileInfo2.completeSuffix() == "json")
        {
            QPushButton *btn_test = new QPushButton(fileInfo2.fileName());
            push_button_vector.push_back(btn_test);
            btn_test->setMinimumHeight(BTNHEIGHT);
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

void MainWindow::go_to_strategy()
{
    readStratFiles();
    ui->stackedWidget->setCurrentWidget(ui->strategy);
}

void MainWindow::go_to_test()
{
    readTestFiles();
    ui->stackedWidget->setCurrentWidget(ui->Tests);
    ui->list_map_test_2->clear();
}
