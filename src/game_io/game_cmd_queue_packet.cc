/*
 * Copyright (C) 2002-2004, 2006-2009 by the Widelands Development Team
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#include "game_io/game_cmd_queue_packet.h"

#include "base/macros.h"
#include "io/fileread.h"
#include "io/filewrite.h"
#include "logic/cmd_queue.h"
#include "logic/game.h"
#include "logic/game_data_error.h"
#include "logic/queue_cmd_factory.h"

namespace Widelands {

#define CURRENT_PACKET_VERSION 2


void GameCmdQueuePacket::read
	(FileSystem & fs, Game & game, MapObjectLoader * const ol)
{
	try {
		FileRead fr;
		fr.Open(fs, "binary/cmd_queue");
		uint16_t const packet_version = fr.Unsigned16();
		if (packet_version == CURRENT_PACKET_VERSION) {
			CmdQueue & cmdq = game.cmdqueue();

			// nothing to be done for m_game

			// Next serial
			cmdq.nextserial = fr.Unsigned32();

			// Erase all currently pending commands in the queue
			cmdq.flush();

			for (;;) {
				uint32_t const packet_id = fr.Unsigned16();

				if (!packet_id)
					break;

				CmdQueue::CmdItem item;
				item.category = fr.Signed32();
				item.serial = fr.Unsigned32();

				if (packet_id == 129) {
					// For backwards compatibility with savegames up to build15:
					// Discard old CheckEventChain commands
					fr.Unsigned16(); // CheckEventChain version
					fr.Unsigned16(); // GameLogicCommand version
					fr.Unsigned32(); // GameLogicCommand duetime
					fr.Unsigned16(); // CheckEventChain ID
					continue;
				}

				GameLogicCommand & cmd =
					QueueCmdFactory::create_correct_queue_command(packet_id);
				cmd.read(fr, game, *ol);

				item.cmd = &cmd;

				cmdq.m_cmds[cmd.duetime() % CMD_QUEUE_BUCKET_SIZE].push(item);
				++ cmdq.m_ncmds;
			}
		} else
			throw GameDataError
				("unknown/unhandled version %u", packet_version);
	} catch (const WException & e) {
		throw GameDataError("command queue: %s", e.what());
	}
}


void GameCmdQueuePacket::write
	(FileSystem & fs, Game & game, MapObjectSaver * const os)
{
	FileWrite fw;

	// Now packet version
	fw.Unsigned16(CURRENT_PACKET_VERSION);

	const CmdQueue & cmdq = game.cmdqueue();

	// nothing to be done for m_game

	// Next serial
	fw.Unsigned32(cmdq.nextserial);

	// Write all commands

	// Find all the items in the current cmdqueue
	int32_t time = game.get_gametime();
	size_t nhandled = 0;

	while (nhandled < cmdq.m_ncmds) {
		// Make a copy, so we can pop stuff
		std::priority_queue<CmdQueue::CmdItem> p = cmdq.m_cmds[time % CMD_QUEUE_BUCKET_SIZE];

		while (!p.empty()) {
			const CmdQueue::CmdItem & it = p.top();
			if (it.cmd->duetime() == time) {
				if (upcast(GameLogicCommand, cmd, it.cmd)) {
					// The id (aka command type)
					fw.Unsigned16(cmd->id());

					// Serial number
					fw.Signed32(it.category);
					fw.Unsigned32(it.serial);

					// Now the command itself
					cmd->write(fw, game, *os);
				}
				++ nhandled;
			}

			// DONE: next command
			p.pop();
		}
		++time;
	}


	fw.Unsigned16(0); // end of command queue

	fw.write(fs, "binary/cmd_queue");
}

}
