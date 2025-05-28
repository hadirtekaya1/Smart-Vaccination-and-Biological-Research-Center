#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT;

public:
    explicit HistoryDialog(QWidget *parent = nullptr);
    ~HistoryDialog();
    void setHistory(const QStringList &history);

signals:
    void historyCleared();

private slots:
    void on_btnClose_clicked();
    void on_btnClear_clicked();

private:
    Ui::HistoryDialog *ui;
    QStringListModel *model;
};

#endif // HISTORYDIALOG_H
