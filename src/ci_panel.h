/*
 * CI_Panel.h
 */
#ifndef CI_PANEL_NEW_H
#define CI_PANEL_NEW_H

#ifndef Q_MOC_RUN
# include <ros/ros.h>
# include <rviz/panel.h>
#endif

#include <std_msgs/String.h>

class InputWidget;
class QScrollArea;
class QLineEdit;

namespace conv_interface_rviz
{
class CI_Panel : public rviz::Panel
{
// This class uses Qt slots and is a subclass of QObject, so it needs the Q_OBJECT macro.
Q_OBJECT
public:
    CI_Panel( QWidget* parent = 0 );
    // virtual ~CI_Panel();

    virtual void load(const rviz::Config& config);
    virtual void save(rviz::Config config) const;

public Q_SLOTS:
    void sendUserInput();
    void displayResponse(const std_msgs::String::ConstPtr& msg);
    void scrollToBottom();
    void performScroll();

protected Q_SLOTS:
    void updateTopic();

protected:
    InputWidget* input_widget_;
    QScrollArea* scrollArea;
    QLineEdit* input_editor_;
    ros::Publisher user_input_publisher_;
    ros::Subscriber llm_response_subscriber_;
    ros::NodeHandle nh_;
};

} // end namespace conv_interface_rviz

#endif // CI_PANEL_NEW_H