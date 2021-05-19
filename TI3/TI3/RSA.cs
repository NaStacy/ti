using System;
using System.Collections.Generic;
using System.Numerics;

namespace TI3
{
    public class RSA
    {
        private long r;
        private long euler;
        private long e;
        private long d;

        public RSA() { }

        public RSA(long p, long q)
        {
            CalculateR(p, q);
            CalculateEuler(p, q);

            GenerateE();
            GenerateD();
        }

        #region Key's
        private void CalculateR(long p, long q)
        {
            this.r = p * q;
        }

        private void CalculateEuler(long p, long q)
        {
            this.euler = (p - 1) * (q - 1);
        }

        private void GenerateE()
        {
            Random rnd = new Random();

            long e = 0;
            bool flag = false;

            while (!flag)
            {
                e = 0;
                while (!IsPrime(e))
                {
                    e = rnd.Next(2, (int)(this.euler - 1));
                }

                if (GCD(e, this.euler) == 1)
                {
                    flag = !flag;
                }    
            }

            this.e = e;
        }

        private void GenerateD()
        {
            long d0 = this.euler; long d1 = this.e;
            long y0 = 0; long y1 = 1;

            while (d1 > 1)
            {
                long q = d0 / d1;
                long d2 = d0 % d1;
                long y2 = y0 - q * y1;

                d0 = d1; d1 = d2;
                y0 = y1; y1 = y2;
            }

            this.d = y1 < 0 ? y1 + this.euler : y1;
        }
        #endregion

        #region Get Pair of Key's
        public long[] GetOpen()
        {
            return new long[2] { this.e, this.r };
        }

        public long[] GetClosed()
        {
            return new long[2] { this.d, this.r };
        }
        #endregion

        #region Encrypted/Decrypted
        public long Encrypted(long num)
        {         
            return (long)BigInteger.ModPow(num, this.d, this.r);
        }

        public long Decrypted(long num)
        {
            return (long)BigInteger.ModPow(num, this.e, this.r);
        }
        #endregion

        #region Prime and Co-Prime Test
        private long GCD(long a, long b)
        {
            if (a == 0)
            {
                return b;
            }
            else
            {
                long min = Math.Min(a, b);
                long max = Math.Max(a, b);

                return GCD(max - min, min);
            }
        }

        static long[] SieveEratosthenes(long n)
        {
            var numbers = new List<long>();
            
            for (int i = 2; i < n; i++)
            {
                numbers.Add(i);
            }

            for (int i = 0; i < numbers.Count; i++)
            {
                for (int j = 2; j < n; j++)
                {
                    numbers.Remove(numbers[i] * j);
                }
            }

            return numbers.ToArray();
        }

        private long[] sieve = SieveEratosthenes(1000);
        public bool IsPrime(long num)
        {
            if (num < 2)
                return false;

            if (num == 2)
                return true;

            if (num % 2 == 0)
                return false;

            for (int i = 0; i < this.sieve.Length; i++)
            {
                if (num != this.sieve[i])
                    if (num % this.sieve[i] == 0)
                        return false;
            }

            return true;
        }
        #endregion
    }
}
