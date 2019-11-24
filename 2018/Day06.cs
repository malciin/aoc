using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using _2018.Utils;

namespace AoC2018
{
    public class Day06 : Day
    {
        private readonly IEnumerable<Vector2d> inputs;

        public Day06()
        {
            inputs = File
                .ReadAllLines("Day06.txt")
                .Select(l =>
                {
                    var splitted = l.Split(", ");
                    return new Vector2d { X = int.Parse(splitted[0]), Y = int.Parse(splitted[1]) };
                })
                .ToArray();
        }

        protected override string Part1()
        {
            var inputDimension = Vector2d.GenerateVectorsDimension(inputs);

            return inputs
                .Where(v => IsFinite(v, inputs, inputDimension))
                .Select(v => GenerateArea(v, inputs).ToArray())
                .OrderByDescending(v => v.Length)
                .First()
                .Length
                .ToString();
        }

        protected override string Part2()
        {
            var inputDimension = Vector2d.GenerateVectorsDimension(inputs);

            var validDestinations = new List<Vector2d>();

            // todo: find smarter way
            for(int x = -2_000 - inputDimension.X; x<2_000; x++)
            {
                if (x % 100 == 0)
                {
                    Console.WriteLine($"X: {x}");
                }
                for(int y = -2_000 - inputDimension.Y; y<2_000; y++)
                {
                    var vector = new Vector2d { X = x + inputDimension.X, Y = y + inputDimension.Y };

                    if (inputs.Select(v => ManhattanDistance(vector, v)).Sum() < 10_000)
                    {
                        validDestinations.Add(vector);
                    }
                }
            }

            return validDestinations.Count.ToString();
        }

        private IEnumerable<Vector2d> GenerateArea(Vector2d vector, IEnumerable<Vector2d> otherVectors)
        {
            var checkedPoints = new HashSet<Vector2d>();
            var pointsToCheck = new HashSet<Vector2d>(new[] { vector });

            while(pointsToCheck.Count != 0)
            {
                var checkedVector= pointsToCheck.First();
                pointsToCheck.Remove(checkedVector);
                checkedPoints.Add(checkedVector);

                var closestVector = GetClosestVectorTo(checkedVector, otherVectors);

                if (closestVector?.Equals(vector) == true)
                    yield return checkedVector;
                else
                    continue;

                foreach(var candidateToCheck in eightDirectionsVectors.Select(v => new Vector2d { X = checkedVector.X + v.X, Y = checkedVector.Y + v.Y }))
                {
                    if (!checkedPoints.Contains(candidateToCheck) && !pointsToCheck.Contains(candidateToCheck))
                    {
                        pointsToCheck.Add(candidateToCheck);
                    }
                }
            }
        }

        private bool IsFinite(Vector2d checkedVector, IEnumerable<Vector2d> otherVectors, Vector2d inputDimensions)
        {
            var pointsToCheck = eightDirectionsVectors
                .Select(v => new Vector2d
                {
                    X = checkedVector.X + inputDimensions.X * v.X,
                    Y = checkedVector.Y + inputDimensions.Y * v.Y
                })
                .ToArray();

            foreach(var pointToCheck in pointsToCheck)
            {
                var closestVector = GetClosestVectorTo(pointToCheck, otherVectors);

                if (closestVector == null)
                {
                    continue;
                }

                if (closestVector.Equals(checkedVector))
                {
                    return false;
                }
            }

            return true;
        }

        /// <returns>Returns closest vector to given position or null if there are multiple vectors close to that point</returns>
        Vector2d? GetClosestVectorTo(Vector2d position, IEnumerable<Vector2d> checkedVectors)
        {
            int currentMinEqualVectors = 1;
            Vector2d currentMinVector = checkedVectors.First();
            int currentMinDistance = ManhattanDistance(currentMinVector, position);

            foreach (var checkedVector in checkedVectors.Skip(1))
            {
                if (currentMinVector.Equals(checkedVector)) continue;

                int computedDistance = ManhattanDistance(checkedVector, position);

                if (currentMinDistance > computedDistance)
                {
                    currentMinEqualVectors = 1;
                    currentMinVector = checkedVector;
                    currentMinDistance = computedDistance;
                }
                else if (currentMinDistance == computedDistance)
                {
                    currentMinEqualVectors++;
                }
            }

            if (currentMinEqualVectors > 1)
                return null;

            return currentMinVector;
        }

        private static int ManhattanDistance(Vector2d first, Vector2d second)
            => Math.Abs(first.X - second.X) + Math.Abs(first.Y - second.Y);

        private static readonly IEnumerable<Vector2d> eightDirectionsVectors = new[]
        {
            new Vector2d(0, 1),
            new Vector2d(0, -1),
            new Vector2d(1, 0),
            new Vector2d(-1, 0),
            new Vector2d(1, 1),
            new Vector2d(1, -1),
            new Vector2d(-1, 1),
            new Vector2d(-1, -1)
        };
    }
}
