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

#ifndef NETMAUMAUMESSAGEBOX_H
#define NETMAUMAUMESSAGEBOX_H

#include <QMessageBox>

class NetMauMauMessageBox : public QMessageBox {
	Q_OBJECT
public:
	explicit NetMauMauMessageBox(QWidget *parent = 0);

	explicit NetMauMauMessageBox(const QString &title, const QString &txt,
								 const QPixmap &pixmap, QWidget *parent = 0);

private:
	void init();
};

#endif // NETMAUMAUMESSAGEBOX_H
