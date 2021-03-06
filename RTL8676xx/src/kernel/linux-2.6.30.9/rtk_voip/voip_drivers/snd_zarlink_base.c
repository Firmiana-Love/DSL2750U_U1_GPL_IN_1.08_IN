#include <linux/kernel.h>
#include "voip_types.h"
#include "voip_debug.h"
#include "con_register.h"

#include "snd_define.h"

//#include "zarlink_int.h"
#include "zarlink_api.h"

// --------------------------------------------------------
// zarlink fxs ops 
// --------------------------------------------------------

static void FXS_Ring_zarlink(voip_snd_t *this, unsigned char ringset )
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	ZarlinkFxsRing(pLine, ringset);
}

static unsigned char FXS_Check_Ring_zarlink(voip_snd_t *this)
{
	unsigned char ringer; //0: ring off, 1: ring on
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;

	ringer = ZarlinkCheckFxsRing(pLine);

	return ringer;
}

static void Set_SLIC_Tx_Gain_zarlink(voip_snd_t *this, unsigned char tx_gain)
{
	printk("Not implemented! Support unity gain only!\n");
}

static void Set_SLIC_Rx_Gain_zarlink(voip_snd_t *this, unsigned char rx_gain)
{
	printk("Not implemented! Support unity gain only!\n");
}

static void SLIC_Set_Ring_Cadence_zarlink(voip_snd_t *this, unsigned short OnMsec, unsigned short OffMsec)
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	ZarlinkSetRingCadence(pLine, OnMsec, OffMsec);
}

static void SLIC_Set_Ring_Freq_Amp_zarlink(voip_snd_t *this, char preset)
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	ZarlinkSetRingFreqAmp(pLine, preset);
}

static void SLIC_Set_Impendance_Country_zarlink(voip_snd_t *this, unsigned short country, unsigned short impd)
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	ZarlinkSetImpedenceCountry(pLine, (unsigned char)country);
}

static void SLIC_Set_Impendance_zarlink(voip_snd_t *this, unsigned short preset)
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	ZarlinkSetImpedence(pLine, preset);
}

#if 0
static void SLIC_GenProcessTone(unsigned int chid, genTone_struct *gen_tone)
{
}
#endif


static void OnHookLineReversal_zarlink(voip_snd_t *this, unsigned char bReversal) //0: Forward On-Hook Transmission, 1: Reverse On-Hook Transmission
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	ZarlinkSetOHT(pLine, bReversal);
}

static void SLIC_Set_LineVoltageZero_zarlink(voip_snd_t *this)
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	ZarlinkSetLineOpen(pLine);
	//ZarlinkSetLineState(pLine, VP_LINE_DISCONNECT);
}

static uint8 SLIC_CPC_Gen_zarlink(voip_snd_t *this)
{
#if 0	// con_polling.c: SLIC_CPC_Gen_cch() do this 
	extern void HookPollingDisable(int cch);

	if (slic_cpc[chid].cpc_start != 0)
	{
		PRINT_R("SLIC CPC gen not stop, ch=%d\n", chid);
		return;
	}
#endif

	uint8 pre_linefeed;
	
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	pre_linefeed = ZarlinkGetLineState( pLine ); // save current linefeed status

	ZarlinkSetLineOpen( pLine );
	//ZarlinkSetLineState( pLine, VP_LINE_DISCONNECT );

#if 0	// con_polling.c: SLIC_CPC_Gen_cch() do this 
	slic_cpc[chid].cpc_timeout = jiffies + (HZ*time_in_ms_of_cpc_signal/1000);
	slic_cpc[chid].cpc_start = 1;
	slic_cpc[chid].cpc_stop = 0;
	HookPollFlag[chid] = 0; // disable hook pooling
#endif
	
	return pre_linefeed;
}

static void SLIC_CPC_Check_zarlink(voip_snd_t *this, uint8 pre_linefeed)	// check in timer
{
#if 0	// con_polling.c: ENTRY_SLIC_CPC_Polling() do this 
	extern void HookPollingEnable(int cch);
	
	if (slic_cpc[chid].cpc_start == 0)
		return;
#endif

	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	// Stop wink function
#if 0
	if ((slic_cpc[chid].cpc_stop == 0) && (time_after(jiffies, slic_cpc[chid].cpc_timeout)))
#endif
	{

		//printk("set linefeed=0x%x\n", slic_cpc[chid].pre_linefeed);
		ZarlinkSetLineState(pLine, pre_linefeed);

#if 0	// con_polling.c: ENTRY_SLIC_CPC_Polling() do this 
		slic_cpc[chid].cpc_timeout2 = jiffies + (HZ*200/1000);
		slic_cpc[chid].cpc_stop = 1;
#endif

	}
	
#if 0	// con_polling.c: ENTRY_SLIC_CPC_Polling() do this 
	if ((slic_cpc[chid].cpc_stop == 1) && (time_after(jiffies, slic_cpc[chid].cpc_timeout2)))
	{
		slic_cpc[chid].cpc_start = 0;
		//HookPollFlag[chid] = 1; // enable hook pooling
		HookPollingEnable( chid );
	}
#endif
}

