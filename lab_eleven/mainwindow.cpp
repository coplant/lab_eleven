#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textInput->setReadOnly(true);
    ui->textOutput->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0, "Открыть", "/input.txt", "*.txt");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    if (file.size() != 0)
    {
        words = file.readAll();
    }
    else if (file.exists())
        QMessageBox::critical(this,"", "Файл пуст!");
    ui->textInput->setText(words);
    QRegExp separators("[\\s|\\n|\\r]+");
    wordList = words.split(separators,QString::SkipEmptyParts);
    for (int i = 0; i < wordList.size(); i++)
    {
        if (wordList[i].size() != 4)
        {
            wordList.removeAt(i);
            i--;
        }
    }
    wordList.removeDuplicates();
    wordList.sort();
    newWords = wordList.join("\n");
    ui->textOutput->setText(newWords);
    file.close();
}

void MainWindow::on_pushButtonSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(0, "Сохранить", "/output.txt", "*.txt");
    QFile file(fileName);

    if ((file.size() != 0) && (file.exists()))
    {
        file.remove();
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << newWords;
        QMessageBox::information(0,"","Сохранение успешно!");
        file.close();
    }
    else if (file.exists())
    {
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << newWords;
        QMessageBox::information(0,"","Сохранение успешно!");
        file.close();
    }
}
