#include "mainwindow.h"
#include "../Crypto.hpp"
#include "../../json/json.hpp"
#include <fstream>
#include <QApplication>
#include <QClipboard>
#include <QTimer>

using json = nlohmann::json;

// ─────────────────────────────────────────────
//  GLOBAL STYLESHEET
// ─────────────────────────────────────────────
static const char* APP_STYLE = R"(
    QMainWindow, QWidget {
        background-color: #0f1117;
        color: #e8eaf0;
        font-family: "Segoe UI", "SF Pro Display", "Helvetica Neue", sans-serif;
        font-size: 13px;
    }

    /* ── Card ────────────────────────────────── */
    QWidget#card {
        background-color: #181c27;
        border: 1px solid #262d40;
        border-radius: 16px;
    }

    /* ── Entry card ──────────────────────────── */
    QWidget#entryCard {
        background-color: #13172050;
        border: 1px solid #1e2535;
        border-radius: 12px;
    }

    /* ── Inputs ──────────────────────────────── */
    QLineEdit {
        background-color: #0f1117;
        color: #e8eaf0;
        border: 1px solid #2a3040;
        border-radius: 8px;
        padding: 10px 14px;
        font-size: 13px;
        selection-background-color: #3d7aff;
    }
    QLineEdit:focus {
        border: 1px solid #3d7aff;
        background-color: #111520;
    }

    /* ── Primary button ──────────────────────── */
    QPushButton#primaryBtn {
        background-color: #3d7aff;
        color: #ffffff;
        border: none;
        border-radius: 8px;
        padding: 11px 0;
        font-size: 13px;
        font-weight: 600;
        letter-spacing: 0.3px;
    }
    QPushButton#primaryBtn:hover  { background-color: #5a8fff; }
    QPushButton#primaryBtn:pressed { background-color: #2d64e0; }

    /* ── Ghost button ────────────────────────── */
    QPushButton#ghostBtn {
        background-color: transparent;
        color: #7a8aaa;
        border: 1px solid #262d40;
        border-radius: 8px;
        padding: 10px 0;
        font-size: 12px;
        font-weight: 500;
    }
    QPushButton#ghostBtn:hover {
        color: #aab4cc;
        border-color: #3d7aff;
        background-color: #1a2035;
    }

    /* ── Icon-only button (reveal / copy) ────── */
    QPushButton#iconBtn {
        background-color: #1e2535;
        color: #7a8aaa;
        border: none;
        border-radius: 6px;
        padding: 4px 8px;
        font-size: 11px;
    }
    QPushButton#iconBtn:hover {
        background-color: #263050;
        color: #aab4cc;
    }
    QPushButton#iconBtn:pressed { background-color: #1a2040; }

    /* ── Scroll area ─────────────────────────── */
    QScrollArea {
        background-color: transparent;
        border: none;
    }
    QScrollArea > QWidget > QWidget {
        background-color: transparent;
    }
    QScrollBar:vertical {
        background: #0f1117;
        width: 6px;
        border-radius: 3px;
    }
    QScrollBar::handle:vertical {
        background: #2a3348;
        border-radius: 3px;
        min-height: 20px;
    }
    QScrollBar::add-line:vertical,
QScrollBar::sub-line:vertical { height: 0; }

/* ── Separator ───────────────────────────── */
QFrame#separator {
    color: #1e2433;
    background-color: #1e2433;
    border: none;
    max-height: 1px;
}

/* ── Labels ──────────────────────────────── */
QLabel#titleLabel   { color: #e8eaf0; font-size: 22px; font-weight: 700; letter-spacing: -0.3px; }
QLabel#subtitleLabel{ color: #4a5470; font-size: 12px; letter-spacing: 0.4px; }
QLabel#iconLabel    { color: #3d7aff; font-size: 36px; }
QLabel#sectionLabel { color: #4a5470; font-size: 11px; font-weight: 600; letter-spacing: 1.2px; }
QLabel#errorLabel   { color: #ff5c5c; font-size: 12px; }

QLabel#welcomeTitle { color: #e8eaf0; font-size: 20px; font-weight: 700; }
QLabel#countLabel   { color: #4a5470; font-size: 12px; }

QLabel#siteLabel    { color: #e8eaf0; font-size: 13px; font-weight: 600; }
QLabel#userLabel    { color: #7a8aaa; font-size: 12px; }
QLabel#noteLabel    { color: #4a5470; font-size: 11px; font-style: italic; }
QLabel#passLabel    { color: #3d7aff; font-size: 12px; font-family: "Courier New", monospace; }
QLabel#emptyLabel   { color: #3a4055; font-size: 13px; }
)";


