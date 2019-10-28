using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;

namespace AoC2018
{
    public class Day01 : Day
    {
        private IEnumerable<int> InputDigits => File.ReadAllLines("Day01.txt")
            .Select(line => int.Parse(line, NumberStyles.AllowLeadingSign));

        protected override string Part1()
            => InputDigits.Sum().ToString();

        protected override string Part2()
        {
            int frequency = 0;
            var seenFrequencies = new HashSet<int>(new[] { frequency });

            while(true)
            {
                foreach (var digit in InputDigits)
                {
                    frequency += digit;

                    if (seenFrequencies.Contains(frequency))
                    {
                        return frequency.ToString();
                    }

                    seenFrequencies.Add(frequency);
                }
            }
        }
    }
}
