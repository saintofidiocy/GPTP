#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

class RestorationTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

  private:
    const CUnit *caster;

  public:
    RestorationTargetFinderProc(const CUnit *caster)
      : caster(caster) {}

    bool match(const CUnit *target) {

		if (target->playerId != caster->playerId)
		  return false;

		if (!scbw::canWeaponTargetUnit(WeaponId::Restoration, target, caster))
		  return false;

		if (target->getCurrentLifeInGame() <= 60)
		  return false;

		if (target->ensnareTimer
			|| target->plagueTimer
			|| target->irradiateTimer
			|| target->lockdownTimer
			|| target->maelstromTimer
			|| target->acidSporeCount)
		  return true;

		return false;

    }
};

CUnit* findBestRestorationTarget(const CUnit *caster, bool isUnderAttack) {

  int bounds = 32 * 32;

  return scbw::UnitFinder::getNearestTarget(
    caster->getX() - bounds, caster->getY() - bounds,
    caster->getX() + bounds, caster->getY() + bounds,
    caster, RestorationTargetFinderProc(caster));
}

class RestorationTargetFinderProcSituational: public scbw::UnitFinderCallbackMatchInterface {

  private:
    const CUnit *caster;

  public:
    RestorationTargetFinderProcSituational(const CUnit *caster)
      : caster(caster) {}

    bool match(const CUnit *target) {

		if (target->playerId != caster->playerId)
		  return false;

		if (!(target->parasiteFlags || target->maelstromTimer))
		  return false;

		if (!scbw::canWeaponTargetUnit(WeaponId::Restoration, target, caster))
		  return false;

		return true;

    }
};


CUnit* findBestRestorationTargetSituational(const CUnit *caster, bool isUnderAttack) {

  if (isUnderAttack)
    return NULL;

  return scbw::UnitFinder::getNearestTarget(caster, RestorationTargetFinderProcSituational(caster));
}

} //AI
