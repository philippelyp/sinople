//
//
//  Copyright (C) 2001,2003 Philippe Paquet. All rights reserved.
//
//
//	scrypt.cpp
//
//	Simple encryption/decryption program using the reference implementation of Sinople
//
//	Who				When		What
//	--------------------------------------------------------------------
//	P. Paquet		17 Aug 01	Creation of Sinople
//	P. Paquet		09 Fev 03	Release
//










//
//	Includes
//

#include <io.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "sinople.h"
#include "md5.h"










//
//	Defines
//

#define PASSPHRASE_MAXIMUM_LENGTH			60
#define PASSPHRASE_MINIMUM_LENGTH			8










//
//	Program flags
//

bool	bDecryption = false;				// Decryption
bool	bEncryption = false;				// Encryption
bool	bPauseAfterEachPage = false;		// Pause after each message page
bool	bDisplayHelp = false;				// Display help










//
//	Globals
//

int		iNumberOfLine = 0;










//
//	Pause
//

void Pause(void)
{
	if(true == bPauseAfterEachPage)
	{
		if(23 == ++iNumberOfLine)
		{
			iNumberOfLine = 0;
			printf("Press any key to continue...\n");
			if(0 == getch())
			{
				getch();
			}
		}
	}
}



//
//	DisplayVersion
//

void DisplayVersion(void)
{
	printf("\n");
	Pause();
	printf("SCrypt Version 1.00 By Philippe Paquet\n");
	Pause();
	printf("\n");
	Pause();
	printf("Compiled on %s\n", __TIMESTAMP__);
	Pause();
}



//
//	DisplayHelp
//

void DisplayHelp(void)
{
	printf("\n");
	Pause();
	printf("Usage: SCrypt {<switches>} <inputfile> <outputfile>\n");
	Pause();
	printf("\n");
	Pause();
	printf("Switches :");
	Pause();
	printf("\n");
	Pause();
	printf("  /e        Encryption\n");
	Pause();
	printf("  /d        Decryption\n");
	Pause();
	printf("  /p        Pause after each message page\n");
	Pause();
	printf("  /h        Display help\n");
	Pause();
	printf("\n");
	Pause();
	printf("\n");
	Pause();
	printf("SCrypt is using the reference implementation of\n");
	Pause();
	printf("Sinople, a 128-bit bloc cipher by Philippe Paquet.\n");
	Pause();
	printf("\n");
	Pause();
	printf("CBC is used as bloc chaining mode and the passphrase hashing\n");
	Pause();
	printf("function is RSA Data Security, Inc. MD5 Message Digest Algorithm.\n");
	Pause();
}



//
//	GetPassword
//

void GetPassphrase(char* const achPassphrase, int iLength)
{
	int		iCharacterIndex = 0;
	char	chCurrentChar = 0;

	memset(achPassphrase, 0, iLength);

	do
	{
		chCurrentChar = getch();

		if(0 == chCurrentChar)
		{
			getch();
		}
		else
		{
			if((chCurrentChar != 0x0D) && (iCharacterIndex < (iLength - 1)))
			{
				printf("*");

				achPassphrase[iCharacterIndex] = chCurrentChar;
				iCharacterIndex++;
			}
		}
	}
	while(chCurrentChar != 0x0D);
	printf("\n");

	// Clear passphare informations
	iCharacterIndex = 0;
	chCurrentChar = 0;
}



//
//	ParseCommandLine
//
//	Parse the command line, sets global variables, etc...
//

void ParseCommandLine(int argc, char *argv[])
{
	int		i;

	for(i = 1; i < argc; i++)
	{
		_strupr(argv[i]);

		if(0 == strcmp(argv[i], "/E"))
		{
			bEncryption = true;
		}

		if(0 == strcmp(argv[i], "/D"))
		{
			bDecryption = true;
		}

		if(0 == strcmp(argv[i], "/P"))
		{
			bPauseAfterEachPage = true;
		}

		if(0 == strcmp(argv[i], "/H"))
		{
			bDisplayHelp = true;
		}
	}
}



//
//	main
//

