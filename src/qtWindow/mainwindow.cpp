#include "mainwindow.h"
#include "../Crypto.hpp"
#include "qlineedit.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Cestionaire");
    setFixedSize(800, 600);

    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);

    // ########################## Page0: login ##########################
    m_loginPage = new QWidget();
    QVBoxLayout *loginLayout = new QVBoxLayout(m_loginPage);
    loginLayout->setAlignment(Qt::AlignCenter);

    m_userField = new QLineEdit();
    m_userField->setPlaceholderText("Nom d'utilisateur");
    m_userField->setMaximumWidth(300);

    m_passField = new QLineEdit();
    m_passField->setPlaceholderText("Mot de passe");
    m_passField->setEchoMode(QLineEdit::Password);
    m_passField->setMaximumWidth(300);

    m_loginBtn = new QPushButton("Se connecter");
    m_loginBtn->setMaximumWidth(300);

    m_accountBtn = new QPushButton("Crée un compte");
    m_accountBtn->setMaximumWidth(300);

    m_statusLabel = new QLabel("");
    m_statusLabel->setAlignment(Qt::AlignCenter);

    loginLayout->addWidget(m_userField);
    loginLayout->addWidget(m_passField);
    loginLayout->addWidget(m_loginBtn);
    loginLayout->addWidget(m_accountBtn);
    loginLayout->addWidget(m_statusLabel);

    // ########################## Page1 : acceuil ##########################
    m_homePage = new QWidget();
    QVBoxLayout *homeLayout = new QVBoxLayout(m_homePage);
    homeLayout->setAlignment(Qt::AlignCenter);

    m_welcomeLabel = new QLabel("Bienvenue !");
    m_welcomeLabel->setAlignment(Qt::AlignCenter);
    m_welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    homeLayout->addWidget(m_welcomeLabel);

    // ########################## Page2 : Creation de compte ##########################
    m_ACPage = new QWidget();
    QVBoxLayout *ACLayout = new QVBoxLayout(m_accountBtn);

    m_ACuserField = new QLineEdit();
    m_ACuserField->setPlaceholderText("Nom d'utilisateur");
    m_ACuserField->setMaximumWidth(300);

    m_ACpassField = new QLineEdit();
    m_ACpassField->setPlaceholderText("Mot de passe");
    m_ACpassField->setEchoMode(QLineEdit::Password);
    m_ACpassField->setMaximumWidth(300);

    m_ACregisterBtn = new QPushButton("Crée compte");
    m_ACregisterBtn->setMaximumWidth(300);

    m_ACstatusLabel = new QLabel("");
    m_ACstatusLabel->setAlignment(Qt::AlignCenter);

    ACLayout->addWidget(m_ACuserField);
    ACLayout->addWidget(m_ACpassField);
    ACLayout->addWidget(m_ACregisterBtn);
    ACLayout->addWidget(m_ACstatusLabel);

    // ########################## ajout de pages ##########################
    m_stack->addWidget(m_loginPage);   // index 0
    m_stack->addWidget(m_homePage);    // index 1
    m_stack->addWidget(m_ACPage);
    m_stack->setCurrentIndex(0);       // démarre sur le login

    // Functions for Page 0
    connect(m_loginBtn, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(m_passField, &QLineEdit::returnPressed, this, &MainWindow::onLoginClicked);

    connect(m_accountBtn, &QPushButton::clicked, this, &MainWindow::onAccountClicked);

    // Functions for Page 1

}

void MainWindow::onLoginClicked() {
    QString user = m_userField->text();
    QString pass = m_passField->text();

    std::filesystem::path userPath = std::filesystem::path("../users") / user.toStdString();

    if (!std::filesystem::exists(userPath)) {
        m_statusLabel->setStyleSheet("color: red");
        m_statusLabel->setText("Utilisateur introuvable");
        return;
    }

    if (Crypto::verifyMasterPassword(pass.toStdString(), Crypto::get(userPath / ".env", "PASSWORD_HASH"), Crypto::get(userPath / ".env", "SALT"))) {
        // ✅ Connexion réussie → on passe à la page d'accueil
        m_welcomeLabel->setText("Bienvenue, " + user + " !");
        m_stack->setCurrentIndex(1); // Page Acceuil
    } else {
        m_statusLabel->setStyleSheet("color: red");
        m_statusLabel->setText("Identifiants incorrects");
    }
}

void MainWindow::onAccountClicked(){
    m_stack->setCurrentIndex(2); // Page account
}
