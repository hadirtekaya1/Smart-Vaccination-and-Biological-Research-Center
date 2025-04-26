#ifndef SCHEDULETESTSWIDGET_H
#define SCHEDULETESTSWIDGET_H

#include <QWidget>

namespace Ui {
class ScheduleTestsWidget;
}

class ScheduleTestsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleTestsWidget(QWidget *parent = nullptr);
    ~ScheduleTestsWidget();

signals:
    void backRequested();  // Ajoutez cette ligne dans les signaux

private slots:
    void on_saveButton_clicked();

    void on_backButton_clicked();

private:
    Ui::ScheduleTestsWidget *ui;
};

#endif // SCHEDULETESTSWIDGET_H
