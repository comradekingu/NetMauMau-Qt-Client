/*
 * Copyright 2014 by Heiko Schäfer <heiko@rangun.de>
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

#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>

#include "launchserverdialog.h"

#include "client.h"
#include "cardtools.h"

LaunchServerDialog::LaunchServerDialog(QWidget *p) : QDialog(p), m_process() {

	setupUi(this);

	QSettings settings;
	settings.beginGroup("Launcher");
	playersSpin->setValue(settings.value("playersSpin", 1).toInt());
	ultimateCheck->setChecked(settings.value("ultimate", false).toBool());
	aiNameEdit->setText(settings.value("aiName",
									   QString::fromUtf8(Client::getDefaultAIName())).toString());
	portSpin->setValue(settings.value("port", Client::getDefaultPort()).toInt());
	pathEdit->setText(settings.value("serverExe",
									 QString::fromUtf8(NetMauMau::Common::getServerExe()))
					  .toString());
	settings.endGroup();

	QObject::connect(execChooseButton, SIGNAL(clicked()), this, SLOT(browse()));
	QObject::connect(playersSpin, SIGNAL(valueChanged(int)), this, SLOT(updateOptions()));
	QObject::connect(ultimateCheck, SIGNAL(stateChanged(int)), this, SLOT(updateOptions()));
	QObject::connect(aiNameEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateOptions()));
	QObject::connect(portSpin, SIGNAL(valueChanged(int)), this, SLOT(updateOptions()));
	QObject::connect(launchButton, SIGNAL(clicked()), this, SLOT(launch()));
	QObject::connect(&m_process, SIGNAL(started()), this, SLOT(launched()));
	QObject::connect(&m_process, SIGNAL(error(QProcess::ProcessError)),
					 this, SLOT(error(QProcess::ProcessError)));
	QObject::connect(&m_process, SIGNAL(finished(int)), this, SLOT(finished(int)));

	updateOptions();
}

LaunchServerDialog::~LaunchServerDialog() {

	QSettings settings;
	settings.beginGroup("Launcher");
	settings.setValue("playersSpin", playersSpin->value());
	settings.setValue("ultimate", ultimateCheck->isChecked());
	settings.setValue("aiName", aiNameEdit->text());
	settings.setValue("port", portSpin->value());
	settings.setValue("serverExe", pathEdit->text());
	settings.endGroup();

	if(m_process.state() == QProcess::Running) {

#ifndef _WIN32
		m_process.terminate();
#else
		m_process.kill();
#endif

		m_process.waitForFinished();
	}
}

void LaunchServerDialog::updateOptions() {

	QString opt;

	if(portSpin->value() != Client::getDefaultPort()) {
		opt.append("-P").append(QString::number(portSpin->value())).append(" ");
	}

	if(playersSpin->value() != 1) {
		opt.append("-p").append(QString::number(playersSpin->value())).append(" ");
	}

	if(!aiNameEdit->text().isEmpty()) {
		opt.append("-A\"").append(aiNameEdit->text()).append("\" ");
	}

	if(ultimateCheck->isChecked()) opt.append("-u");

	optionsEdit->setText(opt.trimmed());
}

void LaunchServerDialog::finished(int ec) {
	if(ec) QMessageBox::warning(this, "Warning", QString("Failed to start %1").
								arg(QString(pathEdit->text()).append(" ")
									.append(optionsEdit->text())));
	launchButton->setDisabled(false);
}

void LaunchServerDialog::launched() {
	launchButton->setDisabled(true);
	emit serverLaunched();
}

void LaunchServerDialog::launch() {

	qDebug("Launching %s...",
		   QString(pathEdit->text()).append(" ").append(optionsEdit->text()).toUtf8().constData());

	QStringList args;

	if(portSpin->value() != Client::getDefaultPort()) {
		args << QString("-P").append(QString::number(portSpin->value()));
	}

	if(playersSpin->value() != 1) {
		args << QString("-p").append(QString::number(playersSpin->value()));
	}

	if(!aiNameEdit->text().isEmpty()) {
		args << QString("-A").append(aiNameEdit->text());
	}

	if(ultimateCheck->isChecked()) args << "-u";

	m_process.start(pathEdit->text(), args);
}

void LaunchServerDialog::error(QProcess::ProcessError) {
	QMessageBox::critical(this, "Error", QString("Failed to start %1").
						  arg(QString(pathEdit->text()).append(" ").append(optionsEdit->text())));
}

void LaunchServerDialog::browse() {

#ifndef _WIN32
	const QString filter = QString::null;
#else
	const QString filter("*.exe");
#endif

	pathEdit->setText(QFileDialog::getOpenFileName(this, "Find NetMauMau server executable",
												   pathEdit->text().isEmpty() ?
													   QDir::currentPath() : pathEdit->text(),
												   filter));
}
