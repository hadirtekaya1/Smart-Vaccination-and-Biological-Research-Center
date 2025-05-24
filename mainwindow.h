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
    void on_sendButton_clicked();                 // Send button for text input
    void on_option1Button_clicked();              // Predefined question 1
    void on_option2Button_clicked();              // Predefined question 2
    void on_option3Button_clicked();              // Predefined question 3
    void on_option4Button_clicked();
    void on_option5Button_clicked();
private:
    Ui::MainWindow *ui;

    QString getResponse(const QString &message);  // Chatbot logic
    void handleUserInput(const QString &input);   // Unified handler for input
};

#endif // MAINWINDOW_H
