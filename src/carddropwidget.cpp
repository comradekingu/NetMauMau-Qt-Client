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

#include <QBoxLayout>
#include <QDragEnterEvent>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QMimeData>
#endif

#include "carddropwidget.h"

#include "gamestate.h"

CardDropWidget::CardDropWidget(QWidget *p) : QWidget(p), m_gameState(0L) {
	setAcceptDrops(true);
}

void CardDropWidget::setGameState(GameState *gs) {
	m_gameState = gs;
}

void CardDropWidget::dragEnterEvent(QDragEnterEvent *e) {

	if(e->mimeData()->hasFormat("application/x-dndcardwidget")) {
		e->acceptProposedAction();
	} else {
		e->ignore();
	}
}

void CardDropWidget::dropEvent(QDropEvent *e) {

	if(e->mimeData()->hasFormat("application/x-dndcardwidget")) {

#if QT_VERSION <= QT_VERSION_CHECK(5, 0, 0)
		QWidget *src = e->source();
#else
		QWidget *src = dynamic_cast<QWidget *>(e->source());
#endif

		if(src && e->mimeData()->data("application/x-dndcardwidget") ==
				src->property("cardDescription").toByteArray()) {

			QLayout *l = layout();

			if(l) {

				QWidget *dst = childAt(e->pos());

				const int didx = dst ? l->indexOf(dst) + 1 :
									   (e->pos().x() < src->mapToGlobal(src->pos()).x() ?
											0 : l->count());

				if(m_gameState) {
					m_gameState->cards().insert(didx, m_gameState->cards().takeAt(l->indexOf(src)));
				}

				static_cast<QBoxLayout *>(l)->insertWidget(didx,
														   l->takeAt(l->indexOf(src))->widget());
				e->acceptProposedAction();
				emit cardsReordered();
				return;
			}
		}
	}

	e->ignore();
}