// ─────────────────────────────────────────────
//  Helper: padded card
// ─────────────────────────────────────────────
QWidget* MainWindow::buildCard(QLayout* innerLayout) {
    QWidget* card = new QWidget();
    card->setObjectName("card");
    card->setLayout(innerLayout);
    innerLayout->setContentsMargins(28, 28, 28, 28);
    if (auto* vb = qobject_cast<QVBoxLayout*>(innerLayout))
        vb->setSpacing(12);
    return card;
}


// ─────────────────────────────────────────────
//  Helper: one password entry card
// ─────────────────────────────────────────────
QWidget* MainWindow::buildEntryCard(const std::string& site,
                                    const std::string& username,
                                    const std::string& password,
                                    const std::string& note)
{
    QWidget* card = new QWidget();
    card->setObjectName("entryCard");

    QVBoxLayout* vl = new QVBoxLayout(card);
    vl->setContentsMargins(16, 14, 16, 14);
    vl->setSpacing(6);

    // — Site + copy button on the same row —
    QHBoxLayout* topRow = new QHBoxLayout();
    topRow->setSpacing(8);

    QLabel* siteLabel = new QLabel(QString::fromStdString(site));
    siteLabel->setObjectName("siteLabel");

    QPushButton* copyBtn = new QPushButton("📋 Copier");
    copyBtn->setObjectName("iconBtn");
    copyBtn->setFixedHeight(24);
    copyBtn->setCursor(Qt::PointingHandCursor);
    copyBtn->setToolTip("Copier le mot de passe");

    topRow->addWidget(siteLabel);
    topRow->addStretch();
    topRow->addWidget(copyBtn);

    // — Username —
    QLabel* userLabel = new QLabel("👤  " + QString::fromStdString(username));
    userLabel->setObjectName("userLabel");

    // — Password row (masked by default) —
    QHBoxLayout* passRow = new QHBoxLayout();
    passRow->setSpacing(8);

    QString maskedPass = QString(password.size(), QChar(0x2022)); // ●●●●
    QLabel* passLabel = new QLabel(maskedPass);
    passLabel->setObjectName("passLabel");

    QPushButton* revealBtn = new QPushButton("👁 Afficher");
    revealBtn->setObjectName("iconBtn");
    revealBtn->setFixedHeight(24);
    revealBtn->setCursor(Qt::PointingHandCursor);
    revealBtn->setCheckable(true);

    passRow->addWidget(passLabel);
    passRow->addStretch();
    passRow->addWidget(revealBtn);

    // — Note (optional) —
    QLabel* noteLabel = nullptr;
    if (!note.empty() && note != "exemplemdp") {
        noteLabel = new QLabel("📝  " + QString::fromStdString(note));
        noteLabel->setObjectName("noteLabel");
    }

    vl->addLayout(topRow);
    vl->addWidget(userLabel);
    vl->addLayout(passRow);
    if (noteLabel) vl->addWidget(noteLabel);

    // — Connections —
    QString pwd = QString::fromStdString(password);

    connect(revealBtn, &QPushButton::toggled, [=](bool checked) {
        if (checked) {
            passLabel->setText(pwd);
            revealBtn->setText("🙈 Masquer");
        } else {
            passLabel->setText(QString(pwd.size(), QChar(0x2022)));
            revealBtn->setText("👁 Afficher");
        }
    });

    connect(copyBtn, &QPushButton::clicked, [=]() {
        QApplication::clipboard()->setText(pwd);
        copyBtn->setText("✅ Copié !");
        QTimer::singleShot(2000, [=]() { copyBtn->setText("📋 Copier"); });
    });

    return card;
}


// ─────────────────────────────────────────────
//  Load entries from mdp.json into m_entriesLayout
// ─────────────────────────────────────────────
void MainWindow::loadEntries() {
    // Clear previous entries (keep only header items: 0..3)
    while (m_entriesLayout->count() > 4) {
        QLayoutItem* item = m_entriesLayout->takeAt(4);
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }

    std::filesystem::path jsonPath = m_sessionPath / "mdp.json";
    std::ifstream file(jsonPath);
    if (!file) return;

    json data;
    try { file >> data; } catch (...) { return; }

    if (!data.contains("entries") || data["entries"].empty()) {
        QLabel* empty = new QLabel("Aucun mot de passe enregistré");
        empty->setObjectName("emptyLabel");
        empty->setAlignment(Qt::AlignCenter);
        m_entriesLayout->addWidget(empty);
        return;
    }

    // Update count label (index 2 in layout = countLabel)
    if (auto* lbl = qobject_cast<QLabel*>(m_entriesLayout->itemAt(2)->widget())) {
        int n = data["entries"].size();
        lbl->setText(QString::number(n) + " entrée" + (n > 1 ? "s" : ""));
    }

    for (const auto& entry : data["entries"]) {
        std::string site     = entry.value("site",     "—");
        std::string username = entry.value("username", "—");
        std::string password = entry.value("password", "");
        std::string note     = entry.value("note",     "");

        m_entriesLayout->addWidget(buildEntryCard(site, username, password, note));
    }

    m_entriesLayout->addStretch();
}


