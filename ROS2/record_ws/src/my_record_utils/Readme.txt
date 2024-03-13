我现在想要实现的功能是：一个节点能够同时录制CAN报文、Ethernet报文以及视频数据。

因此，配置文件应当是这个结构：

topic_recorder_node:
	ros__parameters:
		topics:
			- name: "can_message"
			
