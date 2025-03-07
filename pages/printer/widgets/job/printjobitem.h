/*
* Flo :: PrintJobItem
*
* Provides a list item for a queued print job
*
* Copyright (C) 2024-2025 DigitalArtifex
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PRINTJOBITEM_H
#define PRINTJOBITEM_H

#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QProgressBar>
#include <QGridLayout>
#include <QStringList>
#include <QToolButton>
#include <QTimer>

#include <QKlipper/qklipper.h>
#include "ui/list/qanimatedlistitem.h"

class PrintJobItem : public QAnimatedListItem
{
    Q_OBJECT

public:
    explicit PrintJobItem(QWidget *parent = nullptr);
    ~PrintJobItem();


    QKlipperPrintJob *printJob();
    void setPrintJob(QKlipperPrintJob *job);

signals:
    void removeRequest(PrintJobItem *item);

protected slots:
    void setupUi();
    void onPrintJobStateChanged();
    void onPrintJobCurrentLayerChanged();
    void onPrintJobTotalLayersChanged();
    void onInstanceNameChanged();

    void closeButtonClickEvent();
    void autoRemoveTimerTimeoutEvent();

private:
    QKlipperPrintJob *m_job;

    QLabel *m_jobNameLabel = nullptr;
    QLabel *m_printerNameLabel = nullptr;
    QLabel *m_timeRemainingLabel = nullptr;
    QLabel *m_timeRunningLabel = nullptr;
    QLabel *m_iconLabel = nullptr;
    QWidget *m_iconContainer = nullptr;
    QProgressBar *m_progressBar = nullptr;

    QToolButton *m_closeButton = nullptr;
    QTimer *m_autoRemoveTimer = nullptr;
};

Q_DECLARE_METATYPE(PrintJobItem)

#endif // PRINTJOBITEM_H
