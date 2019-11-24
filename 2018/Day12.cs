using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace AoC2018
{
    public class Day12 : Day
    {
        private readonly string InitialState;
        private readonly IDictionary<string, char> TransitionDictionary;

        public Day12()
        {
            var allLines = File.ReadAllLines("Day12.txt");

            InitialState = allLines[0].Split(" ").Last();
            TransitionDictionary = allLines
                .Skip(2)
                .ToDictionary(
                    l => l.Split(" => ").First(),
                    l => l.Split(" => ").Last().Single());
        }

        protected override string Part1() => SumNumberOfAllPotsAfterGenerations(20).ToString();

        protected override string Part2() => SumNumberOfAllPotsAfterGenerations(50_000_000_000UL).ToString();

        private ulong SumNumberOfAllPotsAfterGenerations(ulong generationNumber)
        {
            var currentState = InitialState;
            ulong leftMostPot = 0;

            for (ulong i = 0; i < generationNumber; i++)
            {
                var stringBuilder = new StringBuilder();
                bool addedLeftPot = false;
                for (int j = -2; j < currentState.Length + 2; j++)
                {
                    var fivePotView = Get5PotViewAt(j, currentState);
                    var transitionExists = TransitionDictionary.TryGetValue(fivePotView, out var transition);

                    if (j < 0 || j >= currentState.Length)
                    {
                        if (transitionExists && transition == '#')
                        {
                            if (j < 0 && !addedLeftPot)
                            {
                                addedLeftPot = true;
                                leftMostPot += (ulong)j;
                            }

                            stringBuilder.Append('#');
                        }
                        continue;
                    }

                    if (transitionExists)
                    {
                        stringBuilder.Append(transition);
                    }
                    else
                    {
                        stringBuilder.Append('.');
                    }
                }

                var untrimmedLength = stringBuilder.Length;
                var nextCurrentState = TrimPots(stringBuilder.ToString());

                if (currentState == nextCurrentState)
                {
                    leftMostPot += generationNumber - i;
                    break;
                }

                currentState = nextCurrentState;
                leftMostPot += (ulong)untrimmedLength - (ulong)currentState.Length;
            }

            ulong potSum = 0;

            foreach (var t in currentState
                .Select((ch, i) => (ch, (ulong)i + leftMostPot))
                .Where(p => p.ch == '#')
                .Select(p => p.Item2))
            {
                potSum += t;
            }

            return potSum;
        }

        private string TrimPots(string pots)
        {
            int charsToSkip = 0;

            foreach(var pot in pots)
            {
                if (pot == '#')
                {
                    break;
                }
                else
                {
                    charsToSkip++;
                }
            }

            return new string(pots.Skip(charsToSkip).ToArray());
        }

        private string Get5PotViewAt(int point, string pots)
        {
            var chars = new char[5];

            for (int i = -2; i <= 2; i++)
            {
                if (point + i >= pots.Length || point + i < 0)
                {
                    chars[i + 2] = '.';
                }
                else
                {
                    chars[i + 2] = pots[point + i];
                }
            }

            return new string(chars);
        }
    }
}
