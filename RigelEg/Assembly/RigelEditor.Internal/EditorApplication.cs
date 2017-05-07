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

        public void InitWithNative(RigelEditorApp nativeApp)
        {
            #region register callback
            nativeApp.delOnGUI += NativeApp_delOnGUI;
            #endregion

            LoadMainAssembly();
            EditorModuleManager.Inst.LoadModuleFromAssembly(mAssemblyRigelEditor);

            
        }


        private void LoadMainAssembly()
        {
            mAssemblyRigelEditor = Assembly.LoadFile(EditorConfig.EditorDataPath + EditorConfig.AssemblyRigelEditorName);
        }


        private void DrawMainMenuBar()
        {
            var menudata = EditorModuleManager.Inst.MainMenuBar;
            
            if (RigelEditorGUI.BeginMainMenuBar())
            {
                if (menudata == null) return;
                foreach (var menu in menudata)
                {
                    if(RigelEditorGUI.BeginMenu(menu.Key))
                    {
                        foreach(var item in menu.Value)
                        {
                            if (RigelEditorGUI.MenuItem(item.Key.Item))
                                item.Value.Invoke(null, null);
                        }

                        RigelEditorGUI.EndMenu();
                    }
                }

                RigelEditorGUI.EndMainMenuBar();
            }
        }


        #region delegate
        private void NativeApp_delOnGUI()
        {
            DrawMainMenuBar();
        }

        #endregion
    }
}
