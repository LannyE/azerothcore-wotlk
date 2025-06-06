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

#include "CreatureScript.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedFollowerAI.h"
#include "SpellInfo.h"

enum AmeData
{
    SAY_READY               = 0,
    SAY_AGGRO1              = 1,
    SAY_SEARCH              = 2,
    SAY_AGGRO2              = 3,
    SAY_AGGRO3              = 4,
    SAY_FINISH              = 5,

    SPELL_DEMORALIZINGSHOUT = 13730,

    QUEST_CHASING_AME       = 4245,
    ENTRY_TARLORD           = 6519,
    ENTRY_TARLORD1          = 6519,
    ENTRY_STOMPER           = 6513,
};

class npc_ame : public CreatureScript
{
public:
    npc_ame() : CreatureScript("npc_ame") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) override
    {
        if (quest->GetQuestId() == QUEST_CHASING_AME)
        {
            CAST_AI(npc_escortAI, (creature->AI()))->Start(false, false, player->GetGUID());
            creature->AI()->Talk(SAY_READY, player);
            creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
            // Change faction so mobs attack
            creature->SetFaction(FACTION_ESCORTEE_N_NEUTRAL_PASSIVE);
        }
        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ameAI(creature);
    }

    struct npc_ameAI : public npc_escortAI
    {
        npc_ameAI(Creature* creature) : npc_escortAI(creature) { }

        uint32 DemoralizingShoutTimer;

        void WaypointReached(uint32 waypointId) override
        {
            if (Player* player = GetPlayerForEscort())
            {
                switch (waypointId)
                {
                    case 19:
                        if (Creature* summoned = me->SummonCreature(ENTRY_STOMPER, -6391.69f, -1730.49f, -272.83f, 4.96f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000))
                        {
                            Talk(SAY_AGGRO1, summoned);
                        }
                        break;
                    case 28:
                        Talk(SAY_SEARCH, player);
                        break;
                    case 38:
                         if (Creature* summoned = me->SummonCreature(ENTRY_TARLORD, -6370.75f, -1382.84f, -270.51f, 6.06f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000))
                         {
                            Talk(SAY_AGGRO2, summoned);
                         }
                        break;
                    case 49:
                        if (Creature* summoned = me->SummonCreature(ENTRY_TARLORD1, -6324.44f, -1181.05f, -270.17f, 4.34f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000))
                        {
                            Talk(SAY_AGGRO3, summoned);
                        }
                        break;
                    case 55:
                        Talk(SAY_FINISH, player);
                        player->GroupEventHappens(QUEST_CHASING_AME, me);
                        break;
                }
            }
        }

        void Reset() override
        {
            DemoralizingShoutTimer = 5000;
        }

        void JustSummoned(Creature* summoned) override
        {
            summoned->AI()->AttackStart(me);
        }

        void JustDied(Unit* /*killer*/) override
        {
            if (Player* player = GetPlayerForEscort())
                player->FailQuest(QUEST_CHASING_AME);
        }

        void UpdateAI(uint32 diff) override
        {
            npc_escortAI::UpdateAI(diff);
            if (!UpdateVictim())
                return;

            if (DemoralizingShoutTimer <= diff)
            {
                DoCastVictim(SPELL_DEMORALIZINGSHOUT);
                DemoralizingShoutTimer = 70000;
            }
            else DemoralizingShoutTimer -= diff;
        }
    };
};

/*####
# npc_ringo
####*/

enum Ringo
{
    SAY_RIN_START               = 0,

    SAY_FAINT                   = 1,

    SAY_WAKE                    = 2,

    SAY_RIN_END_1               = 3,
    SAY_SPR_END_2               = 0,
    SAY_RIN_END_3               = 4,
    EMOTE_RIN_END_4             = 5,
    EMOTE_RIN_END_5             = 6,
    SAY_RIN_END_6               = 7,
    SAY_SPR_END_7               = 1,
    EMOTE_RIN_END_8             = 8,

    SPELL_REVIVE_RINGO          = 15591,
    QUEST_A_LITTLE_HELP         = 4491,
    NPC_SPRAGGLE                = 9997
};

