#!/usr/bin/env python

import rospy
import actionlib
import first_package.msg
import random


class AddTargetAction(object):
    _feedback = first_package.msg.Add2TargetFeedback()
    _result = first_package.msg.Add2TargetResult()

    def __init__(self, name):
        self._action_name = name
        self._as = actionlib.SimpleActionServer(self._action_name, first_package.msg.Add2TargetAction, execute_cb=self.exe_cb, auto_start = False)
        self._as.start()
        rospy.loginfo('Action Server Ready...')

    def exe_cb(self, goal):
        # for sleep 1 second
        r = rospy.Rate(1)
        success = True

        # show start information to user
        rospy.loginfo('Start Add to goal %d', goal.target)

        now = 0

        seconds = rospy.get_time()
        while now < goal.target:
            # check preempt
            if self._as.is_preempt_requested():
                rospy.loginfo('%s: Preempted' % self._action_name)
                self._as.set_preempted()
                success = False
                break

            rand = random.randint(1, 10)  # Integer from 1 to 10, endpoints included
            now = now + rand
            rospy.loginfo('Rand = %d, Now = %d', rand, now)
            self._feedback.now = now
            # publish the feedback
            self._as.publish_feedback(self._feedback)
            # sleep 1 second
            r.sleep()

        if success:
            rospy.loginfo('%s: Succeeded' % self._action_name)
            self._result.final = self._feedback.now
            self._as.set_succeeded(self._result)


if __name__ == '__main__':
    rospy.init_node('Add2TargetServer')
    server = AddTargetAction('Add2Target')
    rospy.spin()
