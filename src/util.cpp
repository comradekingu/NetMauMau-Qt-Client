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

#include <QRegExp>

#include "util.h"

namespace {
const QString replace("<span style=\"color:red;\">\\1 \\2</span>");
const QRegExp heartsRex("(" + QString::fromUtf8("\u2665") + ") ([0-9]{1,2}|[JQKA])");
const QRegExp diamondsRex("(" + QString::fromUtf8("\u2666") + ") ([0-9]{1,2}|[JQKA])");
}

Util::Util() {}

QString &Util::cardStyler(QString &c) {
	c.replace(diamondsRex, replace);
	return c.replace(heartsRex, replace);
}

QString Util::cardStyler(const QString &c) {
	QString ret = c;
	return cardStyler(ret);
}
