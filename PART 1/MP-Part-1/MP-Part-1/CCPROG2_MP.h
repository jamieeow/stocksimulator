/* CCPROG2_MP.h */

/* DO NOT CHANGE the contents of this file */

#ifndef CCPROG2_MP_DEF
 
#define CCPROG2_MP_DEF  1

typedef char StrDate[11];   // for dates in string format "MM/DD/YYYY", ex. "10/24/2016"
typedef char Symbol[9];     // for stock names,  ex. "EEI", "SMPH","URC"

struct DailyData {
     StrDate date;
     float open, high, low, close;  // OHLC values
     float volume;
};

typedef struct DailyData DDType;

#endif
