#pragma once
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QScrollArea>
#include <filesystem>
#include <string>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
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
    QWidget      *m_homePage;
    QLabel       *m_welcomeLabel;
    QVBoxLayout  *m_entriesLayout;  // layout recréé à chaque login

    // Page 2 - Création de compte
    QWidget     *m_ACPage;
    QLineEdit   *m_ACuserField;
    QLineEdit   *m_ACpassField;
    QPushButton *m_ACregisterBtn;
    QLabel      *m_ACstatusLabel;

    // Session
    std::filesystem::path m_sessionPath;

    // Helpers
    QWidget* buildCard(QLayout* innerLayout);
    void     loadEntries();
    QWidget* buildEntryCard(const std::string& site,
                            const std::string& username,
                            const std::string& password,
                            const std::string& note);
};
