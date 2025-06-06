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

#include "Group.h"
#include "AreaDefines.h"
#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "GameTime.h"
#include "GroupMgr.h"
#include "InstanceSaveMgr.h"
#include "LFG.h"
#include "LFGMgr.h"
#include "Log.h"
#include "MapMgr.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "SharedDefines.h"
#include "UpdateFieldFlags.h"
#include "Util.h"
#include "World.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "ArenaTeam.h"
#include "ArenaTeamMgr.h"

//npcbot
#include "botdatamgr.h"
#include "botmgr.h"
//end npcbot

Roll::Roll(ObjectGuid _guid, LootItem const& li) : itemGUID(_guid), itemid(li.itemid),
    itemRandomPropId(li.randomPropertyId), itemRandomSuffix(li.randomSuffix), itemCount(li.count),
    totalPlayersRolling(0), totalNeed(0), totalGreed(0), totalPass(0), itemSlot(0),
    rollVoteMask(ROLL_ALL_TYPE_NO_DISENCHANT)
{
}

Roll::~Roll()
{
}

void Roll::setLoot(Loot* pLoot)
{
    link(pLoot, this);
}

Loot* Roll::getLoot()
{
    return getTarget();
}

Group::Group() : m_leaderName(""), m_groupType(GROUPTYPE_NORMAL),
    m_dungeonDifficulty(DUNGEON_DIFFICULTY_NORMAL), m_raidDifficulty(RAID_DIFFICULTY_10MAN_NORMAL),
    m_bfGroup(nullptr), m_bgGroup(nullptr), m_lootMethod(FREE_FOR_ALL), m_lootThreshold(ITEM_QUALITY_UNCOMMON),
    m_subGroupsCounts(nullptr), m_counter(0), m_maxEnchantingLevel(0), _difficultyChangePreventionTime(0),
    _difficultyChangePreventionType(DIFFICULTY_PREVENTION_CHANGE_NONE)
{
    sScriptMgr->OnConstructGroup(this);
}

Group::~Group()
{
    sScriptMgr->OnDestructGroup(this);

    if (m_bgGroup)
    {
        LOG_DEBUG("bg.battleground", "Group::~Group: battleground group being deleted.");

        if (m_bgGroup->GetBgRaid(TEAM_ALLIANCE) == this)
        {
            m_bgGroup->SetBgRaid(TEAM_ALLIANCE, nullptr);
        }
        else if (m_bgGroup->GetBgRaid(TEAM_HORDE) == this)
        {
            m_bgGroup->SetBgRaid(TEAM_HORDE, nullptr);
        }
        else
            LOG_ERROR("bg.battleground", "Group::~Group: battleground group is not linked to the correct battleground.");
    }

    Rolls::iterator itr;
    while (!RollId.empty())
    {
        itr = RollId.begin();
        Roll* r = *itr;
        RollId.erase(itr);
        delete(r);
    }

    // Sub group counters clean up
    delete[] m_subGroupsCounts;
}

//npcbot
bool Group::Create(Creature* leader)
{
    ASSERT(isBGGroup());

    ObjectGuid leaderGuid = leader->GetGUID();
    ObjectGuid::LowType lowguid = sGroupMgr->GenerateGroupId();

    m_guid = ObjectGuid::Create<HighGuid::Group>(lowguid);
    m_leaderGuid = leaderGuid;
    m_leaderName = leader->GetName();

    m_groupType = GROUPTYPE_BGRAID;

    _initRaidSubGroupsCounter();

    m_lootMethod = FREE_FOR_ALL;

    m_lootThreshold = ITEM_QUALITY_UNCOMMON;
    m_looterGuid = leaderGuid;
    m_masterLooterGuid.Clear();

    m_dungeonDifficulty = DUNGEON_DIFFICULTY_NORMAL;
    m_raidDifficulty = RAID_DIFFICULTY_10MAN_NORMAL;

    if (!AddMember(leader))
        return false;

    return true;
}
//end npcbot

bool Group::Create(Player* leader)
{
    ObjectGuid leaderGuid = leader->GetGUID();
    ObjectGuid::LowType lowguid = sGroupMgr->GenerateGroupId();

    m_guid = ObjectGuid::Create<HighGuid::Group>(lowguid);
    m_leaderGuid = leaderGuid;
    m_leaderName = leader->GetName();
    leader->SetPlayerFlag(PLAYER_FLAGS_GROUP_LEADER);

    if (isBGGroup() || isBFGroup())
        m_groupType = GROUPTYPE_BGRAID;

    if (m_groupType & GROUPTYPE_RAID)
        _initRaidSubGroupsCounter();

    if (!isLFGGroup())
        m_lootMethod = GROUP_LOOT;

    m_lootThreshold = ITEM_QUALITY_UNCOMMON;
    m_looterGuid = leaderGuid;
    m_masterLooterGuid.Clear();

    m_dungeonDifficulty = DUNGEON_DIFFICULTY_NORMAL;
    m_raidDifficulty = RAID_DIFFICULTY_10MAN_NORMAL;

    if (!isBGGroup() && !isBFGroup())
    {
        m_dungeonDifficulty = leader->GetDungeonDifficulty();
        m_raidDifficulty = leader->GetRaidDifficulty();

        // Store group in database
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_GROUP);

        uint8 index = 0;

        stmt->SetData(index++, lowguid);
        stmt->SetData(index++, m_leaderGuid.GetCounter());
        stmt->SetData(index++, uint8(m_lootMethod));
        stmt->SetData(index++, m_looterGuid.GetCounter());
        stmt->SetData(index++, uint8(m_lootThreshold));
        stmt->SetData(index++, m_targetIcons[0].GetRawValue());
        stmt->SetData(index++, m_targetIcons[1].GetRawValue());
        stmt->SetData(index++, m_targetIcons[2].GetRawValue());
        stmt->SetData(index++, m_targetIcons[3].GetRawValue());
        stmt->SetData(index++, m_targetIcons[4].GetRawValue());
        stmt->SetData(index++, m_targetIcons[5].GetRawValue());
        stmt->SetData(index++, m_targetIcons[6].GetRawValue());
        stmt->SetData(index++, m_targetIcons[7].GetRawValue());
        stmt->SetData(index++, uint8(m_groupType));
        stmt->SetData(index++, uint8(m_dungeonDifficulty));
        stmt->SetData(index++, uint8(m_raidDifficulty));
        stmt->SetData(index++, m_masterLooterGuid.GetCounter());

        CharacterDatabase.Execute(stmt);

        ASSERT(AddMember(leader)); // If the leader can't be added to a new group because it appears full, something is clearly wrong.

        sScriptMgr->OnCreate(this, leader);
    }
    else if (!AddMember(leader))
        return false;

    return true;
}

bool Group::LoadGroupFromDB(Field* fields)
{
    ObjectGuid::LowType groupLowGuid = fields[16].Get<uint32>();
    m_guid = ObjectGuid::Create<HighGuid::Group>(groupLowGuid);

    m_leaderGuid = ObjectGuid::Create<HighGuid::Player>(fields[0].Get<uint32>());

    // group leader not exist
    if (!sCharacterCache->GetCharacterNameByGuid(m_leaderGuid, m_leaderName))
    {
        CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_GROUP);
        stmt->SetData(0, groupLowGuid);
        trans->Append(stmt);
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_GROUP_MEMBER_ALL);
        stmt->SetData(0, groupLowGuid);
        trans->Append(stmt);
        CharacterDatabase.CommitTransaction(trans);
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_LFG_DATA);
        stmt->SetData(0, groupLowGuid);
        CharacterDatabase.Execute(stmt);
        return false;
    }

    m_lootMethod = LootMethod(fields[1].Get<uint8>());
    m_looterGuid = ObjectGuid::Create<HighGuid::Player>(fields[2].Get<uint32>());
    m_lootThreshold = ItemQualities(fields[3].Get<uint8>());

    for (uint8 i = 0; i < TARGETICONCOUNT; ++i)
        m_targetIcons[i].Set(fields[4 + i].Get<uint64>());

    m_groupType  = GroupType(fields[12].Get<uint8>());
    if (m_groupType & GROUPTYPE_RAID)
        _initRaidSubGroupsCounter();

    uint32 diff = fields[13].Get<uint8>();
    if (diff >= MAX_DUNGEON_DIFFICULTY)
        m_dungeonDifficulty = DUNGEON_DIFFICULTY_NORMAL;
    else
        m_dungeonDifficulty = Difficulty(diff);

    uint32 r_diff = fields[14].Get<uint8>();
    if (r_diff >= MAX_RAID_DIFFICULTY)
        m_raidDifficulty = RAID_DIFFICULTY_10MAN_NORMAL;
    else
        m_raidDifficulty = Difficulty(r_diff);

    m_masterLooterGuid = ObjectGuid::Create<HighGuid::Player>(fields[15].Get<uint32>());

    if (m_groupType & GROUPTYPE_LFG)
        sLFGMgr->_LoadFromDB(fields, GetGUID());

    return true;
}

void Group::LoadMemberFromDB(ObjectGuid::LowType guidLow, uint8 memberFlags, uint8 subgroup, uint8 roles)
{
    MemberSlot member;
    member.guid = ObjectGuid::Create<HighGuid::Player>(guidLow);

    // skip non-existed member
    if (!sCharacterCache->GetCharacterNameByGuid(member.guid, member.name))
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_GROUP_MEMBER);
        stmt->SetData(0, guidLow);
        stmt->SetData(1, GetGUID().GetCounter());
        CharacterDatabase.Execute(stmt);
        return;
    }

    member.group = subgroup;
    member.flags = memberFlags;
    member.roles = roles;

    m_memberSlots.push_back(member);

    if (!isBGGroup() && !isBFGroup())
    {
        sCharacterCache->UpdateCharacterGroup(ObjectGuid(HighGuid::Player, guidLow), GetGUID());
    }

    SubGroupCounterIncrease(subgroup);

    sLFGMgr->SetupGroupMember(member.guid, GetGUID());
}

//npcbot
void Group::LoadCreatureMemberFromDB(uint32 entry, uint8 memberFlags, uint8 subgroup, uint8 roles)
{
    MemberSlot member;
    member.guid = BotDataMgr::GetNPCBotGuid(entry);

    // skip non-existed bot
    if (member.guid == ObjectGuid::Empty)
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_NPCBOT_GROUP_MEMBER);
        stmt->SetData(0, entry);
        stmt->SetData(1, GetGUID().GetCounter());
        CharacterDatabase.Execute(stmt);
        return;
    }

    CreatureTemplate const* ct = sObjectMgr->GetCreatureTemplate(entry);
    ASSERT(ct);

    member.name = ct->Name;
    member.group = subgroup;
    member.flags = memberFlags;
    member.roles = roles;

    m_memberSlots.push_back(member);

    SubGroupCounterIncrease(subgroup);

    //sLFGMgr->SetupGroupMember(member.guid, GetGUID());
}
//end npcbot

void Group::ConvertToLFG(bool restricted /*= true*/)
{
    m_groupType = GroupType(m_groupType | GROUPTYPE_LFG);
    if (restricted)
    {
        m_groupType  = GroupType(m_groupType | GROUPTYPE_LFG_RESTRICTED);
        m_lootMethod = NEED_BEFORE_GREED;
    }

    if (!isBGGroup() && !isBFGroup())
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_GROUP_TYPE);

        stmt->SetData(0, uint8(m_groupType));
        stmt->SetData(1, GetGUID().GetCounter());

        CharacterDatabase.Execute(stmt);
    }

    SendUpdate();
}

bool Group::CheckLevelForRaid()
{
    for (member_citerator citr = m_memberSlots.begin(); citr != m_memberSlots.end(); ++citr)
        if (Player* player = ObjectAccessor::FindPlayer(citr->guid))
            if (player->GetLevel() < sConfigMgr->GetOption<int32>("Group.Raid.LevelRestriction", 10))
                return true;

    return false;
}

