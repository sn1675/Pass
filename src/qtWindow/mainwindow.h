#pragma once
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QFrame>
#include <filesystem>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    // Page 0
    void onLoginClicked();
    void onAccountClicked();
    // Page 1
    void onAddPasswordClicked();
    // Page 3
    void onSaveEntryClicked();
    void onBackToHomeClicked();

private:
    // ── Helpers ──────────────────────────────────────
    QWidget* buildCard(QLayout* innerLayout);
    QWidget* buildEntryCard(const std::string& site,
                            const std::string& username,
                            const std::string& password,
                            const std::string& note);
    void loadEntries();

    // ── State ─────────────────────────────────────────
    QStackedWidget*        m_stack;
    std::filesystem::path  m_sessionPath;

    // ── Page 0 — Login ────────────────────────────────
    QWidget*     m_loginPage;
    QLineEdit*   m_userField;
    QLineEdit*   m_passField;
    QPushButton* m_loginBtn;
    QPushButton* m_accountBtn;
    QLabel*      m_statusLabel;

    // ── Page 1 — Accueil ──────────────────────────────
    QWidget*     m_homePage;
    QLabel*      m_welcomeLabel;
    QVBoxLayout* m_entriesLayout;
    QPushButton* m_addPasswordBtn;

    // ── Page 2 — Création de compte ───────────────────
    QWidget*     m_ACPage;
    QLineEdit*   m_ACuserField;
    QLineEdit*   m_ACpassField;
    QPushButton* m_ACregisterBtn;
    QLabel*      m_ACstatusLabel;

    // ── Page 3 — Ajout d'un mot de passe ─────────────
    QWidget*     m_addPage;
    QLineEdit*   m_siteField;
    QLineEdit*   m_usernameEntryField;
    QLineEdit*   m_passwordEntryField;
    QLineEdit*   m_noteField;
    QPushButton* m_saveEntryBtn;
    QPushButton* m_backBtn;
    QLabel*      m_addStatusLabel;
};
