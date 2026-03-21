#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QPushButton *m_button;
    QLabel      *m_label;
};
