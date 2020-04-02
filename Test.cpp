#include "Iso8583.h"
#include <constants.h>

int main(void)
{
    Iso8583 iso;

    iso.setField(0, _0200_TRAN_REQ);
    iso.setField(_002_PAN,"88887700000000571");
    iso.setField(_003_PROCESSING_CODE, "000000");
    iso.setField(_004_AMOUNT_TRANSACTION, "000000001234");
    iso.setField(_007_TRANSMISSION_DATE_TIME, "0401143000");
    iso.setField(_011_SYSTEMS_TRACE_AUDIT_NR, "123456");
    iso.setField(_012_TIME_LOCAL, "143000");
    iso.setField(_013_DATE_LOCAL, "0401");
    iso.setField(_022_POS_ENTRY_MODE, "901");
    iso.setField(_035_TRACK_2_DATA, "88887700000000571D501210678696190012");
    iso.setField(_041_CARD_ACCEPTOR_TERM_ID, "12345678");
    iso.setField(_042_CARD_ACCEPTOR_ID_CODE, "102021000004804");
    iso.setField(_049_CURRENCY_CODE_TRAN, "356");
    iso.setField(_052_PIN_DATA, "69F0F586F893F3C9");
    iso.setField(_062_TRANS_ID, "000001");

    cout << iso.printformattedmsg();

    string msg_to_remote = iso.getMsg();

    unsigned char ch;

    for (unsigned i = 0; i < msg_to_remote.length(); i++)
    {
        if (i % 16 == 0)
        {
            printf("\n");
        }
        ch = msg_to_remote.at(i);
        printf("%02X ", ch);
    }

    printf("\n");

    Iso8583 iso_resp;
    iso_resp.parseMsg(msg_to_remote);

    cout << iso_resp.printformattedmsg() << endl;

    return 0;
}