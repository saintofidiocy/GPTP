#include <SCBW/api.h>
#include <DatExtend/datext.h>


// Macros for actual instance declarations
#define SCBW_DATA_VAR(type, name, offset)  type name = (type)offset;
#define SCBW_DATA_DEF(type, name, var)     type& name = (type&)var;

// The header file rudely undefines this
#define SCBW_DATA(type, name, offset)  type const name = (type)offset;

// Pointers to default data
_uavail UnitAvailability_dat = { (u8*)(0x0057F27C + 228 * 0), (u8*)(0x0057F27C + 228 * 1), (u8*)(0x0057F27C + 228 * 2), (u8*)(0x0057F27C + 228 * 3),
                                  (u8*)(0x0057F27C + 228 * 4), (u8*)(0x0057F27C + 228 * 5), (u8*)(0x0057F27C + 228 * 6), (u8*)(0x0057F27C + 228 * 7),
                                  (u8*)(0x0057F27C + 228 * 8), (u8*)(0x0057F27C + 228 * 9), (u8*)(0x0057F27C + 228 * 10), (u8*)(0x0057F27C + 228 * 11) };

ImagesDatExtraOverlayLO_Files lo_files_dat = { (LO_Header**)0x0051F2A8, (LO_Header**)0x00520244, (LO_Header**)0x005211E0, (LO_Header**)0x0052217C, (LO_Header**)0x00523118 };

_bwTechs TechBw_dat = { { (u8*)(0x0058F050 + 20 * 0),(u8*)(0x0058F050 + 20 * 1),(u8*)(0x0058F050 + 20 * 2),(u8*)(0x0058F050 + 20 * 3), // isEnabled
                          (u8*)(0x0058F050 + 20 * 4),(u8*)(0x0058F050 + 20 * 5),(u8*)(0x0058F050 + 20 * 6),(u8*)(0x0058F050 + 20 * 7),
                          (u8*)(0x0058F050 + 20 * 8),(u8*)(0x0058F050 + 20 * 9),(u8*)(0x0058F050 + 20 * 10),(u8*)(0x0058F050 + 20 * 11) },
                        { (u8*)(0x0058F140 + 20 * 0),(u8*)(0x0058F140 + 20 * 1),(u8*)(0x0058F140 + 20 * 2),(u8*)(0x0058F140 + 20 * 3), // isResearched
                          (u8*)(0x0058F140 + 20 * 4),(u8*)(0x0058F140 + 20 * 5),(u8*)(0x0058F140 + 20 * 6),(u8*)(0x0058F140 + 20 * 7),
                          (u8*)(0x0058F140 + 20 * 8),(u8*)(0x0058F140 + 20 * 9),(u8*)(0x0058F140 + 20 * 10),(u8*)(0x0058F140 + 20 * 11) } };

_bwUpgrs UpgradesBw_dat = { { (u8*)(0x0058F278 + 20 * 0),(u8*)(0x0058F278 + 20 * 1),(u8*)(0x0058F278 + 20 * 2),(u8*)(0x0058F278 + 20 * 3), // maxLevel
                              (u8*)(0x0058F278 + 20 * 4),(u8*)(0x0058F278 + 20 * 5),(u8*)(0x0058F278 + 20 * 6),(u8*)(0x0058F278 + 20 * 7),
                              (u8*)(0x0058F278 + 20 * 8),(u8*)(0x0058F278 + 20 * 9),(u8*)(0x0058F278 + 20 * 10),(u8*)(0x0058F278 + 20 * 11) },
                            { (u8*)(0x0058F32C + 20 * 0),(u8*)(0x0058F32C + 20 * 1),(u8*)(0x0058F32C + 20 * 2),(u8*)(0x0058F32C + 20 * 3), // currentLevel
                              (u8*)(0x0058F32C + 20 * 4),(u8*)(0x0058F32C + 20 * 5),(u8*)(0x0058F32C + 20 * 6),(u8*)(0x0058F32C + 20 * 7),
                              (u8*)(0x0058F32C + 20 * 8),(u8*)(0x0058F32C + 20 * 9),(u8*)(0x0058F32C + 20 * 10),(u8*)(0x0058F32C + 20 * 11) } };


