#if GAME_LANGUAGE == LANGUAGE_SPANISH
static const u8 sHardyNatureName[]   = _("Fuerte");
static const u8 sLonelyNatureName[]  = _("Huraña");
static const u8 sBraveNatureName[]   = _("Audaz");
static const u8 sAdamantNatureName[] = _("Firme");
static const u8 sNaughtyNatureName[] = _("Pícara");
static const u8 sBoldNatureName[]    = _("Osada");
static const u8 sDocileNatureName[]  = _("Dócil");
static const u8 sRelaxedNatureName[] = _("Plácida");
static const u8 sImpishNatureName[]  = _("Agitada");
static const u8 sLaxNatureName[]     = _("Floja");
static const u8 sTimidNatureName[]   = _("Miedosa");
static const u8 sHastyNatureName[]   = _("Activa");
static const u8 sSeriousNatureName[] = _("Seria");
static const u8 sJollyNatureName[]   = _("Alegre");
static const u8 sNaiveNatureName[]   = _("Ingenua");
static const u8 sModestNatureName[]  = _("Modesta");
static const u8 sMildNatureName[]    = _("Afable");
static const u8 sQuietNatureName[]   = _("Mansa");
static const u8 sBashfulNatureName[] = _("Tímida");
static const u8 sRashNatureName[]    = _("Alocada");
static const u8 sCalmNatureName[]    = _("Serena");
static const u8 sGentleNatureName[]  = _("Amable");
static const u8 sSassyNatureName[]   = _("Grosera");
static const u8 sCarefulNatureName[] = _("Cauta");
static const u8 sQuirkyNatureName[]  = _("Rara");
#else
static const u8 sHardyNatureName[] = _("Hardy");
static const u8 sLonelyNatureName[] = _("Lonely");
static const u8 sBraveNatureName[] = _("Brave");
static const u8 sAdamantNatureName[] = _("Adamant");
static const u8 sNaughtyNatureName[] = _("Naughty");
static const u8 sBoldNatureName[] = _("Bold");
static const u8 sDocileNatureName[] = _("Docile");
static const u8 sRelaxedNatureName[] = _("Relaxed");
static const u8 sImpishNatureName[] = _("Impish");
static const u8 sLaxNatureName[] = _("Lax");
static const u8 sTimidNatureName[] = _("Timid");
static const u8 sHastyNatureName[] = _("Hasty");
static const u8 sSeriousNatureName[] = _("Serious");
static const u8 sJollyNatureName[] = _("Jolly");
static const u8 sNaiveNatureName[] = _("Naive");
static const u8 sModestNatureName[] = _("Modest");
static const u8 sMildNatureName[] = _("Mild");
static const u8 sQuietNatureName[] = _("Quiet");
static const u8 sBashfulNatureName[] = _("Bashful");
static const u8 sRashNatureName[] = _("Rash");
static const u8 sCalmNatureName[] = _("Calm");
static const u8 sGentleNatureName[] = _("Gentle");
static const u8 sSassyNatureName[] = _("Sassy");
static const u8 sCarefulNatureName[] = _("Careful");
static const u8 sQuirkyNatureName[] = _("Quirky");
#endif

const u8 *const gNatureNamePointers[NUM_NATURES] =
{
    [NATURE_HARDY] = sHardyNatureName,
    [NATURE_LONELY] = sLonelyNatureName,
    [NATURE_BRAVE] = sBraveNatureName,
    [NATURE_ADAMANT] = sAdamantNatureName,
    [NATURE_NAUGHTY] = sNaughtyNatureName,
    [NATURE_BOLD] = sBoldNatureName,
    [NATURE_DOCILE] = sDocileNatureName,
    [NATURE_RELAXED] = sRelaxedNatureName,
    [NATURE_IMPISH] = sImpishNatureName,
    [NATURE_LAX] = sLaxNatureName,
    [NATURE_TIMID] = sTimidNatureName,
    [NATURE_HASTY] = sHastyNatureName,
    [NATURE_SERIOUS] = sSeriousNatureName,
    [NATURE_JOLLY] = sJollyNatureName,
    [NATURE_NAIVE] = sNaiveNatureName,
    [NATURE_MODEST] = sModestNatureName,
    [NATURE_MILD] = sMildNatureName,
    [NATURE_QUIET] = sQuietNatureName,
    [NATURE_BASHFUL] = sBashfulNatureName,
    [NATURE_RASH] = sRashNatureName,
    [NATURE_CALM] = sCalmNatureName,
    [NATURE_GENTLE] = sGentleNatureName,
    [NATURE_SASSY] = sSassyNatureName,
    [NATURE_CAREFUL] = sCarefulNatureName,
    [NATURE_QUIRKY] = sQuirkyNatureName,
};
