using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RigelEditor.Internal
{
    public class EditorModule
    {
        protected string ModuleName;
        protected bool enable = false;
        public bool Enable { get { return enable; } }

        public EditorModule() {
            ModuleName = GetType().Name;
        }

        public virtual void onStart()
        {

        }

        public virtual void onDestroy()
        {

        }

        public virtual void onGUI()
        {

        }
    }
}