// Referenced variables modified by DatExt
SCBW_DATA_VAR(UNITDEATHS*, deathTable_var, 0x0058A364);
SCBW_DATA_VAR(UNITDEATHS*, unitAllCountTable_var, 0x00582324);
SCBW_DATA_VAR(UNITDEATHS*, unitCompleteTable_var, 0x00584DE4);
SCBW_DATA_VAR(UNITDEATHS*, unitKilledTable_var, 0x005878A4);
SCBW_DATA_VAR(BUTTON_SET*, buttonSetTable_var, 0x005187E8);
SCBW_DATA_VAR(UnitStatFuncArrayEntry*, unitStatFuncs_var, 0x005193A0);
SCBW_DATA_VAR(const LO_Header* const*, shieldOverlays_var, 0x0052E5C8);
SCBW_DATA_VAR(u8*, damageOverlayFrame_var, 0x005240D0);
SCBW_DATA_VAR(GrpHead* const*, imageGrpGraphics_var, 0x0051CED0);
SCBW_DATA_VAR(AI_Main*, AIScriptController_var, 0x0068FEE8); // @TODO:
SCBW_DATA_VAR(u32*, aiStrength_var, 0x006BB210);

// scbwdata expects pointer references, so make struct pointers to reference
SCBW_DATA_VAR(_uavail*, UnitAvailability_var, &UnitAvailability_var);
SCBW_DATA_VAR(ImagesDatExtraOverlayLO_Files*, lo_files_var, &lo_files_var);
SCBW_DATA_VAR(_bwTechs*, TechBw_var, &TechBw_var);
SCBW_DATA_VAR(_bwUpgrs*, UpgradesBw_var, &UpgradesBw_var);


// Define the extern variables
SCBW_DATA_DEF(UNITDEATHS*, deathTable, deathTable_var);
SCBW_DATA_DEF(UNITDEATHS*, unitAllCountTable, unitAllCountTable_var);
SCBW_DATA_DEF(UNITDEATHS*, unitCompleteTable, unitCompleteTable_var);
SCBW_DATA_DEF(UNITDEATHS*, unitKilledTable, unitKilledTable_var);
SCBW_DATA_DEF(BUTTON_SET*, buttonSetTable, buttonSetTable_var);
SCBW_DATA_DEF(UnitStatFuncArrayEntry*, unitStatFuncs, unitStatFuncs_var);
SCBW_DATA_DEF(const LO_Header* const*, shieldOverlays, shieldOverlays_var);
SCBW_DATA_DEF(u8*, damageOverlayFrame, damageOverlayFrame_var);
SCBW_DATA_DEF(GrpHead* const*, imageGrpGraphics, imageGrpGraphics_var);
SCBW_DATA_DEF(AI_Main*, AIScriptController, AIScriptController_var);
SCBW_DATA_DEF(u32*, aiStrength, aiStrength_var);

SCBW_DATA_DEF(_uavail*, UnitAvailability, UnitAvailability_var);
SCBW_DATA_DEF(ImagesDatExtraOverlayLO_Files*, lo_files, lo_files_var);
SCBW_DATA_DEF(_bwTechs*, TechBw, TechBw_var);
SCBW_DATA_DEF(_bwUpgrs*, UpgradesBw, UpgradesBw_var);