/*  return value:
	0: Phone dis-connect, 
	1: Phone connect, 
	2: Phone off-hook, 
	3: Check time out ( may connect too many phone set => view as connect),
	4: Can not check, Linefeed should be set to active state first.
*/
//static inline unsigned char SLIC_Get_Hook_Status( int chid );

static inline unsigned int FXS_Line_Check_zarlink( voip_snd_t *this )	// Note: this API may cause watch dog timeout. Should it disable WTD?
{
	//unsigned long flags;
	//unsigned int v_tip, v_ring, tick=0;
	//unsigned int v_tip, v_ring, tick = 0;
	//unsigned int connect_flag = 0, time_out_flag = 0;
	//unsigned char linefeed, rev_linefeed;

	if ( 1 == this ->fxs_ops ->SLIC_Get_Hook_Status( this, 1 ) )
	{
		//PRINT_MSG("%s: Phone 0ff-hook\n",__FUNCTION__);
		return 2;
	}

	return 4;
}


static void SendNTTCAR_zarlink( voip_snd_t *this )
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	ZarlinkSendNTTCAR(pLine);
}

static unsigned int SendNTTCAR_check_zarlink(voip_snd_t *this, unsigned long time_out)
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	return ZarlinkSendNTTCAR_Check(pLine, time_out);
}

static void disableOscillators_zarlink(voip_snd_t *this)
{
	printk("Not implemented!\n");
}

static void SetOnHookTransmissionAndBackupRegister_zarlink(voip_snd_t *this) // use for DTMF caller id
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	ZarlinkSetOHT(pLine, 0);
}

static inline void RestoreBackupRegisterWhenSetOnHookTransmission_zarlink(voip_snd_t *this) // use for DTMF caller id
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	ZarlinkGetLineState(pLine);//thlin test
}

#define PCMLAW_OFFSET	3

CT_ASSERT( PCMMODE_WIDEBAND_LINEAR - PCMMODE_LINEAR == PCMLAW_OFFSET );
CT_ASSERT( PCMMODE_WIDEBAND_ALAW - PCMMODE_ALAW == PCMLAW_OFFSET );
CT_ASSERT( PCMMODE_WIDEBAND_ULAW - PCMMODE_ULAW == PCMLAW_OFFSET );

static void SLIC_PCMSetup_priv_ops( voip_snd_t *this, int enable )
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	int pcm_mode = pLine->pcm_law_save;
	
	printk( "%s:enable=%d,pLine->pcm_law_save=%d\n",__FUNCTION__, enable, pLine->pcm_law_save );
	if( !enable )
		return;
	
	// check if need to switch between narrowband/wideband mode 
	switch( pLine->pcm_law_save ) {
	case PCMMODE_LINEAR:
		if (enable == 2)
			pcm_mode =  PCMMODE_WIDEBAND_LINEAR; 
		break;
	case PCMMODE_ALAW:
		if (enable == 2)
			pcm_mode =  PCMMODE_WIDEBAND_ALAW; 
		break;
	case PCMMODE_ULAW:
		if( enable == 2 ) { //Change to wideband mode
			//pcm_mode = pLine->pcm_law_save;
			pcm_mode =  PCMMODE_WIDEBAND_ULAW; 
		}
		break;
		
	case PCMMODE_WIDEBAND_ALAW: //4
		PRINT_R("%s() PCMMODE_WIDEBAND_ALAW not support\n", __FUNCTION__);
		if( enable == 1 )  //change to narrowband mode
			pcm_mode = 	PCMMODE_ALAW;
		break;

	case PCMMODE_WIDEBAND_ULAW: //5
		PRINT_R("%s() PCMMODE_WIDEBAND_ULAW not support\n", __FUNCTION__);
		if( enable == 1 )  //change to narrowband mode
			pcm_mode = 	PCMMODE_ULAW;
		break;

	case PCMMODE_WIDEBAND_LINEAR: //3
		if( enable == 1 )  //change to narrowband mode
			pcm_mode = 	PCMMODE_LINEAR;
		break;
	}
	
	if( pcm_mode >= 0 ) {
		ZarlinkSetFxsPcmMode(pLine, pcm_mode);
		ZarlinkSetFxsAcProfileByBand(pLine, pcm_mode);
	} else {
		PRINT_R("%s() pcm_mode %d error\n", __FUNCTION__, pcm_mode);
	}		
}

static void SLIC_Set_PCM_state_zarlink(voip_snd_t *this, int enable)
{
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;
	
	/* By the limition of API-II, LE89 series, PCM tx/rx can not be mute at the same time. */
	ZarlinkSetPcmTxOnly(pLine, ( enable ? 0 : 1 ));// mute phone SPK
	//ZarlinkSetPcmRxOnly(chid, ( enable ? 0 : 1 ));// mute phone MIC
}

