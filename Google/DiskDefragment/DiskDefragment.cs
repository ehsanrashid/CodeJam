using System;
using System.Diagnostics;
using System.IO;
using System.Collections;

static class DiskDefrag
{

    public static int MinMoves(String[] disk, int size)
    {
        int moves = 0;

        int files = disk.Length;

        bool[] diskOccupancy = new bool[ size ];
        int[][] sectors = new int[ files ][];

        for (int i = 0; i < files; ++i)
        {
            String file = disk[ i ];
            Debug.Assert(1 <= file.Length && file.Length <= 50);

            String[] fileSectors = file.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            int fileSize = fileSectors.Length;

            sectors[ i ] = new int[ fileSize ];
            for (int j = 0; j < fileSize; ++j)
            {
                try
                {
                    sectors[ i ][ j ] = int.Parse(fileSectors[ j ]);
                    diskOccupancy[ sectors[ i ][ j ] ] = true;
                }
                catch (Exception)
                {
                    return -1;
                }
            }
        }

        #region Array-based

        Console.WriteLine();

        for (int idx = 0; idx < files; ++idx)
        {
            int[] fileSectors = sectors[ idx ];
            int cursSector;

            #region Sequencial

            //Sort(fileSectors, 0);

            //cursSector = fileSectors[ 0 ] + 1;
            //for( int curs = 1; curs < fileSectors.Length; ++curs )
            //{
            //    int nextSector;
            //    nextSector = fileSectors[ curs ];
            //    //nextSector = FindMax(fileSectors, curs);

            //    if( nextSector != cursSector )
            //    {
            //        if( !diskOccupancy[ cursSector ] )
            //        {
            //            Console.WriteLine("{0}->{1}", nextSector, cursSector);
            //            diskOccupancy[ cursSector ] = true;
            //            diskOccupancy[ nextSector ] = false;

            //            PutSector(fileSectors, curs, nextSector);
            //            Sort(fileSectors, curs + 1);
            //            ++moves;
            //        }
            //        else
            //        {
            //            bool exists = false;
            //            for( int next = curs; next < fileSectors.Length; ++next )
            //            {
            //                if( fileSectors[ next ] == cursSector )
            //                {
            //                    exists = true;
            //                    break;
            //                }
            //            }
            //            if( !exists )
            //            {
            //                Console.WriteLine("{0}->>{1}", nextSector, cursSector);
            //                PutSector(fileSectors, curs, nextSector);
            //                ++moves;
            //            }
            //        }
            //    }

            //    if( cursSector >= size )
            //    {
            //        return -1;
            //    }
            //    ++cursSector;
            //}
            #endregion

            #region Sorted-Sequencial

            cursSector = FindMin(fileSectors, 0) + 1;

            for (int curs = 1; curs < fileSectors.Length; ++curs)
            {
                int min = curs; int minSector = fileSectors[ min ];
                for (int next = curs + 1; next < fileSectors.Length; ++next)
                {
                    if (fileSectors[ next ] < minSector)
                    {
                        min = next;
                        minSector = fileSectors[ min ];
                    }
                }

                if (min != curs)
                {
                    fileSectors[ min ] = fileSectors[ curs ];
                    fileSectors[ curs ] = minSector;
                }

                if (minSector != cursSector)
                {
                    if (!diskOccupancy[ cursSector ])
                    {
                        Console.WriteLine("{0}->{1}", minSector, cursSector);
                        diskOccupancy[ cursSector ] = true;
                        diskOccupancy[ minSector ] = false;
                    }
                    else
                    {
                        Console.WriteLine("{0}->>{1}", minSector, cursSector);
                    }
                    ++moves;
                }
                else
                {
                    if (min != curs)
                    {
                        Console.WriteLine("{0}<->{1}", fileSectors[ min ], fileSectors[ curs ]);
                        moves += 2;
                    }
                    else
                    {
                        //Console.WriteLine("-");
                    }
                }

                if (cursSector >= size)
                {
                    return -1;
                }

                ++cursSector;
            }

            #endregion
        }
        #endregion

        #region Hashtable-based

        //Hashtable hashTable = new Hashtable(); // size

        //for( int i = 0; i < files; ++i )
        //{
        //    int[] fileSectors = sectors[ i ];

        //    int orderSector = fileSectors[ 0 ];

        //    //for( int j = 0 ; j < fileSectors.Length ; ++j )
        //    for( int j = 1; j < fileSectors.Length; ++j )
        //    {
        //        int cursSector = fileSectors[ j ];

        //        //if( j == 0 )
        //        //{
        //        //    orderSector = diskOccupancy[ cursSector ] ? FreeSlotIndex( diskOccupancy ) : cursSector;
        //        //    continue;
        //        //}

        //        int fillSector = hashTable[ cursSector ] == null ? cursSector : int.Parse(hashTable[ cursSector ].ToString());

        //        if( ++orderSector != fillSector )
        //        {
        //            int freeSector;
        //            if( !diskOccupancy[ orderSector ] )
        //            {
        //                freeSector = orderSector;
        //            }
        //            else
        //            {
        //                freeSector = FreeSlotIndex(diskOccupancy);
        //                hashTable.Add(cursSector, freeSector);

        //            }

        //            Console.WriteLine("{0} = ({1}->{2})", cursSector, fillSector, freeSector);

        //            diskOccupancy[ freeSector ] = true;
        //            diskOccupancy[ fillSector ] = false;
        //            ++moves;
        //        }
        //    }
        //}
        #endregion

        return moves;
    }


