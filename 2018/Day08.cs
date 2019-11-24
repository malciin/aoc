using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AoC2018
{
    public class Day08 : Day
    {
        private readonly int[] inputs;

        public Day08()
        {
            inputs = File
                .ReadAllText("Day08.txt")
                .Split(" ")
                .Select(str => int.Parse(str))
                .ToArray();
        }

        protected override string Part1()
        {
            (var node, _) = ParseNode(0, inputs);
            return node.SumMetadataRecursive().ToString();
        }

        private (Node Node, int EndedOnIndex) ParseNode(int index, int[] inputs)
        {
            var node = new Node();

            var childrensCount = inputs[index++];
            var metadataCount = inputs[index++];

            for (int i = 0; i < childrensCount; i++)
            {
                (var parsedNode, var endedOnIndex) = ParseNode(index, inputs);
                node.Childs.Add(parsedNode);
                index = endedOnIndex;
            }

            for (int i = 0; i < metadataCount; i++)
            {
                node.Metadata.Add(inputs[index++]);
            }

            return (node, index);
        }

        protected override string Part2()
        {
            (var node, _) = ParseNode(0, inputs);
            return node.ComputeValue().ToString();
        }

        public class Node
        {
            public IList<Node> Childs;
            public IList<int> Metadata;

            public Node()
            {
                Childs = new List<Node>();
                Metadata = new List<int>();
            }

            public int SumMetadataRecursive() => Metadata.Sum() + Childs.Select(child => child.SumMetadataRecursive()).Sum();
            public int ComputeValue()
            {
                int sum = 0;

                if (Childs.Any())
                {
                    // .Select to make indexes to start from 0..n not 1..n+1
                    foreach(var childIndex in Metadata.Select(i => i - 1))
                    {
                        if (0 > childIndex || childIndex >= Childs.Count) continue;

                        sum += Childs[childIndex].ComputeValue();
                    }
                }
                else
                {
                    sum = Metadata.Sum();
                }

                return sum;
            }
        }
    }
}
