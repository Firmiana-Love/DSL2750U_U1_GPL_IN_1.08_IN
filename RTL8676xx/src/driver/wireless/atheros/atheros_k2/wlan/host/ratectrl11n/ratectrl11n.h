/*
 * Copyright (c) 2000-2002 Atheros Communications, Inc., All Rights Reserved
 *
 * Definitions for core driver
 * This is a common header file for all platforms and operating systems.
 */
#ifndef _RATECTRL11N_H_
#define _RATECTRL11N_H_

/* HT 20/40 rates. If 20 bit is enabled then that rate is
 * used only in 20 mode. If both 20/40 bits are enabled
 * then that rate can be used for both 20 and 40 mode */

#define TRUE_20	 	0x2	
#define TRUE_40 	0x4	
#define TRUE_2040	(TRUE_20|TRUE_40)
#define TRUE_ALL_11N	(TRUE_2040|TRUE)

enum {
    WLAN_RC_DS  = 0x01,
    WLAN_RC_40  = 0x02,
    WLAN_RC_SGI = 0x04,
    WLAN_RC_HT  = 0x08,
};


typedef enum {
    WLAN_RC_LEGACY      = 0,
    WLAN_RC_HT_LNPHY    = 1,
    WLAN_RC_HT_PLPHY    = 2,
    WLAN_RC_MAX         = 3
} WLAN_RC_VERS;

#define WLAN_RC_PHY_DS(_phy)   ((_phy == WLAN_RC_PHY_HT_20_DS)           \
                                || (_phy == WLAN_RC_PHY_HT_40_DS)        \
                                || (_phy == WLAN_RC_PHY_HT_20_DS_HGI)    \
                                || (_phy == WLAN_RC_PHY_HT_40_DS_HGI))   
#define WLAN_RC_PHY_40(_phy)   ((_phy == WLAN_RC_PHY_HT_40_SS)           \
                                || (_phy == WLAN_RC_PHY_HT_40_DS)        \
                                || (_phy == WLAN_RC_PHY_HT_40_SS_HGI)    \
                                || (_phy == WLAN_RC_PHY_HT_40_DS_HGI))   
#define WLAN_RC_PHY_SGI(_phy)  ((_phy == WLAN_RC_PHY_HT_20_SS_HGI)      \
                                || (_phy == WLAN_RC_PHY_HT_20_DS_HGI)   \
                                || (_phy == WLAN_RC_PHY_HT_40_SS_HGI)   \
                                || (_phy == WLAN_RC_PHY_HT_40_DS_HGI))   

#define WLAN_RC_PHY_HT(_phy)    (_phy >= WLAN_RC_PHY_HT_20_SS)

	/* Returns the capflag mode */

#define WLAN_RC_CAP_MODE(capflag) (((capflag & WLAN_RC_HT_FLAG)?	\
				    (capflag & WLAN_RC_40_FLAG)?TRUE_40:TRUE_20:\
				    TRUE))

/* Return TRUE if flag supports HT20 && client supports HT20 or
 * return TRUE if flag supports HT40 && client supports HT40.
 * This is used becos some rates overlap between HT20/HT40.
 */

#define WLAN_RC_PHY_HT_VALID(flag, capflag) (((flag & TRUE_20) && !(capflag \
				& WLAN_RC_40_FLAG)) || ((flag & TRUE_40) && \
				  (capflag & WLAN_RC_40_FLAG)))

#define WLAN_RC_NODE_IS_UAPSD(_node)    \
   ((_node)->an_node.ni_flags & IEEE80211_NODE_UAPSD)


#define WLAN_RC_DS_FLAG         (0x01)
#define WLAN_RC_40_FLAG         (0x02)
#define WLAN_RC_SGI_FLAG        (0x04)
#define WLAN_RC_HT_FLAG         (0x08)

/* Index into the rate table */
#define INIT_RATE_MAX_20	23		
#define INIT_RATE_MAX_40	40

/*
 * Rate Table structure for various modes - 'b', 'a', 'g', 'xr';
 * order of fields in info structure is important because hardcoded
 * structures are initialized within the hal for these
 */
#define RATE_TABLE_11N_SIZE             64
#define MAX_SUPPORTED_MCS 	    128

typedef struct regDataLenTable {
    a_uint8_t     numEntries;
    a_uint16_t    frameLenRateIndex[RATE_TABLE_11N_SIZE];
} REG_DATALEN_TABLE;

typedef struct {
    a_bool_t    valid;            /* Valid for use in rate control */
    WLAN_PHY  phy;              /* CCK/OFDM/TURBO/XR */
    a_uint32_t  rateKbps;         /* Rate in Kbits per second */
    a_uint32_t  userRateKbps;     /* User rate in KBits per second */
    a_uint8_t   rateCode;         /* rate that goes into hw descriptors */
    a_uint8_t   shortPreamble;    /* Mask for enabling short preamble in rate code for CCK */
    a_uint8_t   dot11Rate;        /* Value that goes into supported rates info element of MLME */
    a_uint8_t   controlRate;      /* Index of next lower basic rate, used for duration computation */
    A_RSSI    rssiAckValidMin;  /* Rate control related information */
    A_RSSI    rssiAckDeltaMin;  /* Rate control related information */
    a_uint8_t   baseIndex;        /* base rate index */
    a_uint8_t   cw40Index;        /* 40cap rate index */
    a_uint8_t   sgiIndex;         /* shortgi rate index */
    a_uint8_t   htIndex;          /* shortgi rate index */
    a_uint32_t  max4msframelen;   /* Maximum frame length(bytes) for 4ms tx duration */
    a_bool_t    uapsdvalid;       /* Valid for UAPSD nodes */
} rc11n_info_t;

typedef struct {
    int               rateCount;
    rc11n_info_t      info[RATE_TABLE_11N_SIZE];
    a_uint32_t          probeInterval;        /* interval for ratectrl to probe for other rates */
    a_uint32_t          rssiReduceInterval;   /* interval for ratectrl to reduce RSSI */
    a_uint8_t           initialRateMax;   /* the initial rateMax value used in rcSibUpdate() */
    REG_DATALEN_TABLE *regDataLenTable; /* Frame Lengths that comply with Regulatory reqs. */
} RATE_TABLE_11N;

/*
 *  Update the SIB's rate control information
 *
 *  This should be called when the supported rates change
 *  (e.g. SME operation, wireless mode change)
 *
 *  It will determine which rates are valid for use.
 */
void
rcSibUpdate_11n(struct ath_softc *, struct ath_node *, a_uint32_t capflag, 
						a_bool_t keepState);

/*
 * Determines and returns the new Tx rate index.
 */ 
void
rcRateFind_11n(struct ath_softc *sc, struct ath_node *an,
              int numTries, int numRates, int stepDnInc,
              unsigned int rcflag, struct ath_rc_series series[], int *isProbe);

/*
 * This routine is called by the Tx interrupt service routine to give
 * the status of previous frames.
 */
void    
rcUpdate_11n(struct ath_softc *sc, struct ath_node *an,
            A_RSSI rssiAck, a_uint8_t curTxAnt, int finalTSIdx, int Xretries, struct ath_rc_series rcs[],
            int nFrames, int nBad, int sh_lo_retry);


#endif /* _RATECTRL11N_H_ */
