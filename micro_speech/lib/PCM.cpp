#include "PCM.h"
#include "iodefine.h"

uint16_t __attribute__((aligned(512))) g_pcm_buffer[DEFAULT_PCM_BUFFER_SIZE / sizeof(uint16_t)];
#define VECT_S12AD1_S12ADI1 146

PCMClass::PCMClass(int inputPin, int dmaCh) :
	_inputPin(inputPin),
	_dmaCh(dmaCh),
	_onReceive(NULL),
	_DMACm(NULL),
	_channels(0)
{
}

PCMClass::~PCMClass()
{
}

int PCMClass::begin(int channels, long sampleRate)
{
	_channels = channels;

	uint16_t adans0 = 0;
	volatile uint16_t *ad_addr = NULL;

	switch (_inputPin) {
	case PIN_A0: adans0 |= 1 << 10; ad_addr = &S12AD1.ADDR10; break;
	case PIN_A1: adans0 |= 1 << 11; ad_addr = &S12AD1.ADDR11; break;
	case PIN_A2: adans0 |= 1 << 12; ad_addr = &S12AD1.ADDR12; break;
	case PIN_A3: adans0 |= 1 << 13; ad_addr = &S12AD1.ADDR13; break;
	case PIN_A4: adans0 |= 1 << 6; ad_addr = &S12AD1.ADDR6; break;
	case PIN_A5: adans0 |= 1 << 7; ad_addr = &S12AD1.ADDR7; break;
	default: return 0;
	}

	volatile unsigned char *ICU_DMRSRm = NULL;
	switch (_dmaCh){
	case 0: ICU_DMRSRm = &ICU.DMRSR0; _DMACm = (struct st_dmac1 *)&DMAC0; break;
	case 1: ICU_DMRSRm = &ICU.DMRSR1; _DMACm = &DMAC1; break;
	case 2: ICU_DMRSRm = &ICU.DMRSR2; _DMACm = &DMAC2; break;
	case 3: ICU_DMRSRm = &ICU.DMRSR3; _DMACm = &DMAC3; break;
	default: return 0;
	}

	/* 選択型割り込みB設定 S12ADIを146に割り当て */
	IEN(PERIB, INTB146) = 0;
	IPR(PERIB, INTB146) = 1;
	ICU.SLIBR146.BIT.SLI = 68;

	/* 割り込み禁止 */
	switch (_dmaCh){
	case 0: IEN(DMAC, DMAC0I) = 0; break;
	case 1: IEN(DMAC, DMAC1I) = 0; break;
	case 2: IEN(DMAC, DMAC2I) = 0; break;
	case 3: IEN(DMAC, DMAC3I) = 0; break;
	}

	/* 周辺機能の制御レジスタを設定するが、スタートはさせない */

	/*
	 * モジュールストップ機能の設定(S12AD1,TMR0,TMR1)
	 */
	SYSTEM.PRCR.WORD = 0xA502;
	SYSTEM.MSTPCRA.BIT.MSTPA16 = 0;
	SYSTEM.MSTPCRA.BIT.MSTPA5 = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	/* A/D変換停止 */
	S12AD1.ADCSR.BIT.ADST = 0b0;

	/* 12bitADC初期化 */
	S12AD1.ADEXICR.WORD = 0x0000;
	S12AD1.ADANSA0.WORD |= adans0;

	/* 同期トリガ（MTU、TPU、TMR）によるA/D変換の開始を選択 */
	S12AD1.ADCSR.BIT.EXTRG = 0b0;
	/* 同期、非同期トリガによるA/D変換の開始を許可 */
	S12AD1.ADCSR.BIT.TRGE = 0b1;
	/* スキャン終了後のS12ADI0割り込み発生の許可 */
	S12AD1.ADCSR.BIT.ADIE = 0b1;
	/*	シングルスキャンモード */
	S12AD1.ADCSR.BIT.ADCS = 0b0;
	/* 自動クリアを禁止 */
	S12AD1.ADCER.BIT.ACE = 0b0;
	/* A/Dデータレジスタのフォーマットを右詰めにする */
	S12AD1.ADCER.BIT.ADRFMT = 0b0;
	/* TMR0.TCORAとTMR0.TCNT */
	S12AD1.ADSTRGR.BIT.TRSA = 0b011101;

	/* 16ビットカウントモード */
	TMR0.TCCR.BIT.CSS = 0b11;
	TMR0.TCCR.BIT.CKS = 0b000;
	/* 分周クロック：PCLK/8でカウント */
	TMR1.TCCR.BIT.CSS = 0b01;
	TMR1.TCCR.BIT.CKS = 0b010;
	/* PCLK(60MHz)/8/16kHz */
	TMR01.TCORA = 469;
	/* コンペアマッチAによりクリア */
	TMR0.TCR.BIT.CCLR = 0b01;

	/* IRQ端子機能を設定するが、許可はさせない */
	switch (_dmaCh){
	case 0: IPR(DMAC, DMAC0I) = 1; break;
	case 1: IPR(DMAC, DMAC1I) = 1; break;
	case 2: IPR(DMAC, DMAC2I) = 1; break;
	case 3: IPR(DMAC, DMAC3I) = 1; break;
	}

	/* DMA転送禁止 */
	_DMACm->DMCNT.BIT.DTE = 0;

	switch (_dmaCh){
	case 0: IR(DMAC, DMAC0I) = 0; break;
	case 1: IR(DMAC, DMAC1I) = 0; break;
	case 2: IR(DMAC, DMAC2I) = 0; break;
	case 3: IR(DMAC, DMAC3I) = 0; break;
	}

	/* DMACの起動要因を設定する */
	*ICU_DMRSRm = VECT_S12AD1_S12ADI1;

	/* 転送先アドレス更新モード：インクリメント */
	_DMACm->DMAMD.BIT.DM = 0b10;
	/* 転送元アドレス更新モード：アドレス固定 */
	_DMACm->DMAMD.BIT.SM = 0b00;
	/* 転送先アドレス拡張リピートエリア設定ビット(512Byte) */
	_DMACm->DMAMD.BIT.DARA = 0b01001;
	/* 転送元アドレス拡張リピートエリア設定ビット */
	_DMACm->DMAMD.BIT.SARA = 0b00000;
	/* 周辺モジュールによる転送要求 */
	_DMACm->DMTMD.BIT.DCTG = 0b01;
	/* 16ビット転送 */
	_DMACm->DMTMD.BIT.SZ = 0x01;
	/* リピート領域、ブロック領域は設定しない */
	_DMACm->DMTMD.BIT.DTS = 0b10;
	/* ノーマル転送モード */
	_DMACm->DMTMD.BIT.MD = 0b00;

	/* 転送元の開始アドレスを設定 */
	_DMACm->DMSAR = (unsigned long)ad_addr;
	/* 転送先の開始アドレスを設定 */
	_DMACm->DMDAR = (unsigned long)g_pcm_buffer;
	/* 転送データ数を設定 */
	_DMACm->DMCRA = 0;
	/* ブロック転送数を設定 */
	_DMACm->DMCRB = 0;

	/* DMA転送終了割り込み許可 */
	_DMACm->DMINT.BIT.DARIE = 1;
	_DMACm->DMINT.BIT.ESIE = 1;

	/* DMA転送許可 */
	_DMACm->DMCNT.BIT.DTE = 1;

	/* 変換開始（シングルスキャンモード） */
	S12AD1.ADCSR.BIT.ADST = 1;

	/* DMA転送終了割り込み許可 */
	switch (_dmaCh){
	case 0: IEN(DMAC, DMAC0I) = 1; break;
	case 1: IEN(DMAC, DMAC1I) = 1; break;
	case 2: IEN(DMAC, DMAC2I) = 1; break;
	case 3: IEN(DMAC, DMAC3I) = 1; break;
	}

	/* 12bitADC割り込み許可 */
	IEN(PERIB, INTB146) = 1;

	/* DMAC動作許可 */
	DMAC.DMAST.BIT.DMST = 1;

	/* コンペアマッチAによるA/D変換開始要求を許可 */
	TMR0.TCSR.BIT.ADTE = 0b1;

	return 1;
}

