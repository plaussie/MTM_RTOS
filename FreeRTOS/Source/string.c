#include "string.h"

#define NULL 0

void CopyString(char pcSource[],char pcDestination[]) {
    
    unsigned char ucLicznikZnaku;
    
    for(ucLicznikZnaku=0;pcSource[ucLicznikZnaku]!=NULL;ucLicznikZnaku++) {    
        pcDestination[ucLicznikZnaku]=pcSource[ucLicznikZnaku];
    }
    pcDestination[ucLicznikZnaku]=pcSource[ucLicznikZnaku];
}

enum CompResult eCompareString(char pcStr1[],char pcStr2[]) {
    
    unsigned char ucLicznikZnaku;
    
    for(ucLicznikZnaku=0;pcStr1[ucLicznikZnaku]==pcStr2[ucLicznikZnaku];ucLicznikZnaku++) {
        if(NULL==pcStr1[ucLicznikZnaku]) {
            return EQUAL;
        }
    }
    return DIFFERENT;
}

void AppendString(char pcSourceStr[],char pcDestinationStr[]) {
    
    unsigned char ucLicznikZnaku;
    
    for(ucLicznikZnaku=0;pcDestinationStr[ucLicznikZnaku]!=NULL;ucLicznikZnaku++) {}
    CopyString(pcSourceStr,pcDestinationStr+ucLicznikZnaku);
}

void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar){
    
    unsigned char ucLicznikZnaku;
    
    for(ucLicznikZnaku=0;pcString[ucLicznikZnaku]!=NULL;ucLicznikZnaku++) {
        if(cOldChar==pcString[ucLicznikZnaku]){
            pcString[ucLicznikZnaku]=cNewChar;
        }
    }        
}

/////////////

void UIntToHexStr(unsigned int uiValue, char pcStr[]){
	
	unsigned char ucNibbleCounter;
	unsigned char ucCurrentNibble;
	
	pcStr[0]='0';
	pcStr[1]='x';
	pcStr[6]=NULL;
	
	for(ucNibbleCounter=0; ucNibbleCounter<4; ucNibbleCounter++){
		ucCurrentNibble=(uiValue >> (ucNibbleCounter*4))&0x0F;
		if(ucCurrentNibble<10){
			pcStr[5-ucNibbleCounter] = '0'+ucCurrentNibble;
		} 
		else{
			pcStr[5-ucNibbleCounter] = 'A'+(ucCurrentNibble-10);
		}
	}
}
 
 
enum Result {OK, ERROR};

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue){
	
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	
	*puiValue=0;
	
	if((pcStr[0]!='0') || (pcStr[1]!='x') || (pcStr[2]==NULL)){
		return ERROR;
	}
	for(ucCharacterCounter=2; ucCharacterCounter<7; ucCharacterCounter++){
		ucCurrentCharacter = pcStr[ucCharacterCounter];
		if(ucCurrentCharacter==NULL){
			return OK;
		}
		else if(ucCharacterCounter==6){
			return ERROR;
		}
		*puiValue = *puiValue << 4;
		if((ucCurrentCharacter <= '9') && (ucCurrentCharacter >= '0')){
			ucCurrentCharacter = ucCurrentCharacter-'0';
		}
		else if((ucCurrentCharacter <= 'F') && (ucCurrentCharacter >= 'A')){
			ucCurrentCharacter = ucCurrentCharacter-'A'+10;
		}
		else{
			return ERROR;
		}
		*puiValue = (*puiValue) | ucCurrentCharacter;
	}
	return ERROR;
}

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]){
	
	unsigned char ucIndeksKonca;

	for(ucIndeksKonca=0; pcDestinationStr[ucIndeksKonca]!=NULL; ucIndeksKonca++){}
	UIntToHexStr(uiValue, &pcDestinationStr[ucIndeksKonca]);
}
