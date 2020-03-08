#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButtonOpen_clicked();

    void on_pushButtonSave_clicked();
private:
    Ui::MainWindow *ui;
    QString words, newWords;
    QStringList wordList;
};
#endif // MAINWINDOW_H