void PCMClass::end()
{
	/* 割り込み禁止 */
	switch (_dmaCh){
	case 0: IEN(DMAC, DMAC0I) = 0; break;
	case 1: IEN(DMAC, DMAC1I) = 0; break;
	case 2: IEN(DMAC, DMAC2I) = 0; break;
	case 3: IEN(DMAC, DMAC3I) = 0; break;
	}
	IEN(PERIB, INTB146) = 0;

	/* コンペアマッチAによるA/D変換開始要求を禁止 */
	TMR0.TCSR.BIT.ADTE = 0b0;

	/* AD変換停止 */
	S12AD1.ADCSR.BIT.ADST = 0;

	/* DMAC動作停止 */
	DMAC.DMAST.BIT.DMST = 0;
}

int PCMClass::read(void *buffer, size_t size)
{
	//IEN(DMAC, DMACxI) = 0;

	int temp;
	int16_t *pos = (int16_t *)buffer, *end = (int16_t *)((intptr_t)buffer + size);
	uint16_t *src = g_pcm_buffer;
	for (; pos < end; pos++, src++) {
		temp = _gain * (*src - 2048);
		if (temp > 32767)
			temp = 32767;
		else if (temp < -32768)
			temp = -32768;
		*pos = temp;
	}

	//IEN(DMAC, DMACxI) = 1;

	return (intptr_t)pos - (intptr_t)buffer;
}

void PCMClass::onReceive(void(*function)(void))
{
	_onReceive = function;
}

void PCMClass::setGain(int gain)
{
	_gain = gain;
}

void PCMClass::IrqHandler()
{
	switch (_dmaCh){
	case 0: IEN(DMAC, DMAC0I) = 0; break;
	case 1: IEN(DMAC, DMAC1I) = 0; break;
	case 2: IEN(DMAC, DMAC2I) = 0; break;
	case 3: IEN(DMAC, DMAC3I) = 0; break;
	}

	// call receive callback if provided
	if (_onReceive) {
		_onReceive();
	}

	switch (_dmaCh){
	case 0: IEN(DMAC, DMAC0I) = 1; break;
	case 1: IEN(DMAC, DMAC1I) = 1; break;
	case 2: IEN(DMAC, DMAC2I) = 1; break;
	case 3: IEN(DMAC, DMAC3I) = 1; break;
	}

	/* DMA再開 */
	_DMACm->DMCNT.BIT.DTE = 1;
}

extern PCMClass PCM;
