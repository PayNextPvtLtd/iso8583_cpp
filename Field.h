#ifndef FIELD_H
#define FIELD_H

#include <iostream>

#include "LengthFormatter.h"
#include "FieldFormatter.h"

using namespace std;

class Field
{
private:
    FieldFormatter ff;
    LengthFormatter lf;
    string content;

public:
    Field();
    Field(FieldFormatter &ff, LengthFormatter &lf);
    ~Field();
    //
    string getContent();
    bool setContent(string fcontent);
    string getFormattedContent();
    int getFieldLength();
    int getFieldParseLength();
    int getFieldDataParseMsgLen();
    int getFieldDataLength();
    int getFieldLengthType();
    int getFieldLengthFormat();
    int getFieldDataType();
    FieldFormatter getDf();
    LengthFormatter getLf();
};

/*******************************************************************************
 *
 * 
 ******************************************************************************/
Field::Field()
{
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
Field::Field(FieldFormatter &fff, LengthFormatter &flf)
{
    ff = fff;
    lf = flf;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
Field::~Field()
{
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string Field::getContent()
{
    return content;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool Field::setContent(string fcontent)
{
    if (content.length() > lf.getMaxLen())
    {
        return false;
    }
    else
    {
        content = fcontent;
    }

    return true;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string Field::getFormattedContent()
{
    if (getContent().empty())
    {
        return "";
    }

    string byte_content;
    string byte_lencontent;
    string data;

    string data_content = getContent();

    byte_content = ff.getFormattedContent(data_content);

    if (byte_content.empty())
    {
        return "";
    }

    if (lf.getLenType() == _FIXED)
    {
        data.append(byte_content);
    }
    else
    {
        if (lf.getLenFormat() == _BINARY)
        {
            byte_lencontent = lf.getFormattedLength(data_content.length());
        }
        else if (lf.getLenFormat() == _BCD)
        {
            byte_lencontent = lf.getFormattedLength(data_content.length());
        }
        else
        {
            byte_lencontent = lf.getFormattedLength(byte_content.length());
        }

        if (byte_lencontent.empty())
        {
            return "";
        }

        data.append(byte_lencontent);
        data.append(byte_content);
    }

    return data;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int Field::getFieldLength()
{
    string fmaxlen = NumberFormatter::format(lf.getMaxLen());

    return fmaxlen.length();
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int Field::getFieldParseLength()
{
    int l;

    if (lf.getLenType() == _FIXED)
    {
        l = NumberFormatter::format(lf.getMaxLen()).length();
    }
    else
    {
        l = lf.getLenType();
    }

    if ((lf.getLenFormat() == _BINARY) || (lf.getLenFormat() == _BCD))
    {
        if ((l % 2) == 0)
        {
            return (l / 2);
        }
        else
        {
            return ((l + 1) / 2);
        }
    }
    else
    {
        return l;
    }
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int Field::getFieldDataLength()
{
    return lf.getMaxLen();
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int Field::getFieldDataParseMsgLen()
{
    if (ff.getDataType() == _BINARY)
    {
        if ((lf.getMaxLen() % 2) != 0)
        {
            return ((lf.getMaxLen() + 1) / 2);
        }
        else
        {
            return (lf.getMaxLen() / 2);
        }
    }
    else
    {
        return lf.getMaxLen();
    }
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int Field::getFieldLengthType()
{
    return lf.getLenType();
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int Field::getFieldLengthFormat()
{
    return lf.getLenFormat();
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
int Field::getFieldDataType()
{
    return ff.getDataType();
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
FieldFormatter Field::getDf()
{
    return ff;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
LengthFormatter Field::getLf()
{
    return lf;
}

#endif