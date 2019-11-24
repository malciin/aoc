using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text.RegularExpressions;
using _2018.Utils;

namespace AoC2018
{
    public class Day10 : Day
    {
        private readonly (Vector2d Position, Vector2d Velocity)[] inputs;

        public Day10()
        {
            var regex = new Regex(@"position=<\s*(-?\d+),\s*(-?\d+)> velocity=<\s*(-?\d+),\s*(-?\d+)>");
            inputs = File
                .ReadAllLines("Day10.txt")
                .Select(l =>
                {
                    var matches = regex.Match(l);
                    var position = new Vector2d
                    {
                        X = int.Parse(matches.Groups[1].Value),
                        Y = int.Parse(matches.Groups[2].Value),
                    };
                    var velocity = new Vector2d
                    {
                        X = int.Parse(matches.Groups[3].Value),
                        Y = int.Parse(matches.Groups[4].Value),
                    };
                    return (position, velocity);
                })
                .ToArray();
        }

        protected override string Part1()
        {
            var positions = new List<Vector2d>(inputs.Select(p => p.Position)).ToArray();
            var currentDimension = Vector2d.GenerateVectorsDimension(positions);
            int secondPassed = 0;

            while(true)
            {
                secondPassed++;
                var candidatePositions = positions.Select((p, index) => p + inputs[index].Velocity);
                var candidateDimension = Vector2d.GenerateVectorsDimension(candidatePositions);
                if (candidateDimension.Area <= currentDimension.Area)
                {
                    currentDimension = candidateDimension;
                    positions = candidatePositions.ToArray();
                }
                else
                {
                    var minX = positions.Min(p => p.X);
                    var minY = positions.Min(p => p.Y);

                    for (int y = 0; y < currentDimension.Y + 1; y++)
                    {
                        for (int x = 0; x < currentDimension.X + 1; x++)
                        {
                            if (positions.Contains(new Vector2d { X = x + minX, Y = y + minY }))
                            {
                                Console.Write("#");
                            }
                            else
                            {
                                Console.Write(" ");
                            }
                        }
                        Console.WriteLine();
                    }
                    Console.WriteLine($"Seconds passed: {secondPassed}");
                    break;
                }
            }

            return "";
        }

        protected override string Part2()
        {
            return "Check above";
        }
    }
}
