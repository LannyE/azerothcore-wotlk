#include "bot_ai.h"
#include "bpet_ai.h"
#include "Creature.h"
#include "ScriptMgr.h"
#include "SpellAuras.h"
#include "SpellInfo.h"
/*
Dreadlord NpcBot Pets (by Trickerer onlysuffering@gmail.com)
Complete - 100%
TODO:
*/

enum DreadlordPetBaseSpells
{
};

enum DreadlordPetPassives
{
};

enum DreadlordPetSpecial
{
    IMMOLATION_DAMAGE       = 35959,

    INFERNAL_DURATION       = 180000 //3 min
};

class dreadlord_pet_bot : public CreatureScript
{
public:
    dreadlord_pet_bot() : CreatureScript("dreadlord_pet_bot") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new dreadlord_botpetAI(creature);
    }

    struct dreadlord_botpetAI : public bot_pet_ai
    {
        dreadlord_botpetAI(Creature* creature) : bot_pet_ai(creature) { }

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

        void DoPetActions(uint32 /*diff*/)
        {
        }

        void UpdateAI(uint32 diff) override
        {
            if ((liveTimer += diff) >= INFERNAL_DURATION * (IAmFree() ? 20u : 1u) - 2000u)
            {
                canUpdate = false;
                me->setDeathState(DeathState::JustDied);
                return;
            }

            if (!GlobalUpdate(diff))
                return;

            if (!me->IsInCombat())
                DoNonCombatActions(diff);

            //CheckDrainMana(diff);

            if (!CheckAttackTarget())
                return;

            if (IsCasting())
                return;

            DoPetAttack(diff);
        }

        void DoPetAttack(uint32 /*diff*/)
        {
            StartAttack(opponent, IsPetMelee());
        }

        void ApplyClassDamageMultiplierSpell(int32& damage, SpellNonMeleeDamage& /*damageinfo*/, SpellInfo const* spellInfo, WeaponAttackType /*attackType*/, bool /*iscrit*/) const override
        {
            uint32 baseId = spellInfo->GetFirstRankSpell()->Id;
            float fdamage = float(damage);

            float pctbonus = 1.0f;
            pctbonus *= 0.5f;

            if (baseId == IMMOLATION_DAMAGE)
                fdamage += me->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_MAGIC) * me->CalculateDefaultCoefficient(spellInfo, SPELL_DIRECT_DAMAGE) * me->CalculateLevelPenalty(spellInfo);

            damage = int32(fdamage * pctbonus);
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

        void Reset() override
        {
            liveTimer = 0;
        }

        void InitPetSpells() override
        {
        }

        void ApplyPetPassives() const override
        {
        }

    private:
        uint32 liveTimer;
    };
};

void AddSC_dreadlord_bot_pets()
{
    new dreadlord_pet_bot();
}
