using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Reflection;

using RigelCore;
using RigelEditor.Internal;

namespace RigelEngine
{
    class Program
    {
        static void Main(string[] args)
        {
            Thread thread = new Thread(EditorThread);
            thread.Start();

            //wait
            Console.Read();
        }

        private static void EditorThread()
        {
            RigelEditorApp app = new RigelEditorApp();

            EditorApplication.Inst.InitWithNative(app);

            app.Run();
        }
    }
}