namespace units_dat {
SCBW_DATA(const DatLoad*, unitsDat, 0x00513C30);

SCBW_DATA_DEF(u16*,		Graphic,				unitsDat[0].address);	//006644F8 -- DatExt changes this to u16 from u8
SCBW_DATA_DEF(u16*,		SubUnit,				unitsDat[1].address);	//006607C0
//SCBW_DATA_DEF(u16*,	???,					unitsDat[2].address);	//00660C38 //Subunit 2 according to EUDDB
SCBW_DATA_DEF(u16*,		InfestedUnitPartial,	unitsDat[3].address);	//00664980, (Id - UnitId::TerranCommandCenter) for it to work, last valid id is UnitId::Special_OvermindCocoon
SCBW_DATA_DEF(u32*,		ConstructionGraphic,	unitsDat[4].address);	//006610B0
SCBW_DATA_DEF(u8*,		StartDirection,			unitsDat[5].address);	//006605F0  Direction unit will face after it is created. From 0 (top) to 31 (before top turning clockwise).32 means random.
SCBW_DATA_DEF(u8*,		ShieldsEnabled,			unitsDat[6].address);	//006647B0
SCBW_DATA_DEF(u16*,		MaxShieldPoints,		unitsDat[7].address);	//00660E00
SCBW_DATA_DEF(s32*,		MaxHitPoints,			unitsDat[8].address);	//00662350
SCBW_DATA_DEF(u8*,		Elevation,				unitsDat[9].address);	//00663150
SCBW_DATA_DEF(u8*,		MovementFlags,			unitsDat[10].address);	//00660FC8
SCBW_DATA_DEF(u8*,		Rank,					unitsDat[11].address);	//00663DD0
SCBW_DATA_DEF(u8*,		ComputerIdleOrder,		unitsDat[12].address);	//00662EA0
SCBW_DATA_DEF(u8*,		HumanIdleOrder,			unitsDat[13].address);	//00662268
SCBW_DATA_DEF(u8*,		ReturnToIdleOrder,		unitsDat[14].address);	//00664898
SCBW_DATA_DEF(u8*,		AttackUnitOrder,		unitsDat[15].address);	//00663320
SCBW_DATA_DEF(u8*,		AttackMoveOrder,		unitsDat[16].address);	//00663A50
SCBW_DATA_DEF(u8*,		GroundWeapon,			unitsDat[17].address);	//006636B8
SCBW_DATA_DEF(u8*,		MaxGroundHits,			unitsDat[18].address);	//006645E0
SCBW_DATA_DEF(u8*,		AirWeapon,				unitsDat[19].address);	//006616E0
SCBW_DATA_DEF(u8*,		MaxAirHits,				unitsDat[20].address);	//0065FC18
//SCBW_DATA_DEF(u8*,	???,					unitsDat[21].address);	//00660178 //"Computer AI Unit Type" according to EUDDB
SCBW_DATA_DEF(u32*,		BaseProperty,			unitsDat[22].address);  //00664080 AKA SpecialAbilityFlags, UnitProperty, etc. Use with UnitProperty::Enum.
SCBW_DATA_DEF(u8*,		SeekRange,				unitsDat[23].address);  //00662DB8 AKA Target Acquisition Range, Acquire Target Range, etc.
SCBW_DATA_DEF(u8*,		SightRange,				unitsDat[24].address);	//00663238
SCBW_DATA_DEF(u8*,		ArmorUpgrade,			unitsDat[25].address);	//006635D0
SCBW_DATA_DEF(u8*,		SizeType,				unitsDat[26].address);	//00662180
SCBW_DATA_DEF(u8*,		ArmorAmount,			unitsDat[27].address);	//0065FEC8
SCBW_DATA_DEF(u8*,		RightClickAction,		unitsDat[28].address);	//00662098
SCBW_DATA_DEF(u16*,		SoundReady,				unitsDat[29].address);	//00661FC0
SCBW_DATA_DEF(u16*,		SoundWhatFirst,			unitsDat[30].address);	//0065FFB0
SCBW_DATA_DEF(u16*,		SoundWhatLast,			unitsDat[31].address);	//00662BF0
SCBW_DATA_DEF(u16*,		SoundAnnoyedFirst,		unitsDat[32].address);	//00663B38
SCBW_DATA_DEF(u16*,		SoundAnnoyedLast,		unitsDat[33].address);	//00661EE8
SCBW_DATA_DEF(u16*,		SoundYesFirst,			unitsDat[34].address);	//00663C10
SCBW_DATA_DEF(u16*,		SoundYesLast,			unitsDat[35].address);	//00661440
SCBW_DATA_DEF(Point16*,	BuildingDimensions,		unitsDat[36].address);	//00662860
SCBW_DATA_DEF(Point16*,	AddonPlacement,			unitsDat[37].address);	//006626E0
SCBW_DATA_DEF(Box16*,	UnitBounds,				unitsDat[38].address);	//006617C8
SCBW_DATA_DEF(u16*,		PortraitId,				unitsDat[39].address);	//00662F88
SCBW_DATA_DEF(u16*,		MineralCost,			unitsDat[40].address);	//00663888
SCBW_DATA_DEF(u16*,		GasCost,				unitsDat[41].address);	//0065FD00
SCBW_DATA_DEF(u16*,		TimeCost,				unitsDat[42].address);	//00660428
SCBW_DATA_DEF(u16*,		unitsDat43,				unitsDat[43].address);	//00660A70 //"Restriction Address" according to EUDDB
SCBW_DATA_DEF(GroupFlag*, GroupFlags,			unitsDat[44].address);	//006637A0
SCBW_DATA_DEF(u8*,		SupplyProvided,			unitsDat[45].address);  //006646C8 Supply shown in-game is (true supply) / 2; e.g. Zerglings have 1 true supply, Marines have 2 true supply, etc.
SCBW_DATA_DEF(u8*,		SupplyRequired,			unitsDat[46].address);  //00663CE8 Supply shown in-game is (true supply) / 2; e.g. Zerglings have 1 true supply, Marines have 2 true supply, etc.
SCBW_DATA_DEF(u8*,		SpaceRequired,			unitsDat[47].address);	//00664410
SCBW_DATA_DEF(u8*,		SpaceProvided,			unitsDat[48].address);	//00660988
SCBW_DATA_DEF(u16*,		BuildScore,				unitsDat[49].address);	//00663408
SCBW_DATA_DEF(u16*,		DestroyScore,			unitsDat[50].address);	//00663EB8
SCBW_DATA_DEF(u16*,		MapStringId,			unitsDat[51].address);	//00660260
SCBW_DATA_DEF(u8*,		BroodwarOnly,			unitsDat[52].address);	//006606D8
//SCBW_DATA_DEF(u16*, ???,						unitsDat[53].address);	//00661518 //"Staredit Availability Flags" according to EUDDB
} //units_dat (last entry at 0x00513EAC)