int main(int argc, char *argv[])
{
	int		iErrorCode = 0;

	DisplayVersion();

	if(1 == argc)
	{
		DisplayHelp();
	}
	else
	{
		// Parse all the stuff...
		ParseCommandLine(argc, argv);

		// Check that we ask encryption or decryption
		if(((true == bEncryption) && (true == bDecryption)) || ((false == bEncryption) && (false == bDecryption)))
		{
			bDisplayHelp = true;
		}

		// Display help
		if(true == bDisplayHelp)
		{
			DisplayHelp();
			return 1;
		}

		// Get passphrase
		char		achPassphrase[PASSPHRASE_MAXIMUM_LENGTH];
		char		achPassphraseConfirmation[PASSPHRASE_MAXIMUM_LENGTH];

		printf("\n");
		printf("Enter passphrase : ");
		GetPassphrase(achPassphrase, PASSPHRASE_MAXIMUM_LENGTH);
		printf("Confirmation : ");
		GetPassphrase(achPassphraseConfirmation, PASSPHRASE_MAXIMUM_LENGTH);

		// Check that passphrase & confirmation match
		if(strcmp(achPassphrase, achPassphraseConfirmation) != 0)
		{
			// Doesn't match !!!
			printf("\n");
			printf("Passphrase entries does not match !!!\n");

			// Clear passphare
			memset(achPassphrase, 0, PASSPHRASE_MAXIMUM_LENGTH);
			memset(achPassphraseConfirmation, 0, PASSPHRASE_MAXIMUM_LENGTH);

			return 2;
		}

		// Check that passphrase is long enough
		if(strlen(achPassphrase) < PASSPHRASE_MINIMUM_LENGTH)
		{
			// Too short !!!
			printf("\n");
			printf("Passphrase must be at least %u characters !!!\n", PASSPHRASE_MINIMUM_LENGTH);

			// Clear passphare
			memset(achPassphrase, 0, PASSPHRASE_MAXIMUM_LENGTH);
			memset(achPassphraseConfirmation, 0, PASSPHRASE_MAXIMUM_LENGTH);

			return 3;
		}

		// Compute md5
		MD5_CTX		md5Context;

		MD5Init(&md5Context);
		MD5Update(&md5Context, (unsigned char *)&achPassphrase[0], strlen(achPassphrase));
		MD5Final(&md5Context);
		
		// Clear passphare
		memset(achPassphrase, 0, PASSPHRASE_MAXIMUM_LENGTH);
		memset(achPassphraseConfirmation, 0, PASSPHRASE_MAXIMUM_LENGTH);

		// Expand Sinople key
		SINOPLE_ExpandedKey		SinopleExpandedKey;

		SINOPLE_KeySetup((unsigned int*)md5Context.digest, &SinopleExpandedKey);
		
		// Clear md5 context
		memset(&md5Context, 0, sizeof(md5Context));

		// Open file
		int	hInputFilehandle = _open(argv[argc - 2], _O_RDONLY | _O_BINARY);
		if(NULL == hInputFilehandle)
		{
			// Can't open input file
			printf("Can't open file \"%s\".\n", argv[argc - 2]);
			Pause();
			iErrorCode = 4;
		}
		else
		{
			// Go to the end of the file to get the size
			if(-1 == _lseek(hInputFilehandle, 0L, SEEK_END))
			{
				// Can't seek within input file
				printf("Can't seek in file \"%s\".\n", argv[argc - 2]);
				Pause();
				iErrorCode = 5;
			}
			else
			{
				long lFileSize = _tell(hInputFilehandle);

				// Go to the beginning of the file
				if(-1 == _lseek(hInputFilehandle, 0L, SEEK_SET))
				{
					// Can't seek within input file
					printf("Can't seek in file \"%s\".\n", argv[argc - 2]);
					Pause();
					iErrorCode = 6;
				}
				else
				{
					if(true == bEncryption)
					{
						// Compute needed memory size
						long lFileSizeFixed = (lFileSize + 15) & ~15;

						// Allocate memory
						unsigned int* puiFile = (unsigned int *)malloc(lFileSizeFixed);

						if(puiFile != NULL)
						{
							// Can't allocate memory
							printf("Can't allocate memory.\n");
							Pause();
							iErrorCode = 7;
						}
						else
						{
							// Clear memory
							memset(puiFile, 0, lFileSizeFixed);

							if(_read(hInputFilehandle, puiFile, lFileSize) != lFileSize)
							{
								// Can't read input file
								printf("Can't read file \"%s\".\n", argv[argc - 2]);
								Pause();
								iErrorCode = 8;
							}
							else
							{
								// Encrypt using CBC
								printf("\n");
								printf("Encrypting...\n");

								unsigned int uiCbcBuffer[4];

								uiCbcBuffer[0] = 0;
								uiCbcBuffer[1] = 0;
								uiCbcBuffer[2] = 0;
								uiCbcBuffer[3] = 0;

								unsigned int* puiFileIndex = puiFile;

								for(int i = 0; i < (lFileSizeFixed / 16); i++)
								{
									puiFileIndex[0] ^= uiCbcBuffer[0];
									puiFileIndex[1] ^= uiCbcBuffer[1];
									puiFileIndex[2] ^= uiCbcBuffer[2];
									puiFileIndex[3] ^= uiCbcBuffer[3];

									SINOPLE_Encrypt(&SinopleExpandedKey, (const SINOPLE_u32*)puiFileIndex, puiFileIndex);

									uiCbcBuffer[0] = puiFileIndex[0];
									uiCbcBuffer[1] = puiFileIndex[1];
									uiCbcBuffer[2] = puiFileIndex[2];
									uiCbcBuffer[3] = puiFileIndex[3];

									puiFileIndex += 4;
								}

								printf("Done !\n");

								// Open output file
								int	hOutputFilehandle = _open(argv[argc - 1], _O_CREAT | _O_WRONLY | _O_BINARY);
								if(NULL == hOutputFilehandle)
								{
									// Can't open output file
									printf("Can't open file \"%s\".\n", argv[argc - 1]);
									Pause();
									iErrorCode = 9;
								}
								else
								{

									// Go to the beginning of the file
									if(-1 == _lseek(hOutputFilehandle, 0L, SEEK_SET))
									{
										// Can't seek within output file
										printf("Can't seek in file \"%s\".\n", argv[argc - 1]);
										Pause();
										iErrorCode = 10;
									}
									else
									{
										if(_write(hOutputFilehandle, &lFileSize, sizeof(long)) != sizeof(long))
										{
											// Can't write file
											printf("Can't write file \"%s\".\n", argv[argc - 1]);
											Pause();
											iErrorCode = 11;
										}
										else
										{
											if(_write(hOutputFilehandle, puiFile, lFileSizeFixed) != lFileSizeFixed)
											{
												// Can't write file
												printf("Can't write file \"%s\".\n", argv[argc - 1]);
												Pause();
												iErrorCode = 12;
											}
										}
									}

									// Close output file
									_close(hOutputFilehandle);
								}
							}

							// Clear file
							memset(puiFile, 0, lFileSizeFixed);

							// Free memory
							free(puiFile);
						}
					}
					else
					{
						// Using a real file size for decryption
						long lFileSizeReal = 0;

						if(_read(hInputFilehandle, &lFileSizeReal, sizeof(long)) != sizeof(long))
						{
							// Can't read input file
							printf("Can't read file \"%s\".\n", argv[argc - 2]);
							Pause();
							iErrorCode = 13;
						}
						else
						{
							// Compute needed memory size
							long lFileSizeFixed = lFileSize - sizeof(long);

							// Allocate memory
							unsigned int* puiFile = (unsigned int *)malloc(lFileSizeFixed);

							if(puiFile != NULL)
							{
								// Can't allocate memory
								printf("Can't allocate memory.\n");
								Pause();
								iErrorCode = 14;
							}
							else
							{
								if(_read(hInputFilehandle, puiFile, lFileSizeFixed) != lFileSizeFixed)
								{
									// Can't read input file
									printf("Can't read file \"%s\".\n", argv[argc - 2]);
									Pause();
									iErrorCode = 15;
								}
								else
								{
									// Decrypt using CBC
									printf("\n");
									printf("Decrypting...\n");

									unsigned int uiCbcBuffer1[4];
									unsigned int uiCbcBuffer2[4];

									uiCbcBuffer1[0] = 0;
									uiCbcBuffer1[1] = 0;
									uiCbcBuffer1[2] = 0;
									uiCbcBuffer1[3] = 0;

									unsigned int* puiFileIndex = puiFile;

									for(int i = 0; i < (lFileSizeFixed / 16); i++)
									{
										uiCbcBuffer2[0] = puiFileIndex[0];
										uiCbcBuffer2[1] = puiFileIndex[1];
										uiCbcBuffer2[2] = puiFileIndex[2];
										uiCbcBuffer2[3] = puiFileIndex[3];

										SINOPLE_Decrypt(&SinopleExpandedKey, puiFileIndex, puiFileIndex);

										puiFileIndex[0] ^= uiCbcBuffer1[0];
										puiFileIndex[1] ^= uiCbcBuffer1[1];
										puiFileIndex[2] ^= uiCbcBuffer1[2];
										puiFileIndex[3] ^= uiCbcBuffer1[3];

										uiCbcBuffer1[0] = uiCbcBuffer2[0];
										uiCbcBuffer1[1] = uiCbcBuffer2[1];
										uiCbcBuffer1[2] = uiCbcBuffer2[2];
										uiCbcBuffer1[3] = uiCbcBuffer2[3];

										puiFileIndex += 4;
									}

									printf("Done !\n");

									// Open output file
									int	hOutputFilehandle = _open(argv[argc - 1], _O_CREAT | _O_WRONLY | _O_BINARY);
									if(NULL == hOutputFilehandle)
									{
										// Can't open output file
										printf("Can't open file \"%s\".\n", argv[argc - 1]);
										Pause();
										iErrorCode = 16;
									}
									else
									{
										// Go to the beginning of the file
										if(-1 == _lseek(hOutputFilehandle, 0L, SEEK_SET))
										{
											// Can't seek within output file
											printf("Can't seek in file \"%s\".\n", argv[argc - 1]);
											Pause();
											iErrorCode = 17;
										}
										else
										{
											if(_write(hOutputFilehandle, puiFile, lFileSizeReal) != lFileSizeReal)
											{
												// Can't write file
												printf("Can't write file \"%s\".\n", argv[argc - 1]);
												Pause();
												iErrorCode = 18;
											}
										}

										// Close output file
										_close(hOutputFilehandle);
									}
							
								}

								// Clear file
								memset(puiFile, 0, lFileSizeFixed);

								// Free memory
								free(puiFile);
							}
						}
					}
				}
			}

			// Close input file
			_close(hInputFilehandle);
		}

		// Clear Sinople expanded key
		memset(&SinopleExpandedKey, 0, sizeof(SinopleExpandedKey));
	}

	return iErrorCode;
}
