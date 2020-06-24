/* 
 * File:   Utility.h
 * Author: Abhishek M
 *
 */

#ifndef UTILITY_H
#define UTILITY_H

#define M_ToCharPtr(p) reinterpret_cast<char *>(p)                      // Cast to char*
#define M_ToWCharPtr(p) reinterpret_cast<wchar_t *>(p)                  // Cast to wchar_t*
#define M_ToConstCharPtr(p) reinterpret_cast<const char *>(p)           // Cast to const char*
#define M_ToConstWCharPtr(p) reinterpret_cast<const wchar_t *>(p)       // Cast to const wchar_t*
#define M_ToUCharPtr(p) reinterpret_cast<unsigned char *>(p)            // Cast to unsigned char*
#define M_ToConstUCharPtr(p) reinterpret_cast<const unsigned char *>(p) // Cast to const unsigned char*
#define M_ToUCharPtr(n) reinterpret_cast<unsigned char *>(n)            // Cast to unsigned char*
#define M_ToVoidPtr(p) reinterpret_cast<void *>(p)                      // Cast to void*
#define M_ToConstVoidPtr(p) reinterpret_cast<const void *>(p)           // Cast to const void*
#define M_ToIntPtr(n) reinterpret_cast<int *>(n)                        // Cast to int*
#define M_ToConstIntPtr(p) reinterpret_cast<const int *>(p)             // Cast to const int*
#define M_ToDoublePtr(n) reinterpret_cast<double *>(n)                  // Cast to double*
#define M_ToConstDoublePtr(n) reinterpret_cast<const double *>(n)       // Cast to const double*
#define M_ToBoolPtr(n) reinterpret_cast<bool *>(n)                      // Cast to bool*
#define M_ToConstBoolPtr(n) reinterpret_cast<const bool *>(n)           // Cast to const bool*

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/Base64Encoder.h>
#include <Poco/Base64Decoder.h>
#include <Poco/HexBinaryDecoder.h>
#include <Poco/HexBinaryEncoder.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/LocalDateTime.h>
#include <Poco/Util/Application.h>
#include <Poco/Crypto/DigestEngine.h>
#include <Poco/NumberFormatter.h>

#include <openssl/sha.h>

#include <sstream>

#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>
#include <map>

using namespace Poco::Util;
using namespace Poco::Net;
using namespace Poco;
using namespace std;

class Utility
{
public:
    static long converttolong(string value, long defvalue = 0);
    //    static long converttolong(string value, char &p, long defvalue = 0);

    static bool is_number(const std::string &s);
    static bool startsWith(string text, string token);
    static bool endsWith(string text, string token);

    static string ofPostRequest(string url, string body, long timeout_secs);
    static string ofPostRequest(string url, string body, long timeout_secs, map<string, string> headers);
    static string protect(string data);
    static string protectall(string data);
    static string resize(string input, int length, string padchar, bool left_justify);
    static string toBase64(string source);
    static string fromBase64(string source);
    static string convertToString(unsigned char *a, int size);
    static int asc2bcd(char asc);
    static string str2bcd(string data);
    static string bcd2str(string data);
    static bool getSHA256(string input, string &output);
    static string getSHA1(string input);
    static string convertHex2BIN(string data);
    static string convertBIN2Hex(string data);
    static long getTimeInMillis();
    static string getF007();
    static string getF012();
    static string getF013();
    static string getCurrentDateTime();
    static string sendreceive(string request, string remoteip, int remoteport, int conntimeout, int requesttimeout);
    static string printHexData(unsigned char *data, int size);
};
///////////////////////////////////////////////////////////
bool Utility::startsWith(string text, string token)
{
    if (text.length() < token.length())
    {
        return false;
    }

    return (text.compare(0, token.length(), token) == 0);
}
///////////////////////////////////////////////////////////
bool Utility::endsWith(string text, string token)
{
    if (text.length() < token.length())
    {
        return false;
    }

    int pos = text.length() - token.length();

    return (text.compare(pos, token.length(), token) == 0);
}
///////////////////////////////////////////////////////////
long Utility::converttolong(string value, long defvalue)
{
    long val = defvalue;

    if (is_number(value))
    {
        val = atol(value.c_str());
    }

    return val;
}

