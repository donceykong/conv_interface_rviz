/*
 * input_widget_new.h
 */
#ifndef INPUT_WIDGET_H
#define INPUT_WIDGET_H

#include <QWidget>      // Include QWidget for the base class
#include <QLabel>       // Include QLabel to display text
#include <QVBoxLayout>

namespace conv_interface_rviz
{
class InputWidget : public QWidget
{
Q_OBJECT
public:
    InputWidget(QWidget* parent = 0);
    void displayUserInput(const QString& message);  // Method to update text display
    void displayLLMResponse(const QString& message);  // Method to update text display

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QVBoxLayout* layout;
};

} // end namespace conv_interface_rviz

#endif // INPUT_WIDGET_H
