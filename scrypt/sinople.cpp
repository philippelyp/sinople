//
//
//  Copyright (C) 2001,2003 Philippe Paquet. All rights reserved.
//
//
//	Sinople.cpp
//
//	Reference implementation of Sinople
//
//	Who				When		What
//	--------------------------------------------------------------------
//	P. Paquet		17 Aug 01	Creation of Sinople
//	P. Paquet		09 Fev 03	Release
//










//
//	Includes
//

#include <stdlib.h>			// stdlib.h is included to use _rotr and _rotl

#include "sinople.h"











//
//	Globals
//

SINOPLE_u32 g_sbox[2][256] =
{
	{
		0x80b26358, 0x6dd6428b, 0xeb18fbf2, 0xcf9a5de5,
		0x52338ab4, 0xcba557d0, 0x4f3931d0, 0xeede690c,
		0xe1f810ea, 0xcfc4fc91, 0x62203ec7, 0x7a63c227,
		0xedcc58a1, 0x17b62c48, 0x697b6e99, 0x0628dafa,
		0xf0896b35, 0xa71d2cd4, 0xc11a047a, 0x094e3e85,
		0x03b2416d, 0xa2d17b44, 0x6ccdbf9e, 0x2a53fc5d,
		0x8417b843, 0xa9ecd2dc, 0x17eafe12, 0x2a2b5d54,
		0xc16ed9c1, 0xa042b33f, 0x0c604729, 0xbc933ad5,
		0xe6893738, 0xb7b8835d, 0x7e0ef9c9, 0xb1c65d0d,
		0x260a0f19, 0x6f938178, 0x53b0fcf6, 0xe4df5195,
		0x94c6684a, 0x6f826762, 0x66233ef0, 0x11c7d942,
		0x452f1a4f, 0x956737ec, 0xa000a714, 0xe9b27390,
		0x03b1b4cb, 0x3bbc8ab6, 0xfd638b6c, 0x4c72922e,
		0xd63cd9c5, 0x894e0a97, 0xf19f8ba2, 0xebf0be85,
		0x5e942d64, 0x3081bb34, 0x8e4833fb, 0xf4d9b4d4,
		0x2cc15a74, 0xe2c66e50, 0xc6c49908, 0xd522b89b,
		0xe9b7878a, 0x42735a30, 0xafcd72e3, 0x10d4cb7d,
		0x56d6ac6f, 0x99bef655, 0x10aea650, 0xe31fbd7e,
		0xb9e27e67, 0x3bdeac10, 0xdcea30c6, 0xde6353ed,
		0xd3b1b734, 0xa659954b, 0xc14cf94a, 0xa0d23fb4,
		0x1e95071e, 0xe75e7e5e, 0x08228f01, 0xbcbfbd57,
		0x1daf6fda, 0xa782ac71, 0xdb07b735, 0xd8494a42,
		0x78e22620, 0x2a1c2f36, 0x36b74ac2, 0x023e19f3,
		0x13f869aa, 0x073ac9b7, 0x7ceda226, 0x4b3ccfa9,
		0x73f827d8, 0xf6792cbe, 0xbe619895, 0x949cf5b0,
		0xa95c2b7b, 0x2b545008, 0xaa3402a1, 0xaf404381,
		0xda1f9618, 0x9a609e84, 0xb8f66053, 0xe9d8be6b,
		0xa6837c9e, 0x8607f059, 0x8724e9fe, 0x213c444a,
		0xebfe79e0, 0x48d26e03, 0x12962a04, 0x3be911af,
		0x7939fae1, 0x82b16e45, 0x3c423037, 0x268f398c,
		0x1df0f347, 0x589c4782, 0xbe740d24, 0xd3380877,
		0x4cc46d48, 0x32eefa78, 0x566deeb4, 0xe34e6086,
		0xaef1493d, 0x4eb54cd5, 0x12483a81, 0xe949c57c,
		0x5f3cabc7, 0x8390d684, 0xa8caa6c4, 0xa7661ad5,
		0x98ab0a0b, 0xeba59676, 0x1458bfa1, 0x4cb480f6,
		0x328c5f4e, 0xe1c6091a, 0x80241b45, 0x37ecedde,
		0xf8e14e67, 0xd49433f3, 0xb99f501c, 0xd7bff7b3,
		0xa6c9f2a6, 0x15564174, 0xf6bc04f8, 0x8aad4d9f,
		0x16a6791c, 0xe93979f3, 0x599a4ff2, 0xfa251592,
		0x97e81968, 0x38cd3ca4, 0xc1e33a0a, 0xc25660f0,
		0x1c08c7df, 0x4d49df2f, 0x073640b1, 0xca02c608,
		0x9a80116d, 0xf7572437, 0x4432e16c, 0x728623f3,
		0x0204492f, 0x8c7800ee, 0xbf6af2b8, 0x98dbcf56,
		0x904913be, 0x65a80c7f, 0x91a56f29, 0xd435987e,
		0xb9cdc730, 0x8e5b1d54, 0x6c2634a2, 0x507245b9,
		0xfe8cafbb, 0x4e77a150, 0x2ffcc5b6, 0xb6c19a2c,
		0x64f85eed, 0x7f15d598, 0x6ef09636, 0x97916533,
		0xafaa3740, 0x5dab99f5, 0xb8ab11aa, 0xc622d751,
		0x2a1557bc, 0x008708ba, 0x27031ffe, 0x83b9ef1e,
		0xbf1c6a7d, 0x2ce138dd, 0x7efa96a3, 0xb8b71c5b,
		0x0ad106b9, 0x5ee74ae4, 0x609dd74c, 0x6b48acee,
		0xf48da75f, 0xcd69e154, 0x051e6b84, 0xc9e07370,
		0x6e5d66b0, 0x7377951e, 0x994649c9, 0x6e4ee492,
		0x42c3e57b, 0x2e8ef724, 0x3b3abda3, 0xbb2604fd,
		0x7b05db98, 0xfad04d47, 0xd0044319, 0xe51a513b,
		0xb4a3a92a, 0x3707f460, 0xdc474b4d, 0x4a6f4826,
		0x252bc3c0, 0x30acce91, 0x4c81672c, 0x154d34a7,
		0xf1702b0e, 0x4d38fad3, 0x4a567a4f, 0x9e166cba,
		0x5c98810e, 0xc368421c, 0xf3ef9c95, 0xea829a82,
		0x5a15cc0f, 0xfa43d06b, 0x3eb40f31, 0x0ded5d04,
		0x1d1688f4, 0x34f16528, 0xe227ea4e, 0x054149e9,
		0x4b363315, 0xa7e57e11, 0xd023c2c3, 0x1e66227d,
		0xde2d4df4, 0x178bd0db, 0x8867871e, 0x3e2e2edd,
		0x73311581, 0x45319877, 0x5309d50a, 0x342f4780,
	},
	{
		0x2883d2bf, 0x6d06c2ed, 0xbbc0e8a5, 0x9c4d9827,
		0x68b6a43a, 0x076eff68, 0xb4674931, 0x06612aec,
		0xaf0fa5ca, 0x10fc9d00, 0x895fa667, 0x2dc393aa,
		0x88b11802, 0x75546ce7, 0x52fc7389, 0xf997af66,
		0x599d3371, 0x0c956a19, 0x1f886fc0, 0xa0794e40,
		0x859ce835, 0xfb2298ca, 0x669e0cd9, 0x4bbb1508,
		0x66e10d7c, 0xe2e4b233, 0xc2baf581, 0x1d164db4,
		0x6d2fde1a, 0x81937b37, 0xf816db18, 0x18e0ea3f,
		0xd5b3b309, 0x956bcd0b, 0x79e534d4, 0x7e3658e1,
		0x202a7bb5, 0x3c0be11a, 0xd8d62f12, 0x2023f019,
		0xb1175428, 0xfbfe6fb0, 0xc2c60e8a, 0x354bc57b,
		0xef46361f, 0x34335297, 0x5aee0467, 0x51722d58,
		0xe326f5a1, 0x09925b51, 0xabfb8ad6, 0x4dd2ff4a,
		0x6b1bbacb, 0x26983e3c, 0xa1fe9c23, 0x264ed763,
		0xac71cb8a, 0xea8b60e2, 0x215310a2, 0x0953a2e7,
		0xf5c39182, 0xd2cff017, 0x06ccdc0e, 0xd82e0374,
		0xada63b2a, 0xa6085a77, 0x78ff0870, 0xc7702fe4,
		0x102ff069, 0x81e1699a, 0xeb6a743e, 0x5e660919,
		0x0c6f4a7a, 0x8d0012bd, 0x9dd5b86c, 0xc105cafa,
		0x867f0164, 0x5e4db6db, 0xa5313f7e, 0x63b9c6bf,
		0x8eeded7a, 0xd3ad269e, 0xb2f8fb02, 0xd2857062,
		0xc2494a9e, 0x300793d3, 0xde5255fa, 0xde46a7eb,
		0x5858f5ae, 0x4a3c8fce, 0xed28a880, 0xaad61d82,
		0xe20ff8a9, 0x242393ca, 0xc5820824, 0xdf6414f1,
		0x79ba232b, 0x0596efe5, 0x396120d9, 0x601a4815,
		0x9ac582dc, 0xbabf0118, 0xfe34192f, 0xe5593c8c,
		0x54ea84bd, 0xc53547cf, 0xc0ae5c68, 0x431ae965,
		0xeb115498, 0x1948ef0a, 0x1f8279e8, 0xb5f72ff2,
		0xea57dff3, 0x1142daf3, 0xa4b0be26, 0x93b3a27d,
		0x15fb11cd, 0xe0d6f796, 0x5ea177d7, 0x3c139a18,
		0xfac5423d, 0xda49597d, 0xe82d89ad, 0x3a57bc6e,
		0x17b0b3d1, 0x619d2bfe, 0xfd61b277, 0x574c816d,
		0x46dc6f92, 0x4d7a4c0e, 0x3cc8baff, 0x2b858527,
		0xe3bc64af, 0x4a109ed5, 0xc1aba37b, 0xc5d648c0,
		0x3904c4d5, 0x93445aa9, 0xec4ac530, 0x8b03c194,
		0x7298f3f6, 0xf8909a4b, 0xf525eb3c, 0x2abd869d,
		0x08edc0e9, 0xda573ee7, 0x37666622, 0xa7e20c56,
		0xc994d1ac, 0x69535c5c, 0x0a0710fe, 0x13d87044,
		0x061120a6, 0x64102f2a, 0xde22822c, 0x0802a5e5,
		0x3b19469b, 0x3796a3ae, 0xdc42075a, 0x10e57116,
		0x8907e58e, 0xc76cdaed, 0xe0927227, 0x5eeda39e,
		0xdb1cca20, 0x63cd9997, 0x90ec41f5, 0xafb34d94,
		0x456a307d, 0x6f53d57b, 0xa955188a, 0x8913347d,
		0xdd6befa9, 0xaf3d8cfe, 0x0023fa7b, 0x38d51e00,
		0xea1f855e, 0x9bd57db5, 0x08fbc88a, 0x1cee0768,
		0xf8011ebc, 0x72501e9b, 0x4887c627, 0xf6bda3eb,
		0xd384806c, 0x121e9877, 0x70f35da2, 0xdb855ea1,
		0xc1f52a04, 0xdb22405e, 0x164f743a, 0x75ea9507,
		0x4ac97165, 0x15fc4d76, 0x86733df9, 0xa20af90d,
		0x4438daf5, 0x03ecc5b8, 0xa6c1d612, 0x5d2806f0,
		0xcf27017d, 0x66c8f507, 0x5dcfcec4, 0xe49c07ed,
		0x7731d6fe, 0xdfb0c97d, 0x9f4dedde, 0xb5d6e1bd,
		0xe0459143, 0x33cfbd3e, 0x3fd167b3, 0xb354495d,
		0x9130d7f1, 0xab2afbe7, 0x02bc3a4b, 0xf6d4cfde,
		0x348bfa55, 0x15bbdb33, 0x521cf5d3, 0x47370bc3,
		0xadf2d9dd, 0xd0645e4b, 0xb5be9aa2, 0x489e29cd,
		0x0fbb638b, 0x8893f72d, 0x90a682ae, 0x49673a37,
		0xbac5b7b2, 0x36aaab91, 0x1ee872c0, 0x644596fa,
		0x6df2b10e, 0xdaa4658e, 0x000d3505, 0xa834a026,
		0xb0a5b244, 0x4e40f345, 0xb2ee8bf6, 0x294992f4,
		0xf8d0e4f0, 0x948b9b86, 0x633ab27f, 0x8e085752,
		0x1432a534, 0x916b9416, 0x5c26e12b, 0xe979e9c1,
		0x813484c2, 0x4eee8d41, 0xb47f0a94, 0xf0202f42,
		0xb50f26b9, 0xf34c1f05, 0x6669bc56, 0x3041fe77,
	}
};










