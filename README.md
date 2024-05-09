# conv_interface_rviz

Add this package to your ROS1 ws. After building, run 'rosrun conv_interface_rviz send_test_msgs'

This will load the manifest for the Rviz panel. You can edit the send_test_msgs.py such that you send test messages to the /conv_interface_rviz/llm_response topic. This simple publisher is all you would need to send messages you get from an LLM's API. 

