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

#include "addserverdialog.h"

AddServerDialog::AddServerDialog(QWidget *p) : QDialog(p), m_okButton(0L) {

	Qt::WindowFlags f = windowFlags();
	f &= ~Qt::WindowContextHelpButtonHint;
	f &= ~Qt::WindowSystemMenuHint;
	setWindowFlags(f);

	setupUi(this);

	serverAdd->getAddButton()->hide();

	for(int i = 0; buttonBox->buttons().count(); ++i) {
		if(buttonBox->buttonRole(buttonBox->buttons()[i]) == QDialogButtonBox::AcceptRole) {
			m_okButton = buttonBox->buttons()[i];
			break;
		}
	}

	if(m_okButton) {
		m_okButton->setDisabled(true);
		QObject::connect(m_okButton, SIGNAL(clicked()), this, SLOT(addServerClicked()));
	}

	QObject::connect(serverAdd->getHostEdit(), SIGNAL(textChanged(QString)),
					 this, SLOT(enableOkButton(QString)));
}

void AddServerDialog::enableOkButton(const QString &str) {
	m_okButton->setDisabled(str.isEmpty());
}

void AddServerDialog::addServerClicked() {
	emit addServer(serverAdd->getHost(), serverAdd->getPort());
}