//
//	ForwardRoundD
//

void ForwardRoundD(SINOPLE_u32 &z0, SINOPLE_u32 &z1, SINOPLE_u32 &z2, SINOPLE_u32 &z3, SINOPLE_u32 const k)
{
	SINOPLE_u32 x0, x1, x2, x3;
	SINOPLE_u32 f0, f1;
	SINOPLE_u32 sk00, sk01, sk02;
	SINOPLE_u32 sk10, sk11, sk12;

	x0 = z0;
	x1 = z1;
	x2 = z2;
	x3 = z3;

	// Mix x3 with round key
	f0 = x3 ^ k;

	// Compress result
	f1 = _rotr(f0, 2) & 0x000000ff;
	f1 |= _rotr(f0, 4) & 0x0000ff00;
	f1 |= _rotr(f0, 6) & 0x00ff0000;

	// Go trough s-box
	sk00 = g_sbox[0][f1 & 0x000000ff];
	sk10 = g_sbox[1][f1 & 0x000000ff];
	f1 = _rotr(f1, 8);
	sk01 = g_sbox[0][f1 & 0x000000ff];
	sk11 = g_sbox[1][f1 & 0x000000ff];
	f1 = _rotr(f1, 8);
	sk02 = g_sbox[0][f1 & 0x000000ff];
	sk12 = g_sbox[1][f1 & 0x000000ff];

	// Apply to data
	z0 = _rotr(x3, 8);
	z1 = (x0 ^ sk00) + sk10;
	z2 = (x1 ^ sk01) + sk11;
	z3 = (x2 ^ sk02) + sk12;
}



