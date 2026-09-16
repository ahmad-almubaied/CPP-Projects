using System;

    static void Main(string[] args)
    {
        // 1. System Info
        Console.WriteLine("Windows version: {0}", Environment.OSVersion);
        Console.WriteLine("64 Bit operating system? : {0}", Environment.Is64BitOperatingSystem ? "Yes" : "No");
        Console.WriteLine("PC Name : {0}", Environment.MachineName);
        Console.WriteLine("Number of CPUS : {0}", Environment.ProcessorCount);
        Console.WriteLine("Windows folder : {0}", Environment.SystemDirectory);
        Console.WriteLine("Logical Drives Available : {0}", String.Join(", ", Environment.GetLogicalDrives()).TrimEnd(',', ' ').Replace("\\", String.Empty));
        Console.WriteLine("------------------------------------");
    }
