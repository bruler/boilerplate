file(GLOB_RECURSE SOURCES
            *.cpp *.h
            code/*.cpp code/*.h)

set(SOURCES ${SOURCES}
            res/assets/assets.qrc
            res/icons/icons.qrc
            res/qml/qml.qrc)

include(../vendor/CMakeLists.txt)

add_executable(deep-app ${SOURCES})
add_definitions(-DQT_NO_KEYWORDS)

target_link_libraries(deep-app
                      Qt5::Core
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::Concurrent
                      ${OpenCV_LIBS}
                      ${PYTHON_LIBRARIES}
                      ${Boost_LIBRARIES}
                      ${CUDA_LIBRARIES}
                      ${Caffe_LIBRARIES})

set_target_properties(deep-app PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/data/Info.plist)

install(TARGETS deep-app
        RUNTIME DESTINATION bin
        DESTINATION ${CMAKE_INSTALL_BINDIR})
