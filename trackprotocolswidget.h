#ifndef TRACKPROTOCOLSWIDGET_H
#define TRACKPROTOCOLSWIDGET_H

#include <QWidget>

// Forward declaration
namespace Ui {
class TrackProtocolsWidget;  // This must match exactly with your UI class name
}

class TrackProtocolsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrackProtocolsWidget(QWidget *parent = nullptr);
    ~TrackProtocolsWidget();

private:
    Ui::TrackProtocolsWidget *ui;  // Must match the forward declaration
};

#endif // TRACKPROTOCOLSWIDGET_H