void Group::ConvertToRaid()
{
    m_groupType = GroupType(m_groupType | GROUPTYPE_RAID);

    _initRaidSubGroupsCounter();

    if (!isBGGroup() && !isBFGroup())
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_GROUP_TYPE);

        stmt->SetData(0, uint8(m_groupType));
        stmt->SetData(1, GetGUID().GetCounter());

        CharacterDatabase.Execute(stmt);
    }

    SendUpdate();

    // update quest related GO states (quest activity dependent from raid membership)
    for (member_citerator citr = m_memberSlots.begin(); citr != m_memberSlots.end(); ++citr)
        if (Player* player = ObjectAccessor::FindPlayer(citr->guid))
            player->UpdateForQuestWorldObjects();

    // pussywizard: client automatically clears df "eye" near minimap, so remove from raid browser
    if (sLFGMgr->GetState(GetLeaderGUID()) == lfg::LFG_STATE_RAIDBROWSER)
        sLFGMgr->LeaveLfg(GetLeaderGUID());
}

bool Group::AddInvite(Player* player)
{
    if (!player || player->GetGroupInvite())
        return false;
    Group* group = player->GetGroup();
    if (group && (group->isBGGroup() || group->isBFGroup()))
        group = player->GetOriginalGroup();
    if (group)
        return false;

    RemoveInvite(player);

    m_invitees.insert(player);

    player->SetGroupInvite(this);

    sScriptMgr->OnGroupInviteMember(this, player->GetGUID());

    return true;
}

bool Group::AddLeaderInvite(Player* player)
{
    if (!AddInvite(player))
        return false;

    m_leaderGuid = player->GetGUID();
    m_leaderName = player->GetName();
    return true;
}

void Group::RemoveInvite(Player* player)
{
    if (player)
    {
        if (!m_invitees.empty())
            m_invitees.erase(player);
        player->SetGroupInvite(nullptr);
    }
}

void Group::RemoveAllInvites()
{
    for (InvitesList::iterator itr = m_invitees.begin(); itr != m_invitees.end(); ++itr)
        if (*itr)
            (*itr)->SetGroupInvite(nullptr);

    m_invitees.clear();
}

Player* Group::GetInvited(ObjectGuid guid) const
{
    for (InvitesList::const_iterator itr = m_invitees.begin(); itr != m_invitees.end(); ++itr)
    {
        if ((*itr) && (*itr)->GetGUID() == guid)
            return (*itr);
    }
    return nullptr;
}

Player* Group::GetInvited(const std::string& name) const
{
    for (InvitesList::const_iterator itr = m_invitees.begin(); itr != m_invitees.end(); ++itr)
    {
        if ((*itr) && (*itr)->GetName() == name)
            return (*itr);
    }
    return nullptr;
}

//npcbot
bool Group::AddMember(Creature* creature)
{
    // Get first not-full group
    uint8 subGroup = 0;
    if (m_subGroupsCounts)
    {
        bool groupFound = false;
        for (; subGroup < MAX_RAID_SUBGROUPS; ++subGroup)
        {
            if (m_subGroupsCounts[subGroup] < MAXGROUPSIZE)
            {
                groupFound = true;
                break;
            }
        }
        // We are raid group and no one slot is free
        if (!groupFound)
            return false;
    }

    MemberSlot member;
    member.guid      = creature->GetGUID();
    member.name      = creature->GetName();
    member.group     = subGroup;
    member.flags     = 0;
    member.roles     = 0;
    m_memberSlots.push_back(member);

    if (creature->GetBotGroup())
    {
        if (isBGGroup() || isBFGroup()) // if player is in group and he is being added to BG raid group, then call SetBattlegroundRaid()
            creature->SetBattlegroundOrBattlefieldRaid(this, subGroup);
        else //if player is in bg raid and we are adding him to normal group, then call SetOriginalGroup()
            creature->SetOriginalGroup(this, subGroup);
    }
    else //if player is not in group, then call set group
        creature->SetBotGroup(this, subGroup);

    if (!isRaidGroup())
    {
        for (uint8 i = 0; i < TARGETICONCOUNT; ++i)
            m_targetIcons[i].Clear();
    }

    // insert into the table if we're not a battleground group
    if (!isBGGroup() && !isBFGroup())
    {
        //REPLACE INTO characters_npcbot_group_member (guid, entry, memberFlags, subgroup, roles) VALUES(?, ?, ?, ?, ?), CONNECTION_ASYNC
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_NPCBOT_GROUP_MEMBER);
        stmt->SetData(0, GetGUID().GetCounter());
        stmt->SetData(1, member.guid.GetEntry());
        stmt->SetData(2, member.flags);
        stmt->SetData(3, member.group);
        stmt->SetData(4, member.roles);
        CharacterDatabase.Execute(stmt);
    }

    SubGroupCounterIncrease(subGroup);
    SendUpdate();
    sScriptMgr->OnGroupAddMember(this, creature->GetGUID());

    BotMgr::SetBotGroupUpdateFlag(creature, GROUP_UPDATE_FULL);
    UpdateBotOutOfRange(creature);

    return true;
}
//end npcbot

bool Group::AddMember(Player* player)
{
    if (!player)
        return false;

    // Get first not-full group
    uint8 subGroup = 0;
    if (m_subGroupsCounts)
    {
        bool groupFound = false;
        for (; subGroup < MAX_RAID_SUBGROUPS; ++subGroup)
        {
            if (m_subGroupsCounts[subGroup] < MAXGROUPSIZE)
            {
                groupFound = true;
                break;
            }
        }
        // We are raid group and no one slot is free
        if (!groupFound)
            return false;
    }

    MemberSlot member;
    member.guid      = player->GetGUID();
    member.name      = player->GetName();
    member.group     = subGroup;
    member.flags     = 0;
    member.roles     = 0;
    m_memberSlots.push_back(member);

    if (!isBGGroup() && !isBFGroup())
    {
        sCharacterCache->UpdateCharacterGroup(player->GetGUID(), GetGUID());
    }

    SubGroupCounterIncrease(subGroup);

    player->SetGroupInvite(nullptr);
    if (player->GetGroup())
    {
        if (isBGGroup() || isBFGroup()) // if player is in group and he is being added to BG raid group, then call SetBattlegroundRaid()
            player->SetBattlegroundOrBattlefieldRaid(this, subGroup);
        else //if player is in bg raid and we are adding him to normal group, then call SetOriginalGroup()
            player->SetOriginalGroup(this, subGroup);
    }
    else //if player is not in group, then call set group
        player->SetGroup(this, subGroup);

    // if the same group invites the player back, cancel the homebind timer
    _cancelHomebindIfInstance(player);

    if (!isRaidGroup())                                      // reset targetIcons for non-raid-groups
    {
        for (uint8 i = 0; i < TARGETICONCOUNT; ++i)
            m_targetIcons[i].Clear();
    }

    if (!isBGGroup() && !isBFGroup())
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_REP_GROUP_MEMBER);
        stmt->SetData(0, GetGUID().GetCounter());
        stmt->SetData(1, member.guid.GetCounter());
        stmt->SetData(2, member.flags);
        stmt->SetData(3, member.group);
        stmt->SetData(4, member.roles);
        CharacterDatabase.Execute(stmt);
    }

    SendUpdate();

    if (player)
    {
        sScriptMgr->OnGroupAddMember(this, player->GetGUID());

        if (!IsLeader(player->GetGUID()) && !isBGGroup() && !isBFGroup())
        {
            Player::ResetInstances(player->GetGUID(), INSTANCE_RESET_GROUP_JOIN, false);

            if (player->GetDungeonDifficulty() != GetDungeonDifficulty())
            {
                player->SetDungeonDifficulty(GetDungeonDifficulty());
                player->SendDungeonDifficulty(true);
            }
            if (player->GetRaidDifficulty() != GetRaidDifficulty())
            {
                player->SetRaidDifficulty(GetRaidDifficulty());
                player->SendRaidDifficulty(true);
            }
        }
        else if (IsLeader(player->GetGUID()) && isLFGGroup()) // pussywizard
        {
            Player::ResetInstances(player->GetGUID(), INSTANCE_RESET_GROUP_JOIN, false);
        }

        player->SetGroupUpdateFlag(GROUP_UPDATE_FULL);
        UpdatePlayerOutOfRange(player);

        // quest related GO state dependent from raid membership
        if (isRaidGroup())
            player->UpdateForQuestWorldObjects();

        {
            // Broadcast new player group member fields to rest of the group
            player->SetFieldNotifyFlag(UF_FLAG_PARTY_MEMBER);

            UpdateData groupData;
            WorldPacket groupDataPacket;

            // Broadcast group members' fields to player
            for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
            {
                if (itr->GetSource() == player) // pussywizard: no check same map, adding members is single threaded
                {
                    continue;
                }

                if (Player* itrMember = itr->GetSource())
                {
                    if (player->HaveAtClient(itrMember))
                    {
                        itrMember->SetFieldNotifyFlag(UF_FLAG_PARTY_MEMBER);
                        itrMember->BuildValuesUpdateBlockForPlayer(&groupData, player);
                        itrMember->RemoveFieldNotifyFlag(UF_FLAG_PARTY_MEMBER);
                    }

                    if (itrMember->HaveAtClient(player))
                    {
                        UpdateData newData;
                        WorldPacket newDataPacket;
                        player->BuildValuesUpdateBlockForPlayer(&newData, itrMember);
                        if (newData.HasData())
                        {
                            newData.BuildPacket(newDataPacket);
                            itrMember->SendDirectMessage(&newDataPacket);
                        }
                    }
                }
            }

            if (groupData.HasData())
            {
                groupData.BuildPacket(groupDataPacket);
                player->SendDirectMessage(&groupDataPacket);
            }

            player->RemoveFieldNotifyFlag(UF_FLAG_PARTY_MEMBER);
        }

        if (m_maxEnchantingLevel < player->GetSkillValue(SKILL_ENCHANTING))
            m_maxEnchantingLevel = player->GetSkillValue(SKILL_ENCHANTING);
    }

    //npcbot: if player has been added to bot BG raid switch leader to it
    if (!m_leaderGuid.IsPlayer())
        ChangeLeader(player->GetGUID());
    //end npcbot

    return true;
}

