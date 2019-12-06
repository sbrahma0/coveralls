apt-get -qq update
apt-get -qq dist-upgrade
rosdep update
apt-get -y install python-catkin-tools
cd /root/iiwa_stack_ws
rosdep install --from-paths src --ignore-src -r -y
catkin build --no-status --summarize
