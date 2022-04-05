#include <openssl/sha.h>
#include <bits/stdc++.h>
#include <string>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

char *hexdigest(unsigned char *md, int len)
{
    static char buf[80];
    int i;
    for (i = 0; i < len; i++)
        sprintf(buf + i * 2, "%02x", md[i]);
    return buf;
}

ZZ hexToZZ(char *hex)
{
   ZZ res = ZZ(0);
   int i;
   for (i = 0; i < strlen(hex); i += 1)
   {
      res <<= 4;
      char x = hex[i];
      if(x>='0' && x <='9')
         res += hex[i]-48;
      else if(x>='a' && x <='f')
         res += hex[i]-87;
      else if(x>='A' && x <='F')
         res += hex[i]-55;
   }
   return res ;
}

string numberToString(ZZ num)
{
    string s = "";
    while (num > 0)
    {
        s += (num % 10) + '0';
        num /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

// SHA1
ZZ Hash(string s)
{
    unsigned char hash[SHA_DIGEST_LENGTH]; // == 20

    SHA_CTX sha1;
    SHA1_Init(&sha1);
    SHA1_Update(&sha1, s.c_str(), s.length());
    SHA1_Final(hash, &sha1);

    ZZ h = hexToZZ(hexdigest(hash, SHA_DIGEST_LENGTH));
    return h ;
}

ZZ Hash(ZZ m)
{
    string s = numberToString(m);
    return Hash(s);
}

ZZ Hash(char *m)
{
    string s = m;
    return Hash(s);
}