bool Group::RemoveMember(ObjectGuid guid, const RemoveMethod& method /*= GROUP_REMOVEMETHOD_DEFAULT*/, ObjectGuid kicker /*= ObjectGuid::Empty*/, const char* reason /*= nullptr*/)
{
    BroadcastGroupUpdate();

    // LFG group vote kick handled in scripts
    if (isLFGGroup(true) && method == GROUP_REMOVEMETHOD_KICK)
    {
        sLFGMgr->InitBoot(GetGUID(), kicker, guid, std::string(reason ? reason : ""));
        return m_memberSlots.size() > 0;
    }

    // remove member and change leader (if need) only if strong more 2 members _before_ member remove (BG/BF allow 1 member group)
    if (GetMembersCount() > ((isBGGroup() || isLFGGroup() || isBFGroup()) ? 1u : 2u))
    {
        //npcbot: skip group size check before removing a bot
        if (guid.IsCreature())
        {
            if (Creature const* cbot = BotDataMgr::FindBot(guid.GetEntry()))
            {
                Creature* bot = const_cast<Creature*>(cbot);
                if (isBGGroup() || isBFGroup())
                    bot->RemoveFromBattlegroundOrBattlefieldRaid();
                else
                {
                    if (bot->GetOriginalGroup() == this)
                        bot->SetOriginalGroup(nullptr);
                    else
                        bot->SetBotGroup(nullptr);
                }
            }

            // Remove bot from group in DB
            if (!isBGGroup() && !isBFGroup())
            {
                //DELETE FROM characters_npcbot_group_member WHERE entry = ?, CONNECTION_ASYNC
                CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_NPCBOT_GROUP_MEMBER);
                stmt->SetData(0, guid.GetEntry());
                CharacterDatabase.Execute(stmt);
                DelinkBotMember(guid);
            }

            // Update subgroups
            member_witerator slot = _getMemberWSlot(guid);
            if (slot != m_memberSlots.end())
            {
                SubGroupCounterDecrease(slot->group);
                m_memberSlots.erase(slot);
            }

            sScriptMgr->OnGroupRemoveMember(this, guid, method, kicker, reason);

            SendUpdate();

            // do not disband raid group if bot owner logging out within dungeon
            // 1-player raid groups will not happen unless player is gm - bots will rejoin at login
            if (GetMembersCount() < 2 && isRaidGroup() && !(isBGGroup() || isBFGroup()) && GetLeaderGUID())
            {
                Player const* player = ObjectAccessor::FindPlayer(GetLeaderGUID());
                Map const* map = player ? player->FindMap() : nullptr;
                if (!(map && map->IsDungeon() && player && player->GetSession()->PlayerLogout()))
                    Disband();
            }
            else if (GetMembersCount() < ((isLFGGroup() || isBGGroup() || isBFGroup()) ? 1u : 2u))
            {
                Disband();
                return false;
            }

            return true;
        }

        Player* player = ObjectAccessor::FindConnectedPlayer(guid);
        if (player)
        {
            // Battleground group handling
            if (isBGGroup() || isBFGroup())
                player->RemoveFromBattlegroundOrBattlefieldRaid();
            else
                // Regular group
            {
                if (player->GetOriginalGroup() == this)
                    player->SetOriginalGroup(nullptr);
                else
                    player->SetGroup(nullptr);

                // quest related GO state dependent from raid membership
                player->UpdateForQuestWorldObjects();
            }

            WorldPacket data;

            if (method == GROUP_REMOVEMETHOD_KICK || method == GROUP_REMOVEMETHOD_KICK_LFG)
            {
                data.Initialize(SMSG_GROUP_UNINVITE, 0);
                player->GetSession()->SendPacket(&data);
            }

            // Do we really need to send this opcode?
            data.Initialize(SMSG_GROUP_LIST, 1 + 1 + 1 + 1 + 8 + 4 + 4 + 8);
            data << uint8(0x10) << uint8(0) << uint8(0) << uint8(0);
            data << m_guid << uint32(m_counter) << uint32(0) << uint64(0);
            player->GetSession()->SendPacket(&data);
        }

        // Remove player from group in DB
        if (!isBGGroup() && !isBFGroup())
        {
            CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_GROUP_MEMBER);
            stmt->SetData(0, guid.GetCounter());
            stmt->SetData(1, GetGUID().GetCounter());
            CharacterDatabase.Execute(stmt);
        }

        // Remove player from loot rolls
        for (Rolls::iterator it = RollId.begin(); it != RollId.end();)
        {
            Roll* roll = *it;
            Roll::PlayerVote::iterator itr2 = roll->playerVote.find(guid);
            if (itr2 == roll->playerVote.end())
            {
                ++it;
                continue;
            }

            if (itr2->second == GREED || itr2->second == DISENCHANT)
                --roll->totalGreed;
            else if (itr2->second == NEED)
                --roll->totalNeed;
            else if (itr2->second == PASS)
                --roll->totalPass;

            if (itr2->second != NOT_VALID)
                --roll->totalPlayersRolling;

            roll->playerVote.erase(itr2);

            // Xinef: itr can be erased inside
            // Xinef: player is removed from all vote lists so it will not pass above playerVote == playerVote.end statement during second iteration
            if (CountRollVote(guid, roll->itemGUID, MAX_ROLL_TYPE))
                it = RollId.begin();
            else
                ++it;
        }

        // Update subgroups
        member_witerator slot = _getMemberWSlot(guid);
        if (slot != m_memberSlots.end())
        {
            SubGroupCounterDecrease(slot->group);
            m_memberSlots.erase(slot);

            if (!isBGGroup() && !isBFGroup())
            {
                sCharacterCache->ClearCharacterGroup(guid);
            }
        }

        // Reevaluate group enchanter if the leaving player had enchanting skill or the player is offline
        if (!player || player->GetSkillValue(SKILL_ENCHANTING))
        {
            ResetMaxEnchantingLevel();
        }

        // Pick new leader if necessary
        bool validLeader = true;
        if (m_leaderGuid == guid)
        {
            validLeader = false;
            for (member_witerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
            {
                if (ObjectAccessor::FindConnectedPlayer(itr->guid))
                {
                    ChangeLeader(itr->guid);
                    validLeader = true;
                    break;
                }
            }
        }

        _homebindIfInstance(player);
        if (!isBGGroup() && !isBFGroup())
            Player::ResetInstances(guid, INSTANCE_RESET_GROUP_LEAVE, false);

        sScriptMgr->OnGroupRemoveMember(this, guid, method, kicker, reason);

        SendUpdate();

        if (!validLeader)
        {
            // pussywizard: temp do nothing, something causes crashes in MakeNewGroup
            //Disband();
            //return false;
        }

        if (isLFGGroup() && GetMembersCount() == 1)
        {
            Player* leader = ObjectAccessor::FindConnectedPlayer(GetLeaderGUID());
            uint32 mapId = sLFGMgr->GetDungeonMapId(GetGUID());
            lfg::LfgState state = sLFGMgr->GetState(GetGUID());
            if (!mapId || !leader || (leader->IsAlive() && leader->GetMapId() != mapId) || state == lfg::LFG_STATE_NONE)
            {
                Disband();
                return false;
            }
        }

        if (m_memberMgr.getSize() < ((isLFGGroup() || isBGGroup() || isBFGroup()) ? 1u : 2u))
        //npcbot: prevent group from being disbanded due to checking only players count
        if (GetMembersCount() < ((isLFGGroup() || isBGGroup() || isBFGroup()) ? 1u : 2u))
        //end npcbot
        {
            Disband();
            return false;
        }

        return true;
    }
    // If group size before player removal <= 2 then disband it
    else
    {
        sScriptMgr->OnGroupRemoveMember(this, guid, method, kicker, reason);
        Disband();
        return false;
    }
}

void Group::ChangeLeader(ObjectGuid newLeaderGuid)
{
    member_witerator slot = _getMemberWSlot(newLeaderGuid);

    if (slot == m_memberSlots.end())
        return;

    Player* newLeader = ObjectAccessor::FindConnectedPlayer(slot->guid);

    // Don't allow switching leader to offline players
    if (!newLeader)
        return;

    if (!isBGGroup() && !isBFGroup())
    {
        CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
        // Update the group leader
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_GROUP_LEADER);
        stmt->SetData(0, newLeader->GetGUID().GetCounter());
        stmt->SetData(1, GetGUID().GetCounter());
        trans->Append(stmt);
        CharacterDatabase.CommitTransaction(trans);

        sInstanceSaveMgr->CopyBinds(m_leaderGuid, newLeaderGuid, newLeader);
    }

    if (Player* oldLeader = ObjectAccessor::FindConnectedPlayer(m_leaderGuid))
        oldLeader->RemovePlayerFlag(PLAYER_FLAGS_GROUP_LEADER);

    newLeader->SetPlayerFlag(PLAYER_FLAGS_GROUP_LEADER);
    m_leaderGuid = newLeader->GetGUID();
    m_leaderName = newLeader->GetName();
    ToggleGroupMemberFlag(slot, MEMBER_FLAG_ASSISTANT, false);

    WorldPacket data(SMSG_GROUP_SET_LEADER, m_leaderName.size() + 1);
    data << slot->name;
    BroadcastPacket(&data, true);

    sScriptMgr->OnGroupChangeLeader(this, newLeaderGuid, m_leaderGuid); // This hook should be executed at the end - Not used anywhere in the original core
}

void Group::Disband(bool hideDestroy /* = false */)
{
    sScriptMgr->OnGroupDisband(this);

    Player* player;
    uint32 instanceId = 0;

    for (member_citerator citr = m_memberSlots.begin(); citr != m_memberSlots.end(); ++citr)
    {
        if (!isBGGroup() && !isBFGroup())
        {
            sCharacterCache->ClearCharacterGroup(citr->guid);
        }

        //npcbot: set bot's group
        if (citr->guid.IsCreature())
        {
            if (Creature const* cbot = BotDataMgr::FindBot(citr->guid.GetEntry()))
            {
                Creature* bot = const_cast<Creature*>(cbot);
                if (isBGGroup() || isBFGroup())
                    bot->RemoveFromBattlegroundOrBattlefieldRaid();
                else
                {
                    if (bot->GetOriginalGroup() == this)
                        bot->SetOriginalGroup(nullptr);
                    else
                        bot->SetBotGroup(nullptr);
                }
            }
            continue;
        }
        //end npcbot

        player = ObjectAccessor::FindConnectedPlayer(citr->guid);

        if (player && !instanceId && !isBGGroup() && !isBFGroup())
        {
            instanceId = player->GetInstanceId();
        }

        _homebindIfInstance(player);
        if (!isBGGroup() && !isBFGroup())
            Player::ResetInstances(citr->guid, INSTANCE_RESET_GROUP_LEAVE, false);

        if (!player)
            continue;

        //we cannot call _removeMember because it would invalidate member iterator
        //if we are removing player from battleground raid
        if (isBGGroup() || isBFGroup())
            player->RemoveFromBattlegroundOrBattlefieldRaid();
        else
        {
            //we can remove player who is in battleground from his original group
            if (player->GetOriginalGroup() == this)
                player->SetOriginalGroup(nullptr);
            else
                player->SetGroup(nullptr);
        }

        // quest related GO state dependent from raid membership
        if (isRaidGroup())
            player->UpdateForQuestWorldObjects();

        WorldPacket data;
        if (!hideDestroy)
        {
            data.Initialize(SMSG_GROUP_DESTROYED, 0);
            player->GetSession()->SendPacket(&data);
        }

        //we already removed player from group and in player->GetGroup() is his original group, send update
        if (Group* group = player->GetGroup())
        {
            group->SendUpdate();
        }
        else
        {
            data.Initialize(SMSG_GROUP_LIST, 1 + 1 + 1 + 1 + 8 + 4 + 4 + 8);
            data << uint8(0x10) << uint8(0) << uint8(0) << uint8(0);
            data << m_guid << uint32(m_counter) << uint32(0) << uint64(0);
            player->GetSession()->SendPacket(&data);
        }
    }
    RollId.clear();
    m_memberSlots.clear();

    RemoveAllInvites();

    if (!isBGGroup() && !isBFGroup())
    {
        CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();

        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_GROUP);
        stmt->SetData(0, GetGUID().GetCounter());
        trans->Append(stmt);

        stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_GROUP_MEMBER_ALL);
        stmt->SetData(0, GetGUID().GetCounter());
        trans->Append(stmt);

        //npcbot: bot members deletion
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_NPCBOT_GROUP_MEMBER_ALL);
        stmt->SetData(0, GetGUID().GetCounter());
        trans->Append(stmt);
        //end npcbot

        CharacterDatabase.CommitTransaction(trans);

        stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_LFG_DATA);
        stmt->SetData(0, GetGUID().GetCounter());
        CharacterDatabase.Execute(stmt);
    }

    // Cleaning up instance saved data for gameobjects when a group is disbanded
    sInstanceSaveMgr->DeleteInstanceSavedData(instanceId);

    sGroupMgr->RemoveGroup(this);
    delete this;
}

/*********************************************************/
/***                   LOOT SYSTEM                     ***/
/*********************************************************/

void Group::SendLootStartRoll(uint32 CountDown, uint32 mapid, const Roll& r)
{
    WorldPacket data(SMSG_LOOT_START_ROLL, (8 + 4 + 4 + 4 + 4 + 4 + 4 + 1));
    data << r.itemGUID;                                     // guid of rolled item
    data << uint32(mapid);                                  // 3.3.3 mapid
    data << uint32(r.itemSlot);                             // itemslot
    data << uint32(r.itemid);                               // the itemEntryId for the item that shall be rolled for
    data << uint32(r.itemRandomSuffix);                     // randomSuffix
    data << uint32(r.itemRandomPropId);                     // item random property ID
    data << uint32(r.itemCount);                            // items in stack
    data << uint32(CountDown);                              // the countdown time to choose "need" or "greed"
    data << uint8(r.rollVoteMask);                          // roll type mask

    for (Roll::PlayerVote::const_iterator itr = r.playerVote.begin(); itr != r.playerVote.end(); ++itr)
    {
        Player* p = ObjectAccessor::FindConnectedPlayer(itr->first);
        if (!p)
            continue;

        if (itr->second == NOT_EMITED_YET)
            p->GetSession()->SendPacket(&data);
    }
}

void Group::SendLootStartRollToPlayer(uint32 countDown, uint32 mapId, Player* p, bool canNeed, Roll const& r)
{
    if (!p)
        return;

    WorldPacket data(SMSG_LOOT_START_ROLL, (8 + 4 + 4 + 4 + 4 + 4 + 4 + 1));
    data << r.itemGUID;                                     // guid of rolled item
    data << uint32(mapId);                                  // 3.3.3 mapid
    data << uint32(r.itemSlot);                             // itemslot
    data << uint32(r.itemid);                               // the itemEntryId for the item that shall be rolled for
    data << uint32(r.itemRandomSuffix);                     // randomSuffix
    data << uint32(r.itemRandomPropId);                     // item random property ID
    data << uint32(r.itemCount);                            // items in stack
    data << uint32(countDown);                              // the countdown time to choose "need" or "greed"
    uint8 voteMask = r.rollVoteMask;
    if (!canNeed)
        voteMask &= ~ROLL_FLAG_TYPE_NEED;
    data << uint8(voteMask);                                // roll type mask

    p->GetSession()->SendPacket(&data);
}

