#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QGraphicsRectItem>
#include <random>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Window settings
    this->setWindowTitle("Star Field");

    // Misc
    srand(time(0));

    // Create the layouts
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QHBoxLayout *viewLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(viewLayout);

    // Create buttons, scene and view
    QPushButton *btn = new QPushButton("Right click and drag the mouse around...");
    buttonLayout->addWidget(btn);

    m_view = new QGraphicsView();
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setBackgroundBrush(QBrush(QColor("#1F1F1F")));
    viewLayout->addWidget(m_view);
    m_scene = new FieldScene(QRectF(), m_view, this);
    m_view->setScene(m_scene);

    QWidget *dummy = new QWidget(this);
    dummy->setLayout(mainLayout);
    this->setCentralWidget(dummy);

    m_view->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}