//
//	BackwardRoundD
//

void BackwardRoundD(SINOPLE_u32 &z0, SINOPLE_u32 &z1, SINOPLE_u32 &z2, SINOPLE_u32 &z3, SINOPLE_u32 const k)
{
	SINOPLE_u32 x0, x1, x2, x3;
	SINOPLE_u32 f0, f1;
	SINOPLE_u32 sk00, sk01, sk02;
	SINOPLE_u32 sk10, sk11, sk12;

	// Copy input
	x0 = z0;
	x1 = z1;
	x2 = z2;
	x3 = z3;

	// Mix x3 with round key
	f0 = _rotl(x0, 8) ^ k;

	// Compress result
	f1 = _rotr(f0, 2) & 0x000000ff;
	f1 |= _rotr(f0, 4) & 0x0000ff00;
	f1 |= _rotr(f0, 6) & 0x00ff0000;

	// Go trough s-box
	sk00 = g_sbox[0][f1 & 0x000000ff];
	sk10 = g_sbox[1][f1 & 0x000000ff];
	f1 = _rotr(f1, 8);
	sk01 = g_sbox[0][f1 & 0x000000ff];
	sk11 = g_sbox[1][f1 & 0x000000ff];
	f1 = _rotr(f1, 8);
	sk02 = g_sbox[0][f1 & 0x000000ff];
	sk12 = g_sbox[1][f1 & 0x000000ff];

	// Apply to data
	z0 = (x1 - sk10) ^ sk00;
	z1 = (x2 - sk11) ^ sk01;
	z2 = (x3 - sk12) ^ sk02;
	z3 = _rotl(x0, 8);
}



