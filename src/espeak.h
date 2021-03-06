/*
 * Copyright 2015 by Heiko Schäfer <heiko@rangun.de>
 *
 * This file is part of NetMauMau Qt Client.
 *
 * NetMauMau Qt Client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * NetMauMau Qt Client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with NetMauMau Qt Client.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ESPEAK_H
#define ESPEAK_H

#include <QObject>

#include <linkercontrol.h>

#define TR_SPEAK_ARG(text, argument) \
	ESpeak::getInstance().speak(tr(text).arg(argument), tr(text).arg(argument) == \
	QString(text).arg(argument) ? QString("en") : QString::null)

#define TR_SPEAK_NUM(text, ntext, num) \
	ESpeak::getInstance().speak((text), (text) == QString(ntext).arg(QString::number(num)) ? \
	QString("en") : QString::null)

class ESpeak : public QObject {
	Q_OBJECT
	Q_DISABLE_COPY(ESpeak)
public:
	~ESpeak();

	static ESpeak &getInstance();

	void speak(const QString &text, QString lang = QString::null);
	void stop() const;

	bool isDisabled() const _PURE;
	int getVolume() const;

public slots:
	void setDisabled(bool);
	void setVolume(int);

private slots:
	void speakNow();

private:
	explicit ESpeak(QObject *parent = 0);

	bool isSpeaking() const;

private:
	QByteArray m_speakTxt;
	QString m_lang;
	const QString m_systemLang;
	char *m_path;
	bool m_enabled;
};

#endif // ESPEAK_H
