cmake_minimum_required(VERSION 3.16)

project(QtOllamaFrontend VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Sql Xml TextToSpeech)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appQtOllamaFrontend
    src/main.cpp
    src/databasecomponent.h
    src/databasecomponent.cpp
    src/qtollamafrontend.h
    src/qtollamafrontend.cpp
    resources/resources.qrc
)

qt_add_qml_module(appQtOllamaFrontend
    URI QtOllamaFrontend
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/CustomButton.qml
        qml/CustomComboBox.qml
        qml/CustomLabel.qml
        qml/CustomTextArea.qml
        qml/CustomTextField.qml
        qml/CustomCheckBoxTextField.qml
        qml/CustomCheckBoxTextFieldInteger.qml
        qml/CustomCheckBoxTextFieldDouble.qml
        qml/CustomCheckBoxTextFieldBoolean.qml
        qml/DialogAbout.qml
        qml/DialogService.qml
        qml/DialogAddModel.qml
        qml/DialogSelectModel.qml
        qml/DialogPullModel.qml
        qml/DialogModelSettings.qml
        qml/DialogModelOptions.qml
        qml/DialogImage.qml
        qml/DialogTextToSpeech.qml
        qml/DialogExportMessages.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQtOllamaFrontend PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQtOllamaFrontend
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQtOllamaFrontend
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
    PRIVATE Qt6::Xml
    PRIVATE Qt6::TextToSpeech
)

include(GNUInstallDirs)
install(TARGETS appQtOllamaFrontend
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