//
//	ForwardRoundC
//

void ForwardRoundC(SINOPLE_u32 &z0, SINOPLE_u32 &z1, SINOPLE_u32 &z2, SINOPLE_u32 &z3, SINOPLE_u32 const k)
{
	SINOPLE_u32 x0, x1, x2, x3;
	SINOPLE_u32 f;
	SINOPLE_u32 sk0, sk1, sk2, sk3;

	/* Copy input */
	x0 = z0;
	x1 = z1;
	x2 = z2;
	x3 = z3;

	/* Mix x0 with round key */
	f = x0 ^ k;

	/* Go trough s-box */
	sk0 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk1 = g_sbox[1][f & 0x000000ff];
	f = _rotr(f, 8);
	sk2 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk3 = g_sbox[1][f & 0x000000ff];

	/* Apply to data */
	z0 = (((x3 ^ sk3) + sk2) ^ sk1) + sk0;

	/* Mix x1 with round key */
	f = x1 ^ k;

	/* Go trough s-box */
	sk0 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk1 = g_sbox[1][f & 0x000000ff];
	f = _rotr(f, 8);
	sk2 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk3 = g_sbox[1][f & 0x000000ff];

	/* Apply to data */
	z0 = (((z0 ^ sk3) + sk2) ^ sk1) + sk0;

	/* Mix x2 with round key */
	f = x2 ^ k;

	/* Go trough s-box */
	sk0 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk1 = g_sbox[1][f & 0x000000ff];
	f = _rotr(f, 8);
	sk2 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk3 = g_sbox[1][f & 0x000000ff];

	/* Apply to data */
	z0 = (((z0 ^ sk3) + sk2) ^ sk1) + sk0;

	/* Rotation */
	z1 = _rotr(x0, 8);
	z2 = _rotr(x1, 8);
	z3 = _rotr(x2, 8);
}



