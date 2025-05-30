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

#ifndef OUTDOOR_PVP_EP_
#define OUTDOOR_PVP_EP_

#include "DBCStructure.h"
#include "OutdoorPvP.h"

const uint32 EP_AllianceBuffs[4] = {11413, 11414, 11415, 1386};

const uint32 EP_HordeBuffs[4] = {30880, 30683, 30682, 29520};

const uint32 EP_GraveyardZone = AREA_EASTERN_PLAGUELANDS;

const uint32 EP_GraveyardId = 927;

const uint8 EPBuffZonesNum = 3;

const uint32 EP_EWT_CM = 17690;
const uint32 EP_CGT_CM = 17689;
const uint32 EP_NPT_CM = 17696;
const uint32 EP_PWT_CM = 17698;

const uint32 EPBuffZones[EPBuffZonesNum] =
{
    AREA_EASTERN_PLAGUELANDS,
    AREA_STRATHOLME,
    AREA_SCHOLOMANCE
};

//enum EP_TaxiNodes
//{
//    EP_CGT_Taxi = 87,
//    EP_EWT_Taxi = 86,
//    EP_NPT_Taxi = 85,
//    EP_PWT_Taxi = 84
//};

enum EP_Summons
{
    EP_EWT_COMMANDER = 0,
    EP_EWT_SOLDIER1,
    EP_EWT_SOLDIER2,
    EP_EWT_SOLDIER3,
    EP_EWT_SOLDIER4,
    EP_PWT_FLIGHTMASTER,
};

enum EP_GoSummons
{
    EP_NPT_BUFF = 0,
    EP_NPT_FLAGS,
    EP_EWT_FLAGS,
    EP_CGT_FLAGS,
    EP_PWT_FLAGS
};

enum EP_Towers
{
    EP_EWT = 0, // plaguelands 03
    EP_NPT, // plaguelands 01
    EP_PWT, // plaguelands 04
    EP_CGT, // plaguelands 02
    EP_TOWER_NUM
};

const go_type EPCapturePoints[EP_TOWER_NUM] =
{
    {182097, MAP_EASTERN_KINGDOMS, 2574.51f, -4794.89f, 144.704f, -1.45003f, -0.097056f, 0.095578f, -0.656229f, 0.742165f},
    {181899, MAP_EASTERN_KINGDOMS, 3181.08f, -4379.36f, 174.123f, -2.03472f, -0.065392f, 0.119494f, -0.842275f, 0.521553f},
    {182098, MAP_EASTERN_KINGDOMS, 2962.71f, -3042.31f, 154.789f, 2.08426f, -0.074807f, -0.113837f, 0.855928f, 0.49883f},
    {182096, MAP_EASTERN_KINGDOMS, 1860.85f, -3731.23f, 196.716f, -2.53214f, 0.033967f, -0.131914f, 0.944741f, -0.298177f}
};

const go_type EPTowerFlags[EP_TOWER_NUM] =
{
    {182106, MAP_EASTERN_KINGDOMS, 2569.60f, -4772.93f, 115.399f, 2.72271f, 0.0f, 0.0f, 0.978148f, 0.207912f},
    {182106, MAP_EASTERN_KINGDOMS, 3148.17f, -4365.51f, 145.029f, 1.53589f, 0.0f, 0.0f, 0.694658f, 0.71934f},
    {182106, MAP_EASTERN_KINGDOMS, 2992.63f, -3022.95f, 125.593f, 3.03687f, 0.0f, 0.0f, 0.99863f, 0.052336f},
    {182106, MAP_EASTERN_KINGDOMS, 1838.42f, -3703.56f, 167.713f, 0.890118f, 0.0f, 0.0f, 0.430511f, 0.902585f}
};

//const uint32 EPTowerPlayerEnterEvents[EP_TOWER_NUM] = {10691, 10699, 10701, 10705};

//const uint32 EPTowerPlayerLeaveEvents[EP_TOWER_NUM] = {10692, 10698, 10700, 10704};

const uint8 EP_NUM_CREATURES = 6;
const uint8 EP_EWT_NUM_CREATURES = 5;

// one lordaeron commander, 4 soldiers
// should be spawned at EWT and follow a path, but trans-grid pathing isn't safe, so summon them directly at NPT
const creature_type EP_EWT_Summons_A[EP_EWT_NUM_CREATURES] =
{
	/* Lanny - NPCBot
    {17635, MAP_EASTERN_KINGDOMS, 3167.61f, -4352.09f, 138.20f, 4.5811f},
    {17647, MAP_EASTERN_KINGDOMS, 3172.74f, -4352.99f, 139.14f, 4.9873f},
    {17647, MAP_EASTERN_KINGDOMS, 3165.89f, -4354.46f, 138.67f, 3.7244f},
    {17647, MAP_EASTERN_KINGDOMS, 3164.65f, -4350.26f, 138.22f, 2.4794f},
    {17647, MAP_EASTERN_KINGDOMS, 3169.91f, -4349.68f, 138.37f, 0.7444f}	
    */
    {17635, MAP_EASTERN_KINGDOMS, 2545.37f, -4778.07f, 108.13f, 2.3307f},
    {17647, MAP_EASTERN_KINGDOMS, 2549.94f, -4778.65f, 109.10f, 2.3306f},
    {17647, MAP_EASTERN_KINGDOMS, 2545.19f, -4781.94f, 109.24f, 2.3306f},
    {17647, MAP_EASTERN_KINGDOMS, 2545.53f, -4774.84f, 107.52f, 2.3307f},
    {17647, MAP_EASTERN_KINGDOMS, 2541.47f, -4778.71f, 107.85f, 2.3307f}
    // End Lanny NPCBot
};

