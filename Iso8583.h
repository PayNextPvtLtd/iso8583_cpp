#ifndef ISO8583_H
#define ISO8583_H

#include <Poco/NumberParser.h>

#include <map>

#include "Bitmap.h"
#include "Field.h"

using namespace Poco;
using namespace std;

class Iso8583
{
private:
    map<int, Field> fields;
    map<int, string> field_data;
    Bitmap bmap;

public:
    Iso8583();
    ~Iso8583();
    //
    bool isFieldSet(int fieldnum);
    bool setField(int fieldnum, string data);
    string getField(int fieldnum);
    bool removeField(int fieldnum);
    bool clearall();
    string printformattedmsg();
    //
    string getMsg();
    bool parseMsg(string data);
};

/*******************************************************************************
 *
 * 
 ******************************************************************************/
Iso8583::Iso8583()
{
    FieldFormatter ff_0(_BINARY, "0", true, false, 4);
    LengthFormatter lf_0(_FIXED, _NONE, false, 4);

    FieldFormatter ff_1(_BINARY, "F", true, false, 16);
    LengthFormatter lf_1(_FIXED, _NONE, false, 16);

    FieldFormatter ff_2(_BINARY, "F", false, true, 19);
    LengthFormatter lf_2(_LLVAR, _BCD, true, 19);

    FieldFormatter ff_3(_BINARY, "0", true, false, 6);
    LengthFormatter lf_3(_FIXED, _NONE, false, 6);

    FieldFormatter ff_4(_BINARY, "0", true, false, 12);
    LengthFormatter lf_4(_FIXED, _NONE, false, 12);

    FieldFormatter ff_5(_HEX, "0", true, false, 12);
    LengthFormatter lf_5(_FIXED, _NONE, false, 12);

    FieldFormatter ff_6(_HEX, "0", true, false, 12);
    LengthFormatter lf_6(_FIXED, _NONE, false, 12);

    FieldFormatter ff_7(_BINARY, "0", true, false, 10);
    LengthFormatter lf_7(_FIXED, _NONE, false, 10);

    FieldFormatter ff_11(_BINARY, "0", true, false, 6);
    LengthFormatter lf_11(_FIXED, _NONE, false, 6);

    FieldFormatter ff_12(_BINARY, "0", true, false, 6);
    LengthFormatter lf_12(_FIXED, _NONE, false, 6);

    FieldFormatter ff_13(_BINARY, "0", true, false, 4);
    LengthFormatter lf_13(_FIXED, _NONE, false, 4);

    FieldFormatter ff_14(_BINARY, "0", true, false, 4);
    LengthFormatter lf_14(_FIXED, _NONE, false, 4);

    FieldFormatter ff_15(_BINARY, "0", true, false, 4);
    LengthFormatter lf_15(_FIXED, _NONE, false, 4);

    FieldFormatter ff_18(_BINARY, "0", true, false, 4);
    LengthFormatter lf_18(_FIXED, _NONE, false, 4);

    FieldFormatter ff_22(_BINARY, "0", true, true, 3);
    LengthFormatter lf_22(_FIXED, _NONE, false, 3);

    FieldFormatter ff_23(_BINARY, "0", true, false, 3);
    LengthFormatter lf_23(_FIXED, _NONE, false, 3);

    FieldFormatter ff_35(_BINARY, "F", false, true, 80);
    LengthFormatter lf_35(_LLVAR, _BINARY, true, 80);

    FieldFormatter ff_37(_HEX, "0", true, true, 12);
    LengthFormatter lf_37(_FIXED, _NONE, false, 12);

    FieldFormatter ff_38(_HEX, "0", true, true, 6);
    LengthFormatter lf_38(_FIXED, _NONE, false, 6);

    FieldFormatter ff_39(_HEX, "0", true, true, 2);
    LengthFormatter lf_39(_FIXED, _NONE, false, 2);

    FieldFormatter ff_41(_HEX, "0", true, true, 8);
    LengthFormatter lf_41(_FIXED, _NONE, false, 8);

    FieldFormatter ff_42(_HEX, "0", true, true, 15);
    LengthFormatter lf_42(_FIXED, _NONE, false, 15);

    FieldFormatter ff_44(_HEX, "F", false, true, 9999);
    LengthFormatter lf_44(_LLLLVAR, _BINARY, true, 9999);

    FieldFormatter ff_49(_BINARY, "0", true, false, 3);
    LengthFormatter lf_49(_FIXED, _NONE, false, 3);

    FieldFormatter ff_52(_BINARY, "0", true, false, 16);
    LengthFormatter lf_52(_FIXED, _NONE, false, 16);

    FieldFormatter ff_53(_BINARY, "0", true, false, 10);
    LengthFormatter lf_53(_FIXED, _NONE, false, 10);

    FieldFormatter ff_55(_BINARY, "0", false, false, 255);
    LengthFormatter lf_55(_LLLVAR, _BINARY, true, 255);

    FieldFormatter ff_62(_HEX, "0", false, true, 6);
    LengthFormatter lf_62(_LLVAR, _BINARY, true, 6);

    fields.insert(pair<int, Field>(0, Field(ff_0, lf_0)));
    fields.insert(pair<int, Field>(1, Field(ff_1, lf_1)));
    fields.insert(pair<int, Field>(2, Field(ff_2, lf_2)));
    fields.insert(pair<int, Field>(3, Field(ff_3, lf_3)));
    fields.insert(pair<int, Field>(4, Field(ff_4, lf_4)));
    fields.insert(pair<int, Field>(5, Field(ff_5, lf_5)));
    fields.insert(pair<int, Field>(6, Field(ff_6, lf_6)));
    fields.insert(pair<int, Field>(7, Field(ff_7, lf_7)));
    fields.insert(pair<int, Field>(11, Field(ff_11, lf_11)));
    fields.insert(pair<int, Field>(12, Field(ff_12, lf_12)));
    fields.insert(pair<int, Field>(13, Field(ff_13, lf_13)));
    fields.insert(pair<int, Field>(14, Field(ff_14, lf_14)));
    fields.insert(pair<int, Field>(15, Field(ff_15, lf_15)));
    fields.insert(pair<int, Field>(18, Field(ff_18, lf_18)));
    fields.insert(pair<int, Field>(22, Field(ff_22, lf_22)));
    fields.insert(pair<int, Field>(23, Field(ff_23, lf_23)));
    fields.insert(pair<int, Field>(35, Field(ff_35, lf_35)));
    fields.insert(pair<int, Field>(37, Field(ff_37, lf_37)));
    fields.insert(pair<int, Field>(38, Field(ff_38, lf_38)));
    fields.insert(pair<int, Field>(39, Field(ff_39, lf_39)));
    fields.insert(pair<int, Field>(41, Field(ff_41, lf_41)));
    fields.insert(pair<int, Field>(42, Field(ff_42, lf_42)));
    fields.insert(pair<int, Field>(44, Field(ff_44, lf_44)));
    fields.insert(pair<int, Field>(49, Field(ff_49, lf_49)));
    fields.insert(pair<int, Field>(52, Field(ff_52, lf_52)));
    fields.insert(pair<int, Field>(53, Field(ff_53, lf_53)));
    fields.insert(pair<int, Field>(55, Field(ff_55, lf_55)));
    fields.insert(pair<int, Field>(62, Field(ff_62, lf_62)));
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
Iso8583::~Iso8583()
{
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool Iso8583::setField(int fieldnum, string data)
{
    if (fieldnum < 0 || fieldnum > 128)
    {
        return false;
    }

    if (data.empty())
    {
        return false;
    }

    if (data.length() > 0)
    {
        removeField(fieldnum);

        field_data[fieldnum] = data;
    }

    return true;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string Iso8583::getField(int fieldnum)
{
    string value("");

    if (fieldnum < 0 || fieldnum > 128)
    {
        return value;
    }

    if (isFieldSet(fieldnum))
    {
        value = field_data[fieldnum];
    }

    return value;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool Iso8583::isFieldSet(int fieldnum)
{
    if (fieldnum < 0 || fieldnum > 128)
    {
        return false;
    }

    if (field_data.count(fieldnum) > 0)
    {
        return true;
    }

    return false;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool Iso8583::removeField(int fieldnum)
{
    if (fieldnum < 0 || fieldnum > 128)
    {
        return false;
    }

    field_data.erase(fieldnum);

    return true;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool Iso8583::clearall()
{
    field_data.clear();
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string Iso8583::printformattedmsg()
{
    string data;

    data.append(Poco::format("\n> MTI = %s", getField(0)));

    for (int i = 2; i < 129; i++)
    {
        if (isFieldSet(i))
        {
            data.append(Poco::format("\n>> [F%03d] - [%s]", i, getField(i)));
        }
    }

    data.append("\n");

    return data;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string Iso8583::getMsg()
{
    string data("");
    string temp;
    string bmp_val("");
    int i;

    // Calculate bitmap first
    for (i = 0; i < 129; i++)
    {
        if (i != 1)
        {
            if (isFieldSet(i))
            {
                bmap.setBmap(i, true);
            }
        }
    }

    bmp_val = bmap.getBmapstr();

    for (i = 0; i < 129; i++)
    {
        if (i == 1)
        {
            temp = Utility::str2bcd(bmp_val);
            data.append(temp);
        }
        else
        {
            if (isFieldSet(i))
            {
                Field f = fields[i];
                f.setContent(getField(i));
                temp = f.getFormattedContent();
                data.append(temp);
            }
        }
    }

    return data;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool Iso8583::parseMsg(string data)
{
    int field_len;
    string temp;
    string temp_len;
    int l_temp_len;
    int act_len;
    int pos = 0;
    Bitmap bmap;
    int i;

    if (data.empty())
    {
        return false;
    }

    Field f = fields[0];

    // MTI will always be FIXED (4)
    field_len = f.getFieldDataParseMsgLen();
    temp = data.substr(pos, field_len);
    if (f.getFieldDataType() == _HEX)
    {
        // Nothing to do here
    }
    else if (f.getFieldDataType() == _BINARY)
    {
        temp = Utility::bcd2str(temp);
    }
    setField(0, temp);

    // increment position
    pos += field_len;

    // Bitmap (get bitmap 32 - full - assume secondary bitmap is present)
    f = fields[1];
    field_len = 32; // primary + secondary bitmap
    if (f.getFieldDataType() == _HEX)
    {
        // will be same i.e. 32
        temp = data.substr(pos, field_len);
    }
    else if (f.getFieldDataType() == _BINARY)
    {
        field_len = field_len / 2;
        temp = data.substr(pos, field_len);
        temp = Utility::bcd2str(temp);
    }
    else if (f.getFieldDataType() == _EBCDIC)
    {
        // not implemented
    }
    bmap.formbitmap(temp);

    // Check if secondary bitmap is present or absent
    if (!bmap.getBmap(1))
    {
        field_len = field_len / 2;
    }

    // increment position
    pos += field_len;

    for (i = 2; i <= 128; i++)
    {
        if (bmap.getBmap(i))
        {
            f = fields[i];

            if (f.getFieldLengthType() == _FIXED)
            {
                field_len = f.getFieldDataParseMsgLen();
                temp = data.substr(pos, field_len);
                if (f.getFieldDataType() == _HEX)
                {
                    // Nothing to do here
                }
                else if (f.getFieldDataType() == _BINARY)
                {
                    temp = Utility::bcd2str(temp);
                }
                else if (f.getFieldDataType() == _EBCDIC)
                {
                    // Not implemented
                }
                if (f.getDf().getPadRight())
                {
                    temp = temp.substr(0, f.getDf().getMaxLen());
                }
                else
                {
                    temp = temp.substr(temp.length() - f.getDf().getMaxLen(), f.getDf().getMaxLen());
                }
                setField(i, temp);

                pos += field_len;
            }
            else
            {
                field_len = f.getFieldParseLength();
                temp_len = data.substr(pos, field_len);

                if (f.getFieldLengthFormat() == _NONE)
                {
                    l_temp_len = NumberParser::parse(temp_len);
                }
                else if (f.getFieldLengthFormat() == _HEX)
                {
                    l_temp_len = NumberParser::parse(temp_len);
                }
                else if (f.getFieldLengthFormat() == _BINARY)
                {
                    temp_len = Utility::bcd2str(temp_len);
                    l_temp_len = NumberParser::parse(temp_len);
                }
                else if (f.getFieldLengthFormat() == _BCD)
                {
                    temp_len = Utility::bcd2str(temp_len);
                    l_temp_len = NumberParser::parseHex(temp_len);
                }
                else if (f.getFieldLengthFormat() == _EBCDIC)
                {
                    // not implemented
                }

                pos += field_len;
                act_len = l_temp_len;

                if (f.getFieldDataType() == _HEX)
                {
                    temp = data.substr(pos, l_temp_len);
                }
                else if (f.getFieldDataType() == _BINARY)
                {
                    if ((l_temp_len % 2) != 0)
                    {
                        l_temp_len++;
                    }
                    l_temp_len = l_temp_len / 2;
                    temp = data.substr(pos, l_temp_len);
                    temp = Utility::bcd2str(temp);
                }
                else if (f.getFieldDataType() == _EBCDIC)
                {
                    // Not implemented
                }

                if (f.getDf().getPadRight())
                {
                    temp = temp.substr(0, act_len);
                }
                else
                {
                    temp = temp.substr(temp.length() - act_len, act_len);
                }
                setField(i, temp);

                pos += l_temp_len;
            }
        }
    }

    return true;
}

#endif