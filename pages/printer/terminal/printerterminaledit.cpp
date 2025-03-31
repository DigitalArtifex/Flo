#include "printerterminaledit.h"
#include "flo/settings.h"

PrinterTerminalEdit::PrinterTerminalEdit(QWidget *parent)
    : QTextEdit(parent)
{
    QString inputPrefix =
        QString("<font color=\"%1\"><b>%2@%3 $</b></font> ").arg
        (
            Settings::get("theme/highlight-block").toString(),
            m_user,
            m_host
            );
    QString measuredPrefix = QString("%1@%2 $ ").arg(m_user, m_host);
    append(inputPrefix);
    m_inputPos = m_linePos + measuredPrefix.length();

    QTextCursor cursor(document()->findBlock(0));

    //reset linePos
    cursor.movePosition(QTextCursor::End);

    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(resetAutoComplete()));
}

void PrinterTerminalEdit::addMessage(QString message)
{
    QTextBlock block = document()->findBlock(m_inputPos);

    if(block.isValid())
    {
        QString input = block.text().mid(block.text().indexOf('$') + 1);

        while(input.startsWith(" "))
            input.remove(0,1);

        QTextCursor cursor(block);
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();

        append(message);

        //reset linePos
        cursor.movePosition(QTextCursor::End);
        m_linePos = cursor.position();

        QString inputPrefix =
            QString("<font color=\"%1\"><b>%2@%3 $</b></font> ").arg
            (
                Settings::get("theme/highlight-block").toString(),
                m_user,
                m_host
                );
        QString measuredPrefix = QString("%1@%2 $ ").arg(m_user, m_host);

        append(inputPrefix + input);

        m_inputPos = m_linePos + measuredPrefix.length() + 1; //+1 for the newline added with append()

        //move cursor to new inputPos
        cursor.movePosition(QTextCursor::End);
    }
}

void PrinterTerminalEdit::clear()
{
    QTextEdit::clear();

    QString inputPrefix =
        QString("<font color=\"%1\"><b>%2@%3 $</b></font> ").arg
        (
            Settings::get("theme/highlight-block").toString(),
            m_user,
            m_host
            );
    QString measuredPrefix = QString("%1@%2 $ ").arg(m_user, m_host);
    append(inputPrefix);

    //installEventFilter(this);

    QTextCursor cursor(document()->findBlock(0));

    //reset linePos
    cursor.movePosition(QTextCursor::End);
    m_inputPos = textCursor().position();
}

