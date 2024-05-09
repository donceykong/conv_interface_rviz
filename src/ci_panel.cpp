/*
 * CI_Panel.cpp
 */
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>

#include <std_msgs/String.h>

#include "input_widget.h"
#include "ci_panel.h"

namespace conv_interface_rviz
{

CI_Panel::CI_Panel(QWidget* parent)
    : rviz::Panel(parent)
{
    // Setup input layout
    QHBoxLayout* inputLayout = new QHBoxLayout;
    inputLayout->addWidget(new QLabel("Message: "));
    input_editor_ = new QLineEdit;
    inputLayout->addWidget(input_editor_);

    // Create the CI widget inside a scrollable area
    input_widget_ = new InputWidget;
    scrollArea = new QScrollArea;  // Create scroll area to contain the input widget
    scrollArea->setWidget(input_widget_);
    scrollArea->setWidgetResizable(true);  // Ensure the scroll area adapts to the content size
    std::cout << "scrollArea initialized, address: " << (void*)scrollArea << std::endl;

    // Main layout of the panel
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(scrollArea);  // Add scroll area instead of the widget directly
    layout->addLayout(inputLayout);
    setLayout(layout);

    // ROS publisher & subscriber
    user_input_publisher_ = nh_.advertise<std_msgs::String>("conv_interface/user_input", 1);
    llm_response_subscriber_ = nh_.subscribe<std_msgs::String>("conv_interface/llm_response", 1, &CI_Panel::displayResponse, this);

    // Connect the QLineEdit editing finished signal to send user input
    connect(input_editor_, &QLineEdit::editingFinished, this, &CI_Panel::sendUserInput);
    // connect(input_editor_, SIGNAL(editingFinished()), this, SLOT(sendUserInput()));
}

void CI_Panel::displayResponse(const std_msgs::String::ConstPtr& msg)
{
    QString text = QString::fromStdString(msg->data);
    if (!text.isEmpty()) {
        input_widget_->displayLLMResponse(text);
        scrollToBottom();
    }
}

void CI_Panel::sendUserInput()
{
    std_msgs::String msg;
    msg.data = input_editor_->text().toStdString();
    if (!msg.data.empty()) {
        user_input_publisher_.publish(msg);
        input_widget_->displayUserInput(input_editor_->text());  // Display message in the input widget
        Q_EMIT configChanged();
        scrollToBottom();
    }
    input_editor_->clear();  // Optional: clear the editor after sending
}

void CI_Panel::scrollToBottom()
{
    // Schedule the scroll operation to occur after a short delay
    QTimer::singleShot(100, this, SLOT(performScroll()));
}

void CI_Panel::performScroll()
{
    QScrollBar* scrollbar = scrollArea->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void CI_Panel::save(rviz::Config config) const
{
    rviz::Panel::save(config);
    config.mapSetValue("UserInput", input_editor_->text());
}

void CI_Panel::load(const rviz::Config& config)
{
    rviz::Panel::load(config);
    QString input;
    if (config.mapGetString("UserInput", &input)) {
        input_editor_->setText(input);
    }
}

} // namespace conv_interface_rviz

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(conv_interface_rviz::CI_Panel, rviz::Panel)