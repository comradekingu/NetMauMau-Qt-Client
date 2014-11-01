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

#include "cardwidget.h"
#include "cardtools.h"

CardWidget::CardWidget(QWidget *p, const QByteArray &cardDesc) : QPushButton(p),
	NetMauMau::Common::ICard(), m_defaultStyleSheet() {

	setupUi(this);

	m_defaultStyleSheet = styleSheet();

	QObject::connect(this, SIGNAL(clicked()), this, SLOT(clickedCard()));

	if(!cardDesc.isEmpty()) setProperty("cardDescription", cardDesc);
}

NetMauMau::Common::ICard::SUIT CardWidget::getSuit() const {

	NetMauMau::Common::ICard::SUIT s = NetMauMau::Common::ICard::HEARTS;
	NetMauMau::Common::ICard::RANK r = NetMauMau::Common::ICard::ACE;

	if(NetMauMau::Common::parseCardDesc(description(false), &s, &r)) {
		return s;
	}

	return NetMauMau::Common::ICard::HEARTS;
}

NetMauMau::Common::ICard::RANK CardWidget::getRank() const {

	NetMauMau::Common::ICard::SUIT s = NetMauMau::Common::ICard::HEARTS;
	NetMauMau::Common::ICard::RANK r = NetMauMau::Common::ICard::ACE;

	if(NetMauMau::Common::parseCardDesc(description(false), &s, &r)) {
		return r;
	}

	return NetMauMau::Common::ICard::ACE;
}

std::size_t CardWidget::getPoints() const {
	return NetMauMau::Common::getCardPoints(getRank());
}

std::string CardWidget::description(bool) const {
	return property("cardDescription").toByteArray().constData();
}

bool CardWidget::event(QEvent *e) {

	if(e->type() == QEvent::DynamicPropertyChange &&
			(static_cast<QDynamicPropertyChangeEvent *>(e)->propertyName() == "cardDescription")) {
		styleCard();
	}

	return QPushButton::event(e);
}

void CardWidget::clickedCard() {
	emit chosen(this);
}

void CardWidget::changeEvent(QEvent *e) {

	QPushButton::changeEvent(e);

	if(e->type() == QEvent::EnabledChange) styleCard();
}

void CardWidget::styleCard() {

	const QByteArray &cardDesc(property("cardDescription").toByteArray());

	NetMauMau::Common::ICard::SUIT s = NetMauMau::Common::ICard::HEARTS;
	NetMauMau::Common::ICard::RANK r = NetMauMau::Common::ICard::ACE;

	if(NetMauMau::Common::parseCardDesc(cardDesc.constData(), &s, &r)) {
		if(isEnabled() && (s == NetMauMau::Common::ICard::HEARTS ||
						   s == NetMauMau::Common::ICard::DIAMONDS)) {
			setStyleSheet("QPushButton {color: red;}");
		} else {
			setStyleSheet(m_defaultStyleSheet);
		}
	}

	setText(QString::fromUtf8(cardDesc.constData()));
}
