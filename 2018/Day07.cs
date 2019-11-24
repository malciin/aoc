using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
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
            var correctOrder = new StringBuilder();
            var visited = new HashSet<Node>(new NodeComparer());
            var toVisit = new SortedSet<Node>(Node.ConstructFrom(input), new NodeComparer());

            while(toVisit.Any())
            {
                var visiting = toVisit.First();
                toVisit.Remove(visiting);
                visited.Add(visiting);

                correctOrder.Append(visiting.Id);

                foreach(var child in visiting.Childs)
                {
                    if (child.Parents.All(p => visited.Contains(p))
                        && !visited.Contains(child)
                        && !toVisit.Contains(child))
                    {
                        toVisit.Add(child);
                    }
                }
            }

            return correctOrder.ToString();
        }

        protected override string Part2()
        {
            var secondsPassed = 0;
            var workers = new int[] { 0, 0, 0, 0, 0 };
            var assignedJobs = workers.Select(_ => '-').ToArray();

            var visited = new HashSet<Node>(new NodeComparer());
            var visiting = new HashSet<Node>(new NodeComparer());
            var toVisit = new SortedSet<Node>(Node.ConstructFrom(input), new NodeComparer());

            do
            {
                // distribute jobs
                for (int i = 0; i < workers.Length; i++)
                {
                    if (workers[i] != 0) continue;
                    if (toVisit.Count == 0) break;

                    var workerJob = toVisit.First();
                    toVisit.Remove(workerJob);
                    visiting.Add(workerJob);

                    workers[i] = 60 + workerJob.Id - 'A' + 1;
                    assignedJobs[i] = workerJob.Id;
                }

                var secondsToPass = workers.Where(w => w != 0).OrderBy(w => w).First();
                secondsPassed += secondsToPass;

                // move finished jobs
                for(int i = 0; i < workers.Length; i++)
                {
                    if (workers[i] == 0 || workers[i] - secondsToPass != 0) continue;
                    var doneJob = visiting.Single(n => n.Id == assignedJobs[i]);
                    assignedJobs[i] = '-';
                    visiting.Remove(doneJob);
                    visited.Add(doneJob);

                    foreach (var child in doneJob.Childs)
                    {
                        if (child.Parents.All(p => visited.Contains(p))
                            && !visited.Contains(child)
                            && !toVisit.Contains(child))
                        {
                            toVisit.Add(child);
                        }
                    }
                }

                for(int i = 0; i < workers.Length; i++)
                {
                    if (workers[i] > 0) workers[i] -= secondsToPass;
                }
            } while (workers.Any(w => w != 0) || toVisit.Any());

            return secondsPassed.ToString();
        }

        private class Node
        {
            public char Id;

            public IList<Node> Parents;

            public IList<Node> Childs;

            public Node(char Id)
            {
                this.Id = Id;
                Childs = new List<Node>();
                Parents = new List<Node>();
            }

            /// <summary>
            /// Construct node graph and returns available starting root nodes. Requires no cycles in paths.
            /// </summary>
            public static IEnumerable<Node> ConstructFrom(IEnumerable<(char From, char To)> paths)
            {
                var nodesById = new Dictionary<char, Node>();

                foreach(var pathId in paths.SelectMany(p => new[] { p.From, p.To }).Distinct())
                {
                    nodesById.Add(pathId, new Node(pathId));
                }

                foreach (var (From, To) in paths)
                {
                    nodesById[From].Childs.Add(nodesById[To]);
                    nodesById[To].Parents.Add(nodesById[From]);
                }

                return nodesById
                    .Select(p => p.Value)
                    .Where(n => n.Parents.Count == 0)
                    .ToArray();
            }
        }

        private class NodeComparer : IComparer<Node>, IEqualityComparer<Node>
        {
            public int Compare(Node x, Node y)
            {
                if (x.Id < y.Id) return -1;
                if (x.Id > y.Id) return 1;
                return 0;
            }

            public bool Equals(Node x, Node y)
                => x.Id == y.Id;

            public int GetHashCode(Node obj)
                => obj.Id.GetHashCode();
        }
    }
}
