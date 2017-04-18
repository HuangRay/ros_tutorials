#! /usr/bin/env python

import rospy
import actionlib
import first_package.msg

def add2target_client():
    # Creates the SimpleActionClient
    client = actionlib.SimpleActionClient('Add2Target', first_package.msg.Add2TargetAction)


    # Waits until action server ready
    rospy.loginfo("Wait for action server(%s)...","Add2Target")
    client.wait_for_server()


    # set goal
    goal = first_package.msg.Add2TargetGoal(target=100)

    # send to server
    client.send_goal(goal, feedback_cb = fb_cb)

    # Waits for the server result
    client.wait_for_result()

    # Prints out the result of executing the action
    return client.get_result()

def fb_cb( feedback):
    rospy.loginfo("Now feedback = " + str(feedback.now) )


if __name__ == '__main__':
    try:
        rospy.init_node('action_client')
        result = add2target_client()
        rospy.loginfo("Result:" + str(result)  )
    except rospy.ROSInterruptException:
        rospy.logerror("program interrupted before completion", file=sys.stderr)
