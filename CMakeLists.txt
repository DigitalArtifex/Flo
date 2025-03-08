cmake_minimum_required(VERSION 3.19)

project(Flo LANGUAGES CXX VERSION 1.0.7)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-copy")
set(QT_MEDIA_BACKEND "gstreamer")

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
    Quick
    QuickWidgets
    3DCore
    3DQuick
    Graphs
    Multimedia
    MultimediaWidgets
    VirtualKeyboard
    WebSockets
)

qt_standard_project_setup()

set(SOURCES
    3rdparty/QSourceHighlite/languagedata.cpp
    3rdparty/QSourceHighlite/qsourcehighliter.cpp
    3rdparty/QSourceHighlite/qsourcehighliterthemes.cpp
    3rdparty/QVariableStyleSheet/qvariablestylesheet.cpp
    dialogs/InputShaper/inputshaperwizard.cpp
    dialogs/ZOffsetWizard/zoffsetwizard.cpp
    main.cpp
    mainwindow.cpp
    pages/dashboard/dashboardpage.cpp
    pages/dashboard/widgets/printer/printerwidget.cpp
    pages/dashboard/widgets/status/energy/energyconsumptionwidget.cpp
    pages/dashboard/widgets/status/issue/issuelistitem.cpp
    pages/dashboard/widgets/status/issue/issuelistwidget.cpp
    pages/dashboard/widgets/status/job/printjoboverviewitem.cpp
    pages/dashboard/widgets/status/job/printjoboverviewwidget.cpp
    pages/dashboard/widgets/status/statuswidget.cpp
    pages/dashboard/widgets/system/systemwidget.cpp
    pages/loading/loadingpage.cpp
    pages/printer/bedmesh/adjustment/adjustmentscrewframe.cpp
    pages/printer/bedmesh/adjustment/empty/adjustmentscrewemptyframe.cpp
    pages/printer/bedmesh/adjustment/item/adjustmentscrewitemframe.cpp
    pages/printer/bedmesh/bedmeshdata.cpp
    pages/printer/bedmesh/bedmeshwidget.cpp
    pages/printer/bedmesh/health/bedmeshhealthcard.cpp
    pages/printer/bedmesh/probed/empty/probedmeshemptyframe.cpp
    pages/printer/bedmesh/probed/item/probedmeshitemframe.cpp
    pages/printer/bedmesh/probed/probedmeshframe.cpp
    pages/printer/filebrowser/editor/fileeditor.cpp
    pages/printer/filebrowser/filebrowser.cpp
    pages/printer/filebrowser/filebrowseritem.cpp
    pages/printer/filebrowser/filebrowserwidget.cpp
    pages/printer/filebrowser/newfolder/newfolderdialog.cpp
    pages/printer/filebrowser/preview/filepreviewwindow.cpp
    pages/printer/macros/gcodemacrodialog.cpp
    pages/printer/offline/printerofflinescreen.cpp
    pages/printer/printerpage.cpp
    pages/printer/printing/printingpage.cpp
    pages/printer/settings/announcements/printerannouncementitem.cpp
    pages/printer/settings/announcements/printerannouncementview.cpp
    pages/printer/settings/announcements/printerannouncementwidget.cpp
    pages/printer/settings/printersettingspage.cpp
    pages/printer/settings/services/printerservicesview.cpp
    pages/printer/settings/services/servicewidget/printerservicewidget.cpp
    pages/printer/settings/system/mcuwidget/printermcuwidget.cpp
    pages/printer/settings/system/networkwidget/printernetworkwidget.cpp
    pages/printer/settings/system/printersystemview.cpp
    pages/printer/settings/system/systemwidget/printersystemwidget.cpp
    pages/printer/settings/updates/printerupdateitem.cpp
    pages/printer/settings/updates/printerupdateview.cpp
    pages/printer/settings/updates/printerupdatewidget.cpp
    pages/printer/settings/users/editor/printerusereditor.cpp
    pages/printer/settings/users/printerusercard.cpp
    pages/printer/settings/users/printerusersview.cpp
    pages/printer/terminal/printerterminal.cpp
    pages/printer/terminal/printerterminalitem.cpp
    pages/printer/terminal/printerterminalwidget.cpp
    pages/printer/widgets/ledstrips/ledstripcard.cpp
    pages/printer/widgets/ledstrips/ledstripview.cpp
    pages/printer/widgets/powerdevices/powerdevicecard.cpp
    pages/printer/widgets/powerdevices/powerdeviceview.cpp
    pages/printer/widgets/sensors/sensorcard.cpp
    pages/printer/widgets/sensors/sensorview.cpp
    pages/printer/widgets/extruder/extruderinfodialog.cpp
    pages/printer/widgets/extruder/extrudermaterialsdialog.cpp
    pages/printer/widgets/extruder/extruderwidget.cpp
    pages/printer/widgets/printerbed/printerbedinfodialog.cpp
    pages/printer/widgets/printerbed/printerbedtoolsdialog.cpp
    pages/printer/widgets/printerbed/printerbedwidget.cpp
    pages/printer/widgets/printerfan/printerfanitem.cpp
    pages/printer/widgets/printerfan/printerfanwidget.cpp
    pages/printer/widgets/printerwebcam/empty/emptyprinterwebcamframe.cpp
    pages/printer/widgets/printerwebcam/printerwebcamwidget.cpp
    pages/printer/widgets/temperature/temperaturewidget.cpp
    pages/printer/widgets/toolhead/control/toolheadcontrolframe.cpp
    pages/settings/edit_printer/editprinterdialog.cpp
    pages/settings/edit_printer/qmoonrakervalidator.cpp
    pages/settings/printerlistitem.cpp
    pages/settings/printerlistwidget.cpp
    pages/settings/settingspage.cpp
    pages/settings/system/systemsettingspage.cpp
    pages/settings/theme/themesettingspage.cpp
    flo/flo.cpp
    flo/qklipperinstancepool.cpp
    flo/settings.cpp
    dialogs/PositionDialog/positiondialog.cpp
    dialogs/ProgressDialog/progressdialog.cpp
    ui/QIconButton/qiconbutton.cpp
    ui/QWebcamWidget/qwebcamsource.cpp
    ui/QWebcamWidget/qwebcamwidget.cpp
    ui/Switch/switch.cpp
    common/CardWidget/cardwidget.cpp
    common/dialog/dialog.cpp
    ui/layouts/qflowlayout.cpp
    ui/list/qanimatedemptylistitem.cpp
    ui/list/qanimatedlistitem.cpp
    ui/list/qanimatedlistwidget.cpp
    ui/MenuButton/menubutton.cpp
    dialogs/MessageDialog/messagedialog.cpp
    dialogs/PidDialog/piddialog.cpp
    common/QAnimatedWidget/qanimatedwidget.cpp
    validators/QHexColorValidator/qhexcolorvalidator.cpp
    validators/QHttpValidator/qhttpvalidator.cpp
    validators/QMoonrakerDirectoryValidator/qmoonrakerdirectoryvalidator.cpp
    ui/LineGraphWidget/linegraphdata.cpp
    ui/LineGraphWidget/linegraphwidget.cpp
    3rdparty/SlidingStackedWidget/slidingstackedwidget.cpp
    common/Page/page.cpp
    ui/QAnimatedToolBox/qanimatedtoolbox.cpp
    ui/QAnimatedToolBox/qanimatedtoolboxbutton.cpp
    pages/printer/widgets/chamber/printerchamberwidget.cpp
    pages/printer/widgets/toolhead/toolheadwidget.cpp
    pages/printer/widgets/job/printjobitem.cpp
    pages/printer/widgets/job/printjobwidget.cpp
    3rdparty/QtSheet/sheet.cpp
    pages/printer/updating/printerupdatingscreen.cpp
    ui/QNumberEdit/qnumberedit.cpp
    ui/QAccentLabel/qaccentlabel.cpp
)

