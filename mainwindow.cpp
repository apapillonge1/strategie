#include "mainwindow.h"
#include <QRectF>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mainWindow), stackedWidget(new QStackedWidget), test_strat_dir(STRATS_DIR_RPI), strat_dir(TESTS_DIR_RPI)
{

    nbrItemsListWidget = 0;
    ui->setupUi(this);

    init_buttons();

    init_playground();

    init_robot();

    init_plants();

    init_obstacles();

    init_path_finder();

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
    for (auto p : plants)
    {
        delete p;
    }
    plants.clear();
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
        nbrItemsListWidget--;
    }
}

void MainWindow::showTestFiles()
{
    if (nbrItemsListWidget <= 0)
    {
        std::cout << "No item in the list" << std::endl;
        return;
    }
    ui->stackedWidget->setCurrentWidget(ui->map_test_2);
    for (int i = 0; i < ui->list_tests->count(); i++)
    {
        QString fileName = "../tests/" + ui->list_tests->item(i)->text();
        std::cout << fileName.toStdString() << std::endl;
        ui->list_map_test_2->addItem(ui->list_tests->item(i)->text());
    }
}

void MainWindow::launchSelectedStrategy()
{
    if (button_group.checkedId() != -1)
    {
        ui->stackedWidget->setCurrentWidget(ui->menu_start);

        QString filename = button_group.checkedButton()->text();
        std::cout << "path to start file" << filename.toStdString() << std::endl;
        auto stm = make_stm_from_json<action_factory<Context>>(ctx, filename.toStdString(), STRATS_DIR_RPI); //<action_factory<context_vrac>>(ctx, "strat_name", "strat_directory");
        auto manager = new strategyManager(stm);

        return;
    }
    std::cout << "No checked strategy " << std::endl;
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
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));
        std::cout << std::endl;
        if (fileInfo.completeSuffix() == "json")
        {
            QPushButton *btn_test = new QPushButton(fileInfo.completeBaseName());
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
            QPushButton *btn_test = new QPushButton(fileInfo2.completeBaseName());
            push_button_vector.push_back(btn_test);
            btn_test->setMinimumHeight(BTNHEIGHT);
            btn_test->setStyleSheet("QPushButton::checked{background-color: rgb(0,255,0);}");
            btn_test->setCheckable(true);
            grid_strat->addWidget(btn_test);
            button_group.addButton(btn_test);
            std::cout << button_group.id(btn_test) << std::endl;
        }
    }
}

void MainWindow::enable_go_button(void)
{
    if (teamChoice.checkedId() == -1)
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

void MainWindow::init_buttons(void)
{
    button_group.setExclusive(true);

    ui->btn_blue_menu_start->setCheckable(true);
    ui->btn_yellow_menu_start->setCheckable(true);
    ui->btn_blue_menu_start->setStyleSheet("QPushButton::checked{background-color: rgb(0,0,255);}");
    ui->btn_yellow_menu_start->setStyleSheet("QPushButton::checked{background-color: rgb(255,255,0);}");
    teamChoice.addButton(ui->btn_blue_menu_start);
    teamChoice.addButton(ui->btn_yellow_menu_start);
    teamChoice.setExclusive(true);

    ui->stackedWidget->setCurrentWidget(ui->menu);
    connectButtons();
}

void MainWindow::init_playground(void)
{
    QRectF sceneRect(0, 0, playground_width, playground_height);
    QImage image = QIcon(playground_image_resource.data()).pixmap(sceneRect.width(), sceneRect.height()).toImage();

    playground.setSceneRect(sceneRect);
    playground.setBackgroundBrush(image);
    // playground strat
    ui->playground->setAttribute(Qt::WA_AcceptTouchEvents);
    ui->playground->scale(scaling, scaling);
    ui->playground->setScene(&playground);
    // playground test
    ui->playground_test->setAttribute(Qt::WA_AcceptTouchEvents);
    ui->playground_test->scale(scaling, scaling);
    ui->playground_test->setScene(&playground);
}

void MainWindow::init_plants(void)
{
    QPixmap fragile_plant_Pixmap = QPixmap(fragile_plant_ressource.data());
    QPixmap fragile_plant_pot_Pixmap = QPixmap(fragile_plant_pot_ressource.data());
    QPixmap regular_plant_Pixmap = QPixmap(regular_plant_ressource.data());
    QPixmap regular_plant_pot_Pixmap = QPixmap(regular_plant_pot_ressource.data());

    plants.emplaceBack(new Plants(fragile_plant_Pixmap, QRect(200, 200, 500, 500)));

    playground.addItem(plants.back());

    //    fragile_plant.setPixmap(fragile_plant_Pixmap.scaled(fragile_plant_Pixmap.width() * robot_scaling, fragile_plant_Pixmap.height() * robot_scaling));
    //    fragile_plant.setPos(QPointF(100,100));
    //    playground.addItem(&fragile_plant_Pixmap);
}

void MainWindow::init_robot(void)
{
    QPixmap robotPixmap = QPixmap(robot_image_resource.data());
    robot.setPixmap(robotPixmap.scaled(robotPixmap.width() * robot_scaling, robotPixmap.height() * robot_scaling));
    robot.setPos(QPointF(500, 500));
    playground.addItem(&robot);
}

void MainWindow::init_obstacles(void)
{
    QPolygonF leftBorder = {QPointF(-1 * border_gap, -1 * border_gap) , QPointF(-1 * border_gap, playground_height + border_gap)};
    QPolygonF rightBorder = {QPointF(playground_width + border_gap, border_gap) , QPointF(playground_width + border_gap, playground_height + border_gap)};
    QPolygonF upBorder = {QPointF(-1 * border_gap, -1 * border_gap) , QPointF(playground_width + border_gap, border_gap)};
    QPolygonF downBorder = {QPointF(-1 * border_gap, playground_height + border_gap) , QPointF(playground_width + border_gap, playground_height + border_gap)};
    QPolygonF ennemy = QPolygonF(QRectF(QPointF(2100, 1100), QPointF(2200,1900)));

    obstacles.push_back(obstacle(leftBorder));
    obstacles.push_back(obstacle(rightBorder));
    obstacles.push_back(obstacle(upBorder));
    obstacles.push_back(obstacle(downBorder));

    obstacles.push_back(obstacle(QPointF(300, 300), 100, 500));

    playground.on_new_obstacles(obstacles);
}

void MainWindow::init_path_finder(void)
{
    pf.set_hitbox(robot.boundingRect());
    pf.set_current_pos(robot.pos());

    pf.set_obstacles(obstacles);
    pf.set_static_obstacles(obstacles);

    connect(this, &MainWindow::new_goal, &pf, &path_finder<differential>::set_new_goal);
    connect(this, &MainWindow::new_obstacles, &pf, &path_finder<differential>::set_obstacles); // Detection Manager
    connect(this, &MainWindow::new_obstacles, &playground, &playground_scene::on_new_obstacles);
    connect(&pf, &path_finder<differential>::new_path_found, &playground, &playground_scene::on_new_path);
    connect(&robot, &robot_graphic_item::posChanged, &pf, &path_finder<differential>::set_current_pos);
    connect(&pf, &path_finder<differential>::emergency_stop, [](){qDebug() << "emergency stop" << Qt::endl;});

    emit new_goal(QPointF(playground_width/2, playground_height/2), 0);
    emit new_obstacles(obstacles);
}
