using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace AoC2018
{
    public class Day07 : Day
    {
        private readonly IEnumerable<(char From, char To)> input;
        public Day07()
        {
            var regex = new Regex(@"Step (.+) must be finished before step (.+) can begin\.");

            input = File
                .ReadAllLines("Day07.txt")
                .Select(l => (regex.Match(l).Groups[1].Value[0], regex.Match(l).Groups[2].Value[0]));
        }

        protected override string Part1()
        {
            var rootNode = Node.ConstructFrom(input);

            return "";
        }

        protected override string Part2()
        {
            throw new System.NotImplementedException();
        }

        private class Node
        {
            public char Id;

            public IList<Node> Childs;

            public Node(char Id)
            {
                this.Id = Id;
                Childs = new List<Node>();
            }

            /// <summary>
            /// Construct node graph and returns main root node. Requires no cycles in paths.
            /// </summary>
            public static Node ConstructFrom(IEnumerable<(char From, char To)> paths)
            {
                var nodesById = new Dictionary<char, Node>();

                foreach(var pathId in paths.SelectMany(p => new[] { p.From, p.To }).Distinct())
                {
                    nodesById.Add(pathId, new Node(pathId));
                }

                foreach (var (From, To) in paths)
                {
                    nodesById[From].Childs.Add(nodesById[To]);
                }

                return nodesById
                    .Select(p => p.Value)
                    .Single(n => !nodesById.Any(p => p.Value.Childs.Contains(n)));
            }
        }
    }
}