namespace flingy_dat {
SCBW_DATA(const DatLoad*, flingyDat, 0x00515A38);

SCBW_DATA_DEF(u16*, SpriteID,           flingyDat[0].address);	//006CA318
SCBW_DATA_DEF(u32*, TopSpeed,           flingyDat[1].address);	//006C9EF8
SCBW_DATA_DEF(u16*, Acceleration,       flingyDat[2].address);	//006C9C78
SCBW_DATA_DEF(u32*, HaltDistance,       flingyDat[3].address);	//006C9930
SCBW_DATA_DEF(u8*,  TurnSpeed,          flingyDat[4].address);	//006C9E20 Incorrectly known as "Turn Radius"
//SCBW_DATA_DEF(u8*, ???,				flingyDat[5].address);	//006CA240
SCBW_DATA_DEF(u8*,  MovementControl,    flingyDat[6].address);	//006C9858
} //flingy_dat (last entry at 0x00515A80)

namespace weapons_dat {
SCBW_DATA(const DatLoad*, weaponsDat, 0x00513868);

SCBW_DATA_DEF(u16*, Label,              weaponsDat[0].address); //006572E0
SCBW_DATA_DEF(u32*, FlingyId,           weaponsDat[1].address); //00656CA8
//SCBW_DATA_DEF(u8*, ???,				weaponsDat[2].address); //006573E8 //"Special Attack" according to EUDDB
SCBW_DATA_DEF(TargetFlag*, TargetFlags, weaponsDat[3].address); //00657998
SCBW_DATA_DEF(u32*, MinRange,           weaponsDat[4].address); //00656A18
SCBW_DATA_DEF(u32*, MaxRange,           weaponsDat[5].address); //00657470
SCBW_DATA_DEF(u8*,  DamageUpgrade,      weaponsDat[6].address); //006571D0
SCBW_DATA_DEF(u8*,  DamageType,         weaponsDat[7].address); //00657258 Normal, Explosive, etc.. Use with DamageType::Enum.
SCBW_DATA_DEF(u8*,  Behavior,           weaponsDat[8].address); //00656670 Fly and follow target, appear on target unit, etc. Use with WeaponBehavior::Enum.
SCBW_DATA_DEF(u8*,  RemoveAfter,        weaponsDat[9].address); //00657040
SCBW_DATA_DEF(u8*,  ExplosionType,      weaponsDat[10].address);//006566F8 NormalHit, RadialSplash, EnemySplash, etc. Use with WeaponEffect::Enum.
SCBW_DATA_DEF(u16*, InnerSplashRadius,  weaponsDat[11].address);//00656888
SCBW_DATA_DEF(u16*, MediumSplashRadius, weaponsDat[12].address);//006570C8
SCBW_DATA_DEF(u16*, OuterSplashRadius,  weaponsDat[13].address);//00657780
SCBW_DATA_DEF(u16*, DamageAmount,       weaponsDat[14].address);//00656EB0
SCBW_DATA_DEF(u16*, DamageBonus,        weaponsDat[15].address);//00657678
SCBW_DATA_DEF(u8*,  Cooldown,           weaponsDat[16].address);//00656FB8
SCBW_DATA_DEF(u8*,  DamageFactor,       weaponsDat[17].address);//006564E0
SCBW_DATA_DEF(u8*,  AttackAngle,        weaponsDat[18].address);//00656990
SCBW_DATA_DEF(u8*,  LaunchSpin,         weaponsDat[19].address);//00657888
SCBW_DATA_DEF(u8*,  ForwardOffset,      weaponsDat[20].address);//00657910
SCBW_DATA_DEF(u8*,  VerticalOffset,     weaponsDat[21].address);//00656C20
//SCBW_DATA_DEF(u16*, ???,				weaponsDat[22].address);//00656568 //Target Error Message according to EUDDB
SCBW_DATA_DEF(u16*, WeaponIconId,		weaponsDat[23].address);//00656780
} //weapons_dat (last entry at 0x0051397C)

