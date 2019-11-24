using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;

namespace _2018.Utils
{
    public struct Vector2d : IEquatable<Vector2d>
    {
        public int X;
        public int Y;

        public BigInteger Area => new BigInteger(Math.Abs(X)) * new BigInteger(Math.Abs(Y));

        public Vector2d(int X, int Y)
        {
            this.X = X;
            this.Y = Y;
        }

        public bool Equals(Vector2d other) => X == other.X && Y == other.Y;

        public override bool Equals(object obj)
        {
            if (obj is Vector2d vec)
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

        public static Vector2d operator +(Vector2d first, Vector2d second)
           => new Vector2d { X = first.X + second.X, Y = first.Y + second.Y };

        // Generate dimensions of rectangle that contains all input points
        public static Vector2d GenerateVectorsDimension(IEnumerable<Vector2d> inputs)
        {
            var firstInput = inputs.First();

            int minX = firstInput.X;
            int maxX = firstInput.X;
            int minY = firstInput.Y;
            int maxY = firstInput.Y;

            foreach (var input in inputs.Skip(1))
            {
                if (minX > input.X) minX = input.X;
                if (minY > input.Y) minY = input.Y;
                if (maxX < input.X) maxX = input.X;
                if (maxY < input.Y) maxY = input.Y;
            }

            return new Vector2d { X = Math.Abs(maxX - minX), Y = Math.Abs(maxY - minY) };
        }
    }
}
