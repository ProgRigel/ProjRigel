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

            LoadMainAssembly();
            EditorModuleManager.Inst.LoadModuleFromAssembly(mAssemblyRigelEditor);

            Rigel.API.Test();
            Rigel.API.TestParam("sdwd");

            _nativeApp.Run();

            

        }


        private void LoadMainAssembly()
        {
            //mAssemblyRigelEditor = Assembly.LoadFile(EditorConfig.EditorDataPath + EditorConfig.AssemblyRigelEditorName);
            mAssemblyRigelEditor = Assembly.GetAssembly(typeof(EditorApplication));
        }


        private void DrawMainMenuBar()
        {
            
            if (RigelAPI.BeginMainMenuBar())
            {
                foreach (var menu in EditorModuleManager.Inst.MenuCata)
                {
                    if(RigelAPI.BeginMenu(menu))
                    {
                        foreach(var item in EditorModuleManager.Inst.MenuCataDict[menu])
                        {
                            if (RigelAPI.MenuItem(item.Item))
                                EditorModuleManager.Inst.MenuItemDict[item].Invoke(null, null);
                        }

                        RigelAPI.EndMenu();
                    }
                }

                RigelAPI.EndMainMenuBar();
            }
        }

        public void OpenProject(string projFolder,string projFile)
        {
        }

        public void NewProject()
        {

        }

        #region delegate

        private bool modelshowed = false;

        private void NativeApp_delOnGUI()
        {
            DrawMainMenuBar();

            //EditorGUIUtil.onGUI();

            EditorModuleManager.Inst.ExecModuleOnGUI();
        }

        #endregion
    }
}