void Group::SendLootRoll(ObjectGuid sourceGuid, ObjectGuid targetGuid, uint8 rollNumber, uint8 rollType, Roll const& roll, bool autoPass)
{
    WorldPacket data(SMSG_LOOT_ROLL, (8 + 4 + 8 + 4 + 4 + 4 + 1 + 1 + 1));
    data << sourceGuid;                                     // guid of the item rolled
    data << uint32(roll.itemSlot);                          // slot
    data << targetGuid;
    data << uint32(roll.itemid);                            // the itemEntryId for the item that shall be rolled for
    data << uint32(roll.itemRandomSuffix);                  // randomSuffix
    data << uint32(roll.itemRandomPropId);                  // Item random property ID
    data << uint8(rollNumber);                              // 0: "Need for: [item name]" > 127: "you passed on: [item name]"      Roll number
    data << uint8(rollType);                                // 0: "Need for: [item name]" 0: "You have selected need for [item name] 1: need roll 2: greed roll
    data << uint8(autoPass);                                // 1: "You automatically passed on: %s because you cannot loot that item."

    for (Roll::PlayerVote::const_iterator itr = roll.playerVote.begin(); itr != roll.playerVote.end(); ++itr)
    {
        Player* p = ObjectAccessor::FindConnectedPlayer(itr->first);
        if (!p)
            continue;

        if (itr->second != NOT_VALID)
            p->GetSession()->SendPacket(&data);
    }
}

void Group::SendLootRollWon(ObjectGuid sourceGuid, ObjectGuid targetGuid, uint8 rollNumber, uint8 rollType, Roll const& roll)
{
    WorldPacket data(SMSG_LOOT_ROLL_WON, (8 + 4 + 4 + 4 + 4 + 8 + 1 + 1));
    data << sourceGuid;                                     // guid of the item rolled
    data << uint32(roll.itemSlot);                          // slot
    data << uint32(roll.itemid);                            // the itemEntryId for the item that shall be rolled for
    data << uint32(roll.itemRandomSuffix);                  // randomSuffix
    data << uint32(roll.itemRandomPropId);                  // Item random property
    data << targetGuid;                                     // guid of the player who won.
    data << uint8(rollNumber);                              // rollnumber realted to SMSG_LOOT_ROLL
    data << uint8(rollType);                                // rollType related to SMSG_LOOT_ROLL

    for (Roll::PlayerVote::const_iterator itr = roll.playerVote.begin(); itr != roll.playerVote.end(); ++itr)
    {
        Player* p = ObjectAccessor::FindConnectedPlayer(itr->first);
        if (!p)
            continue;

        if (itr->second != NOT_VALID)
            p->GetSession()->SendPacket(&data);
    }
}

void Group::SendLootAllPassed(Roll const& roll)
{
    WorldPacket data(SMSG_LOOT_ALL_PASSED, (8 + 4 + 4 + 4 + 4));
    data << roll.itemGUID;                                     // Guid of the item rolled
    data << uint32(roll.itemSlot);                             // Item loot slot
    data << uint32(roll.itemid);                               // The itemEntryId for the item that shall be rolled for
    data << uint32(roll.itemRandomPropId);                     // Item random property ID
    data << uint32(roll.itemRandomSuffix);                     // Item random suffix ID

    for (Roll::PlayerVote::const_iterator itr = roll.playerVote.begin(); itr != roll.playerVote.end(); ++itr)
    {
        Player* player = ObjectAccessor::FindConnectedPlayer(itr->first);
        if (!player)
            continue;

        if (itr->second != NOT_VALID)
            player->GetSession()->SendPacket(&data);
    }
}

// notify group members which player is the allowed looter for the given creature
void Group::SendLooter(Creature* creature, Player* groupLooter)
{
    ASSERT(creature);

    WorldPacket data(SMSG_LOOT_LIST, (8 + 8));
    data << creature->GetGUID();

    if (GetLootMethod() == MASTER_LOOT && creature->loot.hasOverThresholdItem())
        data << GetMasterLooterGuid().WriteAsPacked();
    else
        data << uint8(0);

    if (groupLooter)
        data << groupLooter->GetPackGUID();
    else
        data << uint8(0);

    BroadcastPacket(&data, false);
}

bool CanRollOnItem(LootItem const& item, Player const* player, Loot* loot)
{
    // Players can't roll on unique items if they already reached the maximum quantity of that item
    ItemTemplate const* proto = sObjectMgr->GetItemTemplate(item.itemid);
    if (!proto)
        return false;

    uint32 itemCount = player->GetItemCount(item.itemid);
    if ((proto->MaxCount > 0 && static_cast<int32>(itemCount) >= proto->MaxCount))
        return false;

    if (!item.AllowedForPlayer(player, loot->sourceWorldObjectGUID))
        return false;

    return true;
}

void Group::GroupLoot(Loot* loot, WorldObject* pLootedObject)
{
    //npcbot
    if (m_memberMgr.getSize() <= 1)
        return;
    //end npcbot

    std::vector<LootItem>::iterator i;
    ItemTemplate const* item;
    uint8 itemSlot = 0;

    for (i = loot->items.begin(); i != loot->items.end(); ++i, ++itemSlot)
    {
        if (i->freeforall)
            continue;

        item = sObjectMgr->GetItemTemplate(i->itemid);
        if (!item)
        {
            continue;
        }

        // roll for over-threshold item if it's one-player loot
        if (item->Quality >= uint32(m_lootThreshold))
        {
            ObjectGuid newitemGUID = ObjectGuid::Create<HighGuid::Item>(sObjectMgr->GetGenerator<HighGuid::Item>().Generate());
            Roll* r = new Roll(newitemGUID, *i);

            //a vector is filled with only near party members
            for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
            {
                Player* member = itr->GetSource();
                if (!member || !member->GetSession())
                    continue;
                if (member->IsAtLootRewardDistance(pLootedObject))
                {
                    r->totalPlayersRolling++;

                    RollVote vote = member->GetPassOnGroupLoot() ? PASS : NOT_EMITED_YET;
                    if (!CanRollOnItem(*i, member, loot))
                    {
                        vote = PASS;
                        ++r->totalPass;
                    }

                    r->playerVote[member->GetGUID()] = vote;
                }
            }

            if (r->totalPlayersRolling > 0)
            {
                r->setLoot(loot);
                r->itemSlot = itemSlot;
                if (item->DisenchantID && m_maxEnchantingLevel >= item->RequiredDisenchantSkill)
                    r->rollVoteMask |= ROLL_FLAG_TYPE_DISENCHANT;

                loot->items[itemSlot].is_blocked = true;

                // If there is any "auto pass", broadcast the pass now.
                if (r->totalPass)
                {
                    for (Roll::PlayerVote::const_iterator itr = r->playerVote.begin(); itr != r->playerVote.end(); ++itr)
                    {
                        Player* p = ObjectAccessor::FindPlayer(itr->first);
                        if (!p)
                            continue;

                        if (itr->second == PASS)
                            SendLootRoll(newitemGUID, p->GetGUID(), 128, ROLL_PASS, *r, true);
                    }
                }

                if (r->totalPass == r->totalPlayersRolling)
                    delete r;
                else
                {
                    SendLootStartRoll(60000, pLootedObject->GetMapId(), *r);

                    RollId.push_back(r);

                    if (Creature* creature = pLootedObject->ToCreature())
                    {
                        creature->m_groupLootTimer = 60000;
                        creature->lootingGroupLowGUID = GetGUID().GetCounter();
                    }
                    else if (GameObject* go = pLootedObject->ToGameObject())
                    {
                        go->m_groupLootTimer = 60000;
                        go->lootingGroupLowGUID = GetGUID().GetCounter();
                    }
                }
            }
            else
                delete r;
        }
        else
            i->is_underthreshold = true;
    }

    for (i = loot->quest_items.begin(); i != loot->quest_items.end(); ++i, ++itemSlot)
    {
        if (!i->follow_loot_rules)
            continue;

        item = sObjectMgr->GetItemTemplate(i->itemid);
        if (!item)
        {
            continue;
        }

        ObjectGuid newitemGUID = ObjectGuid::Create<HighGuid::Item>(sObjectMgr->GetGenerator<HighGuid::Item>().Generate());
        Roll* r = new Roll(newitemGUID, *i);

        //a vector is filled with only near party members
        for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player* member = itr->GetSource();
            if (!member || !member->GetSession())
                continue;

            if (member->IsAtLootRewardDistance(pLootedObject))
            {
                r->totalPlayersRolling++;

                RollVote vote = NOT_EMITED_YET;
                if (!CanRollOnItem(*i, member, loot))
                {
                    vote = PASS;
                    ++r->totalPass;
                }
                r->playerVote[member->GetGUID()] = vote;
            }
        }

        if (r->totalPlayersRolling > 0)
        {
            r->setLoot(loot);
            r->itemSlot = itemSlot;

            loot->quest_items[itemSlot - loot->items.size()].is_blocked = true;

            SendLootStartRoll(60000, pLootedObject->GetMapId(), *r);

            RollId.push_back(r);

            if (Creature* creature = pLootedObject->ToCreature())
            {
                creature->m_groupLootTimer = 60000;
                creature->lootingGroupLowGUID = GetGUID().GetCounter();
            }
            else if (GameObject* go = pLootedObject->ToGameObject())
            {
                go->m_groupLootTimer = 60000;
                go->lootingGroupLowGUID = GetGUID().GetCounter();
            }
        }
        else
            delete r;
    }
}

