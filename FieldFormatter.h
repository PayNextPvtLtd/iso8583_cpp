#ifndef FIELDFORMATTER_H
#define FIELDFORMATTER_H

#include <stdio.h>
#include <iostream>
#include <Utility.h>

#include <Poco/NumberFormatter.h>

#include "LengthFormatter.h"

using namespace std;
using namespace Poco;

#define _HEX 0
#define _EBCDIC 1
#define _BINARY 2

class FieldFormatter
{
private:
    int dataType;
    string padText;
    bool isFixedLen;
    bool padRight;
    int maxlen;

public:
FieldFormatter();
    FieldFormatter(int fdataType, string fpadText, bool fisFixedLen, bool fpadRight, int fmaxlen);
    ~FieldFormatter();
    //
    int getDataType();
    void setDataType(int fdatatype);
    //
    string getPadText();
    void setPadText(string fpadText);
    //
    bool getIsFixedLen();
    void setIsFixedLen(bool fisFixedLen);
    //
    bool getPadRight();
    void setPadRight(bool fpadRight);
    //
    int getMaxLen();
    void setMaxLen(int fmaxLen);
    //
    string getFormattedContent(string data);
};

/*******************************************************************************
 *
 * 
 ******************************************************************************/
FieldFormatter::FieldFormatter()
{
}
/*******************************************************************************
 *
 * 
 ******************************************************************************/
FieldFormatter::FieldFormatter(int fdataType, string fpadText, bool fisFixedLen, bool fpadRight, int fmaxlen)
{
    dataType = fdataType;
    padText = fpadText;
    isFixedLen = fisFixedLen;
    padRight = fpadRight;
    maxlen = fmaxlen;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
FieldFormatter::~FieldFormatter()
{
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int FieldFormatter::getDataType()
{
    return dataType;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
void FieldFormatter::setDataType(int fdatatype)
{
    dataType = fdatatype;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string FieldFormatter::getPadText()
{
    return padText;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
void FieldFormatter::setPadText(string fpadText)
{
    padText = fpadText;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool FieldFormatter::getIsFixedLen()
{
    return isFixedLen;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
void FieldFormatter::setIsFixedLen(bool fisFixedLen)
{
    isFixedLen = fisFixedLen;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool FieldFormatter::getPadRight()
{
    return padRight;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
void FieldFormatter::setPadRight(bool fpadRight)
{
    padRight = fpadRight;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int FieldFormatter::getMaxLen()
{
    return maxlen;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
void FieldFormatter::setMaxLen(int fmaxLen)
{
    maxlen = fmaxLen;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string FieldFormatter::getFormattedContent(string data)
{
    string byte_content;

    if (isFixedLen)
    {
        if (data.length() < maxlen)
        {
            data = Utility::resize(data, maxlen, padText, padRight);
        }
    }

    if (dataType == _HEX)
    {
        byte_content = data;
    }
    else if (dataType == _BINARY)
    {
        if ((data.length() % 2) != 0)
        {
            if (!padRight)
            {
                data = padText + data;
            }
            else
            {
                data = data + padText;
            }
        }
        byte_content = Utility::str2bcd(data);
    }
    else
    {
        byte_content = data;
    }

    return byte_content;
}

#endif