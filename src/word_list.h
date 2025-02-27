#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <string_view>
#include <array>

// Array of common English words (3-8 letters, which is typical for Boggle)
constexpr std::array<std::string_view, 101> WORD_LIST = {
    "THE", "AND", "THAT", "HAVE", "FOR", "NOT", "WITH", "YOU", "THIS", "BUT",
    "FROM", "THEY", "SAY", "HER", "SHE", "WILL", "ONE", "ALL", "WOULD", "THERE",
    "THEIR", "WHAT", "OUT", "ABOUT", "WHO", "GET", "WHICH", "WHEN", "MAKE",
    "CAN", "LIKE", "TIME", "JUST", "HIM", "KNOW", "TAKE", "PEOPLE", "INTO",
    "YEAR", "YOUR", "GOOD", "SOME", "COULD", "THEM", "SEE", "OTHER", "THAN",
    "THEN", "NOW", "LOOK", "ONLY", "COME", "ITS", "OVER", "THINK", "ALSO",
    "BACK", "AFTER", "USE", "TWO", "HOW", "OUR", "WORK", "FIRST", "WELL",
    "WAY", "EVEN", "NEW", "WANT", "ANY", "THESE", "GIVE", "DAY", "MOST",
    "PLAY", "GAME", "TEAM", "WORD", "TEST", "FIND", "MANY", "MUST", "STILL",
    "LIFE", "KNOW", "SAME", "TAKE", "PART", "REAL", "CARE", "MOVE", "FACT",
    "BOOK", "STAR", "HAND", "HERE", "KIND", "NEED", "HOME", "GROW", "FOOD"
};

