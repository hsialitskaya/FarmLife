#include "MainWindow.h"
#include <QDebug>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      gridLayout(new QGridLayout),
      gridRows(world.getWorldX()), 
      gridCols(world.getWorldY())
{

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(gridLayout);

  
    labels.resize(gridRows, QVector<QLabel*>(gridCols));
    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            QLabel *label = new QLabel();
            label->setFixedSize(cellSize, cellSize);
            label->setStyleSheet("border: 1px solid black;");
            label->setAlignment(Qt::AlignCenter);
            gridLayout->addWidget(label, i, j);
            labels[i][j] = label;
        }
    }

    initializeWorld();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::simulateTurn);
    timer->start(2000);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    
    // Ładowanie obrazka tła
    QPixmap backgroundPixmap(":/images/background.jpg");
    
    if (!backgroundPixmap.isNull()) {
        // Skalowanie obrazka tła na rozmiar okna
        painter.drawPixmap(0, 0, width(), height(), backgroundPixmap);
    } else {
        qDebug() << "Nie udało się załadować obrazu tła!";
    }
    
    QMainWindow::paintEvent(event); 
}

void MainWindow::initializeWorld() {
    // Łączna liczba organizmów
    int totalOrganisms = 20;

    QVector<std::string> organismTypes;
    for (const auto& pair : OrganismCreator::creator) {
        organismTypes.push_back(pair.first);
    }

    // Lista dostępnych pozycji
    QVector<Position> availablePositions;
    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            availablePositions.append(Position(i, j));
        }
    }

    // Inicjalizacja generatora liczb losowych
    srand(static_cast<unsigned int>(time(0)));

    // Rozmieszczanie organizmów
    for (int i = 0; i < totalOrganisms; ++i) {
        // Losowanie typu organizmu 
        std::string type = organismTypes[rand() % organismTypes.size()];

        // Wybieramy losową pozycję
        int randomIndex = rand() % availablePositions.size();
        Position randomPosition = availablePositions[randomIndex];

        // Tworzymy organizm i dodajemy go do świata
        world.addOrganism(OrganismCreator::createOrganism(type, randomPosition));

        // Usuwamy wybraną pozycję z dostępnych
        availablePositions.remove(randomIndex);
    }

    updateGUI();
}


void MainWindow::simulateTurn() {
    world.makeTurn();
    updateGUI();
}

void MainWindow::updateGUI() {
    for (int i = 0; i < gridRows; ++i) {
        for (int j = 0; j < gridCols; ++j) {
            Position pos{i, j};
            Organism *org = world.getOrganismFromPosition(pos);
            QLabel *label = labels[i][j];

            if (org) {
                QPixmap pixmap;
                switch (org->getType()) {
                    case 'G': 
                        pixmap = QPixmap(":/images/grass.jpg");
                        break;
                    case 'W': 
                        pixmap = QPixmap(":/images/wolf.jpg");
                        break;
                    case 'S': 
                        pixmap = QPixmap(":/images/sheep.jpg");
                        break;
                    case 'T': 
                        pixmap = QPixmap(":/images/amanita.jpg");
                        break;
                    case 'D': 
                        pixmap = QPixmap(":/images/dandelion.jpg");
                        break;
                    case 'B':
                        pixmap = QPixmap(":/images/bear.jpg");
                        break;
                    case 'E':
                        pixmap = QPixmap(":/images/berries.jpg");
                        break;
                    case 'L':
                        pixmap = QPixmap(":/images/clover.jpg");
                        break;
                    case 'C':
                        pixmap = QPixmap(":/images/cow.jpg");
                        break;
                    case 'K':
                        pixmap = QPixmap(":/images/goat.jpg");
                        break;
                    case 'H':
                        pixmap = QPixmap(":/images/hare.jpg");
                        break;
                    case 'I':
                        pixmap = QPixmap(":/images/pig.jpg");
                        break;
                    default: 
                        pixmap = QPixmap(); // domyślny pusty obrazek
                        break;
                }
                
                if (pixmap.isNull()) {
                    qDebug() << "Nie udało się załadować obrazu dla typu:" << org->getType();
                    label->clear();
                } else {
                    label->setPixmap(pixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
                }
            } else {
                label->clear();
            }
        }
    }
}
