/*
 * local-conference.h
 * Copyright (C) 2010-2017 Belledonne Communications SARL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef _LOCAL_CONFERENCE_H_
#define _LOCAL_CONFERENCE_H_

#include "conference.h"
#include "local-conference-event-handler.h"

// =============================================================================

LINPHONE_BEGIN_NAMESPACE

class LocalConference : public Conference {
public:
	LocalConference (LinphoneCore *core, const Address &myAddress, CallListener *listener = nullptr);
	virtual ~LocalConference();

	LocalConferenceEventHandler * getEventHandler() const { return eventHandler; }

public:
	/* ConferenceInterface */
	void addParticipant (const Address &addr, const CallSessionParams *params, bool hasMedia) override;
	void removeParticipant (const std::shared_ptr<const Participant> &participant) override;

	std::list<Address> parseResourceLists (std::string xmlBody);

protected:
	LocalConferenceEventHandler *eventHandler = nullptr;

private:
	L_DISABLE_COPY(LocalConference);
};

LINPHONE_END_NAMESPACE

#endif // ifndef _LOCAL_CONFERENCE_H_