class npc_ringo : public CreatureScript
{
public:
    npc_ringo() : CreatureScript("npc_ringo") { }

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest) override
    {
        if (quest->GetQuestId() == QUEST_A_LITTLE_HELP)
        {
            if (npc_ringoAI* ringoAI = CAST_AI(npc_ringo::npc_ringoAI, creature->AI()))
            {
                creature->SetStandState(UNIT_STAND_STATE_STAND);
                ringoAI->StartFollow(player, FACTION_ESCORTEE_N_NEUTRAL_PASSIVE, quest);
            }
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_ringoAI(creature);
    }

    struct npc_ringoAI : public FollowerAI
    {
        npc_ringoAI(Creature* creature) : FollowerAI(creature) { }

        uint32 FaintTimer;
        uint32 EndEventProgress;
        uint32 EndEventTimer;

        ObjectGuid SpraggleGUID;

        void Reset() override
        {
            FaintTimer = urand(30000, 60000);
            EndEventProgress = 0;
            EndEventTimer = 1000;
            SpraggleGUID.Clear();
        }

        void MoveInLineOfSight(Unit* who) override

        {
            FollowerAI::MoveInLineOfSight(who);

            if (!me->GetVictim() && !HasFollowState(STATE_FOLLOW_COMPLETE) && who->GetEntry() == NPC_SPRAGGLE)
            {
                if (me->IsWithinDistInMap(who, INTERACTION_DISTANCE))
                {
                    if (Player* player = GetLeaderForFollower())
                    {
                        if (player->GetQuestStatus(QUEST_A_LITTLE_HELP) == QUEST_STATUS_INCOMPLETE)
                            player->GroupEventHappens(QUEST_A_LITTLE_HELP, me);
                    }

                    SpraggleGUID = who->GetGUID();
                    SetFollowComplete(true);
                }
            }
        }

        void SpellHit(Unit* /*pCaster*/, SpellInfo const* pSpell) override
        {
            if (HasFollowState(STATE_FOLLOW_INPROGRESS | STATE_FOLLOW_PAUSED) && pSpell->Id == SPELL_REVIVE_RINGO)
                ClearFaint();
        }

        void SetFaint()
        {
            if (!HasFollowState(STATE_FOLLOW_POSTEVENT))
            {
                SetFollowPaused(true);

                Talk(SAY_FAINT);
            }

            //what does actually happen here? Emote? Aura?
            me->SetStandState(UNIT_STAND_STATE_SLEEP);
        }

        void ClearFaint()
        {
            me->SetStandState(UNIT_STAND_STATE_STAND);

            if (HasFollowState(STATE_FOLLOW_POSTEVENT))
                return;

            Talk(SAY_WAKE);

            SetFollowPaused(false);
        }

        void UpdateFollowerAI(uint32 Diff) override
        {
            if (!UpdateVictim())
            {
                if (HasFollowState(STATE_FOLLOW_POSTEVENT))
                {
                    if (EndEventTimer <= Diff)
                    {
                        Creature* spraggle = ObjectAccessor::GetCreature(*me, SpraggleGUID);
                        if (!spraggle || !spraggle->IsAlive())
                        {
                            SetFollowComplete();
                            return;
                        }

                        switch (EndEventProgress)
                        {
                            case 1:
                                Talk(SAY_RIN_END_1);
                                EndEventTimer = 3000;
                                break;
                            case 2:
                                spraggle->AI()->Talk(SAY_SPR_END_2);
                                EndEventTimer = 5000;
                                break;
                            case 3:
                                Talk(SAY_RIN_END_3);
                                EndEventTimer = 1000;
                                break;
                            case 4:
                                Talk(EMOTE_RIN_END_4);
                                SetFaint();
                                EndEventTimer = 9000;
                                break;
                            case 5:
                                Talk(EMOTE_RIN_END_5);
                                ClearFaint();
                                EndEventTimer = 1000;
                                break;
                            case 6:
                                Talk(SAY_RIN_END_6);
                                EndEventTimer = 3000;
                                break;
                            case 7:
                                spraggle->AI()->Talk(SAY_SPR_END_7);
                                EndEventTimer = 10000;
                                break;
                            case 8:
                                Talk(EMOTE_RIN_END_8);
                                EndEventTimer = 5000;
                                break;
                            case 9:
                                SetFollowComplete();
                                break;
                        }

                        ++EndEventProgress;
                    }
                    else
                        EndEventTimer -= Diff;
                }
                else if (HasFollowState(STATE_FOLLOW_INPROGRESS) && !HasFollowState(STATE_FOLLOW_PAUSED))
                {
                    if (FaintTimer <= Diff)
                    {
                        SetFaint();
                        FaintTimer = urand(60000, 120000);
                    }
                    else
                        FaintTimer -= Diff;
                }

                return;
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_ungoro_crater()
{
    new npc_ame();
    new npc_ringo();
}
