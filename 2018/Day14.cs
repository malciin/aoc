using System;
using System.Collections.Generic;
using System.Linq;

namespace AoC2018
{
    public class Day14 : Day
    {
        protected override string Part1()
        {
            var part1Input = 503761;

            return string.Join(string.Empty, Generate().Skip(part1Input).Take(10));
        }

        protected override string Part2()
        {
            var part1Input = 503761.ToString().Select(x => int.Parse(x.ToString())).ToArray();
            var buffer = new Queue<int>();

            int i = 0;
            foreach (var generated in Generate())
            {
                buffer.Enqueue(generated);
                if (buffer.Count > part1Input.Length) buffer.Dequeue();

                i++;

                if (buffer.SequenceEqual(part1Input))
                {
                    return (i - part1Input.Length).ToString();
                }
            }

            throw new NotImplementedException();
        }

        private IEnumerable<int> Generate()
        {
            var recipes = new List<int>(500_000) { 3, 7 };

            yield return 3;
            yield return 7;

            var firstElf = 0;
            var secondElf = 1;

            while (true)
            {
                var firstElfRecipe = recipes[firstElf];
                var secondElfRecipe = recipes[secondElf];
                var newRecipes = firstElfRecipe + secondElfRecipe;

                if (newRecipes >= 10)
                {
                    recipes.Add(newRecipes / 10);
                    yield return recipes.Last();
                
                    recipes.Add(newRecipes % 10);
                }
                else
                {
                    recipes.Add(newRecipes);
                }
                
                yield return recipes.Last();

                firstElf = (firstElf + firstElfRecipe + 1) % recipes.Count;
                secondElf = (secondElf + secondElfRecipe + 1) % recipes.Count;
            }
        }
    }
}
