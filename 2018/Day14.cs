using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AoC2018
{
    public class Day14 : Day
    {
        protected override string Part1()
        {
            var part1Input = 503761;

            var recipes = new List<int>(500_000) { 3, 7 };
            var firstElf = 0;
            var secondElf = 1;

            for (int i = 0; i < part1Input + 10; i++)
            {
                var firstElfRecipe = recipes[firstElf];
                var secondElfRecipe = recipes[secondElf];
                var newRecipes = firstElfRecipe + secondElfRecipe;

                if (newRecipes >= 10)
                {
                    recipes.Add(newRecipes / 10);
                    recipes.Add(newRecipes % 10);
                }
                else
                {
                    recipes.Add(newRecipes);
                }

                firstElf = (firstElf + firstElfRecipe + 1) % recipes.Count;
                secondElf = (secondElf + secondElfRecipe + 1) % recipes.Count;
            }

            return string.Join(string.Empty, recipes.Skip(part1Input).Take(10));
        }

        protected override string Part2()
        {
            var part1Input = "503761".Select(x => int.Parse(x.ToString())).ToArray();

            var recipes = new List<int>(500_000) { 3, 7 };
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

                    if (recipes.TakeLast(part1Input.Length).SequenceEqual(part1Input))
                    {
                        return (recipes.Count - part1Input.Length).ToString();
                    }

                    recipes.Add(newRecipes % 10);
                }
                else
                {
                    recipes.Add(newRecipes);
                }

                if (recipes.TakeLast(part1Input.Length).SequenceEqual(part1Input))
                {
                    return (recipes.Count - part1Input.Length).ToString();
                }

                firstElf = (firstElf + firstElfRecipe + 1) % recipes.Count;
                secondElf = (secondElf + secondElfRecipe + 1) % recipes.Count;
            }
        }
    }
}