// ─────────────────────────────────────────────
//  Constructor
// ─────────────────────────────────────────────
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("Cestionaire");
    setFixedSize(520, 680);
    setStyleSheet(APP_STYLE);

    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);


    // ══════════════════════════════════════════
    //  PAGE 0 — Login
    // ══════════════════════════════════════════
    m_loginPage = new QWidget();
    QVBoxLayout* loginOuter = new QVBoxLayout(m_loginPage);
    loginOuter->setAlignment(Qt::AlignCenter);
    loginOuter->setContentsMargins(56, 0, 56, 0);

    QVBoxLayout* loginCard = new QVBoxLayout();

    QLabel* loginTitle = new QLabel("Cestionaire");
    loginTitle->setObjectName("titleLabel");
    loginTitle->setAlignment(Qt::AlignCenter);

    QFrame* sep1 = new QFrame(); sep1->setObjectName("separator"); sep1->setFrameShape(QFrame::HLine);

    QLabel* connLabel = new QLabel("CONNEXION");
    connLabel->setObjectName("sectionLabel");

    m_userField = new QLineEdit();
    m_userField->setPlaceholderText("Nom d'utilisateur");

    m_passField = new QLineEdit();
    m_passField->setPlaceholderText("Mot de passe");
    m_passField->setEchoMode(QLineEdit::Password);

    m_loginBtn = new QPushButton("Se connecter");
    m_loginBtn->setObjectName("primaryBtn");
    m_loginBtn->setCursor(Qt::PointingHandCursor);

    m_accountBtn = new QPushButton("Créer un compte");
    m_accountBtn->setObjectName("ghostBtn");
    m_accountBtn->setCursor(Qt::PointingHandCursor);

    m_statusLabel = new QLabel("");
    m_statusLabel->setObjectName("errorLabel");
    m_statusLabel->setAlignment(Qt::AlignCenter);

    loginCard->addWidget(loginTitle);
    loginCard->addSpacing(4);
    loginCard->addWidget(sep1);
    loginCard->addSpacing(4);
    loginCard->addWidget(connLabel);
    loginCard->addWidget(m_userField);
    loginCard->addWidget(m_passField);
    loginCard->addSpacing(4);
    loginCard->addWidget(m_loginBtn);
    loginCard->addWidget(m_accountBtn);
    loginCard->addWidget(m_statusLabel);

    loginOuter->addWidget(buildCard(loginCard));


    // ══════════════════════════════════════════
    //  PAGE 1 — Accueil (scroll + entries)
    // ══════════════════════════════════════════
    m_homePage = new QWidget();
    QVBoxLayout* homeOuter = new QVBoxLayout(m_homePage);
    homeOuter->setContentsMargins(20, 20, 20, 20);
    homeOuter->setSpacing(0);

    // Header card (fixe)
    QWidget* headerCard = new QWidget();
    headerCard->setObjectName("card");
    QHBoxLayout* headerLayout = new QHBoxLayout(headerCard);
    headerLayout->setContentsMargins(20, 16, 20, 16);

    QVBoxLayout* headerText = new QVBoxLayout();
    headerText->setSpacing(2);

    m_welcomeLabel = new QLabel("Bienvenue !");
    m_welcomeLabel->setObjectName("welcomeTitle");

    headerLayout->addLayout(headerText);
    headerLayout->addStretch();

    homeOuter->addWidget(headerCard);
    homeOuter->addSpacing(12);

    // Scroll area for entries
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget* scrollContent = new QWidget();
    scrollContent->setStyleSheet("background: transparent;");

    m_entriesLayout = new QVBoxLayout(scrollContent);
    m_entriesLayout->setContentsMargins(0, 0, 6, 0);
    m_entriesLayout->setSpacing(8);

    // These 4 items are always present (indices 0..3):
    // 0: section label
    // 1: separator
    // 2: countLabel (set dynamically)
    // 3: (spacing item handled via addSpacing — use a dummy widget instead)

    QLabel* mdpSection = new QLabel("MES MOTS DE PASSE");
    mdpSection->setObjectName("sectionLabel");
    m_entriesLayout->addWidget(mdpSection);              // index 0

    QFrame* sep2 = new QFrame();
    sep2->setObjectName("separator");
    sep2->setFrameShape(QFrame::HLine);
    m_entriesLayout->addWidget(sep2);                    // index 1

    // Placeholder count label that loadEntries() will update via itemAt(2)
    QLabel* countPlaceholder = new QLabel("");
    countPlaceholder->setObjectName("countLabel");
    countPlaceholder->hide();
    m_entriesLayout->addWidget(countPlaceholder);        // index 2

    // Spacer widget so index 3 exists (loadEntries keeps items 0..3)
    QLabel* spacerItem = new QLabel("");
    spacerItem->setFixedHeight(4);
    m_entriesLayout->addWidget(spacerItem);              // index 3

    scrollArea->setWidget(scrollContent);
    homeOuter->addWidget(scrollArea);


    // ══════════════════════════════════════════
    //  PAGE 2 — Création de compte
    // ══════════════════════════════════════════
    m_ACPage = new QWidget();
    QVBoxLayout* ACOuter = new QVBoxLayout(m_ACPage);
    ACOuter->setAlignment(Qt::AlignCenter);
    ACOuter->setContentsMargins(56, 0, 56, 0);

    QVBoxLayout* ACCard = new QVBoxLayout();

    QLabel* acTitle = new QLabel("Nouveau compte");
    acTitle->setObjectName("titleLabel");
    acTitle->setAlignment(Qt::AlignCenter);

    QFrame* sep3 = new QFrame(); sep3->setObjectName("separator"); sep3->setFrameShape(QFrame::HLine);

    QLabel* acSection = new QLabel("INFORMATIONS");
    acSection->setObjectName("sectionLabel");

    m_ACuserField = new QLineEdit();
    m_ACuserField->setPlaceholderText("Nom d'utilisateur");

    m_ACpassField = new QLineEdit();
    m_ACpassField->setPlaceholderText("Mot de passe maître");
    m_ACpassField->setEchoMode(QLineEdit::Password);

    m_ACregisterBtn = new QPushButton("Créer le compte");
    m_ACregisterBtn->setObjectName("primaryBtn");
    m_ACregisterBtn->setCursor(Qt::PointingHandCursor);

    m_ACstatusLabel = new QLabel("");
    m_ACstatusLabel->setObjectName("errorLabel");
    m_ACstatusLabel->setAlignment(Qt::AlignCenter);

    ACCard->addWidget(acTitle);
    ACCard->addSpacing(4);
    ACCard->addWidget(sep3);
    ACCard->addSpacing(4);
    ACCard->addWidget(acSection);
    ACCard->addWidget(m_ACuserField);
    ACCard->addWidget(m_ACpassField);
    ACCard->addSpacing(4);
    ACCard->addWidget(m_ACregisterBtn);
    ACCard->addWidget(m_ACstatusLabel);

    ACOuter->addWidget(buildCard(ACCard));


    // ══════════════════════════════════════════
    //  Stack
    // ══════════════════════════════════════════
    m_stack->addWidget(m_loginPage);   // 0
    m_stack->addWidget(m_homePage);    // 1
    m_stack->addWidget(m_ACPage);      // 2
    m_stack->setCurrentIndex(0);

    connect(m_loginBtn,   &QPushButton::clicked,     this, &MainWindow::onLoginClicked);
    connect(m_passField,  &QLineEdit::returnPressed, this, &MainWindow::onLoginClicked);
    connect(m_accountBtn, &QPushButton::clicked,     this, &MainWindow::onAccountClicked);
}


// ─────────────────────────────────────────────
//  Slots
// ─────────────────────────────────────────────
void MainWindow::onLoginClicked() {
    QString user = m_userField->text().trimmed();
    QString pass = m_passField->text();

    std::filesystem::path userPath = std::filesystem::path("../users") / user.toStdString();

    if (!std::filesystem::exists(userPath)) {
        m_statusLabel->setText("Utilisateur introuvable");
        return;
    }

    if (Crypto::verifyMasterPassword(pass.toStdString(),
        Crypto::get(userPath / ".env", "PASSWORD_HASH"),
                                     Crypto::get(userPath / ".env", "SALT"))) {
        m_sessionPath = userPath;
    m_welcomeLabel->setText("Bienvenue, " + user + " !");
    loadEntries();
    m_stack->setCurrentIndex(1);
    m_statusLabel->clear();
                                     } else {
                                         m_statusLabel->setText("Identifiants incorrects");
                                     }
}

void MainWindow::onAccountClicked() {
    m_stack->setCurrentIndex(2);
}
