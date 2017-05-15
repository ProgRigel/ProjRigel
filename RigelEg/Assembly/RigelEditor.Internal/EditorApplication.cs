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

        private RigelEditorApp _nativeApp;

        public void Run()
        {
            _nativeApp = new RigelEditorApp();
            _nativeApp.delOnGUI += NativeApp_delOnGUI;

            RigelAPI.EGUI_loadTTF("yahei.ttf");

            mAssemblyRigelEditor = Assembly.GetAssembly(typeof(EditorApplication));
            EditorModuleManager.Inst.LoadModuleFromAssembly(mAssemblyRigelEditor);

            _nativeApp.Run();

        }


        private void DrawMainMenuBar()
        {
            
            if (RigelEGUI.BeginMainMenuBar())
            {
                foreach (var menu in EditorModuleManager.Inst.MenuCata)
                {
                    if(RigelEGUI.BeginMenu(menu))
                    {
                        foreach(var item in EditorModuleManager.Inst.MenuCataDict[menu])
                        {
                            if (RigelEGUI.MenuItem(item.Item))
                                EditorModuleManager.Inst.MenuItemDict[item].Invoke(null, null);
                        }

                        RigelEGUI.EndMenu();
                    }
                }

                RigelEGUI.EndMainMenuBar();
            }
        }


        #region delegate

        private void NativeApp_delOnGUI()
        {
            DrawMainMenuBar();

            RigelAPI.Text("中文");

            EditorModuleManager.Inst.ExecModuleOnGUI();
        }

        #endregion
    }
}