void Group::NeedBeforeGreed(Loot* loot, WorldObject* lootedObject)
{
    //npcbot
    if (m_memberMgr.getSize() <= 1)
        return;
    //end npcbot

    ItemTemplate const* item;
    uint8 itemSlot = 0;
    for (std::vector<LootItem>::iterator i = loot->items.begin(); i != loot->items.end(); ++i, ++itemSlot)
    {
        if (i->freeforall)
            continue;

        item = sObjectMgr->GetItemTemplate(i->itemid);

        //roll for over-threshold item if it's one-player loot
        if (item->Quality >= uint32(m_lootThreshold))
        {
            ObjectGuid newitemGUID = ObjectGuid::Create<HighGuid::Item>(sObjectMgr->GetGenerator<HighGuid::Item>().Generate());
            Roll* r = new Roll(newitemGUID, *i);

            for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
            {
                Player* playerToRoll = itr->GetSource();
                if (!playerToRoll || !playerToRoll->GetSession())
                    continue;

                if (playerToRoll->IsAtGroupRewardDistance(lootedObject))
                {
                    r->totalPlayersRolling++;

                    RollVote vote = playerToRoll->GetPassOnGroupLoot() ? PASS : NOT_EMITED_YET;
                    if (!CanRollOnItem(*i, playerToRoll, loot))
                    {
                        vote = PASS;
                        r->totalPass++; // Can't broadcast the pass now. need to wait until all rolling players are known
                    }

                    r->playerVote[playerToRoll->GetGUID()] = vote;
                }
            }

            if (r->totalPlayersRolling > 0)
            {
                r->setLoot(loot);
                r->itemSlot = itemSlot;
                if (item->DisenchantID && m_maxEnchantingLevel >= item->RequiredDisenchantSkill)
                    r->rollVoteMask |= ROLL_FLAG_TYPE_DISENCHANT;

                if (item->HasFlag2(ITEM_FLAG2_CAN_ONLY_ROLL_GREED))
                    r->rollVoteMask &= ~ROLL_FLAG_TYPE_NEED;

                loot->items[itemSlot].is_blocked = true;

                //Broadcast Pass and Send Rollstart
                for (Roll::PlayerVote::const_iterator itr = r->playerVote.begin(); itr != r->playerVote.end(); ++itr)
                {
                    Player* p = ObjectAccessor::FindPlayer(itr->first);
                    if (!p)
                        continue;

                    if (itr->second == PASS)
                        SendLootRoll(newitemGUID, p->GetGUID(), 128, ROLL_PASS, *r);
                    else
                        SendLootStartRollToPlayer(60000, lootedObject->GetMapId(), p, p->CanRollForItemInLFG(item, lootedObject) == EQUIP_ERR_OK, *r);
                }

                RollId.push_back(r);

                if (Creature* creature = lootedObject->ToCreature())
                {
                    creature->m_groupLootTimer = 60000;
                    creature->lootingGroupLowGUID = GetGUID().GetCounter();
                }
                else if (GameObject* go = lootedObject->ToGameObject())
                {
                    go->m_groupLootTimer = 60000;
                    go->lootingGroupLowGUID = GetGUID().GetCounter();
                }
            }
            else
                delete r;
        }
        else
            i->is_underthreshold = true;
    }

    for (std::vector<LootItem>::iterator i = loot->quest_items.begin(); i != loot->quest_items.end(); ++i, ++itemSlot)
    {
        if (!i->follow_loot_rules)
            continue;

        item = sObjectMgr->GetItemTemplate(i->itemid);
        ObjectGuid newitemGUID = ObjectGuid::Create<HighGuid::Item>(sObjectMgr->GetGenerator<HighGuid::Item>().Generate());
        Roll* r = new Roll(newitemGUID, *i);

        for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player* playerToRoll = itr->GetSource();
            if (!playerToRoll || !playerToRoll->GetSession())
                continue;

            if (playerToRoll->IsAtGroupRewardDistance(lootedObject))
            {
                r->totalPlayersRolling++;

                RollVote vote = playerToRoll->GetPassOnGroupLoot() ? PASS : NOT_EMITED_YET;
                if (!CanRollOnItem(*i, playerToRoll, loot))
                {
                    vote = PASS;
                    r->totalPass++; // Can't broadcast the pass now. need to wait until all rolling players are known
                }

                r->playerVote[playerToRoll->GetGUID()] = vote;
            }
        }

        if (r->totalPlayersRolling > 0)
        {
            r->setLoot(loot);
            r->itemSlot = itemSlot;

            loot->quest_items[itemSlot - loot->items.size()].is_blocked = true;

            //Broadcast Pass and Send Rollstart
            for (Roll::PlayerVote::const_iterator itr = r->playerVote.begin(); itr != r->playerVote.end(); ++itr)
            {
                Player* p = ObjectAccessor::FindPlayer(itr->first);
                if (!p)
                    continue;

                if (itr->second == PASS)
                    SendLootRoll(newitemGUID, p->GetGUID(), 128, ROLL_PASS, *r);
                else
                    SendLootStartRollToPlayer(60000, lootedObject->GetMapId(), p, p->CanRollForItemInLFG(item, lootedObject) == EQUIP_ERR_OK, *r);
            }

            RollId.push_back(r);

            if (Creature* creature = lootedObject->ToCreature())
            {
                creature->m_groupLootTimer = 60000;
                creature->lootingGroupLowGUID = GetGUID().GetCounter();
            }
            else if (GameObject* go = lootedObject->ToGameObject())
            {
                go->m_groupLootTimer = 60000;
                go->lootingGroupLowGUID = GetGUID().GetCounter();
            }
        }
        else
            delete r;
    }
}

void Group::MasterLoot(Loot* loot, WorldObject* pLootedObject)
{
    LOG_DEBUG("network", "Group::MasterLoot (SMSG_LOOT_MASTER_LIST, 330)");

    for (std::vector<LootItem>::iterator i = loot->items.begin(); i != loot->items.end(); ++i)
    {
        if (i->freeforall)
            continue;

        i->is_blocked = !i->is_underthreshold;
    }

    for (std::vector<LootItem>::iterator i = loot->quest_items.begin(); i != loot->quest_items.end(); ++i)
    {
        if (!i->follow_loot_rules)
            continue;

        i->is_blocked = !i->is_underthreshold;
    }

    std::vector<Player*> looters;
    for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        Player* looter = itr->GetSource();
        if (!looter->IsInWorld())
        {
            continue;
        }

        if (looter->IsAtLootRewardDistance(pLootedObject))
        {
            looters.push_back(looter);
        }
    }

    WorldPacket data(SMSG_LOOT_MASTER_LIST, 1 + looters.size() * (1 + 8));
    data << uint8(looters.size());

    for (Player* looter : looters)
    {
        data << looter->GetGUID();
    }

    for (Player* looter : looters)
    {
        looter->GetSession()->SendPacket(&data);
    }
}

bool Group::CountRollVote(ObjectGuid playerGUID, ObjectGuid Guid, uint8 Choice)
{
    Rolls::iterator rollI = GetRoll(Guid);
    if (rollI == RollId.end())
        return false;
    Roll* roll = *rollI;

    Roll::PlayerVote::iterator itr = roll->playerVote.find(playerGUID);
    // this condition means that player joins to the party after roll begins
    // Xinef: if choice == MAX_ROLL_TYPE, player was removed from the map in removefromgroup
    // Xinef: itr can be invalid as it is not used below
    if (Choice < MAX_ROLL_TYPE && itr == roll->playerVote.end())
        return false;

    if (roll->getLoot())
        if (roll->getLoot()->items.empty())
            return false;

    switch (Choice)
    {
        case ROLL_PASS:                                     // Player choose pass
            SendLootRoll(ObjectGuid::Empty, playerGUID, 128, ROLL_PASS, *roll);
            ++roll->totalPass;
            itr->second = PASS;
            break;
        case ROLL_NEED:                                     // player choose Need
            SendLootRoll(ObjectGuid::Empty, playerGUID, 0, 0, *roll);
            ++roll->totalNeed;
            itr->second = NEED;
            break;
        case ROLL_GREED:                                    // player choose Greed
            SendLootRoll(ObjectGuid::Empty, playerGUID, 128, ROLL_GREED, *roll);
            ++roll->totalGreed;
            itr->second = GREED;
            break;
        case ROLL_DISENCHANT:                               // player choose Disenchant
            SendLootRoll(ObjectGuid::Empty, playerGUID, 128, ROLL_DISENCHANT, *roll);
            ++roll->totalGreed;
            itr->second = DISENCHANT;
            break;
    }

    if (roll->totalPass + roll->totalNeed + roll->totalGreed >= roll->totalPlayersRolling)
    {
        CountTheRoll(rollI, nullptr);
        return true;
    }
    return false;
}

//called when roll timer expires
void Group::EndRoll(Loot* pLoot, Map* allowedMap)
{
    for (Rolls::iterator itr = RollId.begin(); itr != RollId.end();)
    {
        if ((*itr)->getLoot() == pLoot)
        {
            CountTheRoll(itr, allowedMap);           //i don't have to edit player votes, who didn't vote ... he will pass
            itr = RollId.begin();
        }
        else
            ++itr;
    }
}

void Group::CountTheRoll(Rolls::iterator rollI, Map* allowedMap)
{
    Roll* roll = *rollI;
    if (!roll->isValid())                                   // is loot already deleted ?
    {
        RollId.erase(rollI);
        delete roll;
        return;
    }

    //end of the roll
    if (roll->totalNeed > 0)
    {
        if (!roll->playerVote.empty())
        {
            uint8 maxresul = 0;
            ObjectGuid maxguid; // pussywizard: start with 0 >_>
            Player* player = nullptr;

            for (Roll::PlayerVote::const_iterator itr = roll->playerVote.begin(); itr != roll->playerVote.end(); ++itr)
            {
                if (itr->second != NEED)
                    continue;

                player = ObjectAccessor::FindPlayer(itr->first);
                if (!player || (allowedMap != nullptr && player->FindMap() != allowedMap))
                {
                    --roll->totalNeed;
                    continue;
                }

                uint8 randomN = urand(1, 100);
                SendLootRoll(ObjectGuid::Empty, itr->first, randomN, ROLL_NEED, *roll);
                if (maxresul < randomN)
                {
                    maxguid  = itr->first;
                    maxresul = randomN;
                }
            }

            if (maxguid) // pussywizard: added condition
            {
                SendLootRollWon(ObjectGuid::Empty, maxguid, maxresul, ROLL_NEED, *roll);
                player = ObjectAccessor::FindPlayer(maxguid);

                if (player)
                {
                    player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT, roll->itemid, maxresul);

                    ItemPosCountVec dest;
                    LootItem* item = &(roll->itemSlot >= roll->getLoot()->items.size() ? roll->getLoot()->quest_items[roll->itemSlot - roll->getLoot()->items.size()] : roll->getLoot()->items[roll->itemSlot]);
                    InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, roll->itemid, item->count);
                    if (msg == EQUIP_ERR_OK)
                    {
                        item->is_looted = true;
                        roll->getLoot()->NotifyItemRemoved(roll->itemSlot);
                        roll->getLoot()->unlootedCount--;
                        AllowedLooterSet looters = item->GetAllowedLooters();
                        Item* _item = player->StoreNewItem(dest, roll->itemid, true, item->randomPropertyId, looters);
                        if (_item)
                            sScriptMgr->OnPlayerGroupRollRewardItem(player, _item, _item->GetCount(), NEED, roll);
                        player->UpdateLootAchievements(item, roll->getLoot());
                    }
                    else
                    {
                        item->is_blocked = false;
                        item->rollWinnerGUID = player->GetGUID();
                        player->SendEquipError(msg, nullptr, nullptr, roll->itemid);
                    }
                }
            }
            else
                roll->totalNeed = 0;
        }
    }
    if (roll->totalNeed == 0 && roll->totalGreed > 0) // pussywizard: if (roll->totalNeed == 0 && ...), not else if, because numbers can be modified above if player is on a different map
    {
        if (!roll->playerVote.empty())
        {
            uint8 maxresul = 0;
            ObjectGuid maxguid; // pussywizard: start with 0
            Player* player = nullptr;
            RollVote rollvote = NOT_VALID;

            Roll::PlayerVote::iterator itr;
            for (itr = roll->playerVote.begin(); itr != roll->playerVote.end(); ++itr)
            {
                if (itr->second != GREED && itr->second != DISENCHANT)
                    continue;

                player = ObjectAccessor::FindPlayer(itr->first);
                if (!player || (allowedMap != nullptr && player->FindMap() != allowedMap))
                {
                    --roll->totalGreed;
                    continue;
                }

                uint8 randomN = urand(1, 100);
                SendLootRoll(ObjectGuid::Empty, itr->first, randomN, itr->second, *roll);
                if (maxresul < randomN)
                {
                    maxguid  = itr->first;
                    maxresul = randomN;
                    rollvote = itr->second;
                }
            }

            if (maxguid) // pussywizard: added condition
            {
                SendLootRollWon(ObjectGuid::Empty, maxguid, maxresul, rollvote, *roll);
                player = ObjectAccessor::FindPlayer(maxguid);

                if (player)
                {
                    player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED_ON_LOOT, roll->itemid, maxresul);

                    LootItem* item = &(roll->itemSlot >= roll->getLoot()->items.size() ? roll->getLoot()->quest_items[roll->itemSlot - roll->getLoot()->items.size()] : roll->getLoot()->items[roll->itemSlot]);

                    if (rollvote == GREED)
                    {
                        ItemPosCountVec dest;
                        InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, roll->itemid, item->count);
                        if (msg == EQUIP_ERR_OK)
                        {
                            item->is_looted = true;
                            roll->getLoot()->NotifyItemRemoved(roll->itemSlot);
                            roll->getLoot()->unlootedCount--;
                            AllowedLooterSet looters = item->GetAllowedLooters();
                            Item* _item = player->StoreNewItem(dest, roll->itemid, true, item->randomPropertyId, looters);
                            if (_item)
                                sScriptMgr->OnPlayerGroupRollRewardItem(player, _item, _item->GetCount(), GREED, roll);
                            player->UpdateLootAchievements(item, roll->getLoot());
                        }
                        else
                        {
                            item->is_blocked = false;
                            item->rollWinnerGUID = player->GetGUID();
                            player->SendEquipError(msg, nullptr, nullptr, roll->itemid);
                        }
                    }
                    else if (rollvote == DISENCHANT)
                    {
                        item->is_looted = true;
                        roll->getLoot()->NotifyItemRemoved(roll->itemSlot);
                        roll->getLoot()->unlootedCount--;
                        ItemTemplate const* pProto = sObjectMgr->GetItemTemplate(roll->itemid);
                        player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL, 13262); // Disenchant

                        ItemPosCountVec dest;
                        InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, roll->itemid, item->count);

                        if (msg == EQUIP_ERR_OK)
                        {
                            player->AutoStoreLoot(pProto->DisenchantID, LootTemplates_Disenchant, true);
                        }
                        else
                        {
                            Loot loot;
                            loot.FillLoot(pProto->DisenchantID, LootTemplates_Disenchant, player, true);

                            uint32 max_slot = loot.GetMaxSlotInLootFor(player);
                            for(uint32 i = 0; i < max_slot; i++)
                            {
                                LootItem* lootItem = loot.LootItemInSlot(i, player);
                                player->SendEquipError(msg, nullptr, nullptr, lootItem->itemid);
                                player->SendItemRetrievalMail(lootItem->itemid, lootItem->count);
                            }
                        }
                    }
                }
            }
            else
                roll->totalGreed = 0;
        }
    }
    if (roll->totalNeed == 0 && roll->totalGreed == 0) // pussywizard: if, not else, because numbers can be modified above if player is on a different map
    {
        SendLootAllPassed(*roll);

        // remove is_blocked so that the item is lootable by all players
        LootItem* item = &(roll->itemSlot >= roll->getLoot()->items.size() ? roll->getLoot()->quest_items[roll->itemSlot - roll->getLoot()->items.size()] : roll->getLoot()->items[roll->itemSlot]);
        if (item)
            item->is_blocked = false;
    }

    if (Loot* loot = roll->getLoot(); loot && loot->isLooted() && loot->sourceGameObject)
    {
        const GameObjectTemplate* goInfo = loot->sourceGameObject->GetGOInfo();
        if (goInfo && goInfo->type == GAMEOBJECT_TYPE_CHEST)
        {
            // Deactivate chest if the last item was rolled in group
            loot->sourceGameObject->SetLootState(GO_JUST_DEACTIVATED);
        }
    }

    RollId.erase(rollI);
    delete roll;
}

