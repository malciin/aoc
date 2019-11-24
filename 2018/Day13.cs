using System.IO;
using System.Linq;

namespace AoC2018
{
    public class Day13 : Day
    {
        private readonly char[][] track;

        public Day13()
        {
            track = File
                .ReadAllLines("Day13.txt")
                .Select(t => t.ToCharArray())
                .ToArray();
        }

        protected override string Part1()
        {
            throw new System.NotImplementedException();
        }

        protected override string Part2()
        {
            throw new System.NotImplementedException();
        }

        public class Chart
        {
            public int PositionX { get; }
            public int PositionY { get; }

            private bool top;
            private bool left;

            public Chart(int startPositionX, int startPositionY)
            {
                PositionX = startPositionX;
                PositionY = startPositionY;
            }
        }
    }
}
