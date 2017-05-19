using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

using RigelCore;

namespace RigelEditor.Internal
{
    public class EditorApplication :Singleton<EditorApplication>
    {
        private Assembly mAssemblyRigelEditor;

        private RigelEditorApp mNativeApp;

        public void Run()
        {
            mNativeApp = new RigelEditorApp();
            mNativeApp.delOnGUI += EventOnGUI;
            mAssemblyRigelEditor = Assembly.GetAssembly(typeof(EditorApplication));
            mNativeApp.Run();

        }

        private void EventOnGUI()
        {

        }
    }
}