const creature_type EP_EWT_Summons_H[EP_EWT_NUM_CREATURES] =
{
    /* Lanny - NPCBot
    {17995, MAP_EASTERN_KINGDOMS, 3167.61f, -4352.09f, 138.20f, 4.5811f},
    {17996, MAP_EASTERN_KINGDOMS, 3172.74f, -4352.99f, 139.14f, 4.9873f},
    {17996, MAP_EASTERN_KINGDOMS, 3165.89f, -4354.46f, 138.67f, 3.7244f},
    {17996, MAP_EASTERN_KINGDOMS, 3164.65f, -4350.26f, 138.22f, 2.4794f},
    {17996, MAP_EASTERN_KINGDOMS, 3169.91f, -4349.68f, 138.37f, 0.7444f}
    */
    {17995, MAP_EASTERN_KINGDOMS, 2545.37f, -4778.07f, 108.13f, 2.3307f},
    {17996, MAP_EASTERN_KINGDOMS, 2549.94f, -4778.65f, 109.10f, 2.3306f},
    {17996, MAP_EASTERN_KINGDOMS, 2545.19f, -4781.94f, 109.24f, 2.3306f},
    {17996, MAP_EASTERN_KINGDOMS, 2545.53f, -4774.84f, 107.52f, 2.3307f},
    {17996, MAP_EASTERN_KINGDOMS, 2541.47f, -4778.71f, 107.85f, 2.3307f}
    // End Lanny NPCBot
};

enum EP_TowerStates
{
    EP_TS_N = 1,
    EP_TS_N_A = 2,
    EP_TS_N_H = 4,
    EP_TS_A_P = 8,
    EP_TS_H_P = 16,
    EP_TS_A = 32,
    EP_TS_H = 64
};

// when spawning, pay attention at setting the faction manually!
const creature_type EP_PWT_FlightMaster = {17209, MAP_EASTERN_KINGDOMS, 2987.5f, -3049.11f, 120.126f, 5.75959f};

// after spawning, modify the faction so that only the controller will be able to use it with SetUInt32Value(GAMEOBJECT_FACTION, faction_id);
const go_type EP_NPT_LordaeronShrine = {181682, MAP_EASTERN_KINGDOMS, 3167.72f, -4355.91f, 138.785f, 1.69297f, 0.0f, 0.0f, 0.748956f, 0.66262f};

class OutdoorPvPEP;

class OPvPCapturePointEP_EWT : public OPvPCapturePoint
{
public:
    OPvPCapturePointEP_EWT(OutdoorPvP* pvp);

    void ChangeState() override;

    void SendChangePhase() override;

    void FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet) override;

    // used when player is activated/inactivated in the area
    bool HandlePlayerEnter(Player* player) override;
    void HandlePlayerLeave(Player* player) override;

protected:
    void SummonSupportUnitAtNorthpassTower(TeamId teamId);

    void UpdateTowerState();

protected:
    uint32 m_TowerState;

    TeamId m_UnitsSummonedSideId;
};

class OPvPCapturePointEP_NPT : public OPvPCapturePoint
{
public:
    OPvPCapturePointEP_NPT(OutdoorPvP* pvp);

    void ChangeState() override;

    void SendChangePhase() override;

    void FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet) override;

    // used when player is activated/inactivated in the area
    bool HandlePlayerEnter(Player* player) override;
    void HandlePlayerLeave(Player* player) override;

protected:
    void SummonGO(TeamId teamId);

    void UpdateTowerState();

protected:
    uint32 m_TowerState;

    TeamId m_SummonedGOSideId;
};

class OPvPCapturePointEP_CGT : public OPvPCapturePoint
{
public:
    OPvPCapturePointEP_CGT(OutdoorPvP* pvp);

    void ChangeState() override;

    void SendChangePhase() override;

    void FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet) override;

    // used when player is activated/inactivated in the area
    bool HandlePlayerEnter(Player* player) override;
    void HandlePlayerLeave(Player* player) override;

protected:
    void LinkGraveyard(TeamId teamId);

    void UpdateTowerState();

protected:
    uint32 m_TowerState;

    TeamId m_GraveyardSide;
};

class OPvPCapturePointEP_PWT : public OPvPCapturePoint
{
public:
    OPvPCapturePointEP_PWT(OutdoorPvP* pvp);

    void ChangeState() override;

    void SendChangePhase() override;

    void FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet) override;

    // used when player is activated/inactivated in the area
    bool HandlePlayerEnter(Player* player) override;
    void HandlePlayerLeave(Player* player) override;

protected:
    void SummonFlightMaster(TeamId teamId);

    void UpdateTowerState();

protected:
    TeamId m_FlightMasterSpawnedId;

    uint32 m_TowerState;
};

class OutdoorPvPEP : public OutdoorPvP
{
public:
    OutdoorPvPEP();

    bool SetupOutdoorPvP() override;

    void HandlePlayerEnterZone(Player* player, uint32 zone) override;
    void HandlePlayerLeaveZone(Player* player, uint32 zone) override;

    bool Update(uint32 diff) override;

    void FillInitialWorldStates(WorldPackets::WorldState::InitWorldStates& packet) override;

    void SendRemoveWorldStates(Player* player) override;

    void BuffTeams();

    void SetControlledState(uint32 index, TeamId teamId);

private:
    // how many towers are controlled
    TeamId EP_ControlsId[EP_TOWER_NUM];

    uint32 m_AllianceTowersControlled;
    uint32 m_HordeTowersControlled;
};

#endif
