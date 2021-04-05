using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace AoC2018
{
    public class Day03 : Day
    {
        private readonly IEnumerable<(int Id, int PosX, int PosY, int Width, int Height)> inputs;

        public Day03()
        {
            var regex = new Regex(@"#(\d+).*@\s(\d+),(\d+):\s(\d+)x(\d+)");

            inputs = File
                .ReadAllLines("Day03.txt")
                .Select(line =>
                {
                    var values = (regex
                        .Match(line)
                        .Groups as IEnumerable<Group>)
                        .Skip(1)
                        .Select(g => int.Parse(g.Value))
                        .ToArray();

                    return (values[0], values[1], values[2], values[3], values[4]);
                });
        }

        protected override string Part1()
            => inputs
                .SelectMany(inputs => Enumerable
                    .Range(inputs.PosX, inputs.Width)
                    .SelectMany(PosX => Enumerable
                        .Range(inputs.PosY, inputs.Height)
                        .Select(PosY => (inputs.Id, PosX, PosY))))
                .GroupBy(pos => (pos.PosX, pos.PosY))
                .Count(g => g.Count() > 1)
                .ToString();

        protected override string Part2()
        {
            var nonOverlappingIds = new HashSet<int>(inputs.Select(i => i.Id).Distinct());

            var overlappingIds = inputs
                .SelectMany(inputs => Enumerable
                    .Range(inputs.PosX, inputs.Width)
                    .SelectMany(PosX => Enumerable
                        .Range(inputs.PosY, inputs.Height)
                        .Select(PosY => (inputs.Id, PosX, PosY))))
                .GroupBy(pos => (pos.PosX, pos.PosY))
                .Where(g => g.Count() > 1)
                .SelectMany(g => g.Select(i => i.Id))
                .Distinct();

            nonOverlappingIds.ExceptWith(overlappingIds);

            return nonOverlappingIds.Single().ToString();
        }
    }
}