void Group::SetTargetIcon(uint8 id, ObjectGuid whoGuid, ObjectGuid targetGuid)
{
    if (id >= TARGETICONCOUNT)
        return;

    // clean other icons
    if (targetGuid)
        for (int i = 0; i < TARGETICONCOUNT; ++i)
            if (m_targetIcons[i] == targetGuid)
                SetTargetIcon(i, ObjectGuid::Empty, ObjectGuid::Empty);

    m_targetIcons[id] = targetGuid;

    //npcbot: name cache
    bool need_cache_name = false;
    Player const* setter = nullptr;
    for (GroupReference const* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        if (itr->GetSource())
        {
            if (!need_cache_name && itr->GetSource()->GetBotMgr())
                need_cache_name = true;
            if (!setter && itr->GetSource()->GetGUID() == whoGuid)
                setter = itr->GetSource();
        }
    }

    if (need_cache_name && setter)
    {
        Unit const* newtarget = targetGuid ? ObjectAccessor::GetUnit(*setter, targetGuid) : nullptr;
        std::string const& newname = newtarget ? newtarget->GetName() : "";
        for (GroupReference const* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
        {
            Player const* member = itr->GetSource();
            if (member && member->GetBotMgr())
                member->GetBotMgr()->UpdateTargetIconName(id, newname);
        }
    }
    //end npcbot

    WorldPacket data(MSG_RAID_TARGET_UPDATE, (1 + 8 + 1 + 8));
    data << uint8(0);                                       // set targets
    data << whoGuid;
    data << uint8(id);
    data << targetGuid;
    BroadcastPacket(&data, true);
}

void Group::SendTargetIconList(WorldSession* session)
{
    if (!session)
        return;

    WorldPacket data(MSG_RAID_TARGET_UPDATE, (1 + TARGETICONCOUNT * 9));
    data << uint8(1);                                       // list targets

    for (uint8 i = 0; i < TARGETICONCOUNT; ++i)
    {
        if (!m_targetIcons[i])
            continue;

        data << uint8(i);
        data << m_targetIcons[i];
    }

    session->SendPacket(&data);
}

void Group::SendUpdate()
{
    for (member_witerator witr = m_memberSlots.begin(); witr != m_memberSlots.end(); ++witr)
        SendUpdateToPlayer(witr->guid, &(*witr));
}

void Group::SendUpdateToPlayer(ObjectGuid playerGUID, MemberSlot* slot)
{
    //npcbot
    if (!playerGUID.IsPlayer())
        return;
    //end npcbot

    Player* player = ObjectAccessor::FindConnectedPlayer(playerGUID);

    if (!player || player->GetGroup() != this)
        return;

    // if MemberSlot wasn't provided
    if (!slot)
    {
        member_witerator witr = _getMemberWSlot(playerGUID);

        if (witr == m_memberSlots.end()) // if there is no MemberSlot for such a player
            return;

        slot = &(*witr);
    }

    WorldPacket data(SMSG_GROUP_LIST, (1 + 1 + 1 + 1 + 1 + 4 + 8 + 4 + 4 + (GetMembersCount() - 1) * (13 + 8 + 1 + 1 + 1 + 1) + 8 + 1 + 8 + 1 + 1 + 1 + 1));
    data << uint8(m_groupType);                         // group type (flags in 3.3)
    data << uint8(slot->group);
    data << uint8(slot->flags);
    data << uint8(slot->roles);
    if (isLFGGroup())
    {
        data << uint8(sLFGMgr->GetState(m_guid) == lfg::LFG_STATE_FINISHED_DUNGEON ? 2 : 0); // FIXME - Dungeon save status? 2 = done
        data << uint32(sLFGMgr->GetDungeon(m_guid));
    }

    data << m_guid;
    data << uint32(m_counter++);                        // 3.3, value increases every time this packet gets sent
    data << uint32(GetMembersCount() - 1);
    for (member_citerator citr = m_memberSlots.begin(); citr != m_memberSlots.end(); ++citr)
    {
        if (slot->guid == citr->guid)
            continue;

        Player* member = ObjectAccessor::FindConnectedPlayer(citr->guid);

        uint8 onlineState = (member && !member->GetSession()->PlayerLogout()) ? MEMBER_STATUS_ONLINE : MEMBER_STATUS_OFFLINE;
        onlineState = onlineState | ((isBGGroup() || isBFGroup()) ? MEMBER_STATUS_PVP : 0);

        //npcbot: bots are always online
        onlineState |= citr->guid.IsCreature() ? 1 : 0;
        //end npcbot

        data << citr->name;
        data << citr->guid;                             // guid
        data << uint8(onlineState);                     // online-state
        data << uint8(citr->group);                     // groupid
        data << uint8(citr->flags);                     // See enum GroupMemberFlags
        data << uint8(citr->roles);                     // Lfg Roles
    }

    data << m_leaderGuid;                               // leader guid

    if (GetMembersCount() - 1)
    {
        data << uint8(m_lootMethod);                    // loot method

        if (m_lootMethod == MASTER_LOOT)
            data << m_masterLooterGuid;                 // master looter guid
        else
            data << uint64(0);                          // looter guid

        data << uint8(m_lootThreshold);                 // loot threshold
        data << uint8(m_dungeonDifficulty);             // Dungeon Difficulty
        data << uint8(m_raidDifficulty);                // Raid Difficulty
        data << uint8(m_raidDifficulty >= RAID_DIFFICULTY_10MAN_HEROIC);    // 3.3 Dynamic Raid Difficulty - 0 normal/1 heroic
    }

    player->GetSession()->SendPacket(&data);
}

//npcbot
void Group::UpdateBotOutOfRange(Creature* creature)
{
    if (!creature || !creature->IsInWorld() || m_memberMgr.IsEmpty())
        return;

    WorldPacket data;
    BotMgr::BuildBotPartyMemberStatsChangedPacket(creature, &data);

    Player* member;
    for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        member = itr->GetSource();
        if (member/* && (!member->IsInMap(creature) || !member->IsWithinDist(creature, member->GetSightRange(), false))*/)
            member->SendDirectMessage(&data);
    }
}
//end npcbot

void Group::UpdatePlayerOutOfRange(Player* player)
{
    if (!player || !player->IsInWorld())
        return;

    WorldPacket data;
    player->GetSession()->BuildPartyMemberStatsChangedPacket(player, &data);

    for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        Player* member = itr->GetSource();
        if (member && (!member->IsInMap(player) || !member->IsWithinDist(player, member->GetSightRange(player), false)))
            member->GetSession()->SendPacket(&data);
    }
}

void Group::BroadcastPacket(WorldPacket const* packet, bool ignorePlayersInBGRaid, int group, ObjectGuid ignore)
{
    for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        Player* player = itr->GetSource();
        if (!player || (ignore && player->GetGUID() == ignore) || (ignorePlayersInBGRaid && player->GetGroup() != this))
            continue;

        if (group == -1 || itr->getSubGroup() == group)
            player->GetSession()->SendPacket(packet);
    }
}

void Group::BroadcastReadyCheck(WorldPacket const* packet)
{
    for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        Player* player = itr->GetSource();
        if (player)
            if (IsLeader(player->GetGUID()) || IsAssistant(player->GetGUID()))
                player->GetSession()->SendPacket(packet);
    }
}

void Group::OfflineReadyCheck()
{
    for (member_citerator citr = m_memberSlots.begin(); citr != m_memberSlots.end(); ++citr)
    {
        Player* player = ObjectAccessor::FindConnectedPlayer(citr->guid);
        if (!player)
        {
            WorldPacket data(MSG_RAID_READY_CHECK_CONFIRM, 9);
            data << citr->guid;
            data << uint8(0);
            BroadcastReadyCheck(&data);
        }
    }
}

bool Group::SameSubGroup(Player const* member1, Player const* member2) const
{
    if (!member1 || !member2)
        return false;

    if (member1->GetGroup() != this || member2->GetGroup() != this)
        return false;
    else
        return member1->GetSubGroup() == member2->GetSubGroup();
}

// Allows setting sub groups both for online or offline members
void Group::ChangeMembersGroup(ObjectGuid guid, uint8 group)
{
    // Only raid groups have sub groups
    if (!isRaidGroup())
        return;

    // Check if player is really in the raid
    member_witerator slot = _getMemberWSlot(guid);
    if (slot == m_memberSlots.end())
        return;

    // Abort if the player is already in the target sub group
    uint8 prevSubGroup = GetMemberGroup(guid);
    if (prevSubGroup == group)
        return;

    // Update the player slot with the new sub group setting
    slot->group = group;

    // Increase the counter of the new sub group..
    SubGroupCounterIncrease(group);

    // ..and decrease the counter of the previous one
    SubGroupCounterDecrease(prevSubGroup);

    // Preserve new sub group in database for non-raid groups
    if (!isBGGroup() && !isBFGroup())
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_GROUP_MEMBER_SUBGROUP);

        stmt->SetData(0, group);
        stmt->SetData(1, guid.GetCounter());

        CharacterDatabase.Execute(stmt);
    }

    //npcbot
    if (guid.IsCreature())
    {
        Creature const* cbot = BotDataMgr::FindBot(guid.GetEntry());
        if (Creature* bot = cbot ? const_cast<Creature*>(cbot) : nullptr)
        {
            if (bot->GetBotGroup() == this)
                bot->SetOriginalSubGroup(group);
            else
            {
                // If player is in BG raid, it is possible that he is also in normal raid - and that normal raid is stored in m_originalGroup reference
                prevSubGroup = bot->GetOriginalSubGroup();
                bot->SetOriginalSubGroup(group);
            }
        }
    }
    else
    //end npcbot
    // In case the moved player is online, update the player object with the new sub group references
    if (Player* player = ObjectAccessor::FindConnectedPlayer(guid))
    {
        if (player->GetGroup() == this)
            player->GetGroupRef().setSubGroup(group);
        else // If player is in BG raid, it is possible that he is also in normal raid - and that normal raid is stored in m_originalGroup reference
            player->GetOriginalGroupRef().setSubGroup(group);
    }

    // Broadcast the changes to the group
    SendUpdate();
}

