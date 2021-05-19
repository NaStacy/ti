using System;

namespace TI3
{
    class Program
    {
        static void Main(string[] args)
        {
            RSA rsa = new RSA();

            long p = 0;
            while (!rsa.IsPrime(p))
            {
                Console.Write("Введите p: ");
                p = Convert.ToInt32(Console.ReadLine());
            }

            long q = 0;
            Console.WriteLine();
            while (!rsa.IsPrime(q))
            {
                Console.Write("Введите q: ");
                q = Convert.ToInt32(Console.ReadLine());

                if (p == q)
                    q = 0;
            }

            Console.Write("\nВведите сообщение, которое хотите зашифровать: ");
            string message = Console.ReadLine();

            Hash hash = new Hash(p, q);
            long hashMessage = hash.HashFunction(message);
            Console.WriteLine("\nHash message = " + hashMessage);

            rsa = new RSA(p, q);

            long[] keys = rsa.GetOpen();
            Console.WriteLine($"\nОткрытые ключи: e = {keys[0]}, r = {keys[1]}");


            keys = rsa.GetClosed();
            Console.WriteLine($"Закрытые ключи: d = {keys[0]}, r = {keys[1]}");
            
            long s = rsa.Encrypted(hashMessage);
            Console.WriteLine("\nЗашифрованное сообщение: " + s);

            s = rsa.Decrypted(s);
            Console.WriteLine("Расшифрованное сообщение: " + s);
        }
    }
}
