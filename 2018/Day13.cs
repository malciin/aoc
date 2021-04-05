using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AoC2018
{
    public class Day13 : Day
    {
        public Day13()
        {
            testTrack1 =
                @"/---\        " + Environment.NewLine +
                @"|   |  /---\" + Environment.NewLine +
                @"| /-+--+\  |" + Environment.NewLine +
                @"| | |  |v  |" + Environment.NewLine +
                @"\-+-/  \+--/" + Environment.NewLine +
                @"  \-----/   ";
            testTrack2 =
                @"/>-<\  " + Environment.NewLine +
                @"|   |  " + Environment.NewLine +
                @"| /<+-\" + Environment.NewLine +
                @"| | | v" + Environment.NewLine +
                @"\>+</ |" + Environment.NewLine +
                @"  |   ^" + Environment.NewLine +
                @"  \<->/";

            dayTrack = File.ReadAllLines("Day13.txt");
        }

        protected override string Part1()
        {
            (var track, var carts) = LoadTrackAndCarts(testTrack1);

            while (true)
            {
                for (int k = 0; k < carts.Count; k++)
                {
                    carts[k].Move(track);

                    var firstCollision = carts.Select(g => (g.I, g.J)).GroupBy(x => x).FirstOrDefault(g => g.Count() == 2)?.Key;
                    if (firstCollision.HasValue)
                    {
                        return $"{firstCollision.Value.J} {firstCollision.Value.I}";
                    }
                }

                carts = carts.OrderBy(c => c.I).ThenBy(c => c.J).ToList();
            }
        }

        protected override string Part2()
        {
            (var track, var carts) = LoadTrackAndCarts(dayTrack);

            var cartsPositions = new HashSet<(int i, int j)>(carts.Select(x => (x.I, x.J)));
            var crashedCarts = new HashSet<Cart>();
            
            while (true)
            {
                for (int k = 0; k < carts.Count; k++)
                {
                    var cart = carts[k];
                    if (crashedCarts.Contains(cart))
                    {
                        continue;
                    }

                    cartsPositions.Remove((cart.I, cart.J));
                    cart.Move(track);

                    if (cartsPositions.Contains((cart.I, cart.J)))
                    {
                        var crashedCartsNow = carts.Where(x => x.I == cart.I && x.J == cart.J).ToList();
                        
                        crashedCarts.Add(crashedCartsNow[0]);
                        crashedCarts.Add(crashedCartsNow[1]);
                        
                        cartsPositions.Remove((cart.I, cart.J));
                    }
                    else
                    {
                        cartsPositions.Add((cart.I, cart.J));
                    }
                }

                foreach (var crashedCart in crashedCarts)
                {
                    carts.Remove(crashedCart);
                }

                if (crashedCarts.Any())
                {
                    crashedCarts.Clear();
                }

                carts = carts.OrderBy(c => c.I).ThenBy(c => c.J).ToList();

                if (carts.Count == 1)
                {
                    return $"{carts[0].J} {carts[0].I}";
                }
            }
        }

        private void PrintMap(char[][] track, List<Cart> carts)
        {
            for (int i = 0; i < track.Length; i++)
            {
                for (int j = 0; j < track[i].Length; j++)
                {
                    var sign = carts.FirstOrDefault(c => c.I == i && c.J == j)?.Sign;
                    if (sign == null)
                    {
                        Console.Write(track[i][j]);
                        continue;
                    }

                    if (sign == Up)
                    {
                        Console.Write('^');
                    }
                    else if (sign == Left)
                    {
                        Console.Write('<');
                    }
                    else if (sign == Right)
                    {
                        Console.Write('>');
                    }
                    else if (sign == Down)
                    {
                        Console.Write('v');
                    }
                }

                Console.WriteLine();
            }
        }

        private (char[][] track, List<Cart> carts) LoadTrackAndCarts(string trackString)
            => LoadTrackAndCarts(trackString.Split(Environment.NewLine));

        private (char[][] track, List<Cart> carts) LoadTrackAndCarts(IEnumerable<string> trackString)
        {
            var track = trackString.Select(l => l.ToCharArray()).ToArray();
            var carts = new List<Cart>();
            for (int i = 0; i < track.Length; i++)
            {
                for (int j = 0; j < track[i].Length; j++)
                {
                    if (new[] { '^', '>', '<', 'v' }.Contains(track[i][j]))
                    {
                        carts.Add(new Cart(i, j, track[i][j]));
                    }

                    if (new[] { '^', 'v' }.Contains(track[i][j]))
                    {
                        track[i][j] = '|';
                    }

                    if (new[] { '>', '<' }.Contains(track[i][j]))
                    {
                        track[i][j] = '-';
                    }
                }
            }

            return (track, carts);
        }

        private class Cart
        {
            public int Sign { get; private set; }

            public int I { get; private set; }

            public int J { get; private set; }

            private int memory;

            public Cart(int i, int j, char cartSign)
            {
                I = i;
                J = j;

                if (cartSign == '^')
                {
                    Sign = Up;
                }
                else if (cartSign == '>')
                {
                    Sign = Right;
                }
                else if (cartSign == 'v')
                {
                    Sign = Down;
                }
                else if (cartSign == '<')
                {
                    Sign = Left;
                }
                else
                {
                    throw new ArgumentException($"Unrecognized cart sign: {cartSign}", nameof(cartSign));
                }
            }

            public void Move(char[][] track)
            {
                (I, J) = GetNextPosition();
                var nextTrack = track[I][J];

                if (nextTrack == '+')
                {
                    if (memory == 0)
                    {
                        RotateLeft();
                    }
                    else if (memory == 2)
                    {
                        RotateRight();
                    }

                    memory = (memory + 1) % 3;
                    return;
                }

                transitions.SingleOrDefault((v1) => v1.cartSign == Sign && v1.track == nextTrack).modifier?.Invoke(this);
            }

            private (int i, int j) GetNextPosition()
            {
                return Sign switch
                {
                    Up => (I - 1, J),
                    Right => (I, J + 1),
                    Left => (I, J - 1),
                    Down => (I + 1, J),
                    _ => throw new NotImplementedException(),
                };
            }

            private void RotateLeft()
            {
                Sign -= 1;

                if (Sign < 0)
                {
                    Sign = Left;
                }
            }

            private void RotateRight()
            {
                Sign += 1;

                if (Sign > Left)
                {
                    Sign = Up;
                }
            }

            private static readonly List<(int cartSign, int track, Action<Cart> modifier)> transitions = new List<(int chartSign, int track, Action<Cart> modifier)>
            {
                (Left, '/', c => c.RotateLeft()),
                (Left, '\\', c => c.RotateRight()),
                (Right, '/', c => c.RotateLeft()),
                (Right, '\\', c => c.RotateRight()),
                (Up, '/', c => c.RotateRight()),
                (Up, '\\', c => c.RotateLeft()),
                (Down, '/', c => c.RotateRight()),
                (Down, '\\', c => c.RotateLeft()),
            };
        }

        private const int Up = 0;
        private const int Right = 1;
        private const int Down = 2;
        private const int Left = 3;

        private readonly string testTrack1;
        private readonly string testTrack2;
        private readonly string[] dayTrack;
    }
}