    public static int FindMin(int[] array, int start)
    {
        int minValue = array[ start ];
        for (int idx = start + 1; idx < array.Length; ++idx)
        {
            if (array[ idx ] == 0)
            {
                continue;
            }
            minValue = Math.Min(array[ idx ], minValue);
        }
        return minValue;
    }

    public static int FindMax(int[] array, int start)
    {
        int maxValue = array[ start ];
        for (int idx = start + 1; idx < array.Length; ++idx)
        {
            if (array[ idx ] == 0)
            {
                continue;
            }
            maxValue = Math.Max(array[ idx ], maxValue);
        }
        return maxValue;
    }

    //Selection
    public static void Sort(int[] array, int beg, int end)
    {
        if (beg < 0) beg = 0;
        while (beg < end)
        {
            int min = beg; int minValue = array[ min ];
            for (int next = beg + 1; next <= end; ++next)
            {
                if (array[ next ] < minValue)
                {
                    min = next;
                    minValue = array[ min ];
                }
            }

            if (min != beg)
            {
                array[ min ] = array[ beg ];
                array[ beg ] = minValue;
            }
            ++beg;
        }
    }

    public static void Sort(int[] array, int beg)
    {
        Sort(array, beg, array.Length - 1);
    }

    private static void PutSector(int[] fileSectors, int curs, int nextSector)
    {
        for (int next = curs; next < fileSectors.Length; ++next)
        {
            if (fileSectors[ next ] == nextSector)
            {
                int tmpSector = fileSectors[ curs ];
                fileSectors[ curs ] = nextSector;
                fileSectors[ next ] = tmpSector;
                break;
            }
        }
    }

    public static int FreeSlotIndex(bool[] occupancy)
    {
        for (int idx = 0; idx < occupancy.Length; ++idx)
        {
            if (!occupancy[ idx ])
            {
                return idx;
            }
        }
        return -1;
    }

    public static void Main()
    {
        using (StreamReader reader = new StreamReader(new FileStream("DiskDefragment.in", FileMode.Open)))
        {
            using (StreamWriter writer = new StreamWriter(new FileStream("DiskDefragment.out", FileMode.Create)))
            {
                int N = int.Parse(reader.ReadLine());

                for (int i = 1; i <= N; ++i)
                {
                    String lineContent;
                    do
                    {
                        lineContent = reader.ReadLine().Trim();
                    }
                    while (lineContent == String.Empty);

                    String[] inputs = lineContent.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    Debug.Assert(inputs.Length == 2);

                    int files = int.Parse(inputs[ 0 ]);
                    Debug.Assert(1 <= files && files <= 12);

                    int size = int.Parse(inputs[ 1 ]);
                    Debug.Assert(10 <= size && size <= 100);

                    String[] disk = new String[ files ];
                    for (int i = 0; i < files; i++)
                    {
                        String fileContent;
                        do
                        {
                            fileContent = reader.ReadLine().Trim();
                        }
                        while (fileContent == String.Empty);

                        disk[ i ] = fileContent;
                    }

                    Console.SetOut(writer);
                    int minMoves = MinMoves(disk, size);
                    writer.WriteLine(i + ": " + minMoves);
                }
            }
        }
        //Console.ReadKey(true);
    }
}