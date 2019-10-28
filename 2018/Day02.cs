using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AoC2018
{
    public class Day02 : Day
    {
        private string[] input;

        public Day02()
        {
            input = File.ReadAllLines("Day02.txt");
        }

        protected override string Part1()
        {
            var lineCharGrouppings = input
                .Select(line => line.GroupBy(ch => ch));

            var exactlyTwoSameLetterWordsCount = lineCharGrouppings
                .Count(groups => groups.Any(g => g.Count() == 2));

            var exactlyThreeSameLetterWordsCount = lineCharGrouppings
                .Count(groups => groups.Any(g => g.Count() == 3));

            return (exactlyTwoSameLetterWordsCount * exactlyThreeSameLetterWordsCount).ToString();
        }

        protected override string Part2()
        {
            return $"Naive: {Part2_Naive()}\t{Part2_Tricky()}";
        }

        protected string Part2_Naive()
        {
            // Naive version O(n^2)
            foreach(var line in input)
            {
                foreach(var otherLine in input.Except(new[] { line }))
                {
                    var differentCharacters = line
                        .Where((ch, i) => ch != otherLine[i])
                        .Count();

                    if (differentCharacters == 1)
                    {
                        return new string(line.Where((ch, i) => ch == otherLine[i]).ToArray());
                    }
                }
            }

            throw new NotImplementedException();
        }

        protected string Part2_Tricky()
        {
            // Tricky version O(n)
            var seenLetters = new HashSet<string>();

            foreach (var line in input)
            {
                var linesToAdd = Enumerable.Range(0, line.Length).Select(i => line.Remove(i, 1)).ToArray();

                foreach (var lineToAdd in linesToAdd)
                {
                    if (seenLetters.Contains(lineToAdd))
                    {
                        return lineToAdd;
                    }
                }

                foreach (var lineToAdd in linesToAdd.Where(l => !seenLetters.Contains(l)))
                {
                    seenLetters.Add(lineToAdd);
                }
            }

            throw new NotImplementedException();
        }
    }
}
