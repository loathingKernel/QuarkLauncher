// Copyright (C) 2016 Petar Perisin <petar.perisin@gmail.com>
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

#pragma once

#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QPlainTextEdit;
QT_END_NAMESPACE

namespace Utils {

    class FormattedText {
    public:
        FormattedText() = default;
        FormattedText(const QString &txt, const QTextCharFormat &fmt = QTextCharFormat()) :
            text(txt), format(fmt)
        { }

        QString text;
        QTextCharFormat format;
    };

    class AnsiEscapeCodeHandler
    {
    public:
        QList<FormattedText> parseText(const FormattedText &input);
        void endFormatScope();
        static void setTextInEditor(QPlainTextEdit *editor, const QString &text);
        static QString ansiFromColor(const QColor &color);
        static QString noColor();

    private:
        void setFormatScope(const QTextCharFormat &charFormat);

        bool            m_previousFormatClosed = true;
        bool            m_waitingForTerminator = false;
        QString         m_alternateTerminator;
        QTextCharFormat m_previousFormat;
        QString         m_pendingText;
    };

} // namespace Utils
