#ifndef FILEPREVIEWWINDOW_H
#define FILEPREVIEWWINDOW_H

#include <QObject>
#include <QWidget>
#include <QDialog>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMovie>

#include "types/printer.h"
#include "types/klipperfile.h"
#include "ui/QIconButton/qiconbutton.h"

#include "ui/common/dialog/dialog.h"

class FilePreviewWindow : public Dialog
{
    Q_OBJECT
public:
    explicit FilePreviewWindow(KlipperFile file, Printer *printer, QWidget *parent = nullptr);
    ~FilePreviewWindow();

    KlipperFile file() const;

    virtual void setStyleSheet(QString &styleSheet);

protected:
    void setupUi();

protected slots:
    void applyButtonClickEvent();
    void cancelButtonClickEvent();
    void metaDataResultEvent(KlipperFile::Metadata metadata);

private:
    KlipperFile m_file;
    Printer *m_printer = nullptr;

    QGridLayout *m_contentLayout = nullptr;
    QVBoxLayout *m_layout = nullptr;
    QHBoxLayout *m_footerLayout = nullptr;

    QLabel *m_thumbnailLabel = nullptr;
    QLabel *m_nameLabel = nullptr;
    QLabel *m_layerHeightLabel = nullptr;
    QLabel *m_objectHeightLabel = nullptr;
    QLabel *m_filamentTotalLabel = nullptr;
    QLabel *m_estimatedTimeLabel = nullptr;
    QLabel *m_FilamentNameLabel = nullptr;
    QLabel *m_nozzleTemperatureLabel = nullptr;
    QLabel *m_nozzleDiameterLabel = nullptr;
    QLabel *m_bedTemperatureLabel = nullptr;
    QLabel *m_slicerVersionLabel = nullptr;

    QWidget *m_contentWidget = nullptr;
    QWidget *m_footerWidget = nullptr;

    QSpacerItem *m_contentTopSpacer = nullptr;
    QSpacerItem *m_contentBottomSpacer = nullptr;

    QIconButton *m_applyButton = nullptr;
    QIconButton *m_cancelButton = nullptr;
};

#endif // FILEPREVIEWWINDOW_H
