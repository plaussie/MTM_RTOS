enum CompResult {DIFFERENT,EQUAL};

enum CompResult eCompareString(char pcStr1[],char pcStr2[]);
void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar);
void AppendString(char pcSourceStr[],char pcDestinationStr[]);
void UIntToHexStr(unsigned int uiValue, char pcStr[]);
enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue);
void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]);
void CopyString(char pcSource[],char pcDestination[]);
