//
//
//  Copyright (C) 2001,2003 Philippe Paquet. All rights reserved.
//
//
//	Sinople.h
//
//	Reference implementation of Sinople
//
//	Who				When		What
//	--------------------------------------------------------------------
//	P. Paquet		17 Aug 01	Creation of Sinople
//	P. Paquet		09 Fev 03	Release
//

#include <limits.h>			// limits.h is included to use UINT_MAX









//
//	Type definitions
//

#if UINT_MAX >= 4294967295UL

typedef signed short	SINOPLE_s16;
typedef signed int		SINOPLE_s32;
typedef unsigned short	SINOPLE_u16;
typedef unsigned int	SINOPLE_u32;

#else

typedef signed int		SINOPLE_s16;
typedef signed long		SINOPLE_s32;
typedef unsigned int	SINOPLE_u16;
typedef unsigned long	SINOPLE_u32;

#endif









//
//	Definitions
//

typedef struct
{
	SINOPLE_u32	k[64];
}
SINOPLE_ExpandedKey;










//
//	Prototypes
//

void SINOPLE_KeySetup(const SINOPLE_u32* const puiKey, SINOPLE_ExpandedKey* const pExpandedKey);
void SINOPLE_Encrypt(const SINOPLE_ExpandedKey* const pExpandedKey, const SINOPLE_u32* const piPlainText, SINOPLE_u32* const piCipherText);
void SINOPLE_Decrypt(const SINOPLE_ExpandedKey* const pExpandedKey, const SINOPLE_u32* const piCipherText, SINOPLE_u32* const piPlainText);
