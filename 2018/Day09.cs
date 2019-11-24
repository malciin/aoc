using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AoC2018
{
    public class Day09 : Day
    {
        private (int Players, int LastMarbleWorth) input;

        public Day09()
        {
            var rawInput = File
                .ReadAllText("Day09.txt")
                .Split(" ");

            // too tired to write proper parsing
            input = (int.Parse(rawInput[0]), int.Parse(rawInput[6]));
        }

        protected override string Part1()
        {
            var currentMarble = 0;
            var currentPlayer = 0;
            var allPlayersPoints = Enumerable.Range(0, input.Players).Select(_ => 0).ToArray();
            var marbles = new LinkedList<int>(new[] { currentMarble++ });
            var currentPosition = marbles.First;

            while(currentMarble < input.LastMarbleWorth)
            {
                currentPosition = Move(currentPosition, 1, marbles);

                if (currentMarble % 23 == 0)
                {
                    currentPosition = Move(currentPosition, -8, marbles);
                    allPlayersPoints[currentPlayer] += currentMarble;
                    allPlayersPoints[currentPlayer] += currentPosition.Value;
                    var next = currentPosition.Next;
                    marbles.Remove(currentPosition);
                    currentPosition = next;
                }
                else
                {
                    marbles.AddAfter(currentPosition, currentMarble);
                    currentPosition = currentPosition.Next;
                }

                currentPlayer = (currentPlayer + 1) % allPlayersPoints.Length;
                currentMarble++;
            }

            return allPlayersPoints.OrderByDescending(p => p).First().ToString();
        }

        protected override string Part2()
        {
            // copied & pasted all of part1 except change storage player points to unsigned int & multiplying lastMarbleWorth 100 times.
            var currentMarble = 0;
            var currentPlayer = 0;
            var allPlayersPoints = Enumerable.Range(0, input.Players).Select(_ => 0UL).ToArray();
            var marbles = new LinkedList<int>(new[] { currentMarble++ });
            var currentPosition = marbles.First;

            while (currentMarble < input.LastMarbleWorth * 100)
            {
                currentPosition = Move(currentPosition, 1, marbles);

                if (currentMarble % 23 == 0)
                {
                    currentPosition = Move(currentPosition, -8, marbles);
                    allPlayersPoints[currentPlayer] += (ulong)currentMarble;
                    allPlayersPoints[currentPlayer] += (ulong)currentPosition.Value;
                    var next = currentPosition.Next;
                    marbles.Remove(currentPosition);
                    currentPosition = next;
                }
                else
                {
                    marbles.AddAfter(currentPosition, currentMarble);
                    currentPosition = currentPosition.Next;
                }

                currentPlayer = (currentPlayer + 1) % allPlayersPoints.Length;
                currentMarble++;
            }

            return allPlayersPoints.OrderByDescending(p => p).First().ToString();
        }

        /// <summary>
        /// Move node by position with circular wrapping
        /// </summary>
        public LinkedListNode<T> Move<T>(LinkedListNode<T> from, int relativePosition, LinkedList<T> list)
        {
            var currentPosition = from;

            for (int i = 0; i < Math.Abs(relativePosition); i++)
            {
                currentPosition = relativePosition > 0 ? currentPosition.Next : currentPosition.Previous;
                if (currentPosition == null) currentPosition = relativePosition > 0 ? list.First : list.Last;
            }

            return currentPosition;
        }
    }
}
