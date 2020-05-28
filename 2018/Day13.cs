using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AoC2018
{
    public class Day13 : Day
    {
        private readonly char[][] track;
        private readonly IList<ChartPosition> chartsPosition;

        public Day13()
        {
            chartsPosition = new List<ChartPosition>();
            track = File
                .ReadAllLines("Day13.txt")
                .Select(t => t.ToCharArray())
                .ToArray();

            var chartIndicators = new[] { 'v', '>', '<', '^' };
            for (int y = 0; y < track.Length; y++)
            {
                for(int x = 0; x < track[y].Length; x++) 
                {
                    if (!chartIndicators.Contains(track[y][x])) continue;

                    Direction direction;
                    switch(track[y][x]) {
                        case '^':
                            direction = Direction.Up;
                            track[y][x] = '|';
                            break;
                        case 'v':
                            direction = Direction.Down;
                            track[y][x] = '|';
                            break;
                        case '<':
                            direction = Direction.Left;
                            track[y][x] = '-';
                            break;
                        case '>':
                            direction = Direction.Right;
                            track[y][x] = '-';
                            break;
                        default:
                            throw new NotSupportedException();
                    }

                    chartsPosition.Add(new ChartPosition {
                        X = x, Y = y, Direction = direction, State = 0
                    });
                }
            }
        }

        protected override string Part1()
        {
            var comparer = new ChartPositionComparer();
            var currentPositions = new HashSet<(int X, int Y)>(chartsPosition.Select(p => (p.X, p.Y)));
            var currentChartsPositions = new List<ChartPosition>(chartsPosition);
            while(true)
            {
                foreach (var chart in currentChartsPositions.OrderBy(z => z, comparer).ToArray())
                {
                    currentPositions.Remove((chart.X, chart.Y));
                    Move(chart, track);
                    var newPosition = (chart.X, chart.Y);
                    if (currentPositions.Contains(newPosition))
                    {
                        return $"{newPosition.X}x{newPosition.Y}";
                    }
                    currentPositions.Add(newPosition);
                }
            }
        }

        protected override string Part2()
        {
            var comparer = new ChartPositionComparer();
            var currentPositions = new HashSet<(int X, int Y)>(chartsPosition.Select(p => (p.X, p.Y)));
            var currentChartsPositions = new List<ChartPosition>(chartsPosition);
            while (true)
            {
                foreach (var chart in currentChartsPositions.OrderBy(z => z, comparer).ToArray())
                {
                    currentPositions.Remove((chart.X, chart.Y));
                    Move(chart, track);
                    var newPosition = (chart.X, chart.Y);
                    if (currentPositions.Contains(newPosition))
                    {
                        currentChartsPositions = currentChartsPositions.Where(p => p.X != newPosition.X && p.Y != newPosition.Y).ToList();
                        Console.WriteLine($"Part2: Remaining carts: {currentChartsPositions.Count}");
                    }
                    else
                    {
                        currentPositions.Add(newPosition);
                    }
                }

                if (currentChartsPositions.Count == 1)
                {
                    return $"{currentChartsPositions[0].X},{currentChartsPositions[0].Y}";
                }
            }
        }

        private void PrintTrack(char[][] track, List<ChartPosition> currentChartsPositions)
        {
            Console.WriteLine();

            for (int y = 0; y < track.Length; y++)
            {
                for(int x = 0; x < track[y].Length; x++)
                {
                    if (currentChartsPositions.Where(p => p.X == x && p.Y == y).Any())
                    {
                        var chartPosition = currentChartsPositions.SingleOrDefault(p => p.X == x && p.Y == y);
                        switch (chartPosition.Direction)
                        {
                            case Direction.Down:
                                Console.Write('v');
                                break;
                            case Direction.Up:
                                Console.Write('^');
                                break;
                            case Direction.Right:
                                Console.Write('>');
                                break;
                            case Direction.Left:
                                Console.Write('<');
                                break;
                        }
                    }
                    else
                    {
                        Console.Write(track[y][x]);
                    }
                }

                Console.WriteLine();
            }
        }

        void Move(ChartPosition position, char[][] track) {
            switch(position.Direction) {
                case Direction.Up:
                    position.Y--;
                    break;
                case Direction.Down:
                    position.Y++;
                    break;
                case Direction.Left:
                    position.X--;
                    break;
                case Direction.Right:
                    position.X++;
                    break;
            }

            switch(track[position.Y][position.X]) {
                case '/':
                    if (position.Direction == Direction.Right)
                    {
                        position.Direction = Direction.Up;
                    }
                    else if (position.Direction == Direction.Left)
                    {
                        position.Direction = Direction.Down;
                    }
                    else if (position.Direction == Direction.Down)
                    {
                        position.Direction = Direction.Left;
                    }
                    else if (position.Direction == Direction.Up)
                    {
                        position.Direction = Direction.Right;
                    }
                    break;
                case '\\':
                    if (position.Direction == Direction.Right)
                    {
                        position.Direction = Direction.Down;
                    }
                    else if (position.Direction == Direction.Left)
                    {
                        position.Direction = Direction.Up;
                    }
                    else if (position.Direction == Direction.Down)
                    {
                        position.Direction = Direction.Right;
                    }
                    else if (position.Direction == Direction.Up)
                    {
                        position.Direction = Direction.Left;
                    }
                    break;
                case '+':
                    if (position.State == 0) {
                        position.Direction = (int)position.Direction == 0 ? (Direction)3 : --position.Direction;
                        position.State++;
                    }
                    else if (position.State == 1) {
                        position.State++;
                    }
                    else if (position.State == 2) {
                        position.Direction = (int)position.Direction == 3 ? (Direction)0 : ++position.Direction; 
                        position.State = 0;
                    }
                    else {
                        throw new NotSupportedException();
                    }

                    break;
            }
        }

        public class ChartPosition
        {
            public int X;
            public int Y;
            public Direction Direction;
            public int State;
        }

        public struct ChartPositionComparer : IComparer<ChartPosition>
        {
            public int Compare(ChartPosition first, ChartPosition second)
            {
                if (first.Y < second.Y || (first.Y == second.Y && first.X < second.X)) {
                    return -1;
                }
                else if (first.X == second.X && first.Y == second.Y) {
                    return 0;
                }
                else {
                    return 0;
                }
            }
        }

        // Arranged that incrementing direction will mean 90degree
        // rotation and decrementing will mean -90degree rotation
        public enum Direction {
            Up = 0,
            Right = 1,
            Down = 2,
            Left = 3
        }
    }
}
