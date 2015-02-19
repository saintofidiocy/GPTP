#include "spells.h"
#include <AI/ai_common.h>

//V241 for VS2008

namespace AI {

class RecallTargetFinderProc: public scbw::UnitFinderCallbackMatchInterface {

  private:
    const CUnit *caster;

  public:
    RecallTargetFinderProc(const CUnit *caster)
      : caster(caster) {}

	bool match(const CUnit *target) {

		if (target->playerId != caster->playerId)
		  return false;

		if (!target->orderTarget.unit)
		  return false;

		if (target->id == UnitId::carrier
			|| target->id == UnitId::gantrithor
			|| target->id == UnitId::reaver
			|| target->id == UnitId::warbringer) {
		  if (target->getCurrentShieldsInGame() <= 10)
			return true;
		}

		return false;

    }
};

CUnit* findBestRecallTarget(const CUnit *caster, bool isUnderAttack) {

  if (isUnitInUnsafeRegion(caster))
    return NULL;

  return scbw::UnitFinder::getNearestTarget(caster, RecallTargetFinderProc(caster));
}

} //AI