set(HEADERS
    3rdparty/QSourceHighlite/languagedata.h
    3rdparty/QSourceHighlite/qsourcehighliter.h
    3rdparty/QSourceHighlite/qsourcehighliterthemes.h
    3rdparty/QVariableStyleSheet/qvariablestylesheet.h
    dialogs/InputShaper/inputshaperwizard.h
    dialogs/ZOffsetWizard/zoffsetwizard.h
    mainwindow.h
    pages/dashboard/dashboardpage.h
    pages/dashboard/widgets/printer/printerwidget.h
    pages/dashboard/widgets/status/energy/energyconsumptionwidget.h
    pages/dashboard/widgets/status/issue/issuelistitem.h
    pages/dashboard/widgets/status/issue/issuelistwidget.h
    pages/dashboard/widgets/status/job/printjoboverviewitem.h
    pages/dashboard/widgets/status/job/printjoboverviewwidget.h
    pages/dashboard/widgets/status/statuswidget.h
    pages/dashboard/widgets/system/systemwidget.h
    pages/loading/loadingpage.h
    pages/printer/bedmesh/adjustment/adjustmentscrewframe.h
    pages/printer/bedmesh/adjustment/empty/adjustmentscrewemptyframe.h
    pages/printer/bedmesh/adjustment/item/adjustmentscrewitemframe.h
    pages/printer/bedmesh/bedmeshdata.h
    pages/printer/bedmesh/bedmeshwidget.h
    pages/printer/bedmesh/health/bedmeshhealthcard.h
    pages/printer/bedmesh/probed/empty/probedmeshemptyframe.h
    pages/printer/bedmesh/probed/item/probedmeshitemframe.h
    pages/printer/bedmesh/probed/probedmeshframe.h
    pages/printer/filebrowser/editor/fileeditor.h
    pages/printer/filebrowser/filebrowser.h
    pages/printer/filebrowser/filebrowseritem.h
    pages/printer/filebrowser/filebrowserwidget.h
    pages/printer/filebrowser/newfolder/newfolderdialog.h
    pages/printer/filebrowser/preview/filepreviewwindow.h
    pages/printer/macros/gcodemacrodialog.h
    pages/printer/offline/printerofflinescreen.h
    pages/printer/printerpage.h
    pages/printer/printing/printingpage.h
    pages/printer/settings/announcements/printerannouncementitem.h
    pages/printer/settings/announcements/printerannouncementview.h
    pages/printer/settings/announcements/printerannouncementwidget.h
    pages/printer/settings/printersettingspage.h
    pages/printer/settings/services/printerservicesview.h
    pages/printer/settings/services/servicewidget/printerservicewidget.h
    pages/printer/settings/system/mcuwidget/printermcuwidget.h
    pages/printer/settings/system/networkwidget/printernetworkwidget.h
    pages/printer/settings/system/printersystemview.h
    pages/printer/settings/system/systemwidget/printersystemwidget.h
    pages/printer/settings/updates/printerupdateitem.h
    pages/printer/settings/updates/printerupdateview.h
    pages/printer/settings/updates/printerupdatewidget.h
    pages/printer/settings/users/editor/printerusereditor.h
    pages/printer/settings/users/printerusercard.h
    pages/printer/settings/users/printerusersview.h
    pages/printer/terminal/printerterminal.h
    pages/printer/terminal/printerterminalitem.h
    pages/printer/terminal/printerterminalwidget.h
    pages/printer/widgets/sensors/sensorcard.h
    pages/printer/widgets/sensors/sensorview.h
    pages/printer/widgets/powerdevices/powerdevicecard.h
    pages/printer/widgets/powerdevices/powerdeviceview.h
    pages/printer/widgets/ledstrips/ledstripcard.h
    pages/printer/widgets/ledstrips/ledstripview.h
    pages/printer/widgets/extruder/extruderinfodialog.h
    pages/printer/widgets/extruder/extrudermaterialsdialog.h
    pages/printer/widgets/extruder/extruderwidget.h
    pages/printer/widgets/printerbed/printerbedinfodialog.h
    pages/printer/widgets/printerbed/printerbedtoolsdialog.h
    pages/printer/widgets/printerbed/printerbedwidget.h
    pages/printer/widgets/printerfan/printerfanitem.h
    pages/printer/widgets/printerfan/printerfanwidget.h
    pages/printer/widgets/printerwebcam/empty/emptyprinterwebcamframe.h
    pages/printer/widgets/printerwebcam/printerwebcamwidget.h
    pages/printer/widgets/temperature/temperaturewidget.h
    pages/printer/widgets/toolhead/control/toolheadcontrolframe.h
    pages/settings/edit_printer/editprinterdialog.h
    pages/settings/edit_printer/qmoonrakervalidator.h
    pages/settings/printerlistitem.h
    pages/settings/printerlistwidget.h
    pages/settings/settingspage.h
    pages/settings/system/systemsettingspage.h
    pages/settings/theme/themesettingspage.h
    flo/flo.h
    flo/qklipperinstancepool.h
    flo/settings.h
    dialogs/PositionDialog/positiondialog.h
    dialogs/ProgressDialog/progressdialog.h
    ui/QIconButton/qiconbutton.h
    ui/QWebcamWidget/qwebcamsource.h
    ui/QWebcamWidget/qwebcamwidget.h
    ui/Switch/style.h
    ui/Switch/switch.h
    common/CardWidget/cardwidget.h
    common/dialog/dialog.h
    ui/layouts/qflowlayout.h
    ui/list/qanimatedemptylistitem.h
    ui/list/qanimatedlistitem.h
    ui/list/qanimatedlistwidget.h
    ui/MenuButton/menubutton.h
    dialogs/MessageDialog/messagedialog.h
    dialogs/PidDialog/piddialog.h
    common/QAnimatedWidget/qanimatedwidget.h
    validators/QHexColorValidator/qhexcolorvalidator.h
    validators/QHttpValidator/qhttpvalidator.h
    validators/QMoonrakerDirectoryValidator/qmoonrakerdirectoryvalidator.h
    ui/LineGraphWidget/linegraphwidget.h
    ui/LineGraphWidget/linegraphdata.h
    3rdparty/SlidingStackedWidget/slidingstackedwidget.h
    common/Page/page.h
    ui/QAnimatedToolBox/qanimatedtoolbox.h
    ui/QAnimatedToolBox/qanimatedtoolboxbutton.h
    pages/printer/widgets/chamber/printerchamberwidget.h
    3rdparty/QtSheet/sheet.h
    pages/printer/widgets/toolhead/toolheadwidget.h
    pages/printer/widgets/job/printjobitem.h
    pages/printer/widgets/job/printjobwidget.h
    pages/printer/updating/printerupdatingscreen.h
    ui/QNumberEdit/qnumberedit.h
    ui/QAccentLabel/qaccentlabel.h
)

