#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>

using namespace std;

class Bitmap
{
private:
    string bmap;
    //
    string getHexValue(string value);
    string getBINValue(string value);

public:
    Bitmap();
    ~Bitmap();
    //
    bool getBmap(int pos);
    bool setBmap(int pos, bool value);
    //
    string getBmapstr();
    bool formbitmap(string data);
};

/*******************************************************************************
 *
 * 
 ******************************************************************************/
Bitmap::Bitmap()
{
    for (int i = 0; i < 130; i++)
    {
        bmap.append("0");
    }
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
Bitmap::~Bitmap()
{
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool Bitmap::getBmap(int pos)
{
    if (pos < 1 && pos > 128)
    {
        return false;
    }

    char ch = bmap[pos];
    if (ch == '0')
    {
        return false;
    }
    else if (ch == '1')
    {
        return true;
    }

    return false;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool Bitmap::setBmap(int pos, bool value)
{
    if (pos < 1 && pos > 128)
    {
        return false;
    }

    if (value)
    {
        bmap[pos] = '1';
    }
    else
    {
        bmap[pos] = '0';
    }

    return true;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string Bitmap::getBmapstr()
{
    string value = "";
    string temp;
    int bmap_len = 16;
    int pos = 1;

    if (getBmap(1))
    {
        bmap_len = 32;
    }

    for (int i = 0; i < bmap_len; i++)
    {
        pos = (i * 4) + 1;
        temp = bmap.substr(pos, 4);
        value.append(getHexValue(temp));
    }

    return value;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string Bitmap::getHexValue(string value)
{
    string hval("");

    if (value.empty())
    {
        return hval;
    }

    if (value.compare("0000") == 0)
    {
        hval = "0";
    }
    else if (value.compare("0001") == 0)
    {
        hval = "1";
    }
    else if (value.compare("0010") == 0)
    {
        hval = "2";
    }
    else if (value.compare("0011") == 0)
    {
        hval = "3";
    }
    else if (value.compare("0100") == 0)
    {
        hval = "4";
    }
    else if (value.compare("0101") == 0)
    {
        hval = "5";
    }
    else if (value.compare("0110") == 0)
    {
        hval = "6";
    }
    else if (value.compare("0111") == 0)
    {
        hval = "7";
    }
    else if (value.compare("1000") == 0)
    {
        hval = "8";
    }
    else if (value.compare("1001") == 0)
    {
        hval = "9";
    }
    else if (value.compare("1010") == 0)
    {
        hval = "A";
    }
    else if (value.compare("0000") == 0)
    {
        hval = "0";
    }
    else if (value.compare("1011") == 0)
    {
        hval = "B";
    }
    else if (value.compare("1100") == 0)
    {
        hval = "C";
    }
    else if (value.compare("1101") == 0)
    {
        hval = "D";
    }
    else if (value.compare("1110") == 0)
    {
        hval = "E";
    }
    else if (value.compare("1111") == 0)
    {
        hval = "F";
    }

    return hval;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string Bitmap::getBINValue(string value)
{
    if (value.empty())
    {
        return "";
    }

    string bval;

    if (value.compare("0") == 0)
    {
        bval = "0000";
    }
    else if (value.compare("1") == 0)
    {
        bval = "0001";
    }
    else if (value.compare("2") == 0)
    {
        bval = "0010";
    }
    else if (value.compare("3") == 0)
    {
        bval = "0011";
    }
    else if (value.compare("4") == 0)
    {
        bval = "0100";
    }
    else if (value.compare("5") == 0)
    {
        bval = "0101";
    }
    else if (value.compare("6") == 0)
    {
        bval = "0110";
    }
    else if (value.compare("7") == 0)
    {
        bval = "0111";
    }
    else if (value.compare("8") == 0)
    {
        bval = "1000";
    }
    else if (value.compare("9") == 0)
    {
        bval = "1001";
    }
    else if (value.compare("A") == 0)
    {
        bval = "1010";
    }
    else if (value.compare("B") == 0)
    {
        bval = "1011";
    }
    else if (value.compare("C") == 0)
    {
        bval = "1100";
    }
    else if (value.compare("D") == 0)
    {
        bval = "1101";
    }
    else if (value.compare("E") == 0)
    {
        bval = "1110";
    }
    else if (value.compare("F") == 0)
    {
        bval = "1111";
    }

    return bval;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
bool Bitmap::formbitmap(string data)
{
    if (data.empty())
    {
        return false;
    }

    int i;
    int len;
    int pos;

    string s;
    bmap = "0";

    s = data.substr(0, 1);
    s = getBINValue(s);
    bmap.append(s);

    if (getBmap(1))
    {
        len = 32;
    }
    else
    {
        len = 16;
    }

    for (i = 1; i < len; i++)
    {
        s = data.substr(i, 1);
        s = getBINValue(s);
        bmap.append(s);
    }

    if (len == 16)
    {
        for (i = 0; i < 16; i++)
        {
            bmap.append("0000");
        }
    }

    return true;
}

#endif