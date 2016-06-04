#include "MainWindow.h"

// Qt
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Create an empty QWidget with 'this' as parent
    myWidget = new QWidget(this);

    // Create a layout manager for myWidget
    myLayout = new QHBoxLayout();

    // Set the layout manager of myWidget
    // MainWindow takes the ownership of myLayout (parenting)
    myWidget->setLayout(myLayout);

    // Create button quit and start
    quit = new QPushButton("Quitter");
    start = new QPushButton("Start");

    // Add buttons to myLayout, MainWindow takes ownership of them (parenting)
    myLayout->addWidget(quit);
    myLayout->addWidget(start);

    // Load the image
    label = new QLabel();
    label->setPixmap(QPixmap("../ressource/circuit.jpeg"));

    // Add label to myLayout, MainWindow takes ownership of it (parenting)
    myLayout->addWidget(label);

    // Connect quit button signal to close program slot
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    setCentralWidget(myWidget);
}

MainWindow::~MainWindow()
{
    // myWidget is automaticaly delete by MainWindow
    // so myLayout is from myWidget (parenting)
    // so quit and start are from myLayout (parenting)
    // so label is from myLayout (parenting)
}
