using System;
using System.Linq;

namespace CSGO
{
    internal static class ShareLink
    {
        public static ulong ToMatchID(string sharecode)
        {
            sharecode = sharecode.Replace(@"CSGO", @"").Replace(@"-", @"");
            sharecode = new string(sharecode.ToCharArray().Reverse().ToArray());
            const string dictionary = @"ABCDEFGHJKLMNOPQRSTUVWXYZabcdefhijkmnopqrstuvwxyz23456789";
            byte[] result = new byte[18];
            foreach (var cur_char in sharecode)
            {
                byte[] tmp = new byte[18];
                int addval = dictionary.IndexOf(cur_char.ToString(), StringComparison.Ordinal);
                int carry;
                int v;

                for (int t = 17; t >= 0; t--)
                {
                    carry = 0;
                    for (int s = t; s >= 0; s--)
                    {
                        if (t - s == 0)
                        {
                            v = tmp[s] + result[t] * 57;
                        }
                        else
                        {
                            v = 0;
                        }
                        v = v + carry;
                        carry = v >> 8;
                        tmp[s] = (byte)(v & 0xFF);
                    }
                }

                result = tmp;
                carry = 0;

                for (int t = 17; t >= 0; t--)
                {
                    if (t == 17)
                    {
                        v = result[t] + addval;
                    }
                    else
                    {
                        v = result[t];
                    }
                    v = v + carry;
                    carry = v >> 8;
                    result[t] = (byte)(v & 0xFF);
                }
            }
            var matchid = BitConverter.ToUInt64(result, 0);

            return matchid;
        }
    }
}