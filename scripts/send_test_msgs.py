#!/usr/bin/env python3
import roslib; roslib.load_manifest( 'conv_interface_rviz' )
import rospy
from std_msgs.msg import String

# # Publish a string message repeatedly to the 'conv_interface/llm_response' topic, if desired.
# topic = 'conv_interface/llm_response'
# publisher = rospy.Publisher(topic, String, queue_size=5)

# rospy.init_node('test_string_publisher')

# rate = rospy.Rate(1.0)  # 10 Hz
# while not rospy.is_shutdown():
#     # Create a string message
#     message = String()
#     message.data = "Hello from {}.".format(rospy.get_name())
#     publisher.publish(message)

#     rate.sleep()
