#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QGridLayout>
#include <QScreen>
#include <QTextEdit>
#include <QProgressBar>

#include <common/dialog/dialog.h>
#include <ui/QIconButton/qiconbutton.h>

class ProgressDialog : public Dialog
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit ProgressDialog(QWidget *parent = nullptr);

        void addInfoText(const QString &text);
        void setValueText(const QString &text);
        void setValueValue(const qreal &progress);
        void setValueMinimum(const qreal &value);
        void setValueMaximum(const qreal &value);

    signals:

    private slots:
        void setupUi();

    private:
        QGridLayout *m_centralLayout = nullptr;
        QTextEdit *m_infoEdit = nullptr;
        QProgressBar *m_progressBar = nullptr;
};

#endif // PROGRESSDIALOG_H
