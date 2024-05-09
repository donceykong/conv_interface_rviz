/*
 * input_widget.cpp
 */

#include <QPainter>
#include <QScrollArea>

#include "input_widget.h"

namespace conv_interface_rviz
{
InputWidget::InputWidget(QWidget* parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);     // Initialize the layout
    layout->setAlignment(Qt::AlignTop); // Align labels to the top of the widget
    layout->setSpacing(15);             // Set spacing between labels
    setLayout(layout);                  // Set the layout for the widget
}

void InputWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setBrush(QColor(48, 48, 48));   // Dark grey background
    painter.drawRect(rect());               // Fill the background

    // // Add an image to the widget, if desired
    // // TODO: make sure path actually points to conv_interface_rviz ROS package
    // QImage image;
    // if (image.load("conv_interface_rviz/images/text_box.png")) {
    //     painter.drawImage(QRect( hpad, vpad, size, size ), image); // Adjust drawing to fit widget
    // }
}

void InputWidget::displayUserInput(const QString& message)
{
    QLabel* messageLabel = new QLabel(this);    // Create a new label for the message
    messageLabel->setWordWrap(true);            // Enable word wrapping
    messageLabel->setTextFormat(Qt::RichText);  // Enable rich text formatting
    QString formattedMessage = "<b style='color: white; margin-bottom: 0px; padding-bottom: 0px;'>You:</b>"
                           "<p style='color: white; margin-top: 0px; padding-top: 0px;'>" + message + "</p>";
    messageLabel->setText(formattedMessage);    // Set the text of the label
    layout->addWidget(messageLabel);            // Add the label to the layout
}

void InputWidget::displayLLMResponse(const QString& message)
{
    QLabel* messageLabel = new QLabel(this);    // Create a new label for the message
    messageLabel->setWordWrap(true);            // Enable word wrapping
    messageLabel->setTextFormat(Qt::RichText);  // Enable rich text formatting
    QString formattedMessage = "<b style='color: white; margin-bottom: 0px; padding-bottom: 0px;'>Robot:</b>"
                           "<p style='color: white; margin-top: 0px; padding-top: 0px;'>" + message + "</p>";
    messageLabel->setText(formattedMessage);    // Set the text of the label
    layout->addWidget(messageLabel);            // Add the label to the layout
}

} // end namespace conv_interface_rviz