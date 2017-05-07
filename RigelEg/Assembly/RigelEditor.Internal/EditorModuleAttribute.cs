using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RigelEditor.Internal
{
    class EditorModuleAttribute :Attribute
    {
        public string ModuleName { get; private set; }

        public EditorModuleAttribute(string moduleName)
        {
            ModuleName = moduleName;
        }
    }
}
