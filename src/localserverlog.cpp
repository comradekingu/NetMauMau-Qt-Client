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

#include <QMenu>

#include "localserverlog.h"

LocalServerLog::LocalServerLog(QWidget *p) : QPlainTextEdit(p), m_terminateAction(0L) {}

void LocalServerLog::contextMenuEvent(QContextMenuEvent *e) {

	QMenu *menu = createStandardContextMenu();

	if(m_terminateAction) {
		menu->addSeparator();
		menu->addAction(m_terminateAction);
	}

	menu->exec(e->globalPos());

	delete menu;
}

void LocalServerLog::setTerminateAction(QAction *a) {
	m_terminateAction = a;
}