//////////////////////////////////////////////////////////////////////////////
/*
long Utility::converttolong(string value, char &p, long defvalue)
{
    long val = defvalue;

    val = strtol(value.c_str(), &p, 10);

    return val;
}
*/
//////////////////////////////////////////////////////////////////////////////
bool Utility::is_number(const std::string &s)
{
    std::string::const_iterator it = s.begin();

    while (it != s.end() && std::isdigit(*it))
    {
        ++it;
    }

    return !s.empty() && it == s.end();
}
//////////////////////////////////////////////////////////////////////////////

string Utility::ofPostRequest(string url, string body, long timeout_secs)
{
    try
    {
        map<string, string> headers;
        headers["Header"] = "Prime";
        headers["Content-Type"] = "application/json";
        headers["Connection"] = "keep-alive";

        // prepare session
        URI uri(url);
        HTTPClientSession session(uri.getHost(), uri.getPort());

        Timespan ts(timeout_secs, 0L);
        session.setTimeout(ts);

        session.setKeepAlive(true);

        // prepare path
        string path(uri.getPathAndQuery());
        if (path.empty())
        {
            path = "/";
        }

        // send request
        HTTPRequest req(HTTPRequest::HTTP_POST, path, HTTPMessage::HTTP_1_1);
        //req.setContentType("application/x-www-form-urlencoded");

        // Set headers here
        for (map<string, string>::iterator it = headers.begin();
             it != headers.end(); it++)
        {
            req.set(it->first, it->second);
        }

        // Set the request body
        req.setContentLength(body.length());

        // sends request, returns open stream
        std::ostream &os = session.sendRequest(req);
        os << body; // sends the body
        //req.write(std::cout); // print out request

        // get response
        HTTPResponse res;
        //cout << res.getStatus() << " " << res.getReason() << endl;

        if (res.getStatus() == HTTPResponse::HTTPStatus::HTTP_OK)
        {
            istream &is = session.receiveResponse(res);
            stringstream ss;
            StreamCopier::copyStream(is, ss);

            return ss.str();
        }

        return "IO";
    }
    catch (Exception &ex)
    {
        string exc = ex.displayText();

        if (exc.compare("Connection refused") == 0)
        {
            return "IO - " + exc;
        }
        else if (exc.compare("No message received") == 0)
        {
            return "TO - " + exc;
        }
        else if (exc.compare("Timeout") == 0)
        {
            return "TO - " + exc;
        }
        else
        {
            return "IO - " + exc;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////

string Utility::ofPostRequest(string url, string body, long timeout_secs, map<string, string> headers)
{
    try
    {
        // prepare session
        URI uri(url);
        HTTPClientSession session(uri.getHost(), uri.getPort());

        Timespan ts(timeout_secs, 0L);
        session.setTimeout(ts);

        session.setKeepAlive(true);

        // prepare path
        string path(uri.getPathAndQuery());
        if (path.empty())
        {
            path = "/";
        }

        // send request
        HTTPRequest req(HTTPRequest::HTTP_POST, path, HTTPMessage::HTTP_1_1);

        // Set headers here
        for (map<string, string>::iterator it = headers.begin();
             it != headers.end(); it++)
        {
            req.set(it->first, it->second);
        }

        // Set the request body
        req.setContentLength(body.length());

        // sends request, returns open stream
        std::ostream &os = session.sendRequest(req);
        os << body; // sends the body
        //req.write(std::cout); // print out request

        // get response
        HTTPResponse res;
        //cout << res.getStatus() << " " << res.getReason() << endl;

        if (res.getStatus() == HTTPResponse::HTTPStatus::HTTP_OK)
        {
            istream &is = session.receiveResponse(res);
            stringstream ss;
            StreamCopier::copyStream(is, ss);

            return ss.str();
        }

        return "IO";
    }
    catch (Exception &ex)
    {
        string exc = ex.displayText();

        if (exc.compare("Connection refused") == 0)
        {
            return "IO - " + exc;
        }
        else if (exc.compare("No message received") == 0)
        {
            return "TO - " + exc;
        }
        else if (exc.compare("Timeout") == 0)
        {
            return "TO - " + exc;
        }
        else
        {
            return "IO - " + exc;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////

string Utility::protect(string data)
{
    string value;
    int start, end, l, i;

    if (data.empty())
    {
        return "";
    }

    l = data.length();

    if (data.length() > 6)
    {
        start = 6;
    }
    else
    {
        return protectall(data);
    }

    end = l - 4;

    value = data.substr(0, 6);
    for (i = 0; i < l - (10); i++)
    {
        value.append("*");
    }
    value.append(data.substr(l - 4, 4));

    return value;
}
//////////////////////////////////////////////////////////////////////////////

string Utility::protectall(string data)
{
    string value;
    int l, i;

    if (data.empty())
    {
        return "";
    }

    l = data.length();

    value = "";
    for (i = 0; i < l; i++)
    {
        value.append("*");
    }

    return value;
}

//////////////////////////////////////////////////////////////////////////////

string Utility::resize(string input, int length, string padchar, bool left_justify)
{
    if (input.empty())
    {
        input = "";
    }

    if (padchar.empty())
    {
        return input;
    }

    string output = input;

    if (trim(input).length() >= length)
    {
        return input;
    }

    while (output.length() != length)
    {
        if (left_justify)
        {
            output = output.append(padchar);
        }
        else
        {
            output = padchar + output;
        }
    }

    return output;
}

/********************************************************************/

string Utility::toBase64(string source)
{
    istringstream in(source);
    ostringstream out;
    Poco::Base64Encoder b64out(out);

    b64out.rdbuf()->setLineLength(0);

    copy(istreambuf_iterator<char>(in),
         istreambuf_iterator<char>(),
         ostreambuf_iterator<char>(b64out));
    b64out.close(); // always call this at the end!

    return out.str();
}

/********************************************************************/
string Utility::fromBase64(string source)
{
    std::istringstream in(source);
    std::ostringstream out;
    Poco::Base64Decoder b64in(in);

    std::copy(std::istreambuf_iterator<char>(b64in),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(out));

    return out.str();
}

/********************************************************************/
string Utility::convertToString(unsigned char *a, int size)
{
    int i;
    string data("");

    i = 0;

    for (i = 0; i < size; i++)
    {
        data.append(1, a[i]);
    }

    return data;
}

/********************************************************************/
int Utility::asc2bcd(char asc)
{
    if (asc >= '0' && asc <= '9')
        return asc - '0';
    if (asc >= 'A' && asc <= 'F')
        return asc - 'A' + 10;
    if (asc >= 'a' && asc <= 'f')
        return asc - 'a' + 10;

    return 0;
}

/********************************************************************/
string Utility::str2bcd(string data)
{
    int size;
    char *str;
    char *bcd;
    int i;
    string bcd_conv;

    size = data.length();
    str = (char *)malloc(size + 1);
    strcpy(str, data.c_str());

    bcd = (char *)malloc(size);
    for (i = 0; i < size / 2; i++)
    {
        bcd[i] = (asc2bcd(str[2 * i]) << 4) + (asc2bcd(str[2 * i + 1]) & 0x0F);
    }

    bcd_conv = convertToString(M_ToUCharPtr(bcd), size / 2);

    free(bcd);
    free(str);

    return bcd_conv;
}
/********************************************************************/
string Utility::getSHA1(string input)
{
    string output("NA");

    Poco::Crypto::DigestEngine engine("SHA1");
    engine.update(input);

    output = Poco::Crypto::DigestEngine::digestToHex(engine.digest());

    return output;
}
/********************************************************************/
bool Utility::getSHA256(string input, string &output)
{
    SHA256_CTX context;
    char *inp;
    unsigned char *md;
    int length;

    length = input.length();

    inp = (char *)malloc(length + 1);
    strcpy(inp, input.c_str());

    md = (unsigned char *)malloc(65);

    if (!SHA256_Init(&context))
    {
        return false;
    }

    if (!SHA256_Update(&context, M_ToVoidPtr(inp), length))
    {
        return false;
    }

    if (!SHA256_Final(md, &context))
    {
        return false;
    }

    output = convertToString(M_ToUCharPtr(md), strlen(M_ToConstCharPtr(md)));

    free(inp);
    free(md);

    return true;
}

/********************************************************************/
string Utility::convertBIN2Hex(string data)
{
    ostringstream output;
    HexBinaryEncoder encoder(output);

    encoder << data;

    encoder.close();

    return output.str();
}
/********************************************************************/
string Utility::convertHex2BIN(string data)
{
    string output;
    istringstream input_data(data);
    HexBinaryDecoder decoder(input_data);

    try
    {
        decoder >> output;
    }
    catch (DataFormatException &)
    {
        return "";
    }

    if (!decoder.fail())
    {
        return output;
    }

    return "";
}

/********************************************************************/
long Utility::getTimeInMillis()
{
    long timeinmillis;
    timeval t_timeinmillis;

    gettimeofday(&t_timeinmillis, 0);

    timeinmillis = t_timeinmillis.tv_sec * 1000 + t_timeinmillis.tv_usec / 1000;

    return timeinmillis;
}

/********************************************************************/
string Utility::getF007()
{
    string f007;
    LocalDateTime now;
    f007 = Poco::DateTimeFormatter::format(now, "%m%d%H%M%S");

    return f007;
}

/********************************************************************/
string Utility::getF012()
{
    string f012;
    LocalDateTime now;
    f012 = Poco::DateTimeFormatter::format(now, "%H%M%S");

    return f012;
}
/********************************************************************/
string Utility::getF013()
{
    string f013;
    LocalDateTime now;
    f013 = Poco::DateTimeFormatter::format(now, "%m%d");

    return f013;
}
/********************************************************************/

string Utility::bcd2str(string data)
{
    unsigned char ch;
    string value;
    char *temp;
    int i;
    int pos = 0;

    int size = data.length() * 2;

    temp = (char *)malloc(data.length() * 2 + 1);

    for (i = 0; i < data.length(); i++)
    {
        ch = data.at(i);
        pos += sprintf(temp + pos, "%02X", ch);
    }

    value = convertToString(M_ToUCharPtr(temp), size);

    return value;
}
/********************************************************************/

string Utility::getCurrentDateTime()
{
    LocalDateTime now;
    string req = Poco::DateTimeFormatter::format(now, "%Y-%m-%d %H:%M:%s");

    return req;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string Utility::sendreceive(string request, string remoteip, int remoteport, int conntimeout, int requesttimeout)
{
    string resp("IO");
    SocketAddress _sockaddr(remoteip, remoteport);
    StreamSocket _streamsock;

    Poco::Timespan ts(conntimeout, 0);
    Poco::Timespan ts_rxt(requesttimeout, 0);

    string data_to_remote;
    int msg_len;

    int avlbl = 0;

    try
    {
        request = Utility::str2bcd(request);

        msg_len = request.length();
        data_to_remote = Utility::str2bcd(Utility::resize(NumberFormatter::formatHex(msg_len), 4, "0", false)) + request;
        _streamsock.connect(_sockaddr, ts);
        int sentlen = _streamsock.sendBytes(data_to_remote.c_str(), msg_len + 2);

        if (sentlen != msg_len + 2)
        {
            _streamsock.close();

            return resp;
        }

        _streamsock.setReceiveTimeout(ts_rxt);

        char *rsp_data = (char *)malloc(1000);
        avlbl = _streamsock.receiveBytes(rsp_data, 1000);

        if (avlbl > 0)
        {
            resp = Utility::convertToString(M_ToUCharPtr(rsp_data), avlbl);
            resp = resp.substr(2, avlbl - 2);
            resp = Utility::bcd2str(resp);
        }else
        {
            resp = "IO";
        }
        
        _streamsock.close();

        free(rsp_data);
    }
    catch (const std::exception &e)
    {
        resp = "TO";
    }

    return resp;
}

/*******************************************************************************
 *
 * 
 ******************************************************************************/
string Utility::printHexData(unsigned char *data, int size)
{
    char msg[2048] = {0};
    int i;

    for (i = 0; i < size; i++)
    {
        sprintf(msg + strlen(msg), "%02X ", data[i]);
        if (i % 16 == 15)
        {
            sprintf(msg + strlen(msg), "\r\n");
        }
    }

    string s_msg(msg);

    return s_msg;
}

#endif /* UTILITY_H */
