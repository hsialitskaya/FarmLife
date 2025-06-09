#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include "../core/World.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void simulateTurn();

private:
    void initializeWorld();
    void updateGUI();
    void paintEvent(QPaintEvent *event);

    World world;
    QGridLayout *gridLayout;
    QTimer *timer;
    QVector<QVector<QLabel*>> labels;

    int gridRows;
    int gridCols;

    int cellSize = 50; 
};