// Extended array of common English words (3-8 letters) for performance testing
constexpr std::array<std::string_view, 1000> EXTENDED_WORD_LIST = {
    "THE", "AND", "THAT", "HAVE", "FOR", "NOT", "WITH", "YOU", "THIS", "BUT",
    "FROM", "THEY", "SAY", "HER", "SHE", "WILL", "ONE", "ALL", "WOULD", "THERE",
    "THEIR", "WHAT", "OUT", "ABOUT", "WHO", "GET", "WHICH", "WHEN", "MAKE",
    "CAN", "LIKE", "TIME", "JUST", "HIM", "KNOW", "TAKE", "PEOPLE", "INTO",
    "YEAR", "YOUR", "GOOD", "SOME", "COULD", "THEM", "SEE", "OTHER", "THAN",
    "THEN", "NOW", "LOOK", "ONLY", "COME", "ITS", "OVER", "THINK", "ALSO",
    "BACK", "AFTER", "USE", "TWO", "HOW", "OUR", "WORK", "FIRST", "WELL",
    "WAY", "EVEN", "NEW", "WANT", "ANY", "THESE", "GIVE", "DAY", "MOST",
    "PLAY", "GAME", "TEAM", "WORD", "TEST", "FIND", "MANY", "MUST", "STILL",
    "LIFE", "KNOW", "SAME", "TAKE", "PART", "REAL", "CARE", "MOVE", "FACT",
    "BOOK", "STAR", "HAND", "HERE", "KIND", "NEED", "HOME", "GROW", "FOOD",
    "ABLE", "ACID", "AGED", "ALSO", "AREA", "ARMY", "AWAY", "BABY", "BACK",
    "BALL", "BAND", "BANK", "BASE", "BATH", "BEAR", "BEAT", "BEEN", "BEER",
    "BELL", "BELT", "BEST", "BILL", "BIRD", "BLOW", "BLUE", "BOAT", "BODY",
    "BOMB", "BOND", "BONE", "BOOK", "BOOM", "BORN", "BOSS", "BOTH", "BOWL",
    "BULK", "BURN", "BUSH", "BUSY", "CALL", "CALM", "CAME", "CAMP", "CARD",
    "CARE", "CASE", "CASH", "CAST", "CELL", "CHAT", "CHIP", "CITY", "CLUB",
    "COAL", "COAT", "CODE", "COLD", "COME", "COOK", "COOL", "COPE", "COPY",
    "CORE", "COST", "CREW", "CROP", "DARK", "DATA", "DATE", "DAWN", "DAYS",
    "DEAD", "DEAL", "DEAN", "DEAR", "DEBT", "DEEP", "DENY", "DESK", "DIAL",
    "DICK", "DIET", "DISC", "DISK", "DOES", "DONE", "DOOR", "DOSE", "DOWN",
    "DRAW", "DREW", "DROP", "DRUG", "DUAL", "DUKE", "DUST", "DUTY", "EACH",
    "EARN", "EASE", "EAST", "EASY", "EDGE", "ELSE", "EVEN", "EVER", "EVIL",
    "EXIT", "FACE", "FACT", "FAIL", "FAIR", "FALL", "FARM", "FAST", "FATE",
    "FEAR", "FEED", "FEEL", "FEET", "FELL", "FELT", "FILE", "FILL", "FILM",
    "FIND", "FINE", "FIRE", "FIRM", "FISH", "FIVE", "FLAT", "FLOW", "FOOD",
    "FOOT", "FORD", "FORM", "FORT", "FOUR", "FREE", "FROM", "FUEL", "FULL",
    "FUND", "GAIN", "GAME", "GATE", "GAVE", "GEAR", "GENE", "GIFT", "GIRL",
    "GIVE", "GLAD", "GOAL", "GOES", "GOLD", "GOLF", "GONE", "GOOD", "GRAY",
    "GREW", "GREY", "GROW", "GULF", "HAIR", "HALF", "HALL", "HAND", "HANG",
    "HARD", "HARM", "HATE", "HAVE", "HEAD", "HEAR", "HEAT", "HELD", "HELL",
    "HELP", "HERE", "HERO", "HIGH", "HILL", "HIRE", "HOLD", "HOLE", "HOLY",
    "HOME", "HOPE", "HOST", "HOUR", "HUGE", "HUNG", "HUNT", "HURT", "IDEA",
    "INCH", "INTO", "IRON", "ITEM", "JACK", "JANE", "JEAN", "JOHN", "JOIN",
    "JUMP", "JURY", "JUST", "KEEN", "KEEP", "KENT", "KEPT", "KICK", "KILL",
    "KIND", "KING", "KNEE", "KNEW", "KNOW", "LACK", "LADY", "LAID", "LAKE",
    "LAND", "LANE", "LAST", "LATE", "LEAD", "LEFT", "LESS", "LIFE", "LIFT",
    "LIKE", "LINE", "LINK", "LIST", "LIVE", "LOAD", "LOAN", "LOCK", "LOGO",
    "LONG", "LOOK", "LORD", "LOSE", "LOSS", "LOST", "LOVE", "LUCK", "MADE",
    "MAIL", "MAIN", "MAKE", "MALE", "MANY", "MARK", "MASS", "MATT", "MEAL",
    "MEAN", "MEAT", "MEET", "MENU", "MERE", "MIKE", "MILE", "MILK", "MILL",
    "MIND", "MINE", "MISS", "MODE", "MOOD", "MOON", "MORE", "MOST", "MOVE",
    "MUCH", "MUST", "NAME", "NAVY", "NEAR", "NECK", "NEED", "NEWS", "NEXT",
    "NICE", "NICK", "NINE", "NONE", "NOSE", "NOTE", "OKAY", "ONCE", "ONLY",
    "ONTO", "OPEN", "ORAL", "OVER", "PACE", "PACK", "PAGE", "PAID", "PAIN",
    "PAIR", "PALM", "PARK", "PART", "PASS", "PAST", "PATH", "PEAK", "PICK",
    "PINK", "PIPE", "PLAN", "PLAY", "PLOT", "PLUG", "PLUS", "POLL", "POOL",
    "POOR", "PORT", "POST", "PULL", "PURE", "PUSH", "RACE", "RAIL", "RAIN",
    "RANK", "RARE", "RATE", "READ", "REAL", "REAR", "RELY", "RENT", "REST",
    "RICE", "RICH", "RIDE", "RING", "RISE", "RISK", "ROAD", "ROCK", "ROLE",
    "ROLL", "ROOF", "ROOM", "ROOT", "ROSE", "RULE", "RUSH", "RUTH", "SAFE",
    "SAID", "SAKE", "SALE", "SALT", "SAME", "SAND", "SAVE", "SEAT", "SEED",
    "SEEK", "SEEM", "SEEN", "SELF", "SELL", "SEND", "SENT", "SEPT", "SHIP",
    "SHOP", "SHOT", "SHOW", "SHUT", "SICK", "SIDE", "SIGN", "SITE", "SIZE",
    "SKIN", "SLIP", "SLOW", "SNOW", "SOFT", "SOIL", "SOLD", "SOLE", "SOME",
    "SONG", "SOON", "SORT", "SOUL", "SPOT", "STAR", "STAY", "STEP", "STOP",
    "SUCH", "SUIT", "SURE", "TAKE", "TALE", "TALK", "TALL", "TANK", "TAPE",
    "TASK", "TEAM", "TECH", "TELL", "TEND", "TERM", "TEST", "TEXT", "THAN",
    "THAT", "THEM", "THEN", "THEY", "THIN", "THIS", "THUS", "TILL", "TIME",
    "TINY", "TOLD", "TOLL", "TONE", "TONY", "TOOK", "TOOL", "TOUR", "TOWN",
    "TREE", "TRIP", "TRUE", "TUNE", "TURN", "TWIN", "TYPE", "UNIT", "UPON",
    "USED", "USER", "VARY", "VAST", "VERY", "VICE", "VIEW", "VINE", "VOTE",
    "WAGE", "WAIT", "WAKE", "WALK", "WALL", "WANT", "WARD", "WARM", "WASH",
    "WAVE", "WAYS", "WEAK", "WEAR", "WEEK", "WELL", "WENT", "WERE", "WEST",
    "WHAT", "WHEN", "WHOM", "WIDE", "WIFE", "WILD", "WILL", "WIND", "WINE",
    "WING", "WIRE", "WISE", "WISH", "WITH", "WOOD", "WORD", "WORE", "WORK",
    "YARD", "YEAH", "YEAR", "YOUR", "ZERO", "ZONE"
};


#endif // WORD_LIST_H 
