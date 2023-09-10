#include "Interface.h"
#include "ui_Interface.h"

Interface::Interface(QWidget *parent) : QMainWindow(parent), ui(new Ui::Interface) {
    ui->setupUi(this);
    setWindowTitle("Direct Kinematic Problem");

    kinematic = new kin::Kinematic;

    ui->doubleSpinBox_1->setRange(-180, 180);
    ui->doubleSpinBox_2->setRange(-180, 180);
    ui->doubleSpinBox_3->setRange(-180, 180);
    ui->doubleSpinBox_4->setRange(-180, 180);
    ui->doubleSpinBox_5->setRange(-180, 180);
    ui->doubleSpinBox_6->setRange(-180, 180);

    connect(ui->actionOpen_data_file, &QAction::triggered, this, &Interface::openDataFile);
    connect(this, &Interface::needToUpdate, this, &Interface::printResults);
    connect(ui->pushButton, &QPushButton::clicked, this, &Interface::calculate);
}

bool Interface::validateDataFile(const QString& fileName) {
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    int lineCount = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        bool isNumber;
        line.toDouble(&isNumber);

        if (!isNumber) {
            file.close();
            return false;
        }

        lineCount++;
    }

    file.close();
    return lineCount == 6;
}

void Interface::openDataFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Текстовые файлы (*.txt)");
    std::vector<double> thetaDegrees;

    if (validateDataFile(fileName)) {
        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);

            while (!in.atEnd()) {
                QString line = in.readLine();
                thetaDegrees.push_back(line.toDouble());
            }

            kinematic->setThetaDegrees(std::move(thetaDegrees));
            file.close();
            emit needToUpdate();
        }
    }
}

void Interface::calculate() {
    std::vector<double> thetaDegrees(6, 0);

    thetaDegrees[0] = ui->doubleSpinBox_1->value();
    thetaDegrees[1] = ui->doubleSpinBox_2->value();
    thetaDegrees[2] = ui->doubleSpinBox_3->value();
    thetaDegrees[3] = ui->doubleSpinBox_4->value();
    thetaDegrees[4] = ui->doubleSpinBox_5->value();
    thetaDegrees[5] = ui->doubleSpinBox_6->value();

    kinematic->setThetaDegrees(std::move(thetaDegrees));
    emit needToUpdate();
}

void Interface::printResults() {
    std::vector<double> coordinates = kinematic->finalTransformMatrix();

    ui->xLabel->setText(QString("x = ") + QString::number(coordinates[0]));
    ui->yLabel->setText(QString("y = ") + QString::number(coordinates[1]));
    ui->zLabel->setText(QString("z = ") + QString::number(coordinates[2]));

    std::vector<double> newThetaDegrees = kinematic->getThetaDegrees();

    ui->doubleSpinBox_1->setValue(newThetaDegrees[0]);
    ui->doubleSpinBox_2->setValue(newThetaDegrees[1]);
    ui->doubleSpinBox_3->setValue(newThetaDegrees[2]);
    ui->doubleSpinBox_4->setValue(newThetaDegrees[3]);
    ui->doubleSpinBox_5->setValue(newThetaDegrees[4]);
    ui->doubleSpinBox_6->setValue(newThetaDegrees[5]);
}

Interface::~Interface() {
    delete ui;
    delete kinematic;
}

