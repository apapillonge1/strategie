#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamestate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), stackedWidget(new QStackedWidget), test_strat("./../test_strat")
{
    ui->setupUi(this);
    QRectF scene_rect(0, 0, 3000, 2000);
    GameState::get()->playground().setSceneRect(scene_rect);
    QImage image = QIcon(":/ressources/images/vinyles_table_2024_BETA.svg").pixmap(scene_rect.width(), scene_rect.height()).toImage();
    GameState::get()->playground().setBackgroundBrush(image);

    ui->playground->scale(0.2, 0.2);
    ui->playground->setScene(&GameState::get()->playground());

    ui->playground_test->scale(0.2, 0.2);
    ui->playground_test->setScene(&GameState::get()->playground());

    ui->stackedWidget->setCurrentIndex(0); // index stack widget : (0: menu 1: 2: 3: map)
    connectButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectButtons()
{
    // menu connect

    connect(ui->btn_start_menu, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->strategie); });
    connect(ui->btn_tests_menu, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->Tests); });

    // test connect
    connect(ui->btn_close_tests, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu); });
    connect(ui->btn_close_map_test, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->Tests); });
    connect(ui->btn_start_tests, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->map_test_2); });
    connect(ui->btn_suppr_tests, &QPushButton::clicked, this, &MainWindow::on_btn_suppr_test_clicked);

    // stratégie connect
    connect(ui->btn_close_strategie, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu); });
    connect(ui->btn_start_strategie, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu_start); });

    // start connect

    connect(ui->btn_close_menu_start, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->strategie); });
    connect(ui->btn_go_menu_start, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->map_start); });
    connect(ui->btn_close_map_start, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu_start); });
    connect(ui->btn_start_map_start, &QPushButton::clicked, this, [this]()
            { ui->stackedWidget->setCurrentWidget(ui->menu); });

    // lecture du fichier et création de bouton avec leurs noms
    test_strat.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    test_strat.setSorting(QDir::Size | QDir::Reversed);

    QWidget *client = new QWidget(this);
    QGridLayout *grid_test = new QGridLayout(client);
    client->setLayout(grid_test);

    ui->scrollArea->setWidget(client);

    QFileInfoList list = test_strat.entryInfoList();
    std::cout << "fichier present : " << std::endl;

    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10).arg(fileInfo.fileName()));
        std::cout << std::endl;
        if (fileInfo.completeSuffix() == "json")
        {
            QPushButton *btn_test = new QPushButton(fileInfo.fileName());
            btn_test->setFixedHeight(75);
            grid_test->addWidget(btn_test);
            connect(btn_test, &QPushButton::clicked, this, &MainWindow::add_to_test_list);
        }
    }
}

// Class pour ajout de la croix pas encore fonctionnel
class CustomListItemWidget : public QWidget {
public:
    CustomListItemWidget(const QString& labelText, QListWidget* parentListWidget) : QWidget(parentListWidget) {
        QHBoxLayout* layout = new QHBoxLayout(this);

        QLabel* label = new QLabel(labelText, this);
        layout->addWidget(label);

        QPushButton* closeButton = new QPushButton("X", this);
        layout->addWidget(closeButton);

        //connect(closeButton, &QPushButton::clicked, [parentListWidget, this]() {
        //    int index = parentListWidget->row((const QListWidgetItem*)(this));
        //    if (index >= 0) {
        //        QListWidgetItem* item = parentListWidget->takeItem(index);
        //        delete item;
        //    }
        //});
    }
};

void MainWindow::add_to_test_list()
{
    QPushButton *btn = static_cast<QPushButton *>(sender());
    ui->list_tests->setDragEnabled(true);
    ui->list_tests->setDragDropMode(QAbstractItemView::InternalMove);
    ui->list_tests->setAcceptDrops(true);
    QListWidgetItem *item = new QListWidgetItem(btn->text());
    ui->list_tests->addItem(item);
    //ui->list_tests->addItem(btn->text());
    std::cout << btn->text().toStdString() << std::endl;


    //Utilisation de la classe fonctionne pas encore

    //CustomListItemWidget* customWidget = new CustomListItemWidget(btn->objectName(), ui->list_tests);
    //QListWidgetItem* item = new QListWidgetItem(ui->list_tests);
    //item->setSizeHint(customWidget->sizeHint());
    //ui->list_tests->setItemWidget(item, customWidget);
}

void MainWindow::on_btn_suppr_test_clicked()
{
    foreach (QListWidgetItem *ligne, ui->list_tests->selectedItems())
    {
        delete ui->list_tests->takeItem(ui->list_tests->row(ligne));
    }
}





