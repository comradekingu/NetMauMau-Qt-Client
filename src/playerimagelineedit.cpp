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

#include <QUrl>
#include <QDragEnterEvent>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QMimeData>
#endif

#include "playerimagelineedit.h"

PlayerImageLineEdit::PlayerImageLineEdit(QWidget *p) : QLineEdit(p) {
	setReadOnly(true);
	setAcceptDrops(true);
}

void PlayerImageLineEdit::dragEnterEvent(QDragEnterEvent *evt) {

#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
	const bool accept = evt->mimeData()->hasUrls() && evt->mimeData()->urls().first().isLocalFile();
#else
	const bool accept = evt->mimeData()->hasUrls();
#endif

	if(accept) evt->acceptProposedAction();
}

void PlayerImageLineEdit::dropEvent(QDropEvent *evt) {

	if(evt->mimeData()->hasUrls()) {

		const QUrl url(evt->mimeData()->urls().first());

#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
		if(url.isLocalFile()) {
#endif
			setText(url.toLocalFile());
			evt->acceptProposedAction();
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
		}
#endif
	}
}
