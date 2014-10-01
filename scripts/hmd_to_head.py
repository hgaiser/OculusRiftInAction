#!/usr/bin/python

import math
import rospy
import tf
import tf.transformations

from geometry_msgs.msg import Quaternion

if __name__ == '__main__':
	rospy.init_node("HMDToHead")

	listener  = tf.TransformListener()
	#pitch_pub = rospy.Publisher("/MotorManager_head/Head/Pitch/set_angle_position", Float64, queue_size=1)
	#yaw_pub   = rospy.Publisher("/MotorManager_head/Head/Yaw/set_angle_position", Float64, queue_size=1)
	target_pub   = rospy.Publisher("/HeadManager/angle_target", Quaternion, queue_size=1)

	rate = rospy.Rate(50.0);
	while not rospy.is_shutdown():
		try:
			(trans, rot) = listener.lookupTransform("/neck_link", "/oculus", rospy.Time(0))
		except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
			continue

		msg = Quaternion()
		msg.x = rot[0]
		msg.y = rot[1]
		msg.z = rot[2]
		msg.w = rot[3]
		target_pub.publish(msg)
		rate.sleep()
