AUX_SOURCE_DIRECTORY(./src HW1_SRC_LIST)

ADD_EXECUTABLE(hw1 ${HW1_SRC_LIST})

MESSAGE(STATUS "HW1 src list: " ${HW1_SRC_LIST})

target_include_directories(hw1 PRIVATE ./include)
