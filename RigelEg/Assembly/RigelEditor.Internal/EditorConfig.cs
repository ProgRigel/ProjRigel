using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RigelEditor.Internal
{
    public static class EditorConfig
    {
        public static readonly string EditorDataPath = AppDomain.CurrentDomain.BaseDirectory + "Data\\";

        public static readonly string AssemblyRigelEditorName = "RigelEditor.dll";

        public static readonly int MENU_CATA_ORDER_DEF = 100000;
        public static readonly Dictionary<string, int> MENU_CATA_ORDER = new Dictionary<string, int>()
        {
            {"File",0 },
            {"Edit",10 },
            {"Module",20},
            {"Help",30 },
        };
    }
}
