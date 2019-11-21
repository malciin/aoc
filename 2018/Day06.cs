using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AoC2018
{
    public class Day06 : Day
    {
        private readonly IEnumerable<Vector> inputs;

        public Day06()
        {
            inputs = File
                .ReadAllLines("Day06.txt")
                .Select(l =>
                {
                    var splitted = l.Split(", ");
                    return new Vector { X = int.Parse(splitted[0]), Y = int.Parse(splitted[1]) };
                })
                .ToArray();
        }

        protected override string Part1()
        {
            var inputDimension = GenerateInputDimension(inputs);

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
            var inputDimension = GenerateInputDimension(inputs);

            var validDestinations = new List<Vector>();

            // todo: find smarter way
            for(int x = -2_000 - inputDimension.X; x<2_000; x++)
            {
                if (x % 100 == 0)
                {
                    Console.WriteLine($"X: {x}");
                }
                for(int y = -2_000 - inputDimension.Y; y<2_000; y++)
                {
                    var vector = new Vector { X = x + inputDimension.X, Y = y + inputDimension.Y };

                    if (inputs.Select(v => ManhattanDistance(vector, v)).Sum() < 10_000)
                    {
                        validDestinations.Add(vector);
                    }
                }
            }

            return validDestinations.Count.ToString();
        }

        private IEnumerable<Vector> GenerateArea(Vector vector, IEnumerable<Vector> otherVectors)
        {
            var checkedPoints = new HashSet<Vector>();
            var pointsToCheck = new HashSet<Vector>(new[] { vector });

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

                foreach(var candidateToCheck in eightDirectionsVectors.Select(v => new Vector { X = checkedVector.X + v.X, Y = checkedVector.Y + v.Y }))
                {
                    if (!checkedPoints.Contains(candidateToCheck) && !pointsToCheck.Contains(candidateToCheck))
                    {
                        pointsToCheck.Add(candidateToCheck);
                    }
                }
            }
        }

        private bool IsFinite(Vector checkedVector, IEnumerable<Vector> otherVectors, Vector inputDimensions)
        {
            var pointsToCheck = eightDirectionsVectors
                .Select(v => new Vector
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
        Vector? GetClosestVectorTo(Vector position, IEnumerable<Vector> checkedVectors)
        {
            int currentMinEqualVectors = 1;
            Vector currentMinVector = checkedVectors.First();
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

        // Generate dimensions of rectangle that contains all input points
        private Vector GenerateInputDimension(IEnumerable<Vector> inputs)
        {
            var firstInput = inputs.First();

            int minX = firstInput.X;
            int maxX = firstInput.X;
            int minY = firstInput.Y;
            int maxY = firstInput.Y;

            foreach(var input in inputs.Skip(1))
            {
                if (minX > input.X) minX = input.X;
                if (minY > input.Y) minY = input.Y;
                if (maxX < input.X) maxX = input.X;
                if (maxY < input.Y) maxY = input.Y;
            }

            return new Vector { X = Math.Abs(maxX - minX), Y = Math.Abs(maxY - minY) };
        }

        private static int ManhattanDistance(Vector first, Vector second)
            => Math.Abs(first.X - second.X) + Math.Abs(first.Y - second.Y);

        private static readonly IEnumerable<Vector> eightDirectionsVectors = new[]
        {
            new Vector(0, 1),
            new Vector(0, -1),
            new Vector(1, 0),
            new Vector(-1, 0),
            new Vector(1, 1),
            new Vector(1, -1),
            new Vector(-1, 1),
            new Vector(-1, -1)
        };

        private struct Vector : IEquatable<Vector>
        {
            public int X;
            public int Y;

            public Vector(int X, int Y)
            {
                this.X = X;
                this.Y = Y;
            }

            public bool Equals(Vector other) => X == other.X && Y == other.Y;

            public override bool Equals(object obj)
            {
                if (obj is Vector vec)
                    return Equals(vec);

                return false;
            }

            public override int GetHashCode()
            {
                int hash = 17;

                hash = hash * 23 + X.GetHashCode();
                hash = hash * 23 + Y.GetHashCode();

                return hash;
            }
        }
    }
}
