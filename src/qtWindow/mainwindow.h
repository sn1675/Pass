#pragma once
#include "qlabel.h"
#include "qlineedit.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <filesystem>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    // Page 0
    void onLoginClicked();
    void onAccountClicked();

private:
    QStackedWidget *m_stack;

    // Page 0 - Login
    QWidget     *m_loginPage;
    QLineEdit   *m_userField;
    QLineEdit   *m_passField;
    QPushButton *m_loginBtn;
    QPushButton *m_accountBtn;
    QLabel      *m_statusLabel;

    // Page 1 - Accueil
    QWidget     *m_homePage;
    QLabel      *m_welcomeLabel;

    // Page 2 - Login
    QWidget     *m_ACPage;
    QLineEdit   *m_ACuserField;
    QLineEdit   *m_ACpassField;
    QPushButton *m_ACregisterBtn;
    QLabel      *m_ACstatusLabel;

};
