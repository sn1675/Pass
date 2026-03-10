#ifndef MENUDECONNECTION_H
#define MENUDECONNECTION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MenuDeConnection;
}
QT_END_NAMESPACE

class MenuDeConnection : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuDeConnection(QWidget *parent = nullptr);
    ~MenuDeConnection();

private:
    Ui::MenuDeConnection *ui;
};

#endif
