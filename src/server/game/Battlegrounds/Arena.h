/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ARENA_H
#define _ARENA_H

#include "Battleground.h"

enum ArenaBroadcastTexts
{
    ARENA_TEXT_START_ONE_MINUTE             = 15740,
    ARENA_TEXT_START_THIRTY_SECONDS         = 15741,
    ARENA_TEXT_START_FIFTEEN_SECONDS        = 15739,
    ARENA_TEXT_START_BATTLE_HAS_BEGUN       = 15742,
};

enum ArenaSpellIds
{
    SPELL_ALLIANCE_GOLD_FLAG                = 32724,
    SPELL_ALLIANCE_GREEN_FLAG               = 32725,
    SPELL_HORDE_GOLD_FLAG                   = 35774,
    SPELL_HORDE_GREEN_FLAG                  = 35775,

    SPELL_LAST_MAN_STANDING                 = 26549  // Achievement Credit
};

class AC_GAME_API Arena : public Battleground
{
protected:
    Arena();

    void AddPlayer(Player* player) override;
    void RemovePlayer(Player* /*player*/) override;

    void FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet) override;

    //npcbot
    void AddBot(Creature* bot) override;
    void RemoveBotAtLeave(ObjectGuid guid) override;
    void RemoveBot(ObjectGuid /*guid*/) override;
    void HandleBotKillPlayer(Creature* killer, Player* victim) override;
    void HandleBotKillBot(Creature* killer, Creature* victim) override;
    void HandlePlayerKillBot(Creature* victim, Player* killer) override;
    //end npcbot

    void UpdateArenaWorldState();

    void HandleKillPlayer(Player* player, Player* killer) override;

private:
    void RemovePlayerAtLeave(Player* player) override;
    void CheckWinConditions() override;
    void EndBattleground(TeamId winnerTeamId) override;
};

#endif // ACORE_ARENA_H