static unsigned char SLIC_Get_Hook_Status_zarlink(voip_snd_t *this, int directly)
{
	unsigned char status;
	RTKLineObj * const pLine = (RTKLineObj * )this ->priv;

	status = ZarlinkGetFxsHookStatus(pLine, directly);
	
	return status;
}

static void SLIC_read_reg_zarlink(voip_snd_t *this, unsigned int num, unsigned char *val)
{

}


static void SLIC_write_reg_zarlink(voip_snd_t *this, unsigned char num, unsigned char val)
{

}

static void SLIC_read_ram_zarlink(voip_snd_t *this, unsigned short num, unsigned int *val)
{

}

static void SLIC_write_ram_zarlink(voip_snd_t *this, unsigned short num, unsigned int val)
{

}

static void SLIC_dump_reg_zarlink(voip_snd_t *this)
{

}

static void SLIC_dump_ram_zarlink(voip_snd_t *this)
{

}

static void FXS_FXO_DTx_DRx_Loopback_zarlink(voip_snd_t *this, voip_snd_t *daa_snd, unsigned int enable)
{
	printk( "Not implement FXS_FXO loopback\n" );
}

static void SLIC_OnHookTrans_PCM_start_zarlink(voip_snd_t *this)
{
	this ->fxs_ops ->SLIC_Set_PCM_state(this, SLIC_PCM_ON);
	this ->fxs_ops ->OnHookLineReversal(this, 0);		//Forward On-Hook Transmission
	PRINT_MSG("SLIC_OnHookTrans_PCM_start, ch = %d\n", this ->sch);
}

static int enable_zarlink( voip_snd_t *this, int enable )
{
	SLIC_PCMSetup_priv_ops( this, enable );
	this ->fxs_ops ->SLIC_Set_PCM_state( this, enable );
	
	return 0;
}

// --------------------------------------------------------
// channel mapping architecture 
// --------------------------------------------------------

const snd_ops_fxs_t snd_zarlink_fxs_ops = {
	// common operation 
	.enable = enable_zarlink,
	
	// for each snd_type 
	//.SLIC_reset = SLIC_reset_zarlink,
	.FXS_Ring = FXS_Ring_zarlink,
	.FXS_Check_Ring = FXS_Check_Ring_zarlink,
	.FXS_Line_Check = FXS_Line_Check_zarlink,	// Note: this API may cause watch dog timeout. Should it disable WTD?
	.SLIC_Set_PCM_state = SLIC_Set_PCM_state_zarlink,
	.SLIC_Get_Hook_Status = SLIC_Get_Hook_Status_zarlink,
	
	.Set_SLIC_Tx_Gain = Set_SLIC_Tx_Gain_zarlink,
	.Set_SLIC_Rx_Gain = Set_SLIC_Rx_Gain_zarlink,
	.SLIC_Set_Ring_Cadence = SLIC_Set_Ring_Cadence_zarlink,
	.SLIC_Set_Ring_Freq_Amp = SLIC_Set_Ring_Freq_Amp_zarlink,
	.SLIC_Set_Impendance_Country = SLIC_Set_Impendance_Country_zarlink, 
	.SLIC_Set_Impendance = SLIC_Set_Impendance_zarlink,
	.OnHookLineReversal = OnHookLineReversal_zarlink,	//0: Forward On-Hook Transmission, 1: Reverse On-Hook Transmission
	.SLIC_Set_LineVoltageZero = SLIC_Set_LineVoltageZero_zarlink,
	
	.SLIC_CPC_Gen = SLIC_CPC_Gen_zarlink,
	.SLIC_CPC_Check = SLIC_CPC_Check_zarlink,	// check in timer
	
	.SendNTTCAR = SendNTTCAR_zarlink,
	.SendNTTCAR_check = SendNTTCAR_check_zarlink,
	
	.disableOscillators = disableOscillators_zarlink,
	
	.SetOnHookTransmissionAndBackupRegister = SetOnHookTransmissionAndBackupRegister_zarlink,	// use for DTMF caller id
	.RestoreBackupRegisterWhenSetOnHookTransmission = RestoreBackupRegisterWhenSetOnHookTransmission_zarlink,	// use for DTMF caller id
	
	.FXS_FXO_DTx_DRx_Loopback = FXS_FXO_DTx_DRx_Loopback_zarlink,
	.SLIC_OnHookTrans_PCM_start = SLIC_OnHookTrans_PCM_start_zarlink,
	
	// read/write register/ram
	.SLIC_read_reg = SLIC_read_reg_zarlink,
	.SLIC_write_reg = SLIC_write_reg_zarlink,
	.SLIC_read_ram = SLIC_read_ram_zarlink,
	.SLIC_write_ram = SLIC_write_ram_zarlink,
	.SLIC_dump_reg = SLIC_dump_reg_zarlink,
	.SLIC_dump_ram = SLIC_dump_ram_zarlink,
	
	//.SLIC_show_ID = ??
};

