QT       += core gui network multimedia multimediawidgets websockets charts graphs 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation qml quick 3dquick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets openglwidgets virtualkeyboard

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QKlipper/QKlipperConsole/qklippercommand.cpp \
    QKlipper/QKlipperConsole/qklipperconsole.cpp \
    QKlipper/QKlipperFile/qklipperfile.cpp \
    QKlipper/QKlipperInstance/qklipperinstance.cpp \
    QKlipper/QKlipperMessage/qklippermessage.cpp \
    QKlipper/QKlipperPrinter/qklipperadjustmentscrew.cpp \
    QKlipper/QKlipperPrinter/qklipperchamber.cpp \
    QKlipper/QKlipperPrinter/qklipperextruder.cpp \
    QKlipper/QKlipperPrinter/qklipperfan.cpp \
    QKlipper/QKlipperPrinter/qklippergcodemove.cpp \
    QKlipper/QKlipperPrinter/qklippermcu.cpp \
    QKlipper/QKlipperPrinter/qklipperprintbed.cpp \
    QKlipper/QKlipperPrinter/qklipperprintbedmesh.cpp \
    QKlipper/QKlipperPrinter/qklipperprinter.cpp \
    QKlipper/QKlipperPrinter/qklippersteppermotor.cpp \
    QKlipper/QKlipperPrinter/qklippertoolhead.cpp \
    QKlipper/QKlipperServer/qklippergcodestore.cpp \
    QKlipper/QKlipperServer/qklipperjobqueue.cpp \
    QKlipper/QKlipperServer/qklipperprintjob.cpp \
    QKlipper/QKlipperServer/qklipperserver.cpp \
    QKlipper/QKlipperServer/qklipperuser.cpp \
    QKlipper/QKlipperSystem/qklippercanbus.cpp \
    QKlipper/QKlipperSystem/qklippercanbusdevice.cpp \
    QKlipper/QKlipperSystem/qklippercpuinfo.cpp \
    QKlipper/QKlipperSystem/qklipperdistributioninfo.cpp \
    QKlipper/QKlipperSystem/qklipperledstrip.cpp \
    QKlipper/QKlipperSystem/qklipperlibcameradevice.cpp \
    QKlipper/QKlipperSystem/qklippermemorystats.cpp \
    QKlipper/QKlipperSystem/qklippermoonrakerstatsentry.cpp \
    QKlipper/QKlipperSystem/qklippernetworkinterface.cpp \
    QKlipper/QKlipperSystem/qklippernetworkstatsentry.cpp \
    QKlipper/QKlipperSystem/qklipperpowerdevice.cpp \
    QKlipper/QKlipperSystem/qklippersdinfo.cpp \
    QKlipper/QKlipperSystem/qklippersensor.cpp \
    QKlipper/QKlipperSystem/qklippersensordata.cpp \
    QKlipper/QKlipperSystem/qklipperserialperipheral.cpp \
    QKlipper/QKlipperSystem/qklipperservice.cpp \
    QKlipper/QKlipperSystem/qklippersystem.cpp \
    QKlipper/QKlipperSystem/qklipperthrottlestate.cpp \
    QKlipper/QKlipperSystem/qklipperupdatemanager.cpp \
    QKlipper/QKlipperSystem/qklippervirtualizationstate.cpp \
    QKlipper/QKlipperSystem/qklippervirtualsdcard.cpp \
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
    pages/printer/bedmesh/adjustment/adjustmentscrewframe.cpp \
    pages/printer/bedmesh/adjustment/empty/adjustmentscrewemptyframe.cpp \
    pages/printer/bedmesh/adjustment/item/adjustmentscrewitemframe.cpp \
    pages/printer/bedmesh/bedmeshdata.cpp \
    pages/printer/bedmesh/bedmeshwidget.cpp \
    pages/printer/bedmesh/health/bedmeshhealthcard.cpp \
    pages/printer/bedmesh/probed/bedmeshframe.cpp \
    pages/printer/bedmesh/probed/empty/bedmeshemptyframe.cpp \
    pages/printer/bedmesh/probed/item/bedmeshitemframe.cpp \
    pages/printer/filebrowser/editor/fileeditor.cpp \
    pages/printer/filebrowser/filebrowser.cpp \
    pages/printer/filebrowser/filebrowseritem.cpp \
    pages/printer/filebrowser/filebrowserwidget.cpp \
    pages/printer/filebrowser/newfolder/newfolderdialog.cpp \
    pages/printer/filebrowser/overlay/filebrowseroverlay.cpp \
    pages/printer/filebrowser/preview/filepreviewwindow.cpp \
    pages/printer/ledstrips/ledstripcard.cpp \
    pages/printer/ledstrips/ledstripview.cpp \
    pages/printer/macros/gcodemacrodialog.cpp \
    pages/printer/offline/printerofflinescreen.cpp \
    pages/printer/powerdevices/powerdevicecard.cpp \
    pages/printer/powerdevices/powerdeviceview.cpp \
    pages/printer/printerpage.cpp \
    pages/printer/printing/printingpage.cpp \
    pages/printer/sensors/sensorcard.cpp \
    pages/printer/sensors/sensorview.cpp \
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
    pages/printer/terminal/printerterminal.cpp \
    pages/printer/terminal/printerterminalitem.cpp \
    pages/printer/terminal/printerterminalwidget.cpp \
    pages/printer/widgets/extruder/extruderinfodialog.cpp \
    pages/printer/widgets/extruder/extrudermaterialsdialog.cpp \
    pages/printer/widgets/extruder/extrudertemperaturechart.cpp \
    pages/printer/widgets/extruder/extrudertemperaturewidget.cpp \
    pages/printer/widgets/extruder/extruderwidget.cpp \
    pages/printer/widgets/printerbed/bedtemperaturechart.cpp \
    pages/printer/widgets/printerbed/bedtemperaturewidget.cpp \
    pages/printer/widgets/printerbed/printerbedinfodialog.cpp \
    pages/printer/widgets/printerbed/printerbedtoolsdialog.cpp \
    pages/printer/widgets/printerbed/printerbedwidget.cpp \
    pages/printer/widgets/printerfan/printerfanitem.cpp \
    pages/printer/widgets/printerfan/printerfanwidget.cpp \
    pages/printer/widgets/printerwebcam/empty/emptyprinterwebcamframe.cpp \
    pages/printer/widgets/printerwebcam/printerwebcamwidget.cpp \
    pages/printer/widgets/temperature/temperaturechart.cpp \
    pages/printer/widgets/temperature/temperaturewidget.cpp \
    pages/printer/widgets/toolhead/control/toolheadcontrolframe.cpp \
    pages/settings/edit_printer/editprinterdialog.cpp \
    pages/settings/edit_printer/qmoonrakervalidator.cpp \
    pages/settings/printerlistitem.cpp \
    pages/settings/printerlistwidget.cpp \
    pages/settings/settingspage.cpp \
    pages/settings/system/systemsettingspage.cpp \
    pages/settings/theme/themesettingspage.cpp \
    system/flo.cpp \
    system/qklipperinstancepool.cpp \
    system/settings.cpp \
    ui/PositionDialog/positiondialog.cpp \
    ui/ProgressDialog/progressdialog.cpp \
    ui/QIconButton/qiconbutton.cpp \
    ui/QMaskedButton/qmaskedbutton.cpp \
    ui/QThrobber/qthrobber.cpp \
    ui/QWebcamWidget/qwebcamsource.cpp \
    ui/QWebcamWidget/qwebcamwidget.cpp \
    ui/Switch/switch.cpp \
    ui/circularprogressbar.cpp \
    ui/common/cardwidget/cardwidget.cpp \
    ui/common/dialog/dialog.cpp \
    ui/layouts/qflowlayout.cpp \
    ui/list/qanimatedemptylistitem.cpp \
    ui/list/qanimatedlistitem.cpp \
    ui/list/qanimatedlistwidget.cpp \
    ui/menubutton.cpp \
    ui/messagedialog.cpp \
    ui/piddialog.cpp \
    ui/qanimatedwidget.cpp \
    ui/qwidgetanimation.cpp \
    ui/widgetanimation.cpp \
    validators/QHexColorValidator/qhexcolorvalidator.cpp \
    validators/QHttpValidator/qhttpvalidator.cpp \
    validators/QMoonrakerDirectoryValidator/qmoonrakerdirectoryvalidator.cpp