void PrinterTerminalEdit::keyPressEvent(QKeyEvent *event)
{
    //explicitly allow out of bounds copy
    if(event->keyCombination().toCombined() == (Qt::Key_Control | Qt::Key_C) && textCursor().position() < m_inputPos)
    {
        copy();
        event->accept();
        return;
    }

    //ignore edits outside input bounds
    if(textCursor().position() < m_inputPos)
    {
        event->accept();
        return;
    }

    //ignore backspace at inputPos
    if(event->key() == Qt::Key_Backspace  && textCursor().position() == m_inputPos)
    {
        event->accept();
        return;
    }

    else if(event->key() == Qt::Key_Backspace && m_autoComplete)
    {
        m_autoCompleteEdit = true;

        QTextCursor cursor = textCursor();
        cursor.select(QTextCursor::WordUnderCursor);
        cursor.removeSelectedText();
        cursor.insertText(m_autoCompleteInput);

        m_autoCompleteEdit = false;

        resetAutoComplete();

        event->accept();
        return;
    }

    else if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        //accept auto complete
        if(m_autoComplete)
        {
            m_autoCompleteEdit = true;

            bool block = true;

            textCursor().movePosition(QTextCursor::End);

            if(m_parameterAutoComplete)
            {
                if(!m_autoCompleteNoParameterToken)
                    textCursor().insertText("=");
            }
            else if(m_parameterDictionary.contains(m_autoCompleteList[m_autoCompleteIndex]))
            {
                if(!m_autoCompleteNoParameterToken)
                    textCursor().insertText(" ");
            }
            else
                block = false;

            m_autoCompleteEdit = false;

            resetAutoComplete();

            if(block)
            {
                event->accept();
                return;
            }
        }

        QTextBlock block = document()->findBlock(m_inputPos);
        QTextCursor cursor(block);

        if(block.isValid())
        {
            QString input = block.text().mid(block.text().indexOf('$') + 1);

            while(input.startsWith(" "))
                input.remove(0,1);

            if(input.length() <= 0)
            {
                event->accept();
                return;
            }

            //reset linePos
            cursor.movePosition(QTextCursor::End);
            m_linePos = cursor.position();

            QString inputPrefix =
                QString("<font color=\"%1\"><b>%2@%3 $</b></font> ").arg
                (
                    Settings::get("theme/highlight-block").toString(),
                    m_user,
                    m_host
                );
            QString measuredPrefix = QString("%1@%2 $ ").arg(m_user, m_host);

            append(inputPrefix);

            m_inputPos = m_linePos + measuredPrefix.length() + 1; //+1 for the newline added with append()

            //move cursor to new inputPos
            cursor.movePosition(QTextCursor::End);

            emit commandEntered(input);

            event->accept();
            return;
        }
    }
    else if(event->key() == Qt::Key_Tab)
    {
        m_autoCompleteEdit = true;

        QTextCursor cursor = textCursor();

        int cursorPostion = cursor.position();

        cursor.setPosition(m_inputPos);
        cursor.select(QTextCursor::SelectionType::WordUnderCursor);
        QString commandWord = cursor.selectedText();

        cursor.setPosition(cursorPostion);
        cursor.select(QTextCursor::SelectionType::WordUnderCursor);
        QString selectedWord = cursor.selectedText();

        if(!m_autoComplete)
        {
            m_autoComplete = true;
            m_autoCompleteInput = selectedWord;

            if(commandWord == selectedWord)
                m_autoCompleteList = m_commandDictionary.filter(QRegularExpression(QString("^") + commandWord));
            else
            {
                if(commandWord.toUpper() == "HELP")
                    m_autoCompleteNoParameterToken = true;

                m_parameterAutoComplete = true;
                m_autoCompleteList = m_parameterDictionary.values(commandWord).filter(QRegularExpression(selectedWord.toUpper()));
            }

            m_autoCompleteList.sort(Qt::CaseInsensitive);
        }

        if(++m_autoCompleteIndex >= m_autoCompleteList.count())
            m_autoCompleteIndex = 0;

        if(m_autoCompleteList.count() > m_autoCompleteIndex)
        {
            cursor.removeSelectedText();
            cursor.insertText(m_autoCompleteList.at(m_autoCompleteIndex));
        }

        m_autoCompleteEdit = false;
        event->accept();
        return;
    }

    resetAutoComplete();
    QTextEdit::keyPressEvent(event);
}

void PrinterTerminalEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = new QMenu(this);

    QAction *copyAction = new QAction(QIcon::fromTheme("edit-copy"), "Copy");
    copyAction->setEnabled(textCursor().hasSelection());
    connect(copyAction, SIGNAL(triggered(bool)), this, SLOT(copy()));

    QAction *pasteAction = new QAction(QIcon::fromTheme("edit-paste"), "Paste");
    pasteAction->setEnabled(textCursor().position() >= m_inputPos);
    connect(pasteAction, SIGNAL(triggered(bool)), this, SLOT(paste()));

    QAction *cutAction = new QAction(QIcon::fromTheme("edit-cut"), "Cut");
    cutAction->setEnabled(textCursor().position() >= m_inputPos && textCursor().hasSelection());
    connect(cutAction, SIGNAL(triggered(bool)), this, SLOT(cut()));

    menu->addAction(copyAction);
    menu->addAction(pasteAction);
    menu->addAction(cutAction);
    menu->exec(event->globalPos());

    delete menu;
}

void PrinterTerminalEdit::resetAutoComplete()
{
    //ignore events fired by cursorPositionChanged while performing autocomplete
    if(m_autoCompleteEdit)
        return;

    m_autoComplete = false;
    m_parameterAutoComplete = false;
    m_autoCompleteNoParameterToken = false;
    m_autoCompleteIndex = -1;
    m_autoCompleteList.clear();
    m_autoCompleteInput = "";
}

QMultiMap<QString, QString> PrinterTerminalEdit::parameterDictionary() const
{
    return m_parameterDictionary;
}

void PrinterTerminalEdit::setParameterDictionary(const QMultiMap<QString, QString> &parameterDictionary)
{
    m_parameterDictionary = parameterDictionary;
}

QStringList PrinterTerminalEdit::commandDictionary() const
{
    return m_commandDictionary;
}

void PrinterTerminalEdit::setCommandDictionary(const QStringList &commandDictionary)
{
    m_commandDictionary = commandDictionary;
}

QString PrinterTerminalEdit::host() const
{
    return m_host;
}

void PrinterTerminalEdit::setHost(const QString &host)
{
    if(host == m_host)
        return;

    m_host = host;
    clear();
}

QString PrinterTerminalEdit::user() const
{
    return m_user;
}

void PrinterTerminalEdit::setUser(const QString &user)
{
    if(user == m_user)
        return;

    m_user = user;
    clear();
}
