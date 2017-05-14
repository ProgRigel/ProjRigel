using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RigelEditor.Internal
{
    public static class Debug
    {
        private static readonly string Prefix = "[Rigel]";
        public static void Log(object info)
        {
            Console.WriteLine(Prefix+info);
        }

    }
}