// Retrieve the next Round-Roubin player for the group
//
// No update done if loot method is FFA.
//
// If the RR player is not yet set for the group, the first group member becomes the round-robin player.
// If the RR player is set, the next player in group becomes the round-robin player.
//
// If ifneed is true,
//      the current RR player is checked to be near the looted object.
//      if yes, no update done.
//      if not, he loses his turn.
void Group::UpdateLooterGuid(WorldObject* pLootedObject, bool ifneed)
{
    // round robin style looting applies for all low
    // quality items in each loot method except free for all
    if (GetLootMethod() == FREE_FOR_ALL)
        return;

    ObjectGuid oldLooterGUID = GetLooterGuid();
    member_citerator guid_itr = _getMemberCSlot(oldLooterGUID);
    if (guid_itr != m_memberSlots.end())
    {
        if (ifneed)
        {
            // not update if only update if need and ok
            Player* looter = ObjectAccessor::FindPlayer(guid_itr->guid);
            if (looter && looter->IsAtLootRewardDistance(pLootedObject))
                return;
        }
        ++guid_itr;
    }

    // search next after current
    Player* pNewLooter = nullptr;
    for (member_citerator itr = guid_itr; itr != m_memberSlots.end(); ++itr)
    {
        if (Player* player = ObjectAccessor::FindPlayer(itr->guid))
            if (player->IsAtLootRewardDistance(pLootedObject))
            {
                pNewLooter = player;
                break;
            }
    }

    if (!pNewLooter)
    {
        // search from start
        for (member_citerator itr = m_memberSlots.begin(); itr != guid_itr; ++itr)
        {
            if (Player* player = ObjectAccessor::FindPlayer(itr->guid))
                if (player->IsAtLootRewardDistance(pLootedObject))
                {
                    pNewLooter = player;
                    break;
                }
        }
    }

    if (pNewLooter)
    {
        if (oldLooterGUID != pNewLooter->GetGUID())
        {
            SetLooterGuid(pNewLooter->GetGUID());
            SendUpdate();
        }
    }
    else
    {
        SetLooterGuid(ObjectGuid::Empty);
        SendUpdate();
    }
}

GroupJoinBattlegroundResult Group::CanJoinBattlegroundQueue(Battleground const* bgTemplate, BattlegroundQueueTypeId bgQueueTypeId, uint32 MinPlayerCount, uint32 /*MaxPlayerCount*/, bool isRated, uint32 arenaSlot)
{
    // check if this group is LFG group
    if (isLFGGroup())
        return ERR_LFG_CANT_USE_BATTLEGROUND;

    BattlemasterListEntry const* bgEntry = sBattlemasterListStore.LookupEntry(bgTemplate->GetBgTypeID());
    if (!bgEntry)
        return ERR_GROUP_JOIN_BATTLEGROUND_FAIL;

    // too many players in the group
    if (GetMembersCount() > bgEntry->maxGroupSize)
        return ERR_BATTLEGROUND_NONE;

    // get a player as reference, to compare other players' stats to (arena team id, level bracket, etc.)
    Player* reference = GetFirstMember()->GetSource();
    if (!reference)
        return ERR_BATTLEGROUND_JOIN_FAILED;

    PvPDifficultyEntry const* bracketEntry = GetBattlegroundBracketByLevel(bgTemplate->GetMapId(), reference->GetLevel());
    if (!bracketEntry)
        return ERR_BATTLEGROUND_JOIN_FAILED;

    uint32 arenaTeamId = reference->GetArenaTeamId(arenaSlot);
    TeamId teamId = reference->GetTeamId();

    BattlegroundQueueTypeId bgQueueTypeIdRandom = BattlegroundMgr::BGQueueTypeId(BATTLEGROUND_RB, 0);

    // check every member of the group to be able to join
    uint32 memberscount = 0;
    for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next(), ++memberscount)
    {
        Player* member = itr->GetSource();

        // don't let join with offline members
        if (!member)
            return ERR_BATTLEGROUND_JOIN_FAILED;

        if (!sScriptMgr->CanGroupJoinBattlegroundQueue(this, member, bgTemplate, MinPlayerCount, isRated, arenaSlot))
            return ERR_BATTLEGROUND_JOIN_FAILED;

        // don't allow cross-faction groups to join queue
        if (member->GetTeamId() != teamId && !sWorld->getBoolConfig(CONFIG_ALLOW_TWO_SIDE_INTERACTION_GROUP))
            return ERR_BATTLEGROUND_JOIN_TIMED_OUT;

        // don't let join rated matches if the arena team id doesn't match
        if (isRated && member->GetArenaTeamId(arenaSlot) != arenaTeamId)
            return ERR_BATTLEGROUND_JOIN_FAILED;

        // not in the same battleground level braket, don't let join
        PvPDifficultyEntry const* memberBracketEntry = GetBattlegroundBracketByLevel(bracketEntry->mapId, member->GetLevel());
        if (memberBracketEntry != bracketEntry)
            return ERR_BATTLEGROUND_JOIN_RANGE_INDEX;

        // check for deserter debuff in case not arena queue
        if (bgTemplate->GetBgTypeID() != BATTLEGROUND_AA && !member->CanJoinToBattleground())
            return ERR_GROUP_JOIN_BATTLEGROUND_DESERTERS;

        // check if someone in party is using dungeon system
        lfg::LfgState lfgState = sLFGMgr->GetState(member->GetGUID());
        if (lfgState > lfg::LFG_STATE_NONE && (lfgState != lfg::LFG_STATE_QUEUED || !sWorld->getBoolConfig(CONFIG_ALLOW_JOIN_BG_AND_LFG)))
        {
            return ERR_LFG_CANT_USE_BATTLEGROUND;
        }

        // pussywizard: prevent joining when any member is in bg/arena
        if (member->InBattleground())
            return ERR_BATTLEGROUND_JOIN_FAILED;

        // pussywizard: check for free slot, this is actually ensured before calling this function, but just in case
        if (!member->HasFreeBattlegroundQueueId())
            return ERR_BATTLEGROUND_TOO_MANY_QUEUES;

        // don't let join if someone from the group is already in that bg queue
        if (member->InBattlegroundQueueForBattlegroundQueueType(bgQueueTypeId))
        {
            return ERR_BATTLEGROUND_JOIN_FAILED;
        }

        // don't let join if someone from the group is in bg queue random
        if (member->InBattlegroundQueueForBattlegroundQueueType(bgQueueTypeIdRandom))
            return ERR_IN_RANDOM_BG;

        // don't let join to bg queue random if someone from the group is already in bg queue
        if (bgTemplate->GetBgTypeID() == BATTLEGROUND_RB && member->InBattlegroundQueue())
            return ERR_IN_NON_RANDOM_BG;

        // don't let Death Knights join BG queues when they are not allowed to be teleported yet
        if (member->IsClass(CLASS_DEATH_KNIGHT, CLASS_CONTEXT_TELEPORT) && member->GetMapId() == MAP_EBON_HOLD && !member->IsGameMaster() && !member->HasSpell(50977))
            return ERR_GROUP_JOIN_BATTLEGROUND_FAIL;

        if (!member->GetBGAccessByLevel(bgTemplate->GetBgTypeID()))
        {
            return ERR_BATTLEGROUND_JOIN_TIMED_OUT;
        }
    }

    //npcbot
    for (GroupBotReference* bitr = GetFirstBotMember(); bitr != nullptr; bitr = bitr->next(), ++memberscount)
    {
        if (!bitr->GetSource())
            return ERR_BATTLEGROUND_JOIN_FAILED;
    }
    //end npcbot

    // for arenas: check party size is proper
    if (bgTemplate->isArena() && memberscount != MinPlayerCount)
        return ERR_ARENA_TEAM_PARTY_SIZE;

    //check against other arena team members
    if (isRated)
    {
        ArenaTeam* arenaTeam = sArenaTeamMgr->GetArenaTeamById(arenaTeamId);
        for (auto const& itr : arenaTeam->GetMembers())
        {
            Player* teamMember = ObjectAccessor::FindConnectedPlayer(itr.Guid);
            //are they online and not a member of this current group?
            if (teamMember && !IsMember(teamMember->GetGUID()))
            {
                //are they already in queue for a rated arena?
                if (teamMember->InBattlegroundQueueForBattlegroundQueueType(bgQueueTypeId))
                {
                    GroupQueueInfo ginfo;
                    BattlegroundQueue& queue = sBattlegroundMgr->GetBattlegroundQueue(bgQueueTypeId);
                    if (queue.GetPlayerGroupInfoData(teamMember->GetGUID(), &ginfo))
                    {
                        if (ginfo.IsRated)
                            return ERR_BATTLEGROUND_JOIN_FAILED;
                    }
                }
                //are they currently in an arena match?
                Battleground* bg = teamMember->GetBattleground(false);
                if (bg && bg->isRated() && bg->GetMinPlayersPerTeam() == MinPlayerCount)
                    return ERR_BATTLEGROUND_JOIN_FAILED;
            }
        }
    }

    return GroupJoinBattlegroundResult(bgTemplate->GetBgTypeID());
}

//===================================================
//============== Roll ===============================
//===================================================

void Roll::targetObjectBuildLink()
{
    // called from link()
    getTarget()->addLootValidatorRef(this);
}

void Group::SetDungeonDifficulty(Difficulty difficulty)
{
    m_dungeonDifficulty = difficulty;
    if (!isBGGroup() && !isBFGroup())
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_GROUP_DIFFICULTY);

        stmt->SetData(0, uint8(m_dungeonDifficulty));
        stmt->SetData(1, GetGUID().GetCounter());

        CharacterDatabase.Execute(stmt);
    }

    for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        Player* player = itr->GetSource();
        player->SetDungeonDifficulty(difficulty);
        player->SendDungeonDifficulty(true);
    }
}

void Group::SetRaidDifficulty(Difficulty difficulty)
{
    m_raidDifficulty = difficulty;
    if (!isBGGroup() && !isBFGroup())
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_GROUP_RAID_DIFFICULTY);

        stmt->SetData(0, uint8(m_raidDifficulty));
        stmt->SetData(1, GetGUID().GetCounter());

        CharacterDatabase.Execute(stmt);
    }

    for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        Player* player = itr->GetSource();
        player->SetRaidDifficulty(difficulty);
        player->SendRaidDifficulty(true);
    }
}

void Group::ResetInstances(uint8 method, bool isRaid, Player* leader)
{
    if (isBGGroup() || isBFGroup() || isLFGGroup())
        return;

    switch (method)
    {
        case INSTANCE_RESET_ALL:
            {
                if (leader->GetDifficulty(false) != DUNGEON_DIFFICULTY_NORMAL)
                    break;
                std::vector<InstanceSave*> toUnbind;
                BoundInstancesMap const& m_boundInstances = sInstanceSaveMgr->PlayerGetBoundInstances(leader->GetGUID(), Difficulty(DUNGEON_DIFFICULTY_NORMAL));
                for (BoundInstancesMap::const_iterator itr = m_boundInstances.begin(); itr != m_boundInstances.end(); ++itr)
                {
                    InstanceSave* instanceSave = itr->second.save;
                    MapEntry const* entry = sMapStore.LookupEntry(itr->first);
                    if (!entry || entry->IsRaid() || !instanceSave->CanReset())
                        continue;

                    Map* map = sMapMgr->FindMap(instanceSave->GetMapId(), instanceSave->GetInstanceId());
                    if (!map || map->ToInstanceMap()->Reset(method))
                    {
                        leader->SendResetInstanceSuccess(instanceSave->GetMapId());
                        toUnbind.push_back(instanceSave);
                    }
                    else
                    {
                        leader->SendResetInstanceFailed(0, instanceSave->GetMapId());
                    }

                    sInstanceSaveMgr->DeleteInstanceSavedData(instanceSave->GetInstanceId());
                }
                for (std::vector<InstanceSave*>::const_iterator itr = toUnbind.begin(); itr != toUnbind.end(); ++itr)
                    sInstanceSaveMgr->UnbindAllFor(*itr);
            }
            break;
        case INSTANCE_RESET_CHANGE_DIFFICULTY:
            {
                std::vector<InstanceSave*> toUnbind;
                BoundInstancesMap const& m_boundInstances = sInstanceSaveMgr->PlayerGetBoundInstances(leader->GetGUID(), leader->GetDifficulty(isRaid));
                for (BoundInstancesMap::const_iterator itr = m_boundInstances.begin(); itr != m_boundInstances.end(); ++itr)
                {
                    InstanceSave* instanceSave = itr->second.save;
                    MapEntry const* entry = sMapStore.LookupEntry(itr->first);
                    if (!entry || entry->IsRaid() != isRaid || !instanceSave->CanReset())
                        continue;

                    Map* map = sMapMgr->FindMap(instanceSave->GetMapId(), instanceSave->GetInstanceId());
                    if (!map || map->ToInstanceMap()->Reset(method))
                    {
                        leader->SendResetInstanceSuccess(instanceSave->GetMapId());
                        toUnbind.push_back(instanceSave);
                    }
                    else
                    {
                        leader->SendResetInstanceFailed(0, instanceSave->GetMapId());
                    }

                    sInstanceSaveMgr->DeleteInstanceSavedData(instanceSave->GetInstanceId());
                }
                for (std::vector<InstanceSave*>::const_iterator itr = toUnbind.begin(); itr != toUnbind.end(); ++itr)
                    sInstanceSaveMgr->UnbindAllFor(*itr);
            }
            break;
    }
}

