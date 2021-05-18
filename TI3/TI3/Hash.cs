using System;
using System.Numerics;

namespace TI3
{
    public class Hash
    {
        private long p;
        private long q;
        private long h;

        public Hash(long p, long q, long h = 100)
        {
            this.p = p;
            this.q = q;
            this.h = h;
        }

        public long HashFunction(string message)
        {
            long hash = this.h;
            long n = this.p * this.q;

            foreach (char c in message)
            {
                hash = (long)BigInteger.ModPow(hash + (int)c, 2, n);
            }

            return hash;
        }
    }
}
