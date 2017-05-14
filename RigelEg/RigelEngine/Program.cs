using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Reflection;

using RigelEditor.Internal;

namespace RigelEngine
{
    class Program
    {
        static void Main(string[] args)
        {
            Thread thread = new Thread(new ThreadStart(ThreadEditorApp));
            thread.TrySetApartmentState(ApartmentState.STA);
            thread.Start();
        }

        private static void ThreadEditorApp()
        {
            EditorApplication application = new EditorApplication();
            application.Run();
        }
    }
}
