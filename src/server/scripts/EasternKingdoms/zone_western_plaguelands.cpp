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

#include "AreaDefines.h"
#include "CreatureScript.h"
#include "Player.h"
#include "ScriptedCreature.h"

/*######
## npc_the_scourge_cauldron
######*/

class npc_the_scourge_cauldron : public CreatureScript
{
public:
    npc_the_scourge_cauldron() : CreatureScript("npc_the_scourge_cauldron") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_the_scourge_cauldronAI(creature);
    }

    struct npc_the_scourge_cauldronAI : public ScriptedAI
    {
        npc_the_scourge_cauldronAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override { }

        void JustEngagedWith(Unit* /*who*/) override { }

        void DoDie()
        {
            //summoner dies here
            Unit::DealDamage(me, me, me->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
            //override any database `spawntimesecs` to prevent duplicated summons
            uint32 rTime = me->GetRespawnDelay();
            if (rTime < 600)
                me->SetRespawnDelay(600);
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (!who)
                return;

            Player* player = who->ToPlayer();
            if (!player)
                return;

            switch (me->GetAreaId())
            {
                case AREA_FELSTONE_FIELD:
                    if (player->GetQuestStatus(5216) == QUEST_STATUS_INCOMPLETE ||
                            player->GetQuestStatus(5229) == QUEST_STATUS_INCOMPLETE)
                    {
                        me->SummonCreature(11075, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 600000);
                        DoDie();
                    }
                    break;
                case AREA_DALSONS_TEARS:
                    if (player->GetQuestStatus(5219) == QUEST_STATUS_INCOMPLETE ||
                            player->GetQuestStatus(5231) == QUEST_STATUS_INCOMPLETE)
                    {
                        me->SummonCreature(11077, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 600000);
                        DoDie();
                    }
                    break;
                case AREA_GAHRRONS_WITHERING:
                    if (player->GetQuestStatus(5225) == QUEST_STATUS_INCOMPLETE ||
                            player->GetQuestStatus(5235) == QUEST_STATUS_INCOMPLETE)
                    {
                        me->SummonCreature(11078, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 600000);
                        DoDie();
                    }
                    break;
                case AREA_THE_WRITHING_HAUNT:
                    if (player->GetQuestStatus(5222) == QUEST_STATUS_INCOMPLETE ||
                            player->GetQuestStatus(5233) == QUEST_STATUS_INCOMPLETE)
                    {
                        me->SummonCreature(11076, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 600000);
                        DoDie();
                    }
                    break;
            }
        }
    };
};

/*######
##    npcs_andorhal_tower
######*/

enum AndorhalTower
{
    GO_BEACON_TORCH                             = 176093
};

class npc_andorhal_tower : public CreatureScript
{
public:
    npc_andorhal_tower() : CreatureScript("npc_andorhal_tower") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_andorhal_towerAI(creature);
    }

    struct npc_andorhal_towerAI : public ScriptedAI
    {
        npc_andorhal_towerAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetCombatMovement(false);
        }

        void MoveInLineOfSight(Unit* who) override

        {
            if (!who || !who->IsPlayer())
                return;

            if (me->FindNearestGameObject(GO_BEACON_TORCH, 10.0f))
                if (Player* player = who->ToPlayer())
                    player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
        }
    };
};

/*######
##
######*/

void AddSC_western_plaguelands()
{
    new npc_the_scourge_cauldron();
    new npc_andorhal_tower();
}
