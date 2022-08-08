#if ENGLISH
const u8 gRibbonDescriptionPart1_Champion[] = _("CHAMPION-beating, HALL");
const u8 gRibbonDescriptionPart2_Champion[] = _("OF FAME Member RIBBON");
const u8 gRibbonDescriptionPart1_CoolContest[] = _("COOL CONTEST");
const u8 gRibbonDescriptionPart1_BeautyContest[] = _("BEAUTY CONTEST");
const u8 gRibbonDescriptionPart1_CuteContest[] = _("CUTE CONTEST");
const u8 gRibbonDescriptionPart1_SmartContest[] = _("SMART CONTEST");
const u8 gRibbonDescriptionPart1_ToughContest[] = _("TOUGH CONTEST");
const u8 gRibbonDescriptionPart2_NormalRank[] = _("Normal Rank winner!");
const u8 gRibbonDescriptionPart2_SuperRank[] = _("Super Rank winner!");
const u8 gRibbonDescriptionPart2_HyperRank[] = _("Hyper Rank winner!");
const u8 gRibbonDescriptionPart2_MasterRank[] = _("Master Rank winner!");
const u8 gRibbonDescriptionPart1_Winning[] = _("For clearing LV50");
const u8 gRibbonDescriptionPart2_Winning[] = _("at the BATTLE TOWER.");
const u8 gRibbonDescriptionPart1_Victory[] = _("For clearing Open Level");
const u8 gRibbonDescriptionPart2_Victory[] = _("at the BATTLE TOWER.");
const u8 gRibbonDescriptionPart1_Artist[] = _("RIBBON for being chosen");
const u8 gRibbonDescriptionPart2_Artist[] = _("as a super sketch model.");
const u8 gRibbonDescriptionPart1_Effort[] = _("RIBBON awarded for");
const u8 gRibbonDescriptionPart2_Effort[] = _("being a hard worker.");
#elif FRENCH
const u8 gRibbonDescriptionPart1_Champion[] = _("RUBAN d’appartenance");
const u8 gRibbonDescriptionPart2_Champion[] = _("au PANTHEON");
const u8 gRibbonDescriptionPart1_CoolContest[] = _("CONCOURS DE SANG-FROID");
const u8 gRibbonDescriptionPart1_BeautyContest[] = _("CONCOURS DE BEAUTE");
const u8 gRibbonDescriptionPart1_CuteContest[] = _("CONCOURS DE GRACE");
const u8 gRibbonDescriptionPart1_SmartContest[] = _("CONCOURS D’INTEL.");
const u8 gRibbonDescriptionPart1_ToughContest[] = _("CONCOURS DE ROBUS.");
const u8 gRibbonDescriptionPart2_NormalRank[] = _("Gagnant catég. NORMAL!");
const u8 gRibbonDescriptionPart2_SuperRank[] = _("Gagnant catég. SUPER!");
const u8 gRibbonDescriptionPart2_HyperRank[] = _("Gagnant catég. HYPER!");
const u8 gRibbonDescriptionPart2_MasterRank[] = _("Gagnant catég. MASTER!");
const u8 gRibbonDescriptionPart1_Winning[] = _("RUBAN de victoire N.50");
const u8 gRibbonDescriptionPart2_Winning[] = _("à la TOUR DE COMBAT.");
const u8 gRibbonDescriptionPart1_Victory[] = _("RUBAN de Niveau libre");
const u8 gRibbonDescriptionPart2_Victory[] = _("à la TOUR DE COMBAT.");
const u8 gRibbonDescriptionPart1_Artist[] = _("RUBAN pour les modèles");
const u8 gRibbonDescriptionPart2_Artist[] = _("exposés au musée.");
const u8 gRibbonDescriptionPart1_Effort[] = _("RUBAN pour récompenser");
const u8 gRibbonDescriptionPart2_Effort[] = _("un dur travail.");
#endif