namespace upgrades_dat {
SCBW_DATA(const DatLoad*, upgradesDat, 0x005136E0);

SCBW_DATA_DEF(u16*, MineralCostBase,    upgradesDat[0].address);	//00656740
SCBW_DATA_DEF(u16*, MineralCostFactor,  upgradesDat[1].address);	//006559C0
SCBW_DATA_DEF(u16*, GasCostBase,        upgradesDat[2].address);	//00655840
SCBW_DATA_DEF(u16*, GasCostFactor,      upgradesDat[3].address);	//006557C0
SCBW_DATA_DEF(u16*, TimeCostBase,       upgradesDat[4].address);	//00655B80
SCBW_DATA_DEF(u16*, TimeCostFactor,     upgradesDat[5].address);	//00655940
//SCBW_DATA_DEF(u16*, ???,              upgradesDat[6].address);	//006558C0	//Restriction Flags according to EUDDB
SCBW_DATA_DEF(u16*, IconId,             upgradesDat[7].address);	//00655AC0	//"Icon, cmdicons.grp frame" according to EUDDB
SCBW_DATA_DEF(u16*, Label,              upgradesDat[8].address);	//00655A40
SCBW_DATA_DEF(u8*,  Race,               upgradesDat[9].address);	//00655BFC
SCBW_DATA_DEF(u8*,  MaxRepeats,         upgradesDat[10].address);	//00655700
//SCBW_DATA_DEF(u8*, ???,				upgradesDat[11].address);	//00655B3C	//Brood War Flag according to EUDDB
} //upgrades_dat (last entry at 0x00513764)

namespace techdata_dat {
SCBW_DATA(const DatLoad*, techdataDat, 0x005137D8);

SCBW_DATA_DEF(u16*, MineralCost,        techdataDat[0].address);	//00656248
SCBW_DATA_DEF(u16*, GasCost,            techdataDat[1].address);	//006561F0
SCBW_DATA_DEF(u16*, TimeCost,           techdataDat[2].address);	//006563D8
SCBW_DATA_DEF(u16*, EnergyCost,         techdataDat[3].address);	//00656380
//SCBW_DATA_DEF(u16*, ???,				techdataDat[4].address);	//00656198
//SCBW_DATA_DEF(u16*, ???,				techdataDat[5].address);	//006562F8	//Restriction Flags according to EUDDB
SCBW_DATA_DEF(u16*, IconId,				techdataDat[6].address);	//00656430	//"Icon, cmdicons.grp frame" according to EUDDB
SCBW_DATA_DEF(u16*, Label,              techdataDat[7].address);	//006562A0
//SCBW_DATA_DEF(u8*, ???,				techdataDat[8].address);	//00656488	//Race according to EUDDB
//SCBW_DATA_DEF(u8*, ???,				techdataDat[9].address);	//00656350	//"Researched" according to EUDDB
//SCBW_DATA_DEF(u8*, ???,				techdataDat[10].address);	//006564B4	//Brood War Flag according to EUDDB
} //techdata_dat (last entry at 0x00513850)

