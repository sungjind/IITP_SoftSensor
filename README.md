# IITP_SoftSensor
```
  cd <ws>/src
  git clone https://github.com/ros-drivers/rosserial.git
  cd <ws>
  catkin_make
  catkin_make install
```

```
  cd <sketchbook>/libraries
  rm -rf ros_lib
  rosrun rosserial_arduino make_libraries.py .
```

```
  rosrun rosserial_python serial_node.py __name:=serial_node_arduino0 _port:=/dev/ttyUSB0
  rosrun rosserial_python serial_node.py __name:=serial_node_arduino1 _port:=/dev/ttyUSB1
```
