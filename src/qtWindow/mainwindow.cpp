#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{
    setWindowTitle("Cestionaire");
    setFixedSize(800, 600);

    m_label = new QLabel("Bienvenue", this);
    m_label->setGeometry(290, 200, 200, 30);
    m_label->setAlignment(Qt::AlignCenter);

    m_button = new QPushButton("Connection", this);
    m_button->setGeometry(325, 260, 140, 40);

    connect(m_button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
}

void MainWindow::onButtonClicked() {
    m_label->setText("Bonjour depuis Qt !");
}
