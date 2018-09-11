cmake_minimum_required(VERSION 2.8.3)
project(battery_status)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)

catkin_package(
  INCLUDE_DIRS include
  #LIBRARIES battery_status
  CATKIN_DEPENDS roscpp std_msgs
  #DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

FIND_LIBRARY(WIRINGPI_LIBRARY wiringPi) # add path if needed - 

add_executable(read_voltage src/read_voltage.cpp)
add_executable(subscriber src/subscriber.cpp)
add_executable(battery_status src/battery_status.cpp)
add_executable(led_glow src/led_glow.cpp)

target_link_libraries(read_voltage ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY} pthread crypt m rt)

target_link_libraries(subscriber ${catkin_LIBRARIES})

target_link_libraries(battery_status ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY} pthread crypt m rt)

target_link_libraries(led_glow ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY} pthread crypt m rt)


