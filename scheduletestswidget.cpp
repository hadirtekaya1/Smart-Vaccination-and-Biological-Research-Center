#include "scheduletestswidget.h"
#include "ui_scheduletestswidget.h"
#include <QMessageBox>

ScheduleTestsWidget::ScheduleTestsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleTestsWidget)
{
    ui->setupUi(this);
    connect(ui->backButton, &QPushButton::clicked, this, [this]() {
        emit backRequested();
        this->close();
    });

}

ScheduleTestsWidget::~ScheduleTestsWidget()
{
    delete ui;
}
void ScheduleTestsWidget::on_saveButton_clicked()
{
    QString testName = ui->testNameLineEdit->text();
    QDate testDate = ui->testDateEdit->date();

    if (testName.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Please enter a test name.");
        return;
    }

    QMessageBox::information(this, "Saved", "Test \"" + testName + "\" scheduled for " + testDate.toString());
}



void ScheduleTestsWidget::on_backButton_clicked()
{
    this->hide();
    this->show();

}

