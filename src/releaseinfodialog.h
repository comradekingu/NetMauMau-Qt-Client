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

#ifndef RELEASEINFODIALOG_H
#define RELEASEINFODIALOG_H

#include "netmaumaudialog.h"

#include "ui_releaseinfodialog.h"

class QProgressDialog;
class QGitHubReleaseAPI;

class ReleaseInfoDialog : public NetMauMauDialog, private Ui::ReleaseInfoDialog {
	Q_OBJECT
	Q_DISABLE_COPY(ReleaseInfoDialog)
	Q_PROPERTY(QString releaseText READ releaseText WRITE setReleaseText)
	Q_PROPERTY(QDateTime releaseDate READ releaseDate WRITE setReleaseDate)
	Q_PROPERTY(QUrl dlUrl READ dlUrl WRITE setDlUrl)
	Q_PROPERTY(QImage avatar READ avatar WRITE setAvatar)
	Q_PROPERTY(QString login READ login WRITE setLogin)
public:
	explicit ReleaseInfoDialog(const QGitHubReleaseAPI *api, QWidget *parent = 0);

	QString releaseText() const;
	void setReleaseText(const QString &releaseText);

	QDateTime releaseDate() const;
	void setReleaseDate(const QDateTime &releaseDate);

	QUrl dlUrl() const;
	void setDlUrl(const QUrl &u);

	QImage avatar() const;
	void setAvatar(const QImage &a);

	QString login() const;
	void setLogin(const QString &);

private slots:
	void progress(qint64 bytesReceived, qint64 bytesTotal);
	void error(const QString &);
	void downloadZip();
	void downloadTar();

private:
	void save(const QString &fn, const QString &filter, const QByteArray &ba);

private:
	QString m_login;
	QProgressDialog *m_progress;
	const QGitHubReleaseAPI *m_api;
	bool m_hasError;
};

#endif // RELEASEINFODIALOG_H
