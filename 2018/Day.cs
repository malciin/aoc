using System;

namespace AoC2018
{
    public abstract class Day
    {
        protected abstract string Part1();

        protected abstract string Part2();

        public void PrintDayResults()
        {
            var dayName = GetType().Name;

            try
            {
                Console.WriteLine($"{dayName} {nameof(Part1)}: {Part1()}");
            }
            catch (NotImplementedException)
            {
                Console.WriteLine($"{dayName} {nameof(Part1)} not implemented");
            }

            try
            {
                Console.WriteLine($"{dayName} {nameof(Part2)}: {Part2()}");
            }
            catch (NotImplementedException)
            {
                Console.WriteLine($"{dayName} {nameof(Part2)} not implemented");
            }
        }
    }
}
