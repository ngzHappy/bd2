#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtCore/qstring.h>
#include <QtWidgets/QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ValueName_editingFinished();
    void on_ValueIndex_valueChanged(int arg1);
    void updateData();
private:
    Ui::MainWindow *ui;
    QString _m_ValueName;
    int _m_ValueIndex=0;
};

#endif // MAINWINDOW_HPP