HEADERS += \
    QKlipper/QKlipperConsole/qklippercommand.h \
    QKlipper/QKlipperConsole/qklipperconsole.h \
    QKlipper/QKlipperFile/qklipperfile.h \
    QKlipper/QKlipperFile/qklippermetadata.h \
    QKlipper/QKlipperFile/qklipperthumbnail.h \
    QKlipper/QKlipperInstance/qklipperinstance.h \
    QKlipper/QKlipperMessage/qklippermessage.h \
    QKlipper/QKlipperPrinter/qklipperadjustmentscrew.h \
    QKlipper/QKlipperPrinter/qklipperchamber.h \
    QKlipper/QKlipperPrinter/qklipperendstopstatus.h \
    QKlipper/QKlipperPrinter/qklipperextruder.h \
    QKlipper/QKlipperPrinter/qklipperfan.h \
    QKlipper/QKlipperPrinter/qklippergcodemove.h \
    QKlipper/QKlipperPrinter/qklippermcu.h \
    QKlipper/QKlipperPrinter/qklipperposition.h \
    QKlipper/QKlipperPrinter/qklipperprintbed.h \
    QKlipper/QKlipperPrinter/qklipperprintbedmesh.h \
    QKlipper/QKlipperPrinter/qklipperprinter.h \
    QKlipper/QKlipperPrinter/qklipperprobedata.h \
    QKlipper/QKlipperPrinter/qklippersafezhome.h \
    QKlipper/QKlipperPrinter/qklippersteppermotor.h \
    QKlipper/QKlipperPrinter/qklippertemperaturestore.h \
    QKlipper/QKlipperPrinter/qklippertoolhead.h \
    QKlipper/QKlipperServer/qklipperaccessdetails.h \
    QKlipper/QKlipperServer/qklipperannouncement.h \
    QKlipper/QKlipperServer/qklipperclientidentifier.h \
    QKlipper/QKlipperServer/qklippergcodemacro.h \
    QKlipper/QKlipperServer/qklippergcodestore.h \
    QKlipper/QKlipperServer/qklippergcodestorevalue.h \
    QKlipper/QKlipperServer/qklipperjobqueue.h \
    QKlipper/QKlipperServer/qklipperprintjob.h \
    QKlipper/QKlipperServer/qklipperserver.h \
    QKlipper/QKlipperServer/qklipperuser.h \
    QKlipper/QKlipperSystem/qklippercanbus.h \
    QKlipper/QKlipperSystem/qklippercanbusdevice.h \
    QKlipper/QKlipperSystem/qklippercanbusinterface.h \
    QKlipper/QKlipperSystem/qklippercpuinfo.h \
    QKlipper/QKlipperSystem/qklipperdistributioninfo.h \
    QKlipper/QKlipperSystem/qklipperledstrip.h \
    QKlipper/QKlipperSystem/qklipperlibcameradevice.h \
    QKlipper/QKlipperSystem/qklipperlibcameramode.h \
    QKlipper/QKlipperSystem/qklippermemorystats.h \
    QKlipper/QKlipperSystem/qklippermoonrakerstatsentry.h \
    QKlipper/QKlipperSystem/qklippernetworkaddress.h \
    QKlipper/QKlipperSystem/qklippernetworkinterface.h \
    QKlipper/QKlipperSystem/qklippernetworkstatsentry.h \
    QKlipper/QKlipperSystem/qklipperpowerdevice.h \
    QKlipper/QKlipperSystem/qklippersdinfo.h \
    QKlipper/QKlipperSystem/qklippersensor.h \
    QKlipper/QKlipperSystem/qklippersensordata.h \
    QKlipper/QKlipperSystem/qklipperserialperipheral.h \
    QKlipper/QKlipperSystem/qklipperservice.h \
    QKlipper/QKlipperSystem/qklippersystem.h \
    QKlipper/QKlipperSystem/qklipperthrottlestate.h \
    QKlipper/QKlipperSystem/qklipperupdatecommit.h \
    QKlipper/QKlipperSystem/qklipperupdatemanager.h \
    QKlipper/QKlipperSystem/qklipperupdatepackage.h \
    QKlipper/QKlipperSystem/qklipperusbperipheral.h \
    QKlipper/QKlipperSystem/qklipperv412device.h \
    QKlipper/QKlipperSystem/qklipperv412mode.h \
    QKlipper/QKlipperSystem/qklippervirtualizationstate.h \
    QKlipper/QKlipperSystem/qklippervirtualsdcard.h \
    QKlipper/QKlipperSystem/qklipperwebcam.h \
    QKlipper/qklipper.h \
    QKlipper/qklippererror.h \
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
    pages/printer/bedmesh/adjustment/adjustmentscrewframe.h \
    pages/printer/bedmesh/adjustment/empty/adjustmentscrewemptyframe.h \
    pages/printer/bedmesh/adjustment/item/adjustmentscrewitemframe.h \
    pages/printer/bedmesh/bedmeshdata.h \
    pages/printer/bedmesh/bedmeshwidget.h \
    pages/printer/bedmesh/health/bedmeshhealthcard.h \
    pages/printer/bedmesh/probed/bedmeshframe.h \
    pages/printer/bedmesh/probed/empty/bedmeshemptyframe.h \
    pages/printer/bedmesh/probed/item/bedmeshitemframe.h \
    pages/printer/filebrowser/editor/fileeditor.h \
    pages/printer/filebrowser/filebrowser.h \
    pages/printer/filebrowser/filebrowseritem.h \
    pages/printer/filebrowser/filebrowserwidget.h \
    pages/printer/filebrowser/newfolder/newfolderdialog.h \
    pages/printer/filebrowser/overlay/filebrowseroverlay.h \
    pages/printer/filebrowser/preview/filepreviewwindow.h \
    pages/printer/ledstrips/ledstripcard.h \
    pages/printer/ledstrips/ledstripview.h \
    pages/printer/macros/gcodemacrodialog.h \
    pages/printer/offline/printerofflinescreen.h \
    pages/printer/powerdevices/powerdevicecard.h \
    pages/printer/powerdevices/powerdeviceview.h \
    pages/printer/printerpage.h \
    pages/printer/printing/printingpage.h \
    pages/printer/sensors/sensorcard.h \
    pages/printer/sensors/sensorview.h \
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
    pages/printer/terminal/printerterminal.h \
    pages/printer/terminal/printerterminalitem.h \
    pages/printer/terminal/printerterminalwidget.h \
    pages/printer/widgets/extruder/extruderinfodialog.h \
    pages/printer/widgets/extruder/extrudermaterialsdialog.h \
    pages/printer/widgets/extruder/extrudertemperaturechart.h \
    pages/printer/widgets/extruder/extrudertemperaturewidget.h \
    pages/printer/widgets/extruder/extruderwidget.h \
    pages/printer/widgets/printerbed/bedtemperaturechart.h \
    pages/printer/widgets/printerbed/bedtemperaturewidget.h \
    pages/printer/widgets/printerbed/printerbedinfodialog.h \
    pages/printer/widgets/printerbed/printerbedtoolsdialog.h \
    pages/printer/widgets/printerbed/printerbedwidget.h \
    pages/printer/widgets/printerfan/printerfanitem.h \
    pages/printer/widgets/printerfan/printerfanwidget.h \
    pages/printer/widgets/printerwebcam/empty/emptyprinterwebcamframe.h \
    pages/printer/widgets/printerwebcam/printerwebcamwidget.h \
    pages/printer/widgets/temperature/temperaturechart.h \
    pages/printer/widgets/temperature/temperaturewidget.h \
    pages/printer/widgets/toolhead/control/toolheadcontrolframe.h \
    pages/settings/edit_printer/editprinterdialog.h \
    pages/settings/edit_printer/qmoonrakervalidator.h \
    pages/settings/printerlistitem.h \
    pages/settings/printerlistwidget.h \
    pages/settings/settingspage.h \
    pages/settings/system/systemsettingspage.h \
    pages/settings/theme/themesettingspage.h \
    system/flo.h \
    system/qklipperinstancepool.h \
    system/settings.h \
    ui/PositionDialog/positiondialog.h \
    ui/ProgressDialog/progressdialog.h \
    ui/QIconButton/qiconbutton.h \
    ui/QMaskedButton/qmaskedbutton.h \
    ui/QThrobber/qthrobber.h \
    ui/QWebcamWidget/qwebcamsource.h \
    ui/QWebcamWidget/qwebcamwidget.h \
    ui/Switch/style.h \
    ui/Switch/switch.h \
    ui/circularprogressbar.h \
    ui/common/cardwidget/cardwidget.h \
    ui/common/dialog/dialog.h \
    ui/layouts/qflowlayout.h \
    ui/list/qanimatedemptylistitem.h \
    ui/list/qanimatedlistitem.h \
    ui/list/qanimatedlistwidget.h \
    ui/menubutton.h \
    ui/messagedialog.h \
    ui/piddialog.h \
    ui/qanimatedwidget.h \
    ui/qwidgetanimation.h \
    ui/widgetanimation.h \
    validators/QHexColorValidator/qhexcolorvalidator.h \
    validators/QHttpValidator/qhttpvalidator.h \
    validators/QMoonrakerDirectoryValidator/qmoonrakerdirectoryvalidator.h

