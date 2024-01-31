cmake_minimum_required(VERSION 3.12)
project(EasySymbol)

if(debug)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -ggdb")
else()
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-Wall")
endif()

find_package(Qt5 COMPONENTS Core Gui Widgets)

aux_source_directory(src MAIN_SRC)

set(
  MOC_H
    include/mainWindow.h
)

set(
  FORM_SRC
    ui/mainWindow.ui
    ui/popup.ui
)

set(
  RES_SRC
    res.qrc
)

qt5_wrap_cpp(MOCd_H ${MOC_H})
qt5_wrap_ui(UICd_F ${FORM_SRC})
qt5_add_resources(QCCd_res ${RES_SRC})

add_executable(
  ${PROJECT_NAME}
    ${MAIN_SRC}
    ${MOC_H}
    ${MOCd_H}
    ${UICd_F}
    ${QCCd_res}
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)

