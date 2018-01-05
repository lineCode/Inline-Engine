#pragma once

#include <queue>
#include <mutex>

#include "NetworkMessage.hpp"

namespace inl::net
{
	class MessageQueue
	{
	public:
		void EnqueueMessageToSend(const NetworkMessage &msg);
		void EnqueueMessageReceived(const NetworkMessage &msg);

		NetworkMessage DequeueMessageToSend();

		uint32_t SendSize();

	private:
		std::deque<NetworkMessage> m_messagesReceived;
		std::deque<NetworkMessage> m_messagesToSend;

		std::mutex m_receivedMutex;
		std::mutex m_sendMutex;
	};
}