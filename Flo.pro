QT       += core gui charts network multimedia multimediawidgets datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QSourceHighlite/languagedata.cpp \
    QSourceHighlite/qsourcehighliter.cpp \
    QSourceHighlite/qsourcehighliterthemes.cpp \
    QVariableSytleSheet/qvariablestylesheet.cpp \
    main.cpp \
    mainwindow.cpp \
    pages/dashboard/dashboardpage.cpp \
    pages/dashboard/widgets/printer/printerwidget.cpp \
    pages/dashboard/widgets/status/energy/energyconsumptionchart.cpp \
    pages/dashboard/widgets/status/energy/energyconsumptionwidget.cpp \
    pages/dashboard/widgets/status/issue/issuelistitem.cpp \
    pages/dashboard/widgets/status/issue/issuelistwidget.cpp \
    pages/dashboard/widgets/status/job/printjoblistitem.cpp \
    pages/dashboard/widgets/status/job/printjoblistwidget.cpp \
    pages/dashboard/widgets/status/statuswidget.cpp \
    pages/dashboard/widgets/system/systemwidget.cpp \
    pages/loading/loadingpage.cpp \
    pages/printer/bedmesh/q3dprintbedmeshchart.cpp \
    pages/printer/bedmesh/q3dprintbedmeshviewer.cpp \
    pages/printer/filebrowser/editor/fileeditor.cpp \
    pages/printer/filebrowser/filebrowser.cpp \
    pages/printer/filebrowser/filebrowseritem.cpp \
    pages/printer/filebrowser/filebrowserwidget.cpp \
    pages/printer/filebrowser/newfolder/newfolderdialog.cpp \
    pages/printer/filebrowser/overlay/filebrowseroverlay.cpp \
    pages/printer/filebrowser/preview/filepreviewwindow.cpp \
    pages/printer/offline/printerofflinescreen.cpp \
    pages/printer/printerpage.cpp \
    pages/printer/settings/announcements/printerannouncementitem.cpp \
    pages/printer/settings/announcements/printerannouncementview.cpp \
    pages/printer/settings/announcements/printerannouncementwidget.cpp \
    pages/printer/settings/printersettingspage.cpp \
    pages/printer/settings/services/printerservicesview.cpp \
    pages/printer/settings/services/servicewidget/printerservicewidget.cpp \
    pages/printer/settings/system/drivewidget/printerdrivewidget.cpp \
    pages/printer/settings/system/networkwidget/printernetworkchart.cpp \
    pages/printer/settings/system/networkwidget/printernetworkwidget.cpp \
    pages/printer/settings/system/printersystemview.cpp \
    pages/printer/settings/system/systemwidget/printersystemwidget.cpp \
    pages/printer/settings/updates/printerupdateitem.cpp \
    pages/printer/settings/updates/printerupdateview.cpp \
    pages/printer/settings/updates/printerupdatewidget.cpp \
    pages/printer/settings/users/editor/printerusereditor.cpp \
    pages/printer/settings/users/printerusercard.cpp \
    pages/printer/settings/users/printerusersview.cpp \
    pages/printer/temperature/temperaturegraph.cpp \
    pages/printer/terminal/printerterminal.cpp \
    pages/printer/terminal/printerterminalitem.cpp \
    pages/printer/terminal/printerterminalwidget.cpp \
    pages/printer/widgets/extruder/extruderwidget.cpp \
    pages/printer/widgets/printerbed/adjustment/adjustmentscrewframe.cpp \
    pages/printer/widgets/printerbed/adjustment/empty/adjustmentscrewemptyframe.cpp \
    pages/printer/widgets/printerbed/adjustment/item/adjustmentscrewitemframe.cpp \
    pages/printer/widgets/printerbed/bedmesh/bedmeshframe.cpp \
    pages/printer/widgets/printerbed/bedmesh/empty/bedmeshemptyframe.cpp \
    pages/printer/widgets/printerbed/bedmesh/item/bedmeshitemframe.cpp \
    pages/printer/widgets/printerbed/printerbedwidget.cpp \
    pages/printer/widgets/printerfan/printerfanwidget.cpp \
    pages/printer/widgets/printerwebcam/empty/emptyprinterwebcamframe.cpp \
    pages/printer/widgets/printerwebcam/printerwebcamwidget.cpp \
    pages/printer/widgets/toolhead/control/toolheadcontrolframe.cpp \
    pages/settings/add_printer/addbedpage.cpp \
    pages/settings/add_printer/addextruderspage.cpp \
    pages/settings/add_printer/addprinterpage.cpp \
    pages/settings/add_printer/addprinterwizard.cpp \
    pages/settings/add_printer/validateprinterpage.cpp \
    pages/settings/edit_printer/editprinterdialog.cpp \
    pages/settings/edit_printer/qmoonrakervalidator.cpp \
    pages/settings/printerlistitem.cpp \
    pages/settings/printerlistwidget.cpp \
    pages/settings/settingspage.cpp \
    pages/settings/theme/themesettingspage.cpp \
    system/flo.cpp \
    system/printerpool.cpp \
    system/settings.cpp \
    types/bed.cpp \
    types/chamber.cpp \
    types/clientidentifier.cpp \
    types/console/qabstractklipperconsole.cpp \
    types/console/qklipperremoteconsole.cpp \
    types/console/qlocalklipperconsole.cpp \
    types/endstopstatus.cpp \
    types/extruder.cpp \
    types/fan.cpp \
    types/klipperfile.cpp \
    types/klippermessage.cpp \
    types/klipperresponse.cpp \
    types/position.cpp \
    types/printer.cpp \
    types/printjob.cpp \
    types/qsteppermotor.cpp \
    types/system.cpp \
    types/toolhead.cpp \
    ui/QIconButton/qiconbutton.cpp \
    ui/QMaskedButton/qmaskedbutton.cpp \
    ui/QWebcamWidget/qwebcamwidget.cpp \
    ui/circularprogressbar.cpp \
    ui/common/cardwidget/cardwidget.cpp \
    ui/common/dialog/dialog.cpp \
    ui/layouts/qflowlayout.cpp \
    ui/list/qanimatedemptylistitem.cpp \
    ui/list/qanimatedlistitem.cpp \
    ui/list/qanimatedlistwidget.cpp \
    ui/menubutton.cpp \
    ui/messagedialog.cpp \
    ui/qanimatedwidget.cpp \
    ui/qwidgetanimation.cpp \
    ui/widgetanimation.cpp \
    validators/QHexColorValidator/qhexcolorvalidator.cpp \
    validators/QHttpValidator/qhttpvalidator.cpp

HEADERS += \
    QSourceHighlite/languagedata.h \
    QSourceHighlite/qsourcehighliter.h \
    QSourceHighlite/qsourcehighliterthemes.h \
    QVariableSytleSheet/qvariablestylesheet.h \
    mainwindow.h \
    pages/dashboard/dashboardpage.h \
    pages/dashboard/widgets/printer/printerwidget.h \
    pages/dashboard/widgets/status/energy/energyconsumptionchart.h \
    pages/dashboard/widgets/status/energy/energyconsumptionwidget.h \
    pages/dashboard/widgets/status/issue/issuelistitem.h \
    pages/dashboard/widgets/status/issue/issuelistwidget.h \
    pages/dashboard/widgets/status/job/printjoblistitem.h \
    pages/dashboard/widgets/status/job/printjoblistwidget.h \
    pages/dashboard/widgets/status/statuswidget.h \
    pages/dashboard/widgets/system/systemwidget.h \
    pages/loading/loadingpage.h \
    pages/printer/bedmesh/q3dprintbedmeshchart.h \
    pages/printer/bedmesh/q3dprintbedmeshviewer.h \
    pages/printer/filebrowser/editor/fileeditor.h \
    pages/printer/filebrowser/filebrowser.h \
    pages/printer/filebrowser/filebrowseritem.h \
    pages/printer/filebrowser/filebrowserwidget.h \
    pages/printer/filebrowser/newfolder/newfolderdialog.h \
    pages/printer/filebrowser/overlay/filebrowseroverlay.h \
    pages/printer/filebrowser/preview/filepreviewwindow.h \
    pages/printer/offline/printerofflinescreen.h \
    pages/printer/printerpage.h \
    pages/printer/settings/announcements/printerannouncementitem.h \
    pages/printer/settings/announcements/printerannouncementview.h \
    pages/printer/settings/announcements/printerannouncementwidget.h \
    pages/printer/settings/printersettingspage.h \
    pages/printer/settings/services/printerservicesview.h \
    pages/printer/settings/services/servicewidget/printerservicewidget.h \
    pages/printer/settings/system/drivewidget/printerdrivewidget.h \
    pages/printer/settings/system/networkwidget/printernetworkchart.h \
    pages/printer/settings/system/networkwidget/printernetworkwidget.h \
    pages/printer/settings/system/printersystemview.h \
    pages/printer/settings/system/systemwidget/printersystemwidget.h \
    pages/printer/settings/updates/printerupdateitem.h \
    pages/printer/settings/updates/printerupdateview.h \
    pages/printer/settings/updates/printerupdatewidget.h \
    pages/printer/settings/users/editor/printerusereditor.h \
    pages/printer/settings/users/printerusercard.h \
    pages/printer/settings/users/printerusersview.h \
    pages/printer/temperature/temperaturegraph.h \
    pages/printer/terminal/printerterminal.h \
    pages/printer/terminal/printerterminalitem.h \
    pages/printer/terminal/printerterminalwidget.h \
    pages/printer/widgets/extruder/extruderwidget.h \
    pages/printer/widgets/printerbed/adjustment/adjustmentscrewframe.h \
    pages/printer/widgets/printerbed/adjustment/empty/adjustmentscrewemptyframe.h \
    pages/printer/widgets/printerbed/adjustment/item/adjustmentscrewitemframe.h \
    pages/printer/widgets/printerbed/bedmesh/bedmeshframe.h \
    pages/printer/widgets/printerbed/bedmesh/empty/bedmeshemptyframe.h \
    pages/printer/widgets/printerbed/bedmesh/item/bedmeshitemframe.h \
    pages/printer/widgets/printerbed/printerbedwidget.h \
    pages/printer/widgets/printerfan/printerfanwidget.h \
    pages/printer/widgets/printerwebcam/empty/emptyprinterwebcamframe.h \
    pages/printer/widgets/printerwebcam/printerwebcamwidget.h \
    pages/printer/widgets/toolhead/control/toolheadcontrolframe.h \
    pages/settings/add_printer/addbedpage.h \
    pages/settings/add_printer/addextruderspage.h \
    pages/settings/add_printer/addprinterpage.h \
    pages/settings/add_printer/addprinterwizard.h \
    pages/settings/add_printer/validateprinterpage.h \
    pages/settings/edit_printer/editprinterdialog.h \
    pages/settings/edit_printer/qmoonrakervalidator.h \
    pages/settings/printerlistitem.h \
    pages/settings/printerlistwidget.h \
    pages/settings/settingspage.h \
    pages/settings/theme/themesettingspage.h \
    system/flo.h \
    system/printerpool.h \
    system/settings.h \
    types/bed.h \
    types/chamber.h \
    types/clientidentifier.h \
    types/console/qabstractklipperconsole.h \
    types/console/qklipperremoteconsole.h \
    types/console/qlocalklipperconsole.h \
    types/endstopstatus.h \
    types/extruder.h \
    types/fan.h \
    types/gcode/qgcodecommand.h \
    types/gcode/qgcodemacro.h \
    types/gcode/qgcodemove.h \
    types/gcode/qgcodestore.h \
    types/klipperfile.h \
    types/klippermessage.h \
    types/klipperresponse.h \
    types/position.h \
    types/printer.h \
    types/printerdefinition.h \
    types/printjob.h \
    types/qsteppermotor.h \
    types/system.h \
    types/temperaturestore.h \
    types/toolhead.h \
    ui/QIconButton/qiconbutton.h \
    ui/QMaskedButton/qmaskedbutton.h \
    ui/QWebcamWidget/qwebcamwidget.h \
    ui/circularprogressbar.h \
    ui/common/cardwidget/cardwidget.h \
    ui/common/dialog/dialog.h \
    ui/layouts/qflowlayout.h \
    ui/list/qanimatedemptylistitem.h \
    ui/list/qanimatedlistitem.h \
    ui/list/qanimatedlistwidget.h \
    ui/menubutton.h \
    ui/messagedialog.h \
    ui/qanimatedwidget.h \
    ui/qwidgetanimation.h \
    ui/widgetanimation.h \
    validators/QHexColorValidator/qhexcolorvalidator.h \
    validators/QHttpValidator/qhttpvalidator.h

FORMS += \
    mainwindow.ui \
    pages/dashboard/dashboardpage.ui \
    pages/dashboard/widgets/printer/printerwidget.ui \
    pages/dashboard/widgets/system/systemwidget.ui \
    pages/loading/loadingpage.ui \
    pages/printer/filebrowser/editor/fileeditor.ui \
    pages/printer/offline/printerofflinescreen.ui \
    pages/printer/printerpage.ui \
    pages/printer/settings/printersettingspage.ui \
    pages/printer/temperature/temperaturegraph.ui \
    pages/printer/widgets/extruder/extruderwidget.ui \
    pages/printer/widgets/printerbed/adjustment/adjustmentscrewframe.ui \
    pages/printer/widgets/printerbed/adjustment/empty/adjustmentscrewemptyframe.ui \
    pages/printer/widgets/printerbed/adjustment/item/adjustmentscrewitemframe.ui \
    pages/printer/widgets/printerbed/bedmesh/bedmeshframe.ui \
    pages/printer/widgets/printerbed/bedmesh/empty/bedmeshemptyframe.ui \
    pages/printer/widgets/printerbed/bedmesh/item/bedmeshitemframe.ui \
    pages/printer/widgets/printerbed/printerbedwidget.ui \
    pages/settings/add_printer/addbedpage.ui \
    pages/settings/add_printer/addextruderspage.ui \
    pages/settings/add_printer/addprinterpage.ui \
    pages/settings/add_printer/addprinterwizard.ui \
    pages/settings/add_printer/validateprinterpage.ui \
    pages/settings/edit_printer/editprinterdialog.ui \
    pages/settings/printerlistitem.ui \
    pages/settings/printerlistwidget.ui \
    pages/settings/settingspage.ui \
    pages/settings/theme/themesettingspage.ui \
    ui/menubutton.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    QSourceHighlite/QSourceHighlite.pro

DISTFILES += \
    QSourceHighlite/LICENSE \
    QSourceHighlite/QSourceHighlite.pri

RESOURCES += \
    Resources.qrc

linux {
    contains(QMAKE_HOST.arch, arm.*):{
        DEFINES -= LOCAL_PRINTER_DRIVE_AS_SD_INFO
        DEFINES += RASPBERRYPI
    }
    else{
        DEFINES += LOCAL_PRINTER_DRIVE_AS_SD_INFO
        DEFINES += LOCAL_PRINTER_CPU_TEMP_SYSCALL
    }
}