//
//	BackwardRoundC
//

void BackwardRoundC(SINOPLE_u32 &z0, SINOPLE_u32 &z1, SINOPLE_u32 &z2, SINOPLE_u32 &z3, SINOPLE_u32 const k)
{
	SINOPLE_u32 x0, x1, x2, x3;
	SINOPLE_u32 f;
	SINOPLE_u32 sk0, sk1, sk2, sk3;

	/* Copy input */
	x0 = z0;
	x1 = z1;
	x2 = z2;
	x3 = z3;

	/* Mix x3 with round key */
	f = _rotl(x3, 8) ^ k;

	/* Go trough s-box */
	sk0 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk1 = g_sbox[1][f & 0x000000ff];
	f = _rotr(f, 8);
	sk2 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk3 = g_sbox[1][f & 0x000000ff];

	/* Apply to data */
	z3 = (((x0 - sk0) ^ sk1) - sk2) ^ sk3;

	/* Mix x2 with round key */
	f = _rotl(x2, 8) ^ k;

	/* Go trough s-box */
	sk0 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk1 = g_sbox[1][f & 0x000000ff];
	f = _rotr(f, 8);
	sk2 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk3 = g_sbox[1][f & 0x000000ff];

	/* Apply to data */
	z3 = (((z3 - sk0) ^ sk1) - sk2) ^ sk3;

	/* Mix x1 with round key */
	f = _rotl(x1, 8) ^ k;

	/* Go trough s-box */
	sk0 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk1 = g_sbox[1][f & 0x000000ff];
	f = _rotr(f, 8);
	sk2 = g_sbox[0][f & 0x000000ff];
	f = _rotr(f, 8);
	sk3 = g_sbox[1][f & 0x000000ff];

	/* Apply to data */
	z3 = (((z3 - sk0) ^ sk1) - sk2) ^ sk3;

	/* Rotation */
	z0 = _rotl(x1, 8);
	z1 = _rotl(x2, 8);
	z2 = _rotl(x3, 8);
}



//
//	SINOPLE_KeySetup
//