const u8 *const gRibbonDescriptionPointers[][2] =
{
    [CHAMPION_RIBBON]      = {gRibbonDescriptionPart1_Champion,      gRibbonDescriptionPart2_Champion},
    [COOL_RIBBON_NORMAL]   = {gRibbonDescriptionPart1_CoolContest,   gRibbonDescriptionPart2_NormalRank},
    [COOL_RIBBON_SUPER]    = {gRibbonDescriptionPart1_CoolContest,   gRibbonDescriptionPart2_SuperRank},
    [COOL_RIBBON_HYPER]    = {gRibbonDescriptionPart1_CoolContest,   gRibbonDescriptionPart2_HyperRank},
    [COOL_RIBBON_MASTER]   = {gRibbonDescriptionPart1_CoolContest,   gRibbonDescriptionPart2_MasterRank},
    [BEAUTY_RIBBON_NORMAL] = {gRibbonDescriptionPart1_BeautyContest, gRibbonDescriptionPart2_NormalRank},
    [BEAUTY_RIBBON_SUPER]  = {gRibbonDescriptionPart1_BeautyContest, gRibbonDescriptionPart2_SuperRank},
    [BEAUTY_RIBBON_HYPER]  = {gRibbonDescriptionPart1_BeautyContest, gRibbonDescriptionPart2_HyperRank},
    [BEAUTY_RIBBON_MASTER] = {gRibbonDescriptionPart1_BeautyContest, gRibbonDescriptionPart2_MasterRank},
    [CUTE_RIBBON_NORMAL]   = {gRibbonDescriptionPart1_CuteContest,   gRibbonDescriptionPart2_NormalRank},
    [CUTE_RIBBON_SUPER]    = {gRibbonDescriptionPart1_CuteContest,   gRibbonDescriptionPart2_SuperRank},
    [CUTE_RIBBON_HYPER]    = {gRibbonDescriptionPart1_CuteContest,   gRibbonDescriptionPart2_HyperRank},
    [CUTE_RIBBON_MASTER]   = {gRibbonDescriptionPart1_CuteContest,   gRibbonDescriptionPart2_MasterRank},
    [SMART_RIBBON_NORMAL]  = {gRibbonDescriptionPart1_SmartContest,  gRibbonDescriptionPart2_NormalRank},
    [SMART_RIBBON_SUPER]   = {gRibbonDescriptionPart1_SmartContest,  gRibbonDescriptionPart2_SuperRank},
    [SMART_RIBBON_HYPER]   = {gRibbonDescriptionPart1_SmartContest,  gRibbonDescriptionPart2_HyperRank},
    [SMART_RIBBON_MASTER]  = {gRibbonDescriptionPart1_SmartContest,  gRibbonDescriptionPart2_MasterRank},
    [TOUGH_RIBBON_NORMAL]  = {gRibbonDescriptionPart1_ToughContest,  gRibbonDescriptionPart2_NormalRank},
    [TOUGH_RIBBON_SUPER]   = {gRibbonDescriptionPart1_ToughContest,  gRibbonDescriptionPart2_SuperRank},
    [TOUGH_RIBBON_HYPER]   = {gRibbonDescriptionPart1_ToughContest,  gRibbonDescriptionPart2_HyperRank},
    [TOUGH_RIBBON_MASTER]  = {gRibbonDescriptionPart1_ToughContest,  gRibbonDescriptionPart2_MasterRank},
    [WINNING_RIBBON]       = {gRibbonDescriptionPart1_Winning,       gRibbonDescriptionPart2_Winning},
    [VICTORY_RIBBON]       = {gRibbonDescriptionPart1_Victory,       gRibbonDescriptionPart2_Victory},
    [ARTIST_RIBBON]        = {gRibbonDescriptionPart1_Artist,        gRibbonDescriptionPart2_Artist},
    [EFFORT_RIBBON]        = {gRibbonDescriptionPart1_Effort,        gRibbonDescriptionPart2_Effort},
};
