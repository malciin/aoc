using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace AoC2018
{
    public class Day04 : Day
    {
        private readonly IEnumerable<(int GuardId, DateTime DateTime, LogType Type)> input;
        private readonly IEnumerable<(int GuardId, int Minute)> sleepMinutes;

        public Day04()
        {
            var regex = new Regex(@"\[(\d{4}-\d{2}-\d{2}\s\d{2}\:\d{2})\]\s(\w+)\s(\w+).*");
            int currentGuardId = 0;

            input = GetInput(File.ReadAllLines("Day04.txt")).ToArray();

            DateTime lastSleepTime = DateTime.MinValue;
            sleepMinutes = input
                .Where(i => i.Type != LogType.Shift)
                .SelectMany(i =>
                {
                    if (i.Type == LogType.Sleep)
                    {
                        lastSleepTime = i.DateTime;
                        return Enumerable.Empty<(int GuardId, int minute)>();
                    }
                    else
                    {
                        return Enumerable.Range(lastSleepTime.Minute, i.DateTime.Minute - lastSleepTime.Minute).Select(minute => (i.GuardId, minute));
                    }
                })
                .ToArray();
        }

        protected override string Part1()
        {
            (var mostSleepyGuard, var mostSleepyMinute) = sleepMinutes
                .GroupBy(m => m.GuardId)
                .OrderByDescending(g => g.Count())
                .First()
                .GroupBy(m => m.Minute)
                .OrderByDescending(g => g.Count())
                .Select(g => (g.First().GuardId, g.Key))
                .First();

            return (mostSleepyGuard * mostSleepyMinute).ToString();
        }

        protected override string Part2()
        {
            (var mostRegularSleepyGuard, var mostRegularSleepyMinute) = sleepMinutes
                .GroupBy(m => m)
                .OrderByDescending(m => m.Count())
                .Select(g => (g.Key.GuardId, g.Key.Minute))
                .First();

            return (mostRegularSleepyGuard * mostRegularSleepyMinute).ToString();
        }

        private IEnumerable<(int GuardId, DateTime, LogType)> GetInput(IEnumerable<string> rawLines)
        {
            var regex = new Regex(@"\[(\d+-\d+-\d+\s\d+\:\d+)\]\s(\w+)\s\#?(\w+).*");
            var currentGuardId = 0;
            var orderedLines = rawLines
                .OrderBy(l => DateTime.ParseExact(regex.Match(l).Groups[1].Value, "yyyy-MM-dd HH:mm", CultureInfo.InvariantCulture));

            foreach(var line in orderedLines)
            {
                var groups = regex.Match(line).Groups;
                var date = DateTime.ParseExact(groups[1].Value, "yyyy-MM-dd HH:mm", CultureInfo.InvariantCulture);
                LogType type = default;

                switch(groups[2].Value)
                {
                    case "Guard":
                        currentGuardId = int.Parse(groups[3].Value);
                        type = LogType.Shift;
                        break;
                    case "falls":
                        type = LogType.Sleep;
                        break;
                    case "wakes":
                        type = LogType.WakeUp;
                        break;
                }

                yield return (currentGuardId, date, type);
            }
        }

        private enum LogType
        {
            Shift, WakeUp, Sleep
        }
    }
}