void Group::_homebindIfInstance(Player* player)
{
    if (player && !player->IsGameMaster() && player->FindMap() && sMapStore.LookupEntry(player->GetMapId())->IsDungeon())
        player->m_InstanceValid = false;
}

void Group::_cancelHomebindIfInstance(Player* player)
{
    // if player is reinvited to group and in the instance - cancel homebind timer
    if (!player->FindMap() || !player->FindMap()->IsDungeon())
        return;
    InstancePlayerBind* bind = sInstanceSaveMgr->PlayerGetBoundInstance(player->GetGUID(), player->FindMap()->GetId(), player->GetDifficulty(player->FindMap()->IsRaid()));
    if (bind && bind->save->GetInstanceId() == player->GetInstanceId())
        player->m_InstanceValid = true;
}

void Group::BroadcastGroupUpdate(void)
{
    // FG: HACK: force flags update on group leave - for values update hack
    // -- not very efficient but safe
    for (member_citerator citr = m_memberSlots.begin(); citr != m_memberSlots.end(); ++citr)
    {
        Player* pp = ObjectAccessor::FindPlayer(citr->guid);
        if (pp)
        {
            pp->ForceValuesUpdateAtIndex(UNIT_FIELD_BYTES_2);
            pp->ForceValuesUpdateAtIndex(UNIT_FIELD_FACTIONTEMPLATE);
            LOG_DEBUG("group", "-- Forced group value update for '{}'", pp->GetName());
        }
    }
}

void Group::ResetMaxEnchantingLevel()
{
    m_maxEnchantingLevel = 0;
    Player* pMember = nullptr;
    for (member_citerator citr = m_memberSlots.begin(); citr != m_memberSlots.end(); ++citr)
    {
        pMember = ObjectAccessor::FindPlayer(citr->guid);
        if (pMember && pMember->GetSession() && !pMember->GetSession()->IsSocketClosed()
            && m_maxEnchantingLevel < pMember->GetSkillValue(SKILL_ENCHANTING))
        {
            m_maxEnchantingLevel = pMember->GetSkillValue(SKILL_ENCHANTING);
        }
    }
}

void Group::SetLootMethod(LootMethod method)
{
    m_lootMethod = method;
}

void Group::SetLooterGuid(ObjectGuid guid)
{
    m_looterGuid = guid;
}

void Group::SetMasterLooterGuid(ObjectGuid guid)
{
    m_masterLooterGuid = guid;
}

void Group::SetLootThreshold(ItemQualities threshold)
{
    m_lootThreshold = threshold;
}

void Group::SetLfgRoles(ObjectGuid guid, const uint8 roles)
{
    member_witerator slot = _getMemberWSlot(guid);
    if (slot == m_memberSlots.end())
        return;

    slot->roles = roles;
    SendUpdate();
}

bool Group::IsFull() const
{
    return isRaidGroup() ? (m_memberSlots.size() >= MAXRAIDSIZE) : (m_memberSlots.size() >= MAXGROUPSIZE);
}

bool Group::isLFGGroup(bool restricted /*= false*/) const
{
    bool isLFG = m_groupType & GROUPTYPE_LFG;
    return isLFG && (!restricted || (m_groupType & GROUPTYPE_LFG_RESTRICTED) != 0);
}

bool Group::isRaidGroup() const
{
    return m_groupType & GROUPTYPE_RAID;
}

bool Group::isBGGroup() const
{
    return m_bgGroup != nullptr;
}

bool Group::isBFGroup() const
{
    return m_bfGroup != nullptr;
}

bool Group::IsCreated() const
{
    return GetMembersCount() > 0;
}

GroupType Group::GetGroupType() const
{
    return m_groupType;
}

ObjectGuid Group::GetLeaderGUID() const
{
    return m_leaderGuid;
}

Player* Group::GetLeader()
{
    return ObjectAccessor::FindConnectedPlayer(m_leaderGuid);
}

ObjectGuid Group::GetGUID() const
{
    return m_guid;
}

const char* Group::GetLeaderName() const
{
    return m_leaderName.c_str();
}

LootMethod Group::GetLootMethod() const
{
    return m_lootMethod;
}

ObjectGuid Group::GetLooterGuid() const
{
    return m_looterGuid;
}

ObjectGuid Group::GetMasterLooterGuid() const
{
    return m_masterLooterGuid;
}

ItemQualities Group::GetLootThreshold() const
{
    return m_lootThreshold;
}

bool Group::IsMember(ObjectGuid guid) const
{
    return _getMemberCSlot(guid) != m_memberSlots.end();
}

bool Group::IsLeader(ObjectGuid guid) const
{
    return (GetLeaderGUID() == guid);
}

ObjectGuid Group::GetMemberGUID(const std::string& name)
{
    for (member_citerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
        if (itr->name == name)
            return itr->guid;

    return ObjectGuid::Empty;
}

bool Group::IsAssistant(ObjectGuid guid) const
{
    member_citerator mslot = _getMemberCSlot(guid);
    if (mslot == m_memberSlots.end())
        return false;
    return mslot->flags & MEMBER_FLAG_ASSISTANT;
}

bool Group::SameSubGroup(ObjectGuid guid1, ObjectGuid guid2) const
{
    member_citerator mslot2 = _getMemberCSlot(guid2);
    if (mslot2 == m_memberSlots.end())
        return false;
    return SameSubGroup(guid1, &*mslot2);
}

bool Group::SameSubGroup(ObjectGuid guid1, MemberSlot const* slot2) const
{
    member_citerator mslot1 = _getMemberCSlot(guid1);
    if (mslot1 == m_memberSlots.end() || !slot2)
        return false;
    return (mslot1->group == slot2->group);
}

bool Group::HasFreeSlotSubGroup(uint8 subgroup) const
{
    return (m_subGroupsCounts && m_subGroupsCounts[subgroup] < MAXGROUPSIZE);
}

uint8 Group::GetMemberGroup(ObjectGuid guid) const
{
    member_citerator mslot = _getMemberCSlot(guid);
    if (mslot == m_memberSlots.end())
        return (MAX_RAID_SUBGROUPS + 1);
    return mslot->group;
}

void Group::SetBattlegroundGroup(Battleground* bg)
{
    m_bgGroup = bg;
}

void Group::SetBattlefieldGroup(Battlefield* bg)
{
    m_bfGroup = bg;
}

void Group::SetGroupMemberFlag(ObjectGuid guid, bool apply, GroupMemberFlags flag)
{
    // Assistants, main assistants and main tanks are only available in raid groups
    if (!isRaidGroup())
        return;

    // Check if player is really in the raid
    member_witerator slot = _getMemberWSlot(guid);
    if (slot == m_memberSlots.end())
        return;

    // Do flag specific actions, e.g ensure uniqueness
    switch (flag)
    {
        case MEMBER_FLAG_MAINASSIST:
            RemoveUniqueGroupMemberFlag(MEMBER_FLAG_MAINASSIST);         // Remove main assist flag from current if any.
            break;
        case MEMBER_FLAG_MAINTANK:
            RemoveUniqueGroupMemberFlag(MEMBER_FLAG_MAINTANK);           // Remove main tank flag from current if any.
            break;
        case MEMBER_FLAG_ASSISTANT:
            break;
        default:
            return;                                                      // This should never happen
    }

    // Switch the actual flag
    ToggleGroupMemberFlag(slot, flag, apply);

    // Preserve the new setting in the db
    //npcbot
    if (!guid.IsPlayer())
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_NPCBOT_GROUP_MEMBER_FLAG);
        stmt->SetData(0, slot->flags);
        stmt->SetData(1, guid.GetEntry());
        CharacterDatabase.Execute(stmt);
    }
    else
    {
    //end npcbot
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_GROUP_MEMBER_FLAG);

    stmt->SetData(0, slot->flags);
    stmt->SetData(1, guid.GetCounter());

    CharacterDatabase.Execute(stmt);
    //npcbot
    }
    //end npcbot

    // Broadcast the changes to the group
    SendUpdate();
}

Difficulty Group::GetDifficulty(bool isRaid) const
{
    return isRaid ? m_raidDifficulty : m_dungeonDifficulty;
}

Difficulty Group::GetDungeonDifficulty() const
{
    return m_dungeonDifficulty;
}

Difficulty Group::GetRaidDifficulty() const
{
    return m_raidDifficulty;
}

bool Group::isRollLootActive() const
{
    return !RollId.empty();
}

Group::Rolls::iterator Group::GetRoll(ObjectGuid Guid)
{
    Rolls::iterator iter;
    for (iter = RollId.begin(); iter != RollId.end(); ++iter)
        if ((*iter)->itemGUID == Guid && (*iter)->isValid())
            return iter;
    return RollId.end();
}

void Group::LinkMember(GroupReference* pRef)
{
    m_memberMgr.insertFirst(pRef);
}


//npcbot
void Group::LinkBotMember(GroupBotReference* bRef)
{
    m_botMemberMgr.insertFirst(bRef);
}

void Group::DelinkBotMember(ObjectGuid guid)
{
    GroupBotReference* ref = m_botMemberMgr.getFirst();
    while (ref)
    {
        GroupBotReference* nextRef = ref->next();
        if (ref->GetSource()->GetGUID() == guid)
        {
            ref->unlink();
            break;
        }
        ref = nextRef;
    }
}
//end npcbot
void Group::_initRaidSubGroupsCounter()
{
    // Sub group counters initialization
    if (!m_subGroupsCounts)
        m_subGroupsCounts = new uint8[MAX_RAID_SUBGROUPS];

    memset((void*)m_subGroupsCounts, 0, (MAX_RAID_SUBGROUPS)*sizeof(uint8));

    for (member_citerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
        ++m_subGroupsCounts[itr->group];
}

Group::member_citerator Group::_getMemberCSlot(ObjectGuid Guid) const
{
    for (member_citerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
        if (itr->guid == Guid)
            return itr;
    return m_memberSlots.end();
}

Group::member_witerator Group::_getMemberWSlot(ObjectGuid Guid)
{
    for (member_witerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
        if (itr->guid == Guid)
            return itr;
    return m_memberSlots.end();
}

void Group::SubGroupCounterIncrease(uint8 subgroup)
{
    if (m_subGroupsCounts)
        ++m_subGroupsCounts[subgroup];
}

void Group::SubGroupCounterDecrease(uint8 subgroup)
{
    if (m_subGroupsCounts)
        --m_subGroupsCounts[subgroup];
}

void Group::RemoveUniqueGroupMemberFlag(GroupMemberFlags flag)
{
    for (member_witerator itr = m_memberSlots.begin(); itr != m_memberSlots.end(); ++itr)
        if (itr->flags & flag)
            itr->flags &= ~flag;
}

void Group::ToggleGroupMemberFlag(member_witerator slot, uint8 flag, bool apply)
{
    if (apply)
        slot->flags |= flag;
    else
        slot->flags &= ~flag;
}

uint32 Group::GetDifficultyChangePreventionTime() const
{
    return _difficultyChangePreventionTime > GameTime::GetGameTime().count() ? _difficultyChangePreventionTime - GameTime::GetGameTime().count() : 0;
}

void Group::SetDifficultyChangePrevention(DifficultyPreventionChangeType type)
{
    _difficultyChangePreventionTime = GameTime::GetGameTime().count() + MINUTE;
    _difficultyChangePreventionType = type;
}

void Group::DoForAllMembers(std::function<void(Player*)> const& worker)
{
    for (GroupReference* itr = GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        Player* member = itr->GetSource();
        if (!member)
            continue;

        worker(member);
    }
}