namespace orders_dat {
SCBW_DATA(const DatLoad*, ordersDat, 0x00513EC8);

SCBW_DATA_DEF(u16*,		Label,              ordersDat[0].address);	//00665280
SCBW_DATA_DEF(u8*,		UseWeaponTargeting, ordersDat[1].address);	//00664B00
//SCBW_DATA_DEF(u8*,	???,				ordersDat[2].address);	//00665940 //May be "secondary order" used for debug/assert only / "Order goes in bSecondaryOrderID instead of bMainOrderID." according to EUDDB
//SCBW_DATA_DEF(u8*,	???,				ordersDat[3].address);	//00665A00 //May be "Non-subunit" used for debug only
//SCBW_DATA_DEF(u8*,	???,				ordersDat[4].address);	//00664A40
//SCBW_DATA_DEF(u8*,	???,				ordersDat[5].address);	//006657C0 //May be "Subunit can use" used for debug only
SCBW_DATA_DEF(Bool8*,	CanBeInterrupted,	ordersDat[6].address);	//00665040
//SCBW_DATA_DEF(u8*,	???,				ordersDat[7].address);	//00665100
SCBW_DATA_DEF(Bool8*,	CanBeQueued,		ordersDat[8].address);	//00665700
//SCBW_DATA_DEF(u8*,	???,				ordersDat[9].address);	//006651C0
SCBW_DATA_DEF(u8*,		CanBeObstructed,	ordersDat[10].address);	//006654C0 //"Can Be Obstructed?" according to EUDDB
//SCBW_DATA_DEF(u8*,	???,				ordersDat[11].address);	//00664C80
//SCBW_DATA_DEF(u8*,	???,				ordersDat[12].address);	//00664BC0 //May be "Order requires moving"
SCBW_DATA_DEF(u8*,		OrderWeaponId,		ordersDat[13].address);	//00665880
SCBW_DATA_DEF(u8*,		TechUsed,           ordersDat[14].address);	//00664E00
SCBW_DATA_DEF(u8*,		OrderIscriptAnim,	ordersDat[15].address);	//00664D40 //Animation (IscriptAnimation) according to EUDDB
SCBW_DATA_DEF(s16*,		ButtonIcon,			ordersDat[16].address);	//00664EC0
SCBW_DATA_DEF(u16*,		RequirementsOffset,	ordersDat[17].address);	//00665580 //based on context
SCBW_DATA_DEF(u8*,		ObscuredOrder,		ordersDat[18].address);	//00665400
} //orders_dat (last entry at 0x00513FA0)

namespace sprites_dat {
SCBW_DATA(const DatLoad*, spritesDat, 0x00513FB8);

SCBW_DATA_DEF(u16*, ImageId,            spritesDat[0].address);		//00666160
SCBW_DATA_DEF(s8*,  HpBarSize,          spritesDat[1].address);		//00665E50
//SCBW_DATA_DEF(s8*,  ???,				spritesDat[2].address);		//00666570
SCBW_DATA_DEF(u8*,  IsVisible,          spritesDat[3].address);		//00665C48
//SCBW_DATA_DEF(s8*,  ???,				spritesDat[4].address);		//00665AC0 //"Selection Circle" according to EUDDB, not starting at 0
//SCBW_DATA_DEF(s8*,  ???,				spritesDat[5].address);		//00665FD8 //"Selection Vertical Offset" according to EUDDB
} //sprites_dat (last entry at 0x00513FF4)

namespace images_dat {
SCBW_DATA(const DatLoad*, imagesDat, 0x00514010);

//SCBW_DATA_DEF(const u32*,  ???,		imagesDat[0].address);	//00668AA0 //"GRP File" according to EUDDB
SCBW_DATA_DEF(const u8*,  IsTurnable,   imagesDat[1].address);	//0066E860
SCBW_DATA_DEF(const u8*,  IsClickable,  imagesDat[2].address);	//0066C150
//SCBW_DATA_DEF(const u8*,  ???,		imagesDat[3].address);	//0066D4D8 //"Use Full Iscript" according to EUDDB
//SCBW_DATA_DEF(const u8*,  ???,		imagesDat[4].address);	//00667718 //"Draw If Cloaked" according to EUDDB
SCBW_DATA_DEF(const u8*,  RLE_Function, imagesDat[5].address);	//00669E28
SCBW_DATA_DEF(const u8*,  Remapping,    imagesDat[6].address);	//00669A40
//SCBW_DATA_DEF(const u32*,  ???,		imagesDat[7].address);	//0066EC48 //"Iscript ID" according to EUDDB
//SCBW_DATA_DEF(const u32*,  ???,		imagesDat[8].address);	//0066C538 //"Shields Overlay" according to EUDDB
//SCBW_DATA_DEF(const u32*,  ???,		imagesDat[9].address);	//0066B1B0 //"Attack Overlay" according to EUDDB
//SCBW_DATA_DEF(const u32*,  ???,		imagesDat[10].address);	//0066A210 //"Damage Overlay" according to EUDDB
//SCBW_DATA_DEF(const u32*,  ???,		imagesDat[11].address);	//00667B00 //"Special Overlay" according to EUDDB
//SCBW_DATA_DEF(const u32*,  ???,		imagesDat[12].address);	//00666778 //"Landing Dust Overlay" according to EUDDB
//SCBW_DATA_DEF(const u32*,  ???,		imagesDat[13].address);	//0066D8C0 //"Lift-off Dust Overlay" according to EUDDB
} //images_dat (last entry at 0x005140AC)

