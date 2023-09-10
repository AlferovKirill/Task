#pragma once

#include <QMainWindow>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QPushButton>
#include <QDebug>

#include <vector>

#include "Kinematic.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Interface; }
QT_END_NAMESPACE

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

    bool validateDataFile(const QString& fileName);
public slots:
    void openDataFile();
    void calculate();
    void printResults();
signals:
    void needToUpdate();
private:
    Ui::Interface* ui;
    kin::Kinematic* kinematic;
};
