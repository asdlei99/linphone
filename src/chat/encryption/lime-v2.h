/*
 * cpim-chat-message-modifier.h
 * Copyright (C) 2010-2018 Belledonne Communications SARL
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

#ifndef _L_LIME_V2_H_
#define _L_LIME_V2_H_

#include "belle-sip/belle-sip.h"
#include "belle-sip/http-listener.h"
#include "carddav.h"
#include "core/core-listener.h"
#include "encryption-engine-listener.h"
#include "lime/lime.hpp"

// =============================================================================

LINPHONE_BEGIN_NAMESPACE

class BelleSipLimeManager : public lime::LimeManager {
public:
	BelleSipLimeManager (const std::string &db_access, belle_http_provider_t *prov);

private:
	static void processIoError (void *data, const belle_sip_io_error_event_t *event) noexcept;
	static void processResponse (void *data, const belle_http_response_event_t *event) noexcept;
	static void processAuthRequestedFromCarddavRequest (void *data, belle_sip_auth_event_t *event) noexcept;
};

class LimeV2 : public EncryptionEngineListener, public CoreListener {
public:
	LimeV2 (const std::__cxx11::string &db_access, belle_http_provider_t *prov, LinphoneCore *lc);
	std::shared_ptr<BelleSipLimeManager> getLimeManager ();
	lime::limeCallback setLimeCallback (std::string operation);

	// EncryptionEngineListener overrides
	ChatMessageModifier::Result processIncomingMessage (const std::shared_ptr<ChatMessage> &message, int &errorCode) override;
	ChatMessageModifier::Result processOutgoingMessage (const std::shared_ptr<ChatMessage> &message, int &errorCode) override;
	void update (LinphoneConfig *lpconfig) override;
	bool encryptionEnabledForFileTransferCb (const std::shared_ptr<AbstractChatRoom> &ChatRoom) override;
	void generateFileTransferKeyCb (const std::shared_ptr<AbstractChatRoom> &ChatRoom, const std::shared_ptr<ChatMessage> &message) override;
	int downloadingFileCb (const std::shared_ptr<ChatMessage> &message, size_t offset, const uint8_t *buffer, size_t size, uint8_t *decrypted_buffer) override;
	int uploadingFileCb (const std::shared_ptr<ChatMessage> &message, size_t offset, const uint8_t *buffer, size_t size, uint8_t *encrypted_buffer) override;

	// CoreListener overrides
	void onNetworkReachable (bool sipNetworkReachable, bool mediaNetworkReachable) override;
	void onRegistrationStateChanged (LinphoneProxyConfig *cfg, LinphoneRegistrationState state, const std::string &message) override;

private:
	std::shared_ptr<BelleSipLimeManager> belleSipLimeManager;
	std::time_t lastLimeUpdate;
	std::string x3dhServerUrl;
	lime::CurveId curve;
};

LINPHONE_END_NAMESPACE

#endif // _L_LIME_V2_H_