FORMS += \
    mainwindow.ui \
    pages/dashboard/dashboardpage.ui \
    pages/dashboard/widgets/printer/printerwidget.ui \
    pages/dashboard/widgets/system/systemwidget.ui \
    pages/loading/loadingpage.ui \
    pages/printer/bedmesh/probed/empty/bedmeshemptyframe.ui \
    pages/printer/bedmesh/probed/item/bedmeshitemframe.ui \
    pages/printer/filebrowser/editor/fileeditor.ui \
    pages/printer/offline/printerofflinescreen.ui \
    pages/printer/printerpage.ui \
    pages/printer/settings/printersettingspage.ui \
    pages/printer/widgets/extruder/extruderwidget.ui \
    pages/printer/widgets/printerbed/printerbedwidget.ui \
    pages/settings/edit_printer/editprinterdialog.ui \
    pages/settings/printerlistitem.ui \
    pages/settings/printerlistwidget.ui \
    pages/settings/settingspage.ui \
    pages/settings/system/systemsettingspage.ui \
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
    QSourceHighlite/QSourceHighlite.pri \
    README.md \
    pages/printer/bedmesh/BedMeshViewer.qml

RESOURCES += \
    Resources.qrc \
    qml.qrc

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

DEFINES += QUAZIP_STATIC
DEFINES += APPLICATION_RESTART_CODE=-1000
LIBS += -L"3rdparty/QuaZip/lib/" -lquazip1-qt6
