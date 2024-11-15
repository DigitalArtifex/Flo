/*
 * Copyright (c) 2019-2020 Waqar Ahmed -- <waqar.17a@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "qsourcehighliterthemes.h"
#include "../system/settings.h"

namespace QSourceHighlite {

static QHash<QSourceHighliter::Token, QTextCharFormat> formats()
{
    QHash<QSourceHighliter::Token, QTextCharFormat> m_formats;

    QTextCharFormat defaultFormat = QTextCharFormat();

    m_formats[QSourceHighliter::Token::CodeBlock] = defaultFormat;
    m_formats[QSourceHighliter::Token::CodeKeyWord] = defaultFormat;
    m_formats[QSourceHighliter::Token::CodeString] = defaultFormat;
    m_formats[QSourceHighliter::Token::CodeComment] = defaultFormat;
    m_formats[QSourceHighliter::Token::CodeType] = defaultFormat;
    m_formats[QSourceHighliter::Token::CodeOther] = defaultFormat;
    m_formats[QSourceHighliter::Token::CodeNumLiteral] = defaultFormat;
    m_formats[QSourceHighliter::Token::CodeBuiltIn] = defaultFormat;

    return m_formats;
}

static QHash<QSourceHighliter::Token, QTextCharFormat> monokai()
{
    QHash<QSourceHighliter::Token, QTextCharFormat> m_formats = formats();

    m_formats[QSourceHighliter::Token::CodeBlock].setForeground(QColor(227, 226, 214));
    m_formats[QSourceHighliter::Token::CodeKeyWord].setForeground(QColor(249, 38, 114));
    m_formats[QSourceHighliter::Token::CodeString].setForeground(QColor(230, 219, 116));
    m_formats[QSourceHighliter::Token::CodeComment].setForeground(QColor(117, 113, 94));
    m_formats[QSourceHighliter::Token::CodeType].setForeground(QColor(102, 217, 239));
    m_formats[QSourceHighliter::Token::CodeOther].setForeground(QColor(249, 38, 114));
    m_formats[QSourceHighliter::Token::CodeNumLiteral].setForeground(QColor(174, 129, 255));
    m_formats[QSourceHighliter::Token::CodeBuiltIn].setForeground(QColor(166, 226, 46));

    return m_formats;
}

static QHash<QSourceHighliter::Token, QTextCharFormat> system()
{
    QHash<QSourceHighliter::Token, QTextCharFormat> m_formats = formats();

    m_formats[QSourceHighliter::Token::CodeBlock].setForeground(QColor::fromString(Settings::get("theme/highlight-block").toString()));
    m_formats[QSourceHighliter::Token::CodeKeyWord].setForeground(QColor::fromString(Settings::get("theme/highlight-keyword").toString()));
    m_formats[QSourceHighliter::Token::CodeString].setForeground(QColor::fromString(Settings::get("theme/highlight-string").toString()));
    m_formats[QSourceHighliter::Token::CodeComment].setForeground(QColor::fromString(Settings::get("theme/highlight-comment").toString()));
    m_formats[QSourceHighliter::Token::CodeType].setForeground(QColor::fromString(Settings::get("theme/highlight-type").toString()));
    m_formats[QSourceHighliter::Token::CodeOther].setForeground(QColor::fromString(Settings::get("theme/highlight-other").toString()));
    m_formats[QSourceHighliter::Token::CodeNumLiteral].setForeground(QColor::fromString(Settings::get("theme/highlight-numerical").toString()));
    m_formats[QSourceHighliter::Token::CodeBuiltIn].setForeground(QColor::fromString(Settings::get("theme/highlight-builtin").toString()));

    return m_formats;
}

QHash<QSourceHighliter::Token, QTextCharFormat>
        QSourceHighliterTheme::theme(QSourceHighliter::Themes theme) {
    switch (theme) {
    case QSourceHighliter::Themes::Monokai:
        return monokai();
    case QSourceHighliter::Themes::System:
        return system();
    default:
        return {};
    }
}

}
