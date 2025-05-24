#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString userMessage = ui->userInput->text().trimmed();
    if (!userMessage.isEmpty()) {
        handleUserInput(userMessage);
        ui->userInput->clear();
    }
}

void MainWindow::handleUserInput(const QString &input)
{
    ui->chatDisplay->append("You: " + input);
    ui->chatDisplay->append("Bot is typing...");

    QTimer::singleShot(1000, this, [=]() {
        QString currentText = ui->chatDisplay->toPlainText();
        QString updatedText = currentText;
        updatedText.chop(QString("Bot is typing...\n").length());
        ui->chatDisplay->setPlainText(updatedText);

        QString reply = getResponse(input);
        ui->chatDisplay->append("Bot: " + reply);
    });
}

QString MainWindow::getResponse(const QString &message)
{
    QString msg = message.toLower();

    // Vaccine type
    if (msg.contains("primary vaccine") && msg.contains("booster vaccine")){
        return "Primary vaccines are the initial doses required to build immunity, while Booster vaccines enhance or restore protection that may have faded over time.";
        // Vaccine manufacturers
    } else if (msg.contains("sanofi")) {
        return "Sanofi Pasteur produces vaccines for various diseases including influenza.";
    } else if (msg.contains("novavax")) {
        return "Novavax's COVID-19 vaccine is protein-based and a good alternative to mRNA vaccines.";
    } else if (msg.contains("glaxosmithkline") || msg.contains("gsk")) {
        return "GlaxoSmithKline (GSK) is known for vaccines against hepatitis, shingles, and more.";
    }
    else if (msg.contains("pfizer")) {
        return "pfizer is known for vaccines against COVID-19.";
    } else if (msg.contains("moderna")) {
        return "Moderna is one of the leading mRNA COVID-19 vaccine producers.";
    } else if (msg.contains("astrazeneca")) {
        return "AstraZeneca offers a viral vector COVID-19 vaccine with high global use.";

        // Common questions
    } else if (msg.contains("side effects")) {
        return "Common side effects include fever, headache, and fatigue.";
    } else if (msg.contains("which vaccine is best") || msg.contains("best vaccine")) {
        return "All approved vaccines are safe and effective. Consult your doctor for personalized advice.";
    } else if (msg.contains("kids") || msg.contains("children")) {
        return "Yes, children can receive pediatric doses of approved vaccines based on their age group.";
    } else if (msg.contains("schedule") || msg.contains("appointment")) {
        return "You can schedule a vaccine through the Smart Vaccine Center app or website.";
    } else if (msg.contains("how many doses")) {
        return "Most vaccines require 2 doses for primary protection, with boosters recommended later.";
    } else if (msg.contains("difference between mrna and vector")) {
        return "mRNA vaccines (like Pfizer, Moderna) teach cells to make a protein. Vector vaccines (like AstraZeneca) use a harmless virus to deliver instructions.";
    }

    // Fallback
    return "Sorry, I don't have an answer to that. Please consult a healthcare provider.";
}

// Suggestion button handlers
void MainWindow::on_option1Button_clicked()
{
    handleUserInput("What are the common side effects of vaccines ?");
}

void MainWindow::on_option2Button_clicked()
{
    handleUserInput("Which vaccine is best ?");
}

void MainWindow::on_option3Button_clicked()
{
    handleUserInput("Can kids be vaccinated ?");
}
void MainWindow::on_option4Button_clicked()
{
    handleUserInput("Difference between mrna and vector ?");
}
void MainWindow::on_option5Button_clicked()
{
    handleUserInput("How to book an appointment ?");
}
