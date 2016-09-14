#include "stdafx.h"
#include <string>

#include "StringReverse.h"
using namespace std;

BOOL StringReverseW(PWSTR pWideCharStr)
{
   //Get a pointer to the last character in the string.
   PWSTR pEndOfStr=pWideCharStr+wcslen(pWideCharStr)-1;
   wchar_t cCharT;

   //Repeat until we reach the center character
   //in the string.
   while (pWideCharStr < pEndOfStr)
   {
      //Save a character in a temporary variable.
      cCharT=*pWideCharStr;
      
      //Put the last character in the first character.
      *pWideCharStr =*pEndOfStr;
   
      //Put the temporary character in the last character.
      *pEndOfStr=cCharT;
   
      //Move in one character from the left.
      pWideCharStr++;
   
      //Move in one character from the right.
      pEndOfStr--;
   }
   //The string is reversed; return success.
   return(TRUE);
}





BOOL StringReverseA(PSTR pMultiByteStr) 
{
   PWSTR pWideCharStr;
   int nLenOfWideCharStr;
   BOOL fOk = FALSE;

   //Calculate the number of characters needed to hold
   //the wide_character version of string.
   nLenOfWideCharStr = MultiByteToWideChar(CP_ACP, 0,
      pMultiByteStr, -1, NULL, 0);

   //Allocate memory from the process's default heap to 
   //accommodate the size of the wide-character string.
   //Don't forget that MultiByteToWideChar returns the 
   //number of characters,not the number of bytes,so
   //you must multiply by the size of wide character.
   pWideCharStr = (PWSTR)HeapAlloc(GetProcessHeap(), 0, 
      nLenOfWideCharStr * sizeof(WCHAR));

   if (pWideCharStr == NULL)
      return(fOk);

   //Convert the multibyte string to a wide_character string.
   MultiByteToWideChar(CP_ACP, 0, pMultiByteStr, -1, 
      pWideCharStr, nLenOfWideCharStr);

   //Call the wide-character version of this 
   //function to do the actual work 
   fOk = StringReverseW(pWideCharStr);
   if (fOk)
   {
      //Convert the wide-character string back 
      //to a multibyte string.
      WideCharToMultiByte(CP_ACP, 0, pWideCharStr, -1, 
         pMultiByteStr, strlen(pMultiByteStr), NULL, NULL);
   }

   //Free the momory containing the wide-character string.
   HeapFree(GetProcessHeap(), 0, pWideCharStr);

   return(fOk);
}



wstring ANSIToUnicode( const string& str )
{
	 int  len = 0;
	 len = str.length();
	 int  unicodeLen = ::MultiByteToWideChar( CP_ACP,
				0,
				str.c_str(),
				-1,
				NULL,
				0 );  
	 wchar_t *  pUnicode;  
	 pUnicode = new  wchar_t[unicodeLen+1];  
	 memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	 ::MultiByteToWideChar( CP_ACP,
			 0,
			 str.c_str(),
			 -1,
			 (LPWSTR)pUnicode,
			 unicodeLen );  
	 wstring  rt;  
	 rt = ( wchar_t* )pUnicode;
	 delete  pUnicode; 
 
	 return  rt;  
}

string UnicodeToANSI( const wstring& str )
{
	 char*     pElementText;
	 int    iTextLen;
	 // wide char to multi char
	 iTextLen = WideCharToMultiByte( CP_ACP,
			 0,
			 str.c_str(),
			 -1,
			 NULL,
			 0,
	NULL,
			 NULL );
	 pElementText = new char[iTextLen + 1];
	 memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	 ::WideCharToMultiByte( CP_ACP,
			 0,
			 str.c_str(),
			 -1,
			 pElementText,
			 iTextLen,
			 NULL,
			 NULL );
	 string strText;
	 strText = pElementText;
	 delete[] pElementText;
	 return strText;
}

wstring UTF8ToUnicode( const string& str )
{
	 int  len = 0;
	 len = str.length();
	 int  unicodeLen = ::MultiByteToWideChar( CP_UTF8,
				0,
				str.c_str(),
				-1,
				NULL,
				0 );  
	 wchar_t *  pUnicode;  
	 pUnicode = new  wchar_t[unicodeLen+1];  
	 memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	 ::MultiByteToWideChar( CP_UTF8,
			 0,
			 str.c_str(),
			 -1,
			 (LPWSTR)pUnicode,
			 unicodeLen );  
	 wstring  rt;  
	 rt = ( wchar_t* )pUnicode;
	 delete  pUnicode; 
 
	 return  rt;  
}
  
string UnicodeToUTF8( const wstring& str )
{
	 char*     pElementText;
	 int    iTextLen;
	 // wide char to multi char
	 iTextLen = WideCharToMultiByte( CP_UTF8,
			 0,
			 str.c_str(),
			 -1,
			 NULL,
			 0,
			 NULL,
			 NULL );
	 pElementText = new char[iTextLen + 1];
	 memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	 ::WideCharToMultiByte( CP_UTF8,
			 0,
			 str.c_str(),
			 -1,
			 pElementText,
			 iTextLen,
			 NULL,
			 NULL );
	 string strText;
	 strText = pElementText;
	 delete[] pElementText;
	 return strText;
}