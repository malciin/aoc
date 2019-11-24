using System;

namespace AoC2018
{
    public class Day11 : Day
    {
        const int Input = 6548;
        const int GridSizeY = 300;
        const int GridSizeX = 300;
        private readonly int[,] powerGrid;

        public Day11()
        {
            powerGrid = new int[GridSizeY, GridSizeX];

            for (int y = 0; y < GridSizeY; y++)
            {
                for (int x = 0; x < GridSizeX; x++)
                {
                    var rackId = (x + 1) + 10;
                    var powerLevel = (rackId * (y + 1) + Input) * rackId;
                    var hundredDigit = (powerLevel / 100) % 10;

                    powerGrid[y, x] = hundredDigit - 5;
                }
            }
        }

        protected override string Part1()
        {
            int maxX = 0;
            int maxY = 0;
            int currentMaxValue = 0;

            for (int y = 0; y < GridSizeY - 2; y++)
            {
                for (int x = 0; x < GridSizeX - 2; x++)
                {
                    int candidateMaxValue = 0;

                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            candidateMaxValue += powerGrid[y + i, x + j];
                        }
                    }

                    if (candidateMaxValue > currentMaxValue)
                    {
                        maxX = x;
                        maxY = y;
                        currentMaxValue = candidateMaxValue;
                    }
                }
            }

            //FancyPrintGrid();

            return $"{maxX + 1},{maxY + 1}";
        }

        protected override string Part2()
        {
            int maxX = 0;
            int maxY = 0;
            int size = 0;
            int currentMaxValue = 0;

            for (int y = 0; y < GridSizeY; y++)
            {
                for (int x = 0; x < GridSizeX; x++)
                {
                    Console.WriteLine($"X: {x}; Y: {y}; CurrentMax: {currentMaxValue}");
                    for(int candidateSize = 1; candidateSize < Math.Min(GridSizeY - y, GridSizeX - x); candidateSize++)
                    {
                        int candidateMaxValue = 0;


                        for (int i = 0; i < candidateSize; i++)
                        {
                            for (int j = 0; j < candidateSize; j++)
                            {
                                candidateMaxValue += powerGrid[y + i, x + j];
                            }
                        }

                        if (candidateMaxValue > currentMaxValue)
                        {
                            maxX = x;
                            maxY = y;
                            size = candidateSize;
                            currentMaxValue = candidateMaxValue;
                        }
                    }
                }
            }

            return $"{maxX + 1},{maxY + 1},{size}";
        }

        private void FancyPrintGrid()
        {
            Console.Write("          ");
            for (int x = 0; x < GridSizeX; x++)
            {
                Console.Write((x + 1).ToString().PadLeft(4, ' '));
            }
            Console.WriteLine();
            Console.Write("        --");
            for (int x = 0; x < GridSizeX; x++)
            {
                Console.Write("----");
            }
            Console.WriteLine();
            for (int y = 0; y < GridSizeY; y++)
            {
                Console.Write($"Y: {(y + 1).ToString().PadLeft(4, ' ')} | ");
                for (int x = 0; x < GridSizeX; x++)
                {
                    Console.Write(powerGrid[y, x].ToString().PadLeft(4, ' '));
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
    }
}