set(FORMS
    dialogs/InputShaper/inputshaperwizard.ui
    dialogs/ZOffsetWizard/zoffsetwizard.ui
    mainwindow.ui
    pages/dashboard/dashboardpage.ui
    pages/dashboard/widgets/printer/printerwidget.ui
    pages/dashboard/widgets/system/systemwidget.ui
    pages/loading/loadingpage.ui
    pages/printer/bedmesh/probed/empty/probedmeshemptyframe.ui
    pages/printer/bedmesh/probed/item/probedmeshitemframe.ui
    pages/printer/filebrowser/editor/fileeditor.ui
    pages/printer/offline/printerofflinescreen.ui
    pages/printer/printerpage.ui
    pages/printer/settings/printersettingspage.ui
    pages/printer/widgets/extruder/extruderwidget.ui
    pages/printer/widgets/printerbed/printerbedwidget.ui
    pages/settings/edit_printer/editprinterdialog.ui
    pages/settings/printerlistitem.ui
    pages/settings/printerlistwidget.ui
    pages/settings/settingspage.ui
    pages/settings/system/systemsettingspage.ui
    pages/settings/theme/themesettingspage.ui
    ui/MenuButton/menubutton.ui
    pages/printer/widgets/chamber/printerchamberwidget.ui
    pages/printer/updating/printerupdatingscreen.ui
    pages/printer/widgets/toolhead/toolheadwidget.ui
    ui/QNumberEdit/qnumberedit.ui
    ui/QAccentLabel/qaccentlabel.ui
)

set(QML
    pages/printer/bedmesh/BedMeshViewer.qml
    ui/LineGraphWidget/LineGraphWidget.qml
)

set(RESOURCES)

qt_add_resources(RESOURCES Resources.qrc )

qt_add_executable(Flo
    ${FORMS}
    ${HEADERS}
    ${SOURCES}
    ${RESOURCES}
    ${QML}
)

target_link_libraries(Flo
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network
        Qt6::WebSockets
        Qt6::Quick
        Qt6::QuickWidgets
        Qt6::3DQuick
        Qt6::Graphs
        Qt6::3DCore
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        Qt6::VirtualKeyboard
        -L${CMAKE_PREFIX_PATH}/lib -lQt6DAWidgets
        -lQt6Klipper
        -lquazip1-qt6
)

target_include_directories(Flo PRIVATE ./)

target_compile_definitions(Flo PRIVATE APPLICATION_RESTART_CODE=-10000)

include(GNUInstallDirs)

install(TARGETS Flo
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Flo
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