void SINOPLE_KeySetup(const SINOPLE_u32* const puiKey, SINOPLE_ExpandedKey* const pExpandedKey)
{
	SINOPLE_u32	uiKeyBuffer[4];

	/* Copy key to temporary storage */
	uiKeyBuffer[0] = puiKey[0];
	uiKeyBuffer[1] = puiKey[1];
	uiKeyBuffer[2] = puiKey[2];
	uiKeyBuffer[3] = puiKey[3];

	for(SINOPLE_u32 i = 0; i < 16; i++)
	{
		/* Mix key using 16 D-type round, use the loop counter as key */
		for(SINOPLE_u32 j = 0; j < 16; j++)
		{
			ForwardRoundD(uiKeyBuffer[0], uiKeyBuffer[1], uiKeyBuffer[2], uiKeyBuffer[3], i);
		}

		/* Store created sub-keys */
		pExpandedKey->k[i * 4] = uiKeyBuffer[0];
		pExpandedKey->k[(i * 4) + 1] = uiKeyBuffer[1];
		pExpandedKey->k[(i * 4) + 2] = uiKeyBuffer[2];
		pExpandedKey->k[(i * 4) + 3] = uiKeyBuffer[3];
	}
}



//
//	SINOPLE_Encrypt
//

void SINOPLE_Encrypt(const SINOPLE_ExpandedKey* const pExpandedKey, const SINOPLE_u32* const piPlainText, SINOPLE_u32* const piCipherText)
{
	const SINOPLE_u32*		piIn = piPlainText;
	SINOPLE_u32*			piOut = piCipherText;
	SINOPLE_u32				iKeyIndex = 0;
	SINOPLE_u32				i;

	piOut[0] = piIn[0];
	piOut[1] = piIn[1];
	piOut[2] = piIn[2];
	piOut[3] = piIn[3];

	// 16 D-type rounds
	for(i = 0; i < 16; i++)
	{
		ForwardRoundD(piOut[0], piOut[1], piOut[2], piOut[3], pExpandedKey->k[iKeyIndex]);
		iKeyIndex++;
	}

	// 16 C-type rounds
	for(i = 0; i < 16; i++)
	{
		ForwardRoundC(piOut[0], piOut[1], piOut[2], piOut[3], pExpandedKey->k[iKeyIndex]);
		iKeyIndex++;
	}

	// 16 D-type rounds
	for(i = 0; i < 16; i++)
	{
		ForwardRoundD(piOut[0], piOut[1], piOut[2], piOut[3], pExpandedKey->k[iKeyIndex]);
		iKeyIndex++;
	}

	// 16 C-type rounds
	for(i = 0; i < 16; i++)
	{
		ForwardRoundC(piOut[0], piOut[1], piOut[2], piOut[3], pExpandedKey->k[iKeyIndex]);
		iKeyIndex++;
	}
}



//
//	SINOPLE_Decrypt
//

void SINOPLE_Decrypt(const SINOPLE_ExpandedKey* const pExpandedKey, const SINOPLE_u32* const piCipherText, SINOPLE_u32* const piPlainText)
{
	const SINOPLE_u32*		piIn = piCipherText;
	SINOPLE_u32*			piOut = piPlainText;
	SINOPLE_u32				iKeyIndex = 63;
	SINOPLE_u32				i;

	piOut[0] = piIn[0];
	piOut[1] = piIn[1];
	piOut[2] = piIn[2];
	piOut[3] = piIn[3];

	// 16 C-type rounds
	for(i = 0; i < 16; i++)
	{
		BackwardRoundC(piOut[0], piOut[1], piOut[2], piOut[3], pExpandedKey->k[iKeyIndex]);
		iKeyIndex--;
	}

	// 16 D-type rounds
	for(i = 0; i < 16; i++)
	{
		BackwardRoundD(piOut[0], piOut[1], piOut[2], piOut[3], pExpandedKey->k[iKeyIndex]);
		iKeyIndex--;
	}

	// 16 C-type rounds
	for(i = 0; i < 16; i++)
	{
		BackwardRoundC(piOut[0], piOut[1], piOut[2], piOut[3], pExpandedKey->k[iKeyIndex]);
		iKeyIndex--;
	}

	// 16 D-type rounds
	for(i = 0; i < 16; i++)
	{
		BackwardRoundD(piOut[0], piOut[1], piOut[2], piOut[3], pExpandedKey->k[iKeyIndex]);
		iKeyIndex--;
	}
}
