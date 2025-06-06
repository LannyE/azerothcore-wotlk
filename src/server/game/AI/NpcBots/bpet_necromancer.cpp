#include "bot_ai.h"
#include "bpet_ai.h"
#include "Player.h"
#include "ScriptMgr.h"
/*
Necromancer NpcBot Pets (by Trickerer onlysuffering@gmail.com)
Notes:
Extra abilities. For the sake of defending the owner added Taunt. For self defense added Blocking (block value unchanged)
Both abilities are one-time use
Complete - 100%
TODO:
*/

enum NecromancerPetBaseSpells
{
    BLOCKING_1                          = 3248,
    TAUNT_1                             = 37548
};
enum NecromancerPetPassives
{
};
enum NecromancerPetSpecial
{
    THREAT_BASE                         = 5,
    MINION_DURATION                     = 65000
};

class necromancer_pet_bot : public CreatureScript
{
public:
    necromancer_pet_bot() : CreatureScript("necromancer_pet_bot") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new necromancer_botpetAI(creature);
    }

    struct necromancer_botpetAI : public bot_pet_ai
    {
        necromancer_botpetAI(Creature* creature) : bot_pet_ai(creature) { }

        void JustEngagedWith(Unit* u) override { bot_pet_ai::JustEngagedWith(u); }
        void KilledUnit(Unit* u) override { bot_pet_ai::KilledUnit(u); }
        void EnterEvadeMode(EvadeReason why = EVADE_REASON_OTHER) override { bot_pet_ai::EnterEvadeMode(why); }
        void MoveInLineOfSight(Unit* u) override { bot_pet_ai::MoveInLineOfSight(u); }
        void JustDied(Unit* u) override { bot_pet_ai::JustDied(u); }
        void DoNonCombatActions(uint32 /*diff*/) { }

        void StartAttack(Unit* u, bool force = false)
        {
            if (!bot_pet_ai::StartAttack(u, force))
                return;
            GetInPosition(force, u);
        }

        void UpdateAI(uint32 diff) override
        {
            if ((liveTimer += diff) >= _getMaxDuration())
            {
                canUpdate = false;
                me->setDeathState(DeathState::JustDied);
                return;
            }

            if (!GlobalUpdate(diff))
                return;

            if (!me->IsInCombat())
                DoNonCombatActions(diff);

            if (!CheckAttackTarget())
                return;

            if (IsCasting())
                return;

            DoPetAttack(diff);
        }

        void DoPetAttack(uint32 diff)
        {
            StartAttack(opponent, IsPetMelee());

            if (IsSpellReady(TAUNT_1, diff, false) && Rand() < 50 &&
                ((opponent->GetVictim() == petOwner && !IsTank(petOwner)) ||
                (opponent->GetVictim() == petOwner->GetBotOwner() && !IsTank(petOwner->GetBotOwner()))) &&
                !opponent->HasAuraType(SPELL_AURA_MOD_TAUNT) && me->IsWithinMeleeRange(opponent))
            {
                me->CastSpell(opponent, GetSpell(TAUNT_1), false);
                SetSpellCooldown(TAUNT_1, std::numeric_limits<uint32>::max());
                return;
            }

            if (IsSpellReady(BLOCKING_1, diff) && !me->getAttackers().empty() && Rand() < 25)
            {
                me->CastSpell(me, GetSpell(BLOCKING_1), true);
                SetSpellCooldown(BLOCKING_1, std::numeric_limits<uint32>::max());
                return;
            }
        }

        void OnPetClassSpellGo(SpellInfo const* /*spellInfo*/) override
        {
        }

        void SpellHit(Unit* wcaster, SpellInfo const* spell) override
        {
            Unit* caster = wcaster->ToUnit();
            if (!caster)
                return;

            OnSpellHit(caster, spell);
        }

        void SpellHitTarget(Unit* /*wtarget*/, SpellInfo const* /*spell*/) override
        {
        }

        void DamageDealt(Unit* victim, uint32& damage, DamageEffectType damageType, SpellSchoolMask damageSchoolMask) override
        {
            bot_pet_ai::DamageDealt(victim, damage, damageType, damageSchoolMask);
        }

        void DamageTaken(Unit* u, uint32& /*damage*/, DamageEffectType /*damageType*/, SpellSchoolMask /*schoolMask*/) override
        {
            if (!u)
                return;
            if (!u->IsInCombat() && !me->IsInCombat())
                return;
            OnOwnerDamagedBy(u);
        }

        void OwnerAttackedBy(Unit* u) override
        {
            if (!u)
                return;
            OnOwnerDamagedBy(u);
        }

        uint32 GetData(uint32 data) const override
        {
            switch (data)
            {
                case BOTPETAI_MISC_DURATION:
                    return liveTimer;
                case BOTPETAI_MISC_DURATION_MAX:
                    return _getMaxDuration();
                case BOTPETAI_MISC_MAXLEVEL:
                    return maxlevel;
                default:
                    return bot_pet_ai::GetData(data);
            }
        }

        void SetData(uint32 data, uint32 value) override
        {
            switch (data)
            {
                case BOTPETAI_MISC_MAXLEVEL:
                    maxlevel = uint8(value);
                    SetPetStats(true);
                    break;
                default:
                    break;
            }
        }

        void Reset() override
        {
            liveTimer = 0;
            maxlevel = 1;
        }

        void InitPetSpells() override
        {
            InitSpellMap(TAUNT_1, true, false);
            InitSpellMap(BLOCKING_1, true, false);
        }

        void ApplyPetPassives() const override
        {
        }

    private:
        uint32 _getMaxDuration() const
        {
            return MINION_DURATION * (IAmFree() ? 5u : 1u);
        }

        uint32 liveTimer;
        uint8 maxlevel;
    };
};

void AddSC_necromancer_bot_pets()
{
    new necromancer_pet_bot();
}
