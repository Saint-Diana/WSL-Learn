# CAN Channel Driver
## can_publisher_node
In this node, we accomplish the function of capturing CAN messages and publishing them to ROS2 topic.
In order to change the channel number and the topic name, we extract the two parameters from the code to config/publisher.yaml configuration file. So we can change them flexibly.

TODO: We need to create a node which can record any topic signals LIKE ROSBAG.