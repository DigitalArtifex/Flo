#ifndef PRINTERTERMINALEDIT_H
#define PRINTERTERMINALEDIT_H

#include <QTextEdit>
#include <QTextBlock>
#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include <QStyle>

class PrinterTerminalEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit PrinterTerminalEdit(QWidget *parent = nullptr);

    void addMessage(QString message);

    QString user() const;

    QString host() const;

    QStringList commandDictionary() const;

    QMultiMap<QString, QString> parameterDictionary() const;

public slots:
    void clear();

    void setUser(const QString &user);

    void setHost(const QString &host);

    void setCommandDictionary(const QStringList &commandDictionary);

    void setParameterDictionary(const QMultiMap<QString, QString> &parameterDictionary);

signals:
    void commandEntered(QString);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;


private slots:
    void resetAutoComplete();

private:
    qint64 m_inputPos = 0;
    qint64 m_linePos = 0;

    QString m_user = "user";
    QString m_host = "host";

    bool m_autoComplete = false;
    bool m_parameterAutoComplete = false;
    bool m_autoCompleteEdit = false;
    bool m_autoCompleteNoParameterToken = false;

    int m_autoCompleteIndex = 0;
    QString m_autoCompleteInput;
    QStringList m_autoCompleteList;
    QStringList m_commandDictionary;
    QMultiMap<QString,QString> m_parameterDictionary;
};

#endif // PRINTERTERMINALEDIT_H
