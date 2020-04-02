#ifndef LENGTHFORMATTER_H
#define LENGTHFORMATTER_H

#include <stdio.h>
#include <iostream>
#include <Utility.h>

#include <Poco/NumberFormatter.h>

using namespace std;
using namespace Poco;

// Length Format
#define _NONE -1
#define _HEX 0
#define _EBCDIC 1
#define _BINARY 2
#define _BCD 3

// Length Type
#define _FIXED 0     /* Fixed              */
#define _LVAR 1      /* Variable - 0..9  */
#define _LLVAR 2     /* Variable - 0..99   */
#define _LLLVAR 3    /* Variable - 0..999  */
#define _LLLLVAR 4   /* Variable - 0..9999 */
#define _LLLLLVAR 5  /* Variable - 0..99999 */
#define _LLLLLLVAR 6 /* Variable - 0..999999 */

class LengthFormatter
{
public:
    LengthFormatter();
    LengthFormatter(int llenType, int llenFormat, bool ppadZeroLeft, int mmaxlen);
    ~LengthFormatter();
    //
    int getLenType();
    void setLenType(int llenType);
    //
    int getLenFormat();
    void setLenFormat(int llenFormat);
    //
    bool getPadZeroLeft();
    void setPadZeroLeft(bool padZeroLeft);
    //
    int getMaxLen();
    void setMaxLen(int mmaxlen);
    //
    string getFormattedLength(int len);

private:
    int lenType;
    int lenFormat;
    bool padZeroLeft;
    int maxlen;
};

/*******************************************************************************
 *
 * 
 ******************************************************************************/
LengthFormatter::LengthFormatter()
{
}
/*******************************************************************************
 *
 * 
 ******************************************************************************/
LengthFormatter::LengthFormatter(int llenType, int llenFormat, bool ppadZeroLeft, int mmaxlen)
{
    lenType = llenType;
    lenFormat = llenFormat;
    padZeroLeft = ppadZeroLeft;
    maxlen = mmaxlen;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
LengthFormatter::~LengthFormatter()
{
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int LengthFormatter::getLenFormat()
{
    return lenFormat;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
void LengthFormatter::setLenFormat(int llenFormat)
{
    lenFormat = llenFormat;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int LengthFormatter::getLenType()
{
    return lenType;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
void LengthFormatter::setLenType(int llenType)
{
    lenType = llenType;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool LengthFormatter::getPadZeroLeft()
{
    return padZeroLeft;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
void LengthFormatter::setPadZeroLeft(bool ppadZeroLeft)
{
    padZeroLeft = ppadZeroLeft;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int LengthFormatter::getMaxLen()
{
    return maxlen;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
void LengthFormatter::setMaxLen(int mmaxLen)
{
    maxlen = mmaxLen;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string LengthFormatter::getFormattedLength(int len)
{
    string str_datalen;
    string byte_datalen;

    str_datalen = NumberFormatter::format0(len, lenType);

    if (lenFormat == _HEX)
    {
        byte_datalen = str_datalen;
    }
    else if (lenFormat == _BINARY)
    {
        if ((str_datalen.length() % 2) != 0)
        {
            str_datalen = "0" + str_datalen;
        }
        byte_datalen = Utility::str2bcd(str_datalen);
    }
    else if (lenFormat == _BCD)
    {
        str_datalen = NumberFormatter::formatHex(len);
        str_datalen = Utility::resize(str_datalen, lenType, "0", false);
        if ((str_datalen.length() % 2) != 0)
        {
            str_datalen = "0" + str_datalen;
        }
        byte_datalen = Utility::str2bcd(str_datalen);
    }
    else
    {
        byte_datalen = str_datalen;
    }

    return byte_datalen;
}
